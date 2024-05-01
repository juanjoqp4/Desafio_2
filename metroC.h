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
        int **hour,total_lines, act_line, len;             //Estructura de datos enfocada al tiempo junto con total de lineas junto con la linea actual y su respectivo tamaño
    public:
        //Constructor
        Metro( );

        //Muestra la linea que este referenciada por act_line
        void ShowMe( );

        //Restablece los atributos para el manejo de diferentes lineas a gusto del usuario o a necesidad del programador
        void Restart( );
        void Restart(int);

        //Agrega una nueva estacion a cualquier linea
        void NewStation( );

        //Elimina una estacion de cualquier linea
        void RemStation( );

        //Elimina la ultima linea de la red metro
        void RemLine( );

        //Agrega una nueva linea a la red
        void AddLines( );

        //Configura Hour ante una nueva linea
        void ConfHour( );

        //Menus dentro del programa
        void Admin( );
        void Info( );

        //Desarrolla la simulacion de recorridos
        int Simulation( );

        //Se encarga de la introduccion de nuevos tiempos de llegada
        void Time(int,int);

        //Se encarga de marcar las estaciones de transferencia
        string Transf( );

        //Se encarga de las validaciones
        friend int Validation(int,int, int);

        // Destructor
        ~Metro( ) {
            for(int i = 0; i < total_lines; i++) delete[ ] stations[i];     // Liberar la memoria del arreglo de strings
            delete[ ] stations;                                                     // Liberar la memoria del arreglo de punteros
            stations = nullptr;                                             // Establecer el puntero a nullptr (buena práctica)

            if(total_lines == 1) total_lines -= 1;
            for(int i = 0; i < total_lines; i++) delete[ ] hour[i];     // Liberar la memoria del arreglo de strings
            delete[ ] hour;                                                     // Liberar la memoria del arreglo de punteros
            hour = nullptr;                                             // Establecer el puntero a nullptr (buena práctica)
            cout << "-->Memoria liberada..." << endl;
            sleep(1.5);
        }
};

#endif // METRO_H
