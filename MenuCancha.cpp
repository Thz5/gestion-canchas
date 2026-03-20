#include "MenuCancha.h"
#include "ConfiguracionMenu.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

using namespace std;
using namespace rlutil;

void menuCancha::mostrar()
{
    hidecursor();
    vector<string> opciones
    {
        " Registrar Cancha ",
        " Canchas Registradas ",
        " Modificar Cancha ",
        " Eliminar Cancha ",
        " Volver "
    };

    while (true)
    {
        int opcion = menuConFlechas(opciones, "MENU CANCHAS");

        cls();
        switch (opcion)
        {
        case 0:
            cls();
            manager.registrarCancha();
            break;
        case 1:
            cls();
            manager.listarCanchas();
            break;
        case 2:
            cls();
            manager.modificarCancha();
            break;
        case 3:
            cls();
            manager.eliminarCancha();
            break;
        case 4:
            cls();
            centrarTexto(" Volviendo al Menu Principal...", 18);
            anykey();
            return;
        default:
            centrarTexto("Opcion invalida.\n", 18);
            break;
        }
        anykey();
        cls();
    }
}
