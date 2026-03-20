#include "ConfiguracionMenu.h"
#include "MainMenu.h"
#include <iostream>
#include <cstdlib>
using namespace std;
using namespace rlutil;

void MainMenu::mostrar(Contexto obj)
{
    hidecursor();

    MenuClientes menuClientes;
    menuCancha menuCancha;
    Sistema menuAlquileres; ///HAY QUE CAMBIAR EL NOMBRE DE "SISTEMA" POR "MenuAlquiler"
    menuInformes menuInforme;
    MenuBackup mb;


    hidecursor();
    vector<string> opciones =
    {
        " Menu de Clientes ",
        " Menu de Canchas ",
        " Menu de Alquileres ",
        " Informes ",
        " Backup ",
        " Salir "
    };
    while(true)
    {
        int opcion = menuConFlechas(opciones, "SISTEMA DE GESTION DE CANCHAS");;

        cls();
        switch (opcion)
        {
        case 0:
            cls();
            menuClientes.mostrar();
            break;
        case 1:
            cls();
            menuCancha.mostrar();
            break;
        case 2:
            cls();
            menuAlquileres.mostrarMenu();
            break;

        case 3:
            cls();
            menuInforme.mostrar();
            break;

        case 4:
            cls();
            mb.mostrar();
            break;

        case 5:
            cls();
            centrarTexto("SALIENDO DEL SISTEMA.\n", 15);
            return;

        default:
            cls();
            setColor(RED);
            centrarTexto("OPCION INVALIDA.\n", 15);
            break;
        }

        anykey();
        setColor(BLUE);
        cls();
    }
}
