#ifndef METRO_H
#define METRO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Metro{
    private:
        string **stations;                              //Estructura de datos principal
        int total_lines, act_line, len;             //Total de lineas junto con la linea actual y su respectivo tamaño
    public:
        //Constructor
        Metro( );

        //Muestra la linea que este referenciada por act_line
        void ShowMe( );

        //Restablece los atributos para el manejo de diferentes lineas
        void Restart( );

        //Agrega una nueva estacion a cualquier linea
        void NewStation( );

        //void Del_Station( );

        //Agrega una nueva linea a la red
        void AddLines( );

        //Menus dentro del programa
        void Admin( );
        void Info( );

        // Destructor
        ~Metro( ) {
            for(int i = 0; i < total_lines; i++) delete[ ] stations[i];     // Liberar la memoria del arreglo de strings
            delete[ ] stations;                                                     // Liberar la memoria del arreglo de punteros
            stations = nullptr;                                             // Establecer el puntero a nullptr (buena práctica)
            cout << "-->Memoria liberada..." << endl;
            sleep(1.5);
        }
};

#endif // METRO_H
