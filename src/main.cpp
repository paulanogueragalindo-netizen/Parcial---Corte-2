#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>

const int    filas         = 25;
const int    columnas      = 25;
const double tarifaMinuto = 150.0;

struct RegistroCarro {
    std::string placa;
    std::string modelo;
    std::time_t entrada;
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
        archivo << "Posicion : Fila " << carro.fila
                        << ", Columna " << carro.columna << "\n";
        archivo << "Entrada  : " << strEntrada << "\n";
        archivo << "Salida   : " << strSalida << "\n";
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

        for (int j = 0; j < (int)linea.size(); j++) {
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

int main() {
    
return 0;
}
 
