#include "Sistema.h"
#include "ConfiguracionMenu.h"
#include <iostream>

using namespace std;
using namespace rlutil;

void Sistema::mostrarMenu()
{
    vector<string> opciones
    {
        " Registrar Alquiler ",
        " Mostrar Alquileres ",
        " Buscar Alquiler por Fecha ",
        " Registrar Pago ",
        " Modificar Alquiler ",
        " Cancelar Alquiler ",
        " Volver "
    };
    while (true)
    {
        int opcion = menuConFlechas(opciones, "GESTION DE ALQUILERES");

        cls();
        switch (opcion)
        {
        case 0:
            manager.registrarAlquiler();
            break;
        case 1:
            manager.mostrarAlquileres();
            break;
        case 2:
            manager.buscarAlquilerPorFecha();
            break;
        case 3:
            manager.registrarPago();
            break;
        case 4:
            manager.modificarAlquiler();
            break;
        case 5:
            manager.cancelarAlquiler();
            break;
        case 6:
            centrarTexto("Volviendo al Menu Principal...", 18);
            return;
        }
        cls();
    }
}


