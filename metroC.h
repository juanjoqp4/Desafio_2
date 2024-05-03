#ifndef METRO_H
#define METRO_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>

using namespace std;

class Metro{
    private:
        int total_lines, len,**hour, act_line;  //Estructura de datos enfocada al tiempo junto con la linea actual de la red sobre la que se trabaja, su tamaño y el total de lineas
        string **stations;                              //Estructura de datos principal

    public:
        //Constructor
        Metro( );

        class Simulation {
            Metro* metroSystem;
            public:
                Simulation(Metro* metro) : metroSystem(metro) { }
                int Travel( );
                // Aqui se puede acceder a los miembros de Metro a traves de metroSystem
                // Por ejemplo:
                // int time = metroSystem->hour[metroSystem->act_line][0];
        };

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
        void RemLines( );

        //Agrega una nueva linea a la red
        void AddLines( );

        //Configura Hour ante una nueva linea
        void ConfHour( );

        //Menus dentro del programa
        void Admin( );
        void Info( );

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
