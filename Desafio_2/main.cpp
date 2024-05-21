#include "Func.cpp"

int main()
{
    bool sesion = true;
    do
    {

        sesion = Titan( );

    }while(sesion == true);         //Cierra el programa cuando salga del menu principal

    system("cls");
    cout << "|--> Programa Finalizado" << endl;

    return 0;
}
