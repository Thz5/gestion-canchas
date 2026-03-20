#include "MenuBackup.h"
#include "Backup.h"
#include "ConfiguracionMenu.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace rlutil;

void MenuBackup::mostrar()
{
    hidecursor();

    vector<string> opciones
    {
        " Crear backup general ",
        " Restaurar backup general ",
        " Volver "
    };

    while (true)
    {
        int opcion = menuConFlechas(opciones, "MENU BACKUP");

        cls();
        Backup b;

        switch (opcion)
        {
        case 0:
            b.crearBackupGeneral();
            break;
        case 1:
            b.restaurarBackupGeneral();
            break;
        case 2:
            hidecursor();
            centrarTexto("Volviendo al Menu Principal...",18);
            anykey();
            return;
        }
        cls();
    }
}
