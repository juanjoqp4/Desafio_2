#include "metroC.h"

Metro :: Metro( ){
    stations = new string *[1];                     //Se inicializa una linea de metro por defecto
    len = 6;
    total_lines = 1;
    act_line = 0;
    stations[0] = new string[len] {"Envigado", "La Estrella", "Sabaneta", "San Antonio", "Bello", ""};
}

void Metro :: Restart( ){                                                                   //Se restablecen los atributos para la respectiva linea
    cout << "Especifique la linea sobre la que va a trabajar: ";
    cin >> act_line;

    act_line -= 1;
    len = 0;

    while (! stations[act_line][len].empty( )) {                //Toma el tamaño de la linea referenciada
        len++;
    }
}

void Metro :: ShowMe( ){                //Dependiendo la linea actual y su tamaño, imprime su contenido
    if(len != 0){
        cout << "Estas son nuestras estaciones de la linea " << act_line + 1 << " actualmente: " << endl << endl;
        for (int i = 0; i < len; ++i){
            if(! stations[act_line][i].empty( )) cout << i + 1 << ". " << stations[act_line][i] << endl;
        }
        cout << endl;
    }else cout << endl << "No hay estaciones en esta linea, agrega alguna :)" << endl << endl;
}

void Metro::AddLines( ) {
    string **Space = new string *[total_lines + 1];     // Crea un nuevo arreglo para la nueva línea en base al total de lineas que hubiera en ese momento
    len = 0;

    for(int i = 0; i < total_lines; i++){                                       //Se toma la copia de los arreglos anteriores
        for(int j = 0; ! stations[ i ][ j ].empty( );j++) len++;           //Toma el tamaño del arreglo en i
        len++;
        //cout << "//Len: " << len << endl;

        Space[i] = new string [len];                    //Le da los espacios necesarios para la copia
        for(int k = 0; k < len; k++) {
            Space[i][k] = stations[i][k];           //Copia los elementos del arreglo anterior
            //cout << "Copia-->" << Space[i][k] << endl;
        }
        len = 0;
    }

    for(int d = 0; d < total_lines; d++){           //Despues de copiar libera el arreglo anterior
        delete[ ] stations[d];
    }
    delete[ ] stations;
    stations = nullptr;

    total_lines += 1;              // Incrementar el número total de líneas
    Space[total_lines - 1] = new string[1];     //Le da un espacio a la nueva linea

    Space[total_lines - 1][0] = "";         //La funcion de una cadena vacia, es poder tomar con empty los distintos tamaños de cada linea

    stations = Space;        // Actualiza el puntero con el nuevo arreglo
    //ShowMe( );

    cout << "Se ha agregado una nueva linea de metro." << endl << endl;
}

void Metro::NewStation( ){                  //Agrega una nueva estacion a la linea referenciada
    string a;
    int b;
    ShowMe( );

    cout << "Digite el nombre de la nueva estacion: ";
    cin.ignore( );
    getline(cin, a);
    cout << "Digite la posicion donde desea ubicar la nueva estacion: ";                //Validar para el numero de espacios disponibles
    cin >> b;
    cin.ignore( );

    // Crear un nuevo arreglo para la línea actual con un espacio más
    string newSt [len + 2] = {};
    newSt[b - 1] = a;
    int sup = 0;

    // Copiar elementos del arreglo antiguo al nuevo
    for (int i = 0; i <= len; i++) {
        if(sup == b - 1) sup++;
        newSt[sup] = stations[act_line][i];
        sup++;
    }

    len += 2;           //Aumenta 2, uno para la nueva estacion y otro para la cadena vacia

    stations[act_line] = new string [len];
    stations[act_line][len-1] = "";

    for(int k = 0; k < len; k++){
        stations[act_line][k] = newSt[k];                           //El arreglo principal toma los datos del arreglo nuevo
        //cout << "-->" << stations[act_line][k] << endl;
    }

    //ShowMe( );
}

void Metro :: Admin( ){             //Menu para administrar la red metro
    system("cls");
    char opt = '0';
    while(opt != '5'){
        cout << "|-->Menu Administrador\n1. Agregar linea a la red\n2. Agregar estacion a una linea\n3. Eliminar una linea\n4. Eliminar una estacion\n5. Salir\n|Digite aqui-->";
        cin >> opt;
        cin.ignore( );
        system("cls");
        if((opt > 49) && (opt < 53)) Restart( );            //Solo se referenciaran lineas de la opcion 2 a 4

        switch(opt){
        case '1':
        {
            AddLines( );
        break;
        }

        case '2':
        {
            NewStation( );
        break;
        }

        case '3':
        {

        break;
        }

        case '4':
        {

        break;
        }

        case '5':
        {
            //Sale del ciclo
        break;
        }

        default: cout << "Opcion invalida, vuelva a intetarlo" << endl;
        }               //Switch
    }
}

void Metro :: Info( ){      //Menu para mostrar al usuario la informacion general o especifica de la red metro
    system("cls");
    char opt = '0';
    while(opt != '3'){
        cout << "|-->Menu de Informacion\n1. Informacion General\n2. Informacion Especifica\n3. Salir\n|Digite aqui-->";
        cin >> opt;
        cin.ignore( );
        //if((opt > 48) && (opt < 52)) Restart( );
        system("cls");

        switch(opt){
        case '1':
        {
            system("cls");
            cout << endl << "--> La red metro cuenta actualmente con " << total_lines << " lineas de metro." << endl << endl;
            cout << endl << "--> Cada linea cuenta con: " << endl;
            int cont = 0;
            for(int i = 0; i < total_lines; i++){
                cout << "Linea " << i + 1 << ": ";
                for(int j = 0; ! stations[i][j].empty( ); j++){
                    cout << stations[i][j] << " - ";
                    cont++;
                }
                cout << cont << " Estaciones en total" << endl << endl << endl;
                cont = 0;
            }
        break;
        }

        case '2':
        {
            //Hacer otro menu, donde pueda ingresar un nombre y este lo busque entre los distintos arreglos, y de ahi le especifique la linea. tambien uno que cuente el total de estaciones
        break;
        }

        case '3':
        {
            //Sale del ciclo
        break;
        }

        default: cout << "Opcion invalida, vuelva a intetarlo" << endl;
        }               //Switch
    }
}

/*
void Metro :: Del_Station(){
    int b;
    ShowMe();

    cout << "Digite la estacion que desea eliminar: ";
    cin >> b;

    len--;

    string* newStations = new string[len];

    int sup = 0;
    // Copiar elementos del arreglo antiguo al nuevo
    for (int i = 0; i < len; ++i) {
        newStations[i] = stations[sup];
        sup++;
        if(sup == b - 1) sup++;
    }

    // Liberar la memoria del arreglo antiguo
    delete[] stations;

    // Actualizar el puntero al nuevo arreglo
    stations = newStations;
    ShowMe();
}
*/

//------------------------------------------------------------

//------------------------------------------------------------

bool Titan( ){              //Menu principal, desde aqui el usuario puede ir a la parte administrativa o informativa
    char opt = '0';
    bool state = true;
    Metro user;

    while(state){
        system("cls");
        cout << "-->Menu Principal\n\n1. Administrar Red Metro\n2. Consultar Informacion\n3. Salir\n|Digite aqui-->";
        cin >> opt;
        cin.ignore( );

        switch(opt){
        case '1':
        {
            user.Admin( );              //Abre el menu de administracion
        break;
        }

        case '2':
        {
            user.Info( );
        break;
        }

        case '3':
        {
            state = false;
        break;
        }
        default: cout << "Opcion incorrecta, vuelva a intentarlo" << endl;
        }           //Switch
    }
}
