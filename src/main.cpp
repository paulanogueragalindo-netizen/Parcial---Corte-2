#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>
#include <random>

const int filas = 25;
const int columnas = 25;
const double tarifaMinuto = 150.0;

struct RegistroCarro {
    std::string placa;
    std::string modelo;
    std::time_t entrada;
    std::string ticket;
    int fila;
    int columna;
};

struct Casilla {
    std::string tipo;    
    bool ocupado;
    RegistroCarro carro;

    double calcularCobro() {
        std::time_t ahora = std::time(0);
        double segundos = std::difftime(ahora, carro.entrada);
        double minutos = std::ceil(segundos / 60.0);
        double total = minutos * tarifaMinuto;
        return total;
    }

    void guardarHistorial(double cobro) {
        std::ofstream archivo("historial.txt", std::ios::app);
        std::time_t ahora = std::time(0);
        double segundos = std::difftime(ahora, carro.entrada);
        double minutos = std::ceil(segundos / 60.0);
        double total = minutos * tarifaMinuto;

        std::string strEntrada = std::ctime(&carro.entrada);
        std::string strSalida  = std::ctime(&ahora);

        strEntrada.erase(strEntrada.size() - 1);
        strSalida.erase(strSalida.size() - 1);

        archivo << "==============================\n";
        archivo << "Placa    : " << carro.placa << "\n";
        archivo << "Modelo   : " << carro.modelo << "\n";
        archivo << "Posicion : Fila " << carro.fila << ", Columna " << carro.columna << "\n";
        archivo << "Entrada  : " << strEntrada << "\n";
        archivo << "Salida   : " << strSalida << "\n";
        archivo << "Ticket   : " << carro.ticket << "\n";
        archivo << "Tiempo   : " << minutos << " minuto(s)" << "\n";
        archivo << "Total    : $" << cobro << "\n";
        archivo << "==============================\n\n";

        archivo.close();
    }
};

std::vector<std::vector<Casilla>> Mapa;

int cupos_disponibles = 0;
void generarArchivo() {
    std::ofstream archivo("parqueadero.txt");

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {

            if (i == 0 || i == filas - 1 || j == 0 || j == columnas - 1) {
                if (i == 0 && j == 2) {
                    archivo << "E";
                } else if (i == filas - 1 && j == 2) {
                    archivo << "S";
                } else {
                    archivo << "W";
                }
            }
            else if (i % 4 == 0) {
                archivo << "V";
            }
            else {
                if (j % 4 == 3) {
                    archivo << "V";
                } else {
                    archivo << "C";
                }
            }
        }
        archivo << "\n";
    }

    archivo.close();
    std::cout << ">> Archivo parqueadero.txt generado.\n";
}

void cargarMapa() {
    Mapa.clear();
    std::ifstream archivo("parqueadero.txt");
    std::string linea;

    while (std::getline(archivo, linea)) {
        std::vector<Casilla> fila;

        for (int j = 0; j < linea.size(); j++) {
            Casilla casilla;
            casilla.ocupado = false;

            char letra = linea[j];
            switch (letra) {
                case 'W': casilla.tipo = "Pared";       
                break;
                case 'E': casilla.tipo = "Entrada";     
                break;
                case 'S': casilla.tipo = "Salida";      
                break;
                case 'V': casilla.tipo = "Via";         
                break;
                case 'C': casilla.tipo = "Parkingspot"; cupos_disponibles++; 
                break;
                default:  casilla.tipo = "Pared";       
                break;
            }
            fila.push_back(casilla);
        }
        Mapa.push_back(fila);
    }
    archivo.close();
}

void mostrarMapa() {
    std::cout << "\n===== MAPA DEL PARQUEADERO =====\n\n";

    for (int i = 0; i < Mapa.size(); i++) {
        for (int j = 0; j < Mapa[i].size(); j++) {
            std::string tipo = Mapa[i][j].tipo;

            if (tipo == "Pared") {
                std::cout << "W";
            } else if (tipo == "Entrada") {
                std::cout << "E";
            } else if (tipo == "Salida") {
                std::cout << "S";
            } else if (tipo == "Via") {
                std::cout << "V";
            } else if (tipo == "Parkingspot") {
                if (Mapa[i][j].ocupado) {
                    std::cout << "X"; 
                } else {
                    std::cout << "C"; 
                }
            }
        }
        std::cout << "\n";
    }

    std::cout << "\nReferencia: W=Pared  E=Entrada  S=Salida  V=Via  C=Libre  X=Ocupado\n";
}

std::string ticket(){
    int longitud = 10;
    std::string caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, caracteres.size()-1);

    bool unico = true;
    std::string ticket;
    do{
        ticket.clear();
        unico = true;
        for(int i = 0; i < longitud; i++){
            ticket += caracteres[distribution(generator)];
        }

        for (int i= 0; i < Mapa.size(); i++){
            for (int j= 0 ; j < Mapa[i].size(); j ++){
                if(Mapa[i][j].carro.ticket == ticket){
                    unico = false;
                }
            }
        }
    } while(!unico);
    
    return ticket;
}

void registrarIngreso() {
    if (cupos_disponibles == 0) {
        std::cout << ">> No hay espacios disponibles.\n";
        return;
    }

    std::string placa, modelo;

    std::cout << "\n>> ESCANEANDO VEHICULO...\n";
    std::cout << ">> Ingrese la placa detectada : ";
    std::cin  >> placa;
    std::cout << ">> Ingrese el modelo del carro: ";
    std::cin  >> modelo;

    for (int i = 0; i < Mapa.size(); i++) {
        for (int j = 0; j < Mapa[i].size(); j++) {
            if (Mapa[i][j].ocupado && Mapa[i][j].carro.placa == placa) {
                std::cout << ">> ERROR: Ese carro ya esta en el parqueadero.\n";
                return;
            }
        }
    }

    for (int i = 0; i < Mapa.size(); i++) {
        for (int j = 0; j < Mapa[i].size(); j++) {
            if (Mapa[i][j].tipo == "Parkingspot" && !Mapa[i][j].ocupado) {

                std::time_t ahora  = std::time(0);
                std::string strEntrada = std::ctime(&ahora);
                if (!strEntrada.empty() && strEntrada[strEntrada.size() - 1] == '\n')
                    strEntrada.erase(strEntrada.size() - 1);

                Mapa[i][j].ocupado       = true;
                Mapa[i][j].carro.placa   = placa;
                Mapa[i][j].carro.modelo  = modelo;
                Mapa[i][j].carro.entrada = ahora;
                Mapa[i][j].carro.fila    = i;
                Mapa[i][j].carro.columna = j;
                Mapa[i][j].carro.ticket = ticket();

                std::cout << "\n\033[34m VEHICULO REGISTRADO\n";
                std::cout << "-------------------------\n\033[0m";
                std::cout << ">> Placa    : " << placa << "\n";
                std::cout << ">> Modelo   : " << modelo << "\n";
                std::cout << ">> Posicion : Fila " << i << ", Columna " << j << "\n";
                std::cout << ">> Entrada  : " << strEntrada << "\n";
                std::cout << ">> Ticket   : " << Mapa[i][j].carro.ticket << "\n";
                std::cout << "\033[34m-------------------------\n\033[0m";
                std::cout << ">> Espacios disponibles: "<< cupos_disponibles << "\n";
                cupos_disponibles++;
                return;
            }
        }
    }
}

void registrarSalida() {
    std::string placa;
    std::cout << "\n>> Ingrese la placa del carro a retirar: ";
    std::cin  >> placa;

    for (int i = 0; i < Mapa.size(); i++) {
        for (int j = 0; j < Mapa[i].size(); j++) {
            if (Mapa[i][j].ocupado && Mapa[i][j].carro.placa == placa) {
                std::string ticket_usuario;
                std::cout << "Ingresar el codigo del ticket asignado:";
                std::cin >> ticket_usuario;
                if (Mapa[i][j].carro.ticket != ticket_usuario){
                    std::cout << "NO COINCIDE\n";
                    return;
                }

                std::time_t ahora  = std::time(0);
                double segundos    = std::difftime(ahora, Mapa[i][j].carro.entrada);
                double minutos     = std::ceil(segundos / 60.0);
                if (minutos < 1.0) minutos = 1.0;
                double cobro       = minutos * tarifaMinuto;

                std::string strEntrada = std::ctime(&Mapa[i][j].carro.entrada);
                std::string strSalida  = std::ctime(&ahora);
                strEntrada.erase(strEntrada.size() - 1);
                strSalida.erase(strSalida.size() - 1);

                std::cout << "\n\033[34m VEHICULO ENCONTRADO\n";
                std::cout << "-------------------------\n\033[0m";
                std::cout << ">> Placa    : " << Mapa[i][j].carro.placa  << "\n";
                std::cout << ">> Modelo   : " << Mapa[i][j].carro.modelo << "\n";
                std::cout << ">> Posicion : Fila " << i << ", Columna " << j << "\n";
                std::cout << ">> Entrada  : " << strEntrada << "\n";
                std::cout << ">> Salida   : " << strSalida << "\n";
                std::cout << ">> ticket   : " << Mapa[i][j].carro.ticket << "\n";
                std::cout << ">> Tiempo   : " << minutos << " minuto(s)\n";
                std::cout << ">> Total    : $" << cobro << "\n";
                std::cout << "\033[34m-------------------------\n\033[0m";

                Mapa[i][j].guardarHistorial(cobro);
                Mapa[i][j].ocupado       = false;
                Mapa[i][j].carro.placa   = "";
                Mapa[i][j].carro.modelo  = "";
                Mapa[i][j].carro.entrada = 0;
                Mapa[i][j].carro.fila    = 0;
                Mapa[i][j].carro.columna = 0;
                Mapa[i][j].carro.ticket = "";

                std::cout << ">> Espacio liberado. ¡Hasta pronto!\n";
                cupos_disponibles--;
                return;
            }
        }
    }

    std::cout << ">> ERROR: Placa no encontrada en el parqueadero.\n";
}

void ubicarCarro(){
    std::string placa;
    std::cout << "\n>> Ingrese la placa del carro a retirar: ";
    std::cin  >> placa;
    for (int i = 0; i < Mapa.size(); i++){
        for (int j = 0; j < Mapa[i].size(); j++){
            if (Mapa[i][j].carro.placa == placa){
                std::cout << "Su carro esta en la ubicacion: Fila " << i << ", Columna " << j << std::endl;
                return;
            }
        }
    }
    std:: cout << "No se encuentra el carro\n";
}

void mostrarMenu() {
    std::cout << "\n\033[32m===========================\n";
    std::cout << "   MENU PARQUEADERO\n";
    std::cout << "===========================\n\033[0m";
    std::cout << "1. Ver mapa del parqueadero\n";
    std::cout << "2. Registrar ingreso de carro\n";
    std::cout << "3. Registrar salida de carro\n";
    std::cout << "4. Ver espacios disponibles\n";
    std::cout << "5. Ubicar un carro\n";
    std::cout << "6. Salir del sistema";
    std::cout << "\n\033[32m===========================\n\033[0m";
    std::cout << "Seleccione una opcion: ";
}

int main (){
    std::cout << ">> Iniciando sistema de parqueadero..\n";
    generarArchivo();
    cargarMapa();
    std::cout << ">> Sistema listo. Espacios disponibles: "<< cupos_disponibles << "\n";

    int opcion = 0;

while (opcion != 5) {
        mostrarMenu();
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                mostrarMapa();
                break;
            case 2:
                registrarIngreso();
                break;
            case 3:
                registrarSalida();
                break;
            case 4:
                std::cout << ">> Espacios disponibles: "<< cupos_disponibles << "\n";
                break;
            case 5:
                ubicarCarro();
                break;
            case 6:
                std::cout << ">> Cerrando sistema. ¡Hasta luego!\n";
                break;
            default:
                std::cout << ">> Opcion invalida. Intente de nuevo.\n";
                break;
        }
    }
    return 0;
}