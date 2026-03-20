#include "ConfiguracionMenu.h"
#include "Backup.h"
#include <cstdio>
#include <iostream>
using namespace std;
using namespace rlutil;

bool Backup::copiarArchivo(const char* origen, const char* destino)
{
    FILE* pOrigen = fopen(origen, "rb");
    if (pOrigen == nullptr) return false;

    FILE* pDestino = fopen(destino, "wb");
    if (pDestino == nullptr)
    {
        fclose(pOrigen);
        return false;
    }

    char buffer[4096];
    size_t leidos;

    while ((leidos = fread(buffer, 1, sizeof(buffer), pOrigen)) > 0)
    {
        fwrite(buffer, 1, leidos, pDestino);
    }

    fclose(pOrigen);
    fclose(pDestino);
    return true;
}

void Backup::crearBackupGeneral()
{
    bool ok1 = copiarArchivo("Clientes.dat", "Clientes.bkp");
    bool ok2 = copiarArchivo("Canchas.dat", "Canchas.bkp");
    bool ok3 = copiarArchivo("alquileres.dat", "alquileres.bkp");

    cls();
    if (ok1 && ok2 && ok3)
    {
        centrarTexto("Backup creado correctamente.", 23);
    }
    else
    {
        centrarTexto("Error creando backup. Verifique los archivos.", 23);
    }
    cout << endl;
    system("pause");
}

void Backup::restaurarBackupGeneral()
{
    bool ok1 = copiarArchivo("Clientes.bkp", "Clientes.dat");
    bool ok2 = copiarArchivo("Canchas.bkp", "Canchas.dat");
    bool ok3 = copiarArchivo("alquileres.bkp", "alquileres.dat");

    cls();
    if (ok1 && ok2 && ok3)
    {
        centrarTexto("Backup restaurado correctamente.", 23);
    }
    else
    {
        centrarTexto("Error restaurando backup. Verifique los archivos .bkp.", 23);
    }
    cout << endl;
    system("pause");
}
