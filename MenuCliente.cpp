#include "MenuCliente.h"
#include "ConfiguracionMenu.h"
#include "rlutil.h"
#include <vector>
#include <string>

using namespace std;
using namespace rlutil;

void MenuClientes::mostrar()
{
    vector<string> opciones
    {
        " Registrar Cliente ",
        " Modificar Cliente ",
        " Eliminar Cliente ",
        " Buscar por ID ",
        " Buscar por DNI ",
        " Clientes Registrados ",
        " Recuperar Cliente ",
        " Volver "
    };

    while (true)
    {
        int opcion = menuConFlechas(opciones, "GESTION DE CLIENTES");

        cls();
        switch (opcion)
        {
        case 0:
            manager.altaCliente();
            break;
        case 1:
            manager.modificarCliente();
            break;
        case 2:
            manager.eliminarCliente();
            break;
        case 3:
            manager.buscarPorId();
            break;
        case 4:
            manager.buscarPorDni();
            break;
        case 5:
            manager.listarClientes();
            break;
        case 6:
            manager.recuperarCliente();
            break;
        case 7:
            centrarTexto("Volviendo al Menu Principal...", 18);
            anykey();
            return;

        default:
            setColor(RED);
            centrarTexto("OPCION INVALIDA.", 15);
            setColor(BLACK);
            centrarTexto("Intente nuevamente...", 16);
            anykey();
            break;
        }

        anykey();
        cls();
    }
}
