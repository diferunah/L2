#include <iostream>
#include "startShip.h"
#include "snake.h"

using namespace std;

int main(int argc, char const *argv[])
{
    system("cls");

        int menu = 0;

    while(true)
    {
        cout << "**************" << endl;
        cout << "MENU DE JUEGOS" << endl;
        cout << "**************" << endl;

        cout << endl;

        cout << "Seleccione un juego:" << endl;

        cout << "1 - StarShip" << endl;
        cout << "2 - Snake" << endl;
        

        cout << endl;

        cout << "Ingrese un numero del menu para seleccionar un juego: ";
        cin >> menu;

            switch (menu)
            {
            case 1:
                {starShip();
                break;}
            
            case 2:
                {snake();
                break;}
            
            
            }


    }

    return 0;
}
