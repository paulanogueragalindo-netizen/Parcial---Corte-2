#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cmath>
#include <fstream>

struct RegistroCarro {
    std::string placas;
    std::string modelo;
    std::time_t entrada;
};

struct Casillas {
    std::string tipo;
    RegistroCarro carro;
    void registrar(RegistroCarro &carro_nuevo){

    }

    void eliminar_registro(){

    }
};

int main(){
    std::vector<std::vector<Casillas>> Mapa;
    std::ifstream parqueadero("../data/parqueadero.txt");
    std::string linea;
    while (getline (parqueadero, linea)){
        std::vector<Casillas> fila;
        for(int i = 0; i < linea.size(); i++){
            Casillas casilla;

            char letra = linea[i];
            switch (letra){
                case 'P':
                    casilla.tipo = "Pared";
                    break;
                case 'E':
                    casilla.tipo = "Entrada";
                    break;
                case 'S':
                    casilla.tipo = "Salida";
                    break;
                case 'V':
                    casilla.tipo = "Via";
                    break;
                case 'C':
                    casilla.tipo = "Parkingspot";
                    break;
                default:
                    break;
            }
            fila.push_back(casilla);
        }
        Mapa.push_back(fila);
    } 

    
}