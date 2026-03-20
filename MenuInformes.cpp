#include "MenuInformes.h"
#include "ConfiguracionMenu.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace rlutil;

void menuInformes::mostrar()
{
    hidecursor();

    vector<string> opciones
    {
        " Mes con mayor demanda ",
        " Tamano menos alquilado ",
        " Variacion porcentual respecto al mes anterior ",
        " Cantidad de alquileres por mes ",
        " Alquileres con senas mayores al 50% ",
        " Recaudacion por tipo de cancha ",
        " Metodo de pago mas utilizado ",
        " Nuevos clientes por mes ",
        " Volver "
    };

    while (true)
    {
        int opcion = menuConFlechas(opciones, "INFORMES");

        cls();

        switch (opcion)
        {
        case 0:
            informes.mesMayorDemanda();
            break;
        case 1:
            informes.tamanoMenosAlquilado();
            break;
        case 2:
            informes.variacionPorcentual();
            break;
        case 3:
            informes.alquileresPorMesEnAnio();
            break;
        case 4:
            informes.alquileresConSeniaMayor50();
            break;
        case 5:
            informes.recaudacionPorTipoCancha();
            break;
        case 6:
            informes.metodoPagoMasUtilizado();
            break;
        case 7:
            informes.clientesNuevosPorMesEnAnio();
            break;
        case 8:
            hidecursor();
            centrarTexto("Volviendo al Menu Principal...", 18);
            anykey();
            return;
        }

        anykey();
        cls();
    }
}
