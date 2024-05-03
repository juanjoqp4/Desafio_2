#include "metroC.h"

int Validation(int var, int min, int max);

Metro :: Metro( ){
        stations = new string *[1];                     //Se inicializa una linea de metro por defecto
        hour = new int *[1];
        len = 6;
        total_lines = 1;
        act_line = 0;
        stations[0] = new string[len] {"A", "B", "C", "D", "E", ""};
        hour[0] = new int[len - 1] {2, 7, 3, 4, 0};
}

void Metro :: Restart( ){                                                                   //Se restablecen los atributos para la respectiva linea
    cout << "Especifique la linea sobre la que va a trabajar: ";
    cin >> act_line;
    act_line = Validation(act_line, 1, total_lines);
    act_line -= 1;
    len = 0;

    while (! stations[act_line][len].empty( )) {                //Toma el tamaño de la linea referenciada
        len++;
    }
}

void Metro :: Restart(int Transf){
    act_line = Transf;
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

string Metro :: Transf( ){
    string station = "";
    int transf = 0, line = 0;
    cout << endl <<"Digite la linea donde se hara la transferencia: ";
    cin >> line;
    line = Validation(line, 1, total_lines);
    line--;
    Restart(line);
    ShowMe( );
    cout << "Seleccione la estacion de transferencia: ";
    cin >> transf;
    transf = Validation(transf, 1, len);
    transf--;

    station = stations[line][transf];
    return station;
}

void Metro::AddLines( ) {
    string **Space = new string *[total_lines + 1], station = "";     // Crea un nuevo arreglo para la nueva línea en base al total de lineas que hubiera en ese momento

    station = Transf( );
    len = 0;
    for(int i = 0; i < total_lines; i++){                                       //Se toma la copia de los arreglos anteriores
        for(int j = 0; ! stations[ i ][ j ].empty( );j++) len++;           //Toma el tamaño del arreglo en i
        len++;

        Space[i] = new string [len];                    //Le da los espacios necesarios para la copia
        for(int k = 0; k < len; k++) {
            Space[i][k] = stations[i][k];           //Copia los elementos del arreglo anterior
        }
        len = 0;
    }

    for(int d = 0; d < total_lines; d++){           //Despues de copiar libera el arreglo anterior
        delete[ ] stations[d];
    }
    delete[ ] stations;
    stations = nullptr;

    total_lines += 1;              // Incrementar el número total de líneas
    Space[total_lines - 1] = new string[2];     //Le da un espacio a la nueva linea

    Space[total_lines - 1][0] = station;
    Space[total_lines - 1][1] = "";         //La funcion de una cadena vacia, es poder tomar con empty los distintos tamaños de cada linea

    stations = Space;        // Actualiza el puntero con el nuevo arreglo
    //ShowMe( );
    ConfHour( );
    cout << "Se ha agregado una nueva linea de metro." << endl << endl;
}

void Metro :: ConfHour( ){
    int **sup = new int *[total_lines];
    for(int i = 0; i < total_lines - 1; i++){
        Restart(i);
        sup[i] = new int [len];
        for(int j = 0; j < len; j++){
            sup[i][j] = hour[i][j];
            //cout << "Copia Tiempos-->" << sup[i][j] << endl;
        }
    if(i + 1 == total_lines - 1) sup[i + 1] = new int [1];
    }

    sup[total_lines - 1][0] = 0;                            //ERROR: A veces lo agrega bien, o a veces mal
    if(total_lines != 2) for(int i = 0; i < total_lines; i++) delete[ ] hour[i];     // Liberar la memoria del arreglo de strings
    delete[ ] hour;                                                     // Liberar la memoria del arreglo de punteros
    hour = nullptr;                                             // Establecer el puntero a nullptr (buena práctica)

    hour = sup;
}

void Metro :: RemLines( ) {
    string** updatedLines = new string*[total_lines - 1];                   // Crear un nuevo arreglo para las lineas restantes

    for (int i = 0; i < total_lines - 1; ++i) {             // Copiar elementos antes de la ultima linea
        updatedLines[i] = stations[i];
    }

    delete[ ] stations;
    stations = updatedLines;                    // Eliminar el antiguo arreglo y actualizar el puntero
    total_lines--;              // Disminuir el numero total de lineas

    cout << "La linea " << total_lines + 1 << " ha sido eliminada exitosamente." << endl << endl;
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
    b = (act_line != 0)? Validation(b, 2, len + 1) : Validation(b, 1, len + 1);                      //El minimo es 2 en estaciones distintas a la primera, porque siempre va a estar la estacion de transferencia en la primera posicion


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

    len += 1;           //Aumenta 2, uno para la nueva estacion y otro para la cadena vacia

    stations[act_line] = new string [len + 1];
    stations[act_line][len] = "";

    for(int k = 0; k < len; k++){
        stations[act_line][k] = newSt[k];                           //El arreglo principal toma los datos del arreglo nuevo
        //cout << "-->" << stations[act_line][k] << endl;
    }
    int pin = len - 1;

    if(pin > 0) Time(1, b);         //Si hay por lo menos una estacion, hace el proceso de los tiempos

    cout << endl << "Se agrego la nueva estacion a la linea " << act_line + 1 << endl;
    //ShowMe( );
}

void Metro :: Time(int type, int ubi) {
    if (type == 1) {
        int time = 0, time2 = 0;
        bool c = false;
        int *newt;

        cout << "|-->Digite el tiempo de llegada desde " << stations[act_line][ubi - 2] << ": ";
        cin >> time;

        if (stations[act_line][ubi] != "") {                                                                                        //Si la estacion fue agregada en la ultima posicion, solo debe recibir el tiempo de llegada desde n - 1
            cout << "|-->Digite el tiempo de llegada hasta " << stations[act_line][ubi] << ": ";
            cin >> time2;
            c = true;
        }

        if (c == true) newt = new int [len + 1];
        else newt = new int [len];

        if(c == true){
            int sup = 0;
            for(int i = 0; i < len + 1; i++){
                if(i != ubi - 1){
                    newt[i] = hour[act_line][sup];
                    sup++;
                }
                //cout << "Copia/" << newt[i] << "+Original+" << hour[act_line][sup - 1] << endl;
            }
            newt[ubi - 1] = time2;
            newt[ubi - 2] = time;
        }else{
            int sup = 0;
            hour[act_line][len - 1] = 0;
            for(int i = 0; i < len - 1; i++){
                if(i != ubi - 2){
                    newt[i] = hour[act_line][sup];
                    sup++;
                }
            //cout << "Copia/" << newt[i] << "+Original+" << hour[act_line][sup - 1] << endl;
            }
            newt[ubi - 2] = time;
        }

        delete[ ] hour[act_line];                                                     // Liberar la memoria del arreglo de punteros //ERROR: DESPUES DE AGREGAR 2 ESTACIONES EN LA ULTIMA POSICION SE CAE EL PROGRAMA AQUI
        hour[act_line] = newt;

    } else {
        len++;
        // Eliminar una estación y ajustar los tiempos
        bool isLastStation = (ubi - 1 == len);
        int *newt;

        if (isLastStation) {
            cout << "entro" << endl;
            newt = new int[len - 1];         // Si es la ultima estacion, simplemente reducir el tamaño del arreglo de tiempos
            for (int i = 0; i < len - 1; ++i) {
                newt[i] = hour[act_line][i];
            }
        } else {
            // Si la estación está entre otras, sumar los tiempos y reducir el tamaño del arreglo
            newt = new int[len - 1];
            int sup = 0;
            for (int i = 0; i < len - 1; ++i) {
                if (i == ubi - 2) {
                    //cout << "//" << hour[act_line][i] << " + " << hour[act_line][i + 1] << endl;

                    newt[i] = hour[act_line][i] + hour[act_line][i + 1];        // Sumar los tiempos de la estacion eliminada y la siguiente

                   // cout << "Resultado : " << newt[i] << endl;
                    sup += 2; // Saltar el tiempo 2 espacios, ya que reemplazamos 1 y eliminamos otro
                } else{
                    if(i == ubi - 1) i++;
                    newt[i] = hour[act_line][sup];
                    //cout << "-->Copia : " << hour[act_line][sup] << endl;
                    sup++;
                }
            }
        }

        delete[ ] hour[act_line]; // Liberar la memoria del arreglo anterior
        hour[act_line] = newt; // Asignar el nuevo arreglo de tiempos
        len--; // Ajustar el tamaño de la línea
    }
}

void Metro::RemStation( ) {
    ShowMe( );
    bool comp = false;
    int ind;
    cout << "Digite la estacion que desea eliminar: ";
    cin >> ind;
    if(act_line > 0 && (ind - 1) == 0){
        cout << endl << "No puedes eliminar una estacion de transferencia, intentalo de nuevo" << endl;
    }else{

        for(int i = 0; ! stations[ 0 ][ i ].empty( ); i++){
            if(act_line != 0 && stations[ 0 ][ i ] == stations [act_line][ind - 1]) comp = true;
        }

        if(comp == true) cout << endl << "No puedes eliminar una estacion de transferencia, intentalo de nuevo" << endl;
        else{
            string* updatedStations = new string[len];      // Crea un nuevo arreglo para almacenar las estaciones actualizadas

            for (int i = 0; i < ind - 1; ++i) {
                updatedStations[i] = stations[act_line][i];         // Copia los elementos antes que la estacion sea removida
            }

            for (int i = ind; i <= len; ++i) {
                updatedStations[i - 1] = stations[act_line][i];          // Copia los elementos despues saltandose la estacion eliminada
            }

            delete[ ] stations[act_line];                   // Borra el arreglo antiguo y actualiza el puntero
            stations[act_line] = updatedStations;
            len--;                                                      // Reduce el numero total de estaciones en la linea

            cout << "La estacion ha sido eliminada exitosamente." << endl << endl;
        }
    }
    int pin = len - 1;
    if(pin > 0) Time(2, ind);         //Si hay por lo menos una estacion, hace el proceso de los tiempos
}

void Metro :: Admin( ){             //Menu para administrar la red metro
    system("cls");
    char opt = '0';
    while(opt != '5'){
        cout << "|-->Menu Administrador\n1. Agregar linea a la red\n2. Agregar estacion a una linea\n3. Eliminar una linea\n4. Eliminar una estacion\n5. Salir\n|Digite aqui-->";
        cin >> opt;
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
            if (total_lines == 1) {
                cout << "No se puede eliminar la unica linea existente." << endl << endl;
            }else RemLines( );
        break;
        }

        case '4':
        {
            RemStation( );
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
        cout << endl << "|-->Menu de Informacion\n1. Informacion General\n2. Buscador\n3. Salir\n|Digite aqui-->";
        cin >> opt;
        system("cls");

        switch(opt){
        case '1':
        {
            cout << endl << "--> La red metro cuenta actualmente con " << total_lines << " lineas de metro." << endl << endl;
            cout << endl << "--> Cada linea cuenta con: " << endl;
            int cont = 0, tots = 0;
            for(int i = 0; i < total_lines; i++){
                cout << "Linea " << i + 1 << ": ";
                for(int j = 0; ! stations[i][j].empty( ); j++){
                    cout << stations[i][j] << " - ";
                    cont++;
                    tots++;
                }
                cout << cont << " Estaciones en total" << endl;
                cont = 0;
            }
            if(total_lines > 1) cout << "La red cuenta con un total de " << tots - (total_lines - 1) << " estaciones"  << endl << endl;
        break;
        }

        case '2':
        {
            char opt2;
            bool res = false;
            cout << "|Digite aqui la estacion-->";

            string stationName = "";
            cin.ignore( );
            getline(cin, stationName);
            for (int i = 0; i < total_lines; ++i) {
                for (int j = 0; !stations[i][j].empty( ); j++) {
                    if (stations[i][j] == stationName) {
                        cout << "La estacion \"" << stations[i][j] << "\" se encuentra en la linea " << i + 1 << " de nuestra red" << endl << endl;
                        res = true;
                        break;
                    }
                }
            }
            if(res == false) cout << "La estacion " << stationName << " no existe dentro de nuestra red" << endl << endl;
            else res = false;
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

int Metro :: Simulation :: Travel( ){
        int first, last, sub_act, sub_len;
        cout << "Especifique la linea sobre la que va a trabajar: ";
        cin >> metroSystem->act_line;

        sub_act = metroSystem->act_line;

        sub_act = Validation(sub_act, 1, metroSystem->total_lines);
        sub_act -= 1;
        metroSystem->len = 0;

        while (!metroSystem->stations[sub_act][metroSystem->len].empty( )) {
            metroSystem->len++;
        }

        sub_len = metroSystem->len;

        if(sub_len != 1){
            cout << "Estas son nuestras estaciones de la linea " << sub_act + 1 << " actualmente: " << endl << endl;
            for (int i = 0; i < sub_len; ++i){
                if(!metroSystem->stations[sub_act][i].empty( )) cout << i + 1 << ". " << metroSystem->stations[sub_act][i] << endl;
            }
            cout << endl;
        } else {
            cout << endl << "No hay suficientes estaciones para hacer una simulacion en esta linea, agrega alguna :)" << endl << endl;
        }

        cout << "Digite la estacion de partida: ";
        cin >> first;
        first = Validation(first, 1, sub_len) - 1;

        cout << "Digite la estacion de llegada: ";
        cin >> last;
        last = Validation(last, 1, sub_len) - 1;
        int cont = 0;

        if(first > last){
            for(int i = first - 1; i >= last; i--){
                cont += metroSystem->hour[sub_act][i];
            }
        } else {
            for(int j = first; j < last; j++){
                cout << "Suma recorrido: " << metroSystem->hour[sub_act][j] << endl;
                cont += metroSystem->hour[sub_act][j];
            }
        }

        cout << "El recorrido desde " << metroSystem->stations[sub_act][first] << " hasta " << metroSystem->stations[sub_act][last] << " dura aproximadamente " << cont << " minutos..." << endl << endl;
        return cont;
    }
//------------------------------------------------------------

//------------------------------------------------------------

bool Titan( ){              //Menu principal, desde aqui el usuario puede ir a la parte administrativa o informativa
    char opt = '0';
    bool state = true;
    int time = 0;
    Metro user;

    while(state){

        if(time == 0) system("cls");
        time = 0;

        cout << endl << "-->Menu Principal\n\n1. Administrar Red Metro\n2. Consultar Informacion\n3. Simulacion de recorrido\n4. Salir\n|Digite aqui-->";
        cin >> opt;

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
            system("cls");
            Metro :: Simulation passenger(&user);
            time = passenger.Travel( );
        break;
        }

        case '4':
        {
            state = false;
        break;
        }
        default: cout << "Opcion incorrecta, vuelva a intentarlo" << endl;
        }           //Switch
    }
}

int Validation(int var, int min, int max){
    char opt = char(var + 48);

    while(opt < char(min + 48) || opt > char(max + 48)){
        cout << endl << "Opcion incorrecta, vuelva a intentarlo: ";
        cin >> opt;
    }
    return int(opt - 48);
}
