#include "metroC.h"

int Validation(int var, int min, int max);
int Validation(int var, int min);

Metro :: Metro() {
    stations = new string*[1];          // Se inicializa una linea de metro por defecto
    hour = new int*[1];
    len = 22;                   // Se ajusta el tamaño para las 21 estaciones de la linea A y un espacio nulo
    total_lines = 1;
    act_line = 0;
    stations[0] = new string[len] {
        "La Estrella", "Sabaneta", "Itagui", "Envigado", "Ayura", "Aguacatala",
        "El Poblado", "Industriales", "Exposiciones", "Alpujarra", "San Antonio",                   // Se inicializan las estaciones de la linea A
        "Parque Berrio", "Prado", "Hospital", "Universidad", "Caribe",
        "Tricentenario", "Acevedo", "Madera", "Bello", "Niquia", ""
    };
    // Se inicializan los tiempos entre estaciones, asumiendo un tiempo estimado entre cada una

    hour[0] = new int[len] {7, 3, 2, 4, 2, 2, 3, 5, 2, 2, 7, 2, 1, 2, 3, 2, 4, 2, 6, 2, 4,0};           // El último valor se establece en 0 por comodidad
}

void Metro :: Restart( ){                                                                   //Se restablecen los atributos para la respectiva linea
    cout << "Especifique la linea sobre la que va a trabajar: ";
    cin >> act_line;
    act_line = Validation(act_line, 1, total_lines);                //Se valida que la linea si exista
    act_line -= 1;                                                          //Se ajusta al indice
    len = 0;

    while (! stations[act_line][len].empty( )) {                //Toma el tamaño de la linea referenciada
        len++;
    }
}

void Metro :: Restart(int p){               //Se reestablecen los atributos para la linea p
    act_line = p;
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
    line = Validation(line, 1, total_lines);                //Comprueba la linea elegida
    line--;
    Restart(line);                      //Se reestablecen los atributos para la linea line
    ShowMe( );
    cout << "Seleccione la estacion de transferencia: ";
    cin >> transf;
    transf = Validation(transf, 1, len);                //Comprueba la estacion elegida
    transf--;

    station = stations[line][transf];           //Toma esa estacion de la linea referenciada y la retorna
    return station;
}

void Metro::AddLines( ) {
    string **Space = new string *[total_lines + 1], station = "";     // Crea un nuevo arreglo para la nueva línea en base al total de lineas que hubiera en ese momento

    station = Transf( );                //Toma la estacion de transferencia
    len = 0;
    for(int i = 0; i < total_lines; i++){                                       //Se toma la copia de los arreglos anteriores
        for(int j = 0; ! stations[ i ][ j ].empty( );j++) len++;           //Toma el tamaño del arreglo en i
        len++;

        Space[i] = new string [len];                    //Le da los espacios necesarios para la copia mas la cadena vacia
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

    Space[total_lines - 1][0] = station;                //Agrega la estacion de transferencia y el espacio vacio
    Space[total_lines - 1][1] = "";         //La funcion de una cadena vacia, es poder tomar con empty los distintos tamaños de cada linea

    stations = Space;        // Actualiza el puntero con el nuevo arreglo
    //ShowMe( );
    ConfHour( );                //Configura los tiempos para la nueva linea
    cout << "Se ha agregado una nueva linea de metro." << endl << endl;
}

void Metro :: ConfHour( ){
    int **sup = new int *[total_lines];                 //Inicializa el arreglo de copia
    for(int i = 0; i < total_lines - 1; i++){
        Restart(i);                                                 //Para cada ciclo es necesario tener los atributos de las diferentes lineas
        sup[i] = new int [len];                                 //Se inicializa un espacio con el mismo tamaño del arreglo original
        for(int j = 0; j < len; j++){
            sup[i][j] = hour[i][j];                                                 //Copia los tiempos de cada linea
            //cout << "Copia Tiempos-->" << sup[i][j] << endl;
        }
    if(i + 1 == total_lines - 1) sup[i + 1] = new int [1];          //Cuando este en el penultimo arreglo le da un espacio al nuevo arreglo que corresponde a la nueva linea
    }

    sup[total_lines - 1][0] = 0;

    for(int i = 0; i < total_lines - 1; i++){
        delete[ ] hour[i];     // Liberar la memoria del arreglo de strings, una linea menos ya que contiene una menos
    }
    delete[ ] hour;                                                     // Liberar la memoria del arreglo de punteros
    hour = nullptr;                                             // Establecer el puntero a nullptr (buena practica)

    hour = sup;                 //Apunta el puntero original a la copia con nuevos espacios
}

void Metro :: RemLines( ) {
    string** updatedLines = new string*[total_lines - 1];                   // Crear un nuevo arreglo para las lineas restantes
    int** updatedH = new int*[total_lines - 1];                   // Crear un nuevo arreglo para las lineas restantes

    int sup = 0;

    for (int i = 0; i < total_lines - 1; i++) {             // Copiar todo menos uno
        if(i != act_line){
            updatedLines[i] = stations[sup];                        //Copia cada linea
            updatedH[i] = hour[sup];
            //cout << "Copia de linea #" << sup + 1 << endl;
            sup++;
        }else{
            updatedLines[i] = stations[sup += 1];               //Cuando llega a la que quiere borrar, se salta 1 espacio y continua
            updatedH[i] = hour[sup];
            //cout << "Copia de linea #" << sup + 1 << endl;
            sup++;
        }
    }

    delete[ ] hour;
    delete[ ] stations;
    stations = updatedLines;                    // Eliminar el antiguo arreglo y actualizar el puntero
    hour = updatedH;
    total_lines--;              // Disminuir el numero total de lineas

    cout << "La linea " << act_line + 1 << " ha sido eliminada exitosamente." << endl << endl;
}

void Metro::NewStation( ){                  //Agrega una nueva estacion a la linea referenciada
    string a;
    int b;
    ShowMe( );                      //Muestra el estado de la linea actual

    cout << "Digite el nombre de la nueva estacion: ";
    cin.ignore( );                                                              //"Limpia" el cin
    getline(cin, a);                                                            //Toma la nueva estacion
    cout << "Digite la posicion donde desea ubicar la nueva estacion: ";
    cin >> b;
    b = (act_line != 0)? Validation(b, 2, len + 1) : Validation(b, 1, len + 1);                      //El minimo es 2 en  lineas mayores a 1, porque siemre va a estar la estacion de transferencia en la primera posicion

    string newSt [len + 2] = {};            // Crear un nuevo arreglo para la línea actual con un espacio más
    newSt[b - 1] = a;                           //Añade la estacion a la posicion elegida
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
    if (type == 1) {                                            //Tipo 1 es para agregar y tipo 2 para borrar
        int time = 0, time2 = 0;
        bool c = false, situat = false;                                         //c determina si hay que agregar 1 o 2 tiempos(reemplaza 1 y agrega otro)
        int *newt;

        if(act_line != 0 && ubi - 1 != 0){
            cout << "|-->Digite el tiempo de llegada desde " << stations[act_line][ubi - 2] << ": ";
            cin >> time;
        }else situat = true;

        if (situat == false) time = Validation(time, 1);         //Valida el tiempo de 1 hasta infinito

        if (stations[act_line][ubi] != "") {                                                                                        //Si la estacion fue agregada en la ultima posicion, solo debe recibir el tiempo de llegada desde n - 1
            cout << "|-->Digite el tiempo de llegada hasta " << stations[act_line][ubi] << ": ";
            cin >> time2;
            time2 = Validation(time2, 1);
            if(situat == false) c = true;                                   //Hay que agregar 2 tiempos al arreglo si no se da la situacion de 0 - 0
        }

        newt = new int [len + 1];            //Siempre se agrega 1 espacio de mas

        if(c == true){
            int sup = 0;
            for(int i = 0; i < len + 1; i++){
                if(i != ubi - 1){
                    newt[i] = hour[act_line][sup];                  //Se copia todo menos el tiempo correspondiente a la ubicacion de la estacion
                    sup++;
                }
                //cout << "Copia/" << newt[i] << "+Original+" << hour[act_line][sup - 1] << endl;
            }
            newt[ubi - 1] = time2;                  //Se agrega el nuevo tiempo
            newt[ubi - 2] = time;                   //Se reemplaza el de la posicion anterior
        }else{
            int sup = 0;
            int pin = (situat == false)? ubi - 2 : ubi - 1;
            hour[act_line][len - 1] = 0;
            for(int i = 0; i < len - 1; i++){
                if(i != pin){
                    newt[i] = hour[act_line][sup];                  //Se omite el tiempo a la posicion anterior de la estacion
                    sup++;
                }
            //cout << "Copia/" << newt[i] << "+Original+" << hour[act_line][sup - 1] << endl;
            }
            if(situat == false) newt[ubi - 2] = time;               //Se agrega el tiempo a la posicion anterior de la estacion
            else newt[ubi - 1] = time2;
        }

        delete[ ] hour[act_line];                                                     // Liberar la memoria del arreglo de punteros
        hour[act_line] = newt;                                                      //Cuando lo depuro no lanza el error(?)

    } else {
        len++;
        // Eliminar una estacion y ajustar los tiempos
        bool isLastStation = (ubi - 1 == len);                          //Si es la ultima estacion toma true
        int *newt;

        if (isLastStation) {
            //cout << "entró" << endl;
            newt = new int[len - 1];         // Si es la ultima estacion, simplemente reducir el tamaño del arreglo de tiempos
            for (int i = 0; i < len - 1; ++i) {
                newt[i] = hour[act_line][i];            //Copia todos menos el ultimo
            }
        } else {
            // Si la estación esta entre otras, sumar los tiempos y reducir el tamaño del arreglo
            newt = new int[len - 1];
            int sup = 0;

            if(ubi - 1 == 0 && act_line == 0) sup = 1;

            for (int i = 0; i < len - 1; ++i) {
                if (i == ubi - 2) {
                    newt[i] = hour[act_line][i] + hour[act_line][i + 1];        // Sumar los tiempos de la estacion eliminada y la siguiente
                    sup += 2; // Saltar el tiempo 2 espacios, ya que reemplazamos 1 y eliminamos otro
                } else{
                    if(i == ubi - 1 && (ubi - 1 != 0 && act_line == 0)) i++;                                                   //Si llega al reemplazado lo salta siempre y cuando no sea la primera posicion de la primera linea
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
    if(len > 1){                                    //Si solo hay una estacion, no la va a borrar
        ShowMe( );
        bool comp = false;
        int ind;
        cout << "Digite la estacion que desea eliminar: ";
        cin >> ind;
        if(act_line > 0 && (ind - 1) == 0){
            cout << endl << "No puedes eliminar una estacion de transferencia, intentalo de nuevo" << endl;         //La unica linea que puede no tener estaciones de transferencia en la primera posicion es la #1
        }else{

            ind = Validation(ind, 1, len);                                  //Comprueba que este dentro del rango
            for(int i = 0; ! stations[ 0 ][ i ].empty( ); i++){
                if(act_line != 0 && stations[ 0 ][ i ] == stations [act_line][ind - 1]) comp = true;            //Comprueba que esa estacion no este en la primera linea
            }

            if(act_line != total_lines - 1){                    //Si no es la ultima hace el proceso para comprobar
                int sub_act = act_line;
                cout << "Eliminando " << stations[sub_act][ind - 1] << "..." << endl;
                sleep(1.5);
                comp = Search(stations[sub_act][ind - 1]);           //Si estamos en la primera linea, comprueba que la estacion no sea la transferencia de una linea
            }
            if(comp == true) cout << endl << "|-->No puedes eliminar una estacion de transferencia, intentalo de nuevo" << endl;
            else{
                string* updatedStations = new string[len];      // Crea un nuevo arreglo para almacenar las estaciones actualizadas // OJO

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
        if(pin > 0) Time(2, ind);         //Si hay por lo menos una estacion, hace el proceso del borrado de tiempos
    }else cout << "No puedes eliminar la unica estacion que hay en la linea, intenta agregar mas :)" << endl;
}

void Metro :: Admin( ){             //Menu para administrar la red metro
    system("cls");
    char opt = '0';
    bool comp = false;
    while(opt != '5'){
        cout << "|-->Menu Administrador\n1. Agregar linea a la red\n2. Agregar estacion a una linea\n3. Eliminar una linea\n4. Eliminar una estacion\n5. Salir\n|Digite aqui-->";
        cin >> opt;
        opt = Validation(int(opt - 48), 1, 5);              //Es necesario validar, ya que ante numeros de 2 digitos ocurre un error y el default no ayuda
        opt = char(opt + 48);                               //Vuelve a su forma char
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
            //Escalar, vectorial y volumenes Geo Vect Parcial viernes
        case '3':
        {
            cout << "Buscando posible estacion de transferencia..." << endl;
            sleep(1.5);
            int save = act_line, savlen = len;                  //Se guardan los datos de la linea actual
            if (total_lines == 1) {
                cout << "No se puede eliminar la unica linea existente." << endl << endl;
            }else{
                if(save != total_lines - 1){                        //Si no es la ultima linea se realiza un proceso para comprobar que no hayan lineas con estaciones de transferencia
                    for(int i = 0; i < savlen; i++){
                        comp = Search(stations[save][i]);               //Comprueba que cada estacion de la linea actual no sea de transferencia
                        Restart(save);
                        if(comp == true) break;                 //En el caso de que sea de transferencia el algoritmo rompe el ciclo automaticamente
                    }
                    if(comp == false){                  //Si sobrevivio al segmento anterior restablece los datos de esa linea para posteriormente borrarla
                        Restart(save);
                        RemLines( );
                    }
                    else cout << endl << "No puedes eliminar una linea con estaciones de transferencia" << endl << endl;
                } else RemLines( );             //Al ser la ultima linea no hay nada que comprobar, simplemente se borra
            }
            comp = false;
        break;
        }

        case '4':
        {
            RemStation( );              //Elimina una estacion
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
        opt = Validation(int(opt - 48),1,3);                //Comprueba el dato de entrada
        opt = char(opt + 48);           //Vuelve a su forma char
        system("cls");

        switch(opt){
        case '1':
        {
            cout << endl << "--> La red metro cuenta actualmente con " << total_lines << " lineas de metro." << endl << endl;
            cout << endl << "--> Cada linea cuenta con: " << endl;
            int cont = 0, tots = 0;
            for(int i = 0; i < total_lines; i++){                                       //Este segmento se encarga de mostrar el estado actual de la red
                cout << "Linea " << i + 1 << ": ";
                for(int j = 0; ! stations[i][j].empty( ); j++){
                    cout << stations[i][j] << " - ";
                    cont++;
                    tots++;
                }
                cout << cont << " Estaciones en total" << endl;
                cont = 0;
            }
            if(total_lines > 1) cout << "La red cuenta con un total de " << tots - (total_lines - 1) << " estaciones"  << endl << endl;             //Se descuentan las estaciones de transferencia
        break;
        }

        case '2':
        {
            char opt2;
            bool res = false;
            cout << "|Digite aqui la estacion-->";                              //Este segmento se encarga de mostrarle al usuario en que linea se encuentra alguna estacion

            string stationName = "";
            cin.ignore( );
            getline(cin, stationName);
            for (int i = 0; i < total_lines; ++i) {
                for (int j = 0; !stations[i][j].empty( ); j++) {
                    if (stations[i][j] == stationName) {
                        cout << "La estacion \"" << stations[i][j] << "\" se encuentra en la linea " << i + 1 << " de nuestra red" << endl << endl;
                        res = true;
                        break;                                      //Cuando la encuentra sale del ciclo
                    }
                }
                if(res == true) break;
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

bool Metro :: Search(string obj){                       //Busca obj entre todas las estaciones que hay despues de la linea actual en su primera posicion

    for(int i = act_line + 1; i < total_lines; i++){
        if(stations[i][0] == obj){
            return true;                            //Si la encuentra retorna true, y si no pues...
        }
    }
    return false;
}

int Metro :: Simulation :: Travel( ){                                                   //Esta clase simula el viaje de un pasajero a traves del sistema metro
        int first, last, sub_act, sub_len, cont = 0;
        bool comp = true;
        cout << "Especifique la linea sobre la que va a trabajar: ";
        cin >> metroSystem->act_line;

        sub_act = metroSystem->act_line;                //Reemplaza la instancia a un atributo con una variable mas facil de manejar

        sub_act = Validation(sub_act, 1, metroSystem->total_lines);
        sub_act -= 1;
        metroSystem->len = 0;

        while (!metroSystem->stations[sub_act][metroSystem->len].empty( )) {                //Agarra el tamaño del arreglo actual a traves del puntero
            metroSystem->len++;
        }

        sub_len = metroSystem->len;                     //Lo mismo aqui

        if(sub_len != 1){
            cout << "Estas son nuestras estaciones de la linea " << sub_act + 1 << " actualmente: " << endl << endl;                //Al no saber como usar ShowMe aqui, simplemente copie su codigo
            for (int i = 0; i < sub_len; ++i){
                if(!metroSystem->stations[sub_act][i].empty( )) cout << i + 1 << ". " << metroSystem->stations[sub_act][i] << endl;
            }
            cout << endl;
        } else {
            cout << endl << "No hay suficientes estaciones para hacer una simulacion en esta linea, agrega alguna :)" << endl << endl;
            comp = false;       //Si solo hay una estacion no va a hacer la simulacion
        }
        if(comp == true){
            cout << "Digite la estacion de partida: ";
            cin >> first;
            first = Validation(first, 1, sub_len) - 1;                  //Valida la estacion de partida y la ajusta para los indices

            cout << "Digite la estacion de llegada: ";
            cin >> last;
            last = Validation(last, 1, sub_len) - 1;                    //Lo mismo aqui

            if(first > last){                                                   //Si la primera es mayor va a hacerlo en reversa
                for(int i = first - 1; i >= last; i--){
                    cont += metroSystem->hour[sub_act][i];              //Se suman los tiempos del arreglo
                }
            } else {
                for(int j = first; j < last; j++){                          //Aqui lo mismo
                    //cout << "Suma recorrido: " << metroSystem->hour[sub_act][j] << endl;
                    cont += metroSystem->hour[sub_act][j];
                }
            }

            cout << "El recorrido desde " << metroSystem->stations[sub_act][first] << " hasta " << metroSystem->stations[sub_act][last] << " dura aproximadamente " << cont << " minutos..." << endl << endl;
        }
        return cont;    //Retorna el tiempo para saber si limpia consola o no
    }
//------------------------------------------------------------

//------------------------------------------------------------

bool Titan( ){              //Menu principal, desde aqui el usuario puede ir a la parte administrativa o informativa
    char opt = '0';
    bool state = true;
    int time = 0;
    Metro user;

    while(state){                               //Mientras que state sea true el programa se ejecutara

        if(time == 0) system("cls");            //Si el tiempo que devuelve de la simulacion es 0 borra consola
        time = 0;

        cout << endl << "-->Menu Principal\n\n1. Administrar Red Metro\n2. Consultar Informacion\n3. Simulacion de recorrido\n4. Salir\n|Digite aqui-->";
        cin >> opt;
        opt = Validation(int(opt - 48),1,4);                //Comprueba la opcion y la retorna a char
        opt = char(opt + 48);
        switch(opt){
        case '1':
        {
            user.Admin( );              //Abre el menu de administracion
        break;
        }

        case '2':
        {
            user.Info( );               //Abre el menu de informacion
        break;
        }

        case '3':
        {
            system("cls");
            Metro :: Simulation passenger(&user);       //Crea un objeto pasajero a traves de la instancia user de metro, para asi poder usar sus atributos para la simulacion
            time = passenger.Travel( );                 //Simula a gusto del usuario
        break;
        }

        case '4':
        {
            state = false;              //Cierra el programa
        break;
        }
        default: cout << "Opcion incorrecta, vuelva a intentarlo" << endl;
        }           //Switch
    }
}

int Validation(int var, int min, int max) {                         //Valida var en un rango de min a max
    int input = var;
    var = 0;
    bool validInput = true;
    if(input < min || input > max) validInput = false;                  //Si no esta dentro del rango tira de una vez el false
    while (!validInput) {
        cout << "Ingrese un numero entre " << min << " y " << max << ": ";
        if (cin >> input) {                                         //Si manda error se va al cin.clean( )
            if (input >= min && input <= max) {         // Verificar si esta dentro del rango
                validInput = true;                      //Cuando este dentro de un rango valido manda true
                return input;
            } else {
                cout << "Opcion invalida, Intentelo nuevamente." << endl;
            }
        } else {
            cout << "Opcion invalida, Intentelo nuevamente." << endl;
            cin.clear( );                                                                                       // Limpiar el estado de error
            cin.ignore(numeric_limits<std::streamsize>::max( ), '\n');                          // Funcion sacada de IA Copilot para Ignorar caracteres inválidos
        }
    }
    return input;               //Retorna el valor correcto
}

int Validation(int var, int min) {                      //En esta version sobrecargada no tiene limite maximo
    int input = var;
    bool validInput = true;
    if (input < min) validInput = false;
    while (!validInput) {
        cout << "Ingrese un numero mayor o igual a " << min << ": ";
        if (cin >> input) {
            if (input >= min) {
                validInput = true;
                return input;
            } else {
                cout << "Opcion invalida. Intentelo nuevamente." << endl;
            }
        } else {
            cout << "Entrada no valida. Intentelo nuevamente." << endl;
            cin.clear();                                                    // Limpiar el estado de error
            cin.ignore(std::numeric_limits<std::streamsize>::max( ), '\n');                  // Ignorar caracteres invalidos
        }
    }
    return input;
}
