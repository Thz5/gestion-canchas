#include <cstdio>
#include "CanchaArchivo.h"
#include <iostream>

using namespace std;

CanchaArchivo::CanchaArchivo(const char* ruta)
{
    rutaArchivo = ruta;
}

void CanchaArchivo::guardarCancha(const Cancha &reg)
{
    FILE* p = fopen(rutaArchivo, "ab");
    if (p == NULL) return;

    fwrite(&reg, sizeof(Cancha), 1, p);
    fclose(p);
}

void CanchaArchivo::mostrarCanchas()
{
    FILE* p = fopen(rutaArchivo, "rb");
    if (p == nullptr)
    {
        cout << "NO SE PUDO ABRIR EL ARCHIVO." << endl;
        return;
    }

    Cancha reg;
    int count = 0;


    const int boxW = 48;
    const int boxH = 6;
    const int cols = 3;
    const int startX = 2;
    const int startY = 2;
    const int gapX = 4;
    const int gapY = 1;

    while (fread(&reg, sizeof(Cancha), 1, p))
    {
        if (reg.getActivo())
        {
            int col = count % cols;
            int row = count / cols;

            int x = startX + col * (boxW + gapX);
            int y = startY + row * (boxH + gapY);

            reg.mostrar(x, y);

            count++;
        }
    }

    fclose(p);
}

int CanchaArchivo::cantidadRegistros()
{
    FILE* p = fopen(rutaArchivo, "rb");
    if (p == NULL) return 0;

    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Cancha);
    fclose(p);
    return cant;
}

Cancha CanchaArchivo::leerRegistro(int pos)
{
    Cancha reg;
    FILE* p = fopen(rutaArchivo, "rb");
    if (p == NULL) return reg;

    fseek(p, pos * sizeof(Cancha), SEEK_SET);
    fread(&reg, sizeof(Cancha), 1, p);
    fclose(p);
    return reg;
}

bool CanchaArchivo::guardarRegistro(int pos, const Cancha &reg)
{
    FILE* p = fopen(rutaArchivo, "rb+");
    if (p == NULL) return false;

    fseek(p, pos * sizeof(Cancha), SEEK_SET);
    bool ok = fwrite(&reg, sizeof(Cancha), 1, p);
    fclose(p);
    return ok;
}

int CanchaArchivo::buscarPorId(int idBuscado)
{
    int cant = cantidadRegistros();

    for (int i = 0; i < cant; i++)
    {
        Cancha reg = leerRegistro(i);
        if (reg.getIdCancha() == idBuscado) return i;
    }

    return -1;
}

bool CanchaArchivo::existeCanchaPorID(int id)
{
    int pos = buscarPorId(id);
    if (pos < 0) return false;

    Cancha reg = leerRegistro(pos);
    return reg.getActivo();
}

Cancha CanchaArchivo::leerCanchaPorID(int id)
{
    int pos = buscarPorId(id);

    Cancha vacia;
    vacia.setIdCancha(-1);
    vacia.setActivo(false);

    if (pos < 0) return vacia;

    Cancha reg = leerRegistro(pos);
    if (!reg.getActivo()) return vacia;

    return reg;
}
