#include "SistemaArchivos.h"
#include "ConfiguracionMenu.h"
#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;
using namespace rlutil;

SistemaArchivos::SistemaArchivos(const char* ruta)
{
    rutaArchivo = ruta;
}

void SistemaArchivos::guardarAlquiler(const Alquiler &obj)
{
    FILE *p = fopen(rutaArchivo, "ab");
    if (p == nullptr)
    {
        setColor(RED);
        centrarTexto("Error al abrir el archivo para guardar.\n", 15);
        setColor(BLACK);
        return;
    }

    fwrite(&obj, sizeof(Alquiler), 1, p);
    fclose(p);
}

void SistemaArchivos::mostrarAlquileres()
{
    FILE *p = fopen(rutaArchivo, "rb");
    if (p == nullptr)
    {
        centrarTexto("No hay alquileres registrados o no se pudo abrir el archivo.", 15);
        anykey();
        return;
    }

    Alquiler obj;
    int count = 0;

    // CONFIGURACIÓN DE LA GRILLA
    const int boxW = 48;   // ancho total visual (ajustado para tu caja)
    const int boxH = 9;    // alto total (debe coincidir con boxH usado en Alquiler::mostrar)
    const int cols = 3;    // columnas por fila
    const int startX = 2;
    const int startY = 2;
    const int gapX = 4;    // separación horizontal
    const int gapY = 2;    // separación vertical

    while (fread(&obj, sizeof(Alquiler), 1, p) == 1)
    {


        int col = count % cols;
        int row = count / cols;

        int x = startX + col * (boxW + gapX);
        int y = startY + row * (boxH + gapY);

        obj.mostrar(x, y);

        count++;
    }

    fclose(p);

    // Mensaje final ubicado bajo la última fila de cajas
    int filas = (count + cols - 1) / cols;
    int finalY = startY + filas * (boxH + gapY) + 1;
    gotoxy(2, finalY);
    cout << "Presione cualquier tecla para volver...";
    anykey();
}

void SistemaArchivos::buscarPorFecha()
{
    Alquiler obj;
    Fecha fe;
    FILE *p = fopen(rutaArchivo, "rb");
    if (!p)
    {
        setColor(RED);
        centrarTexto("ERROR AL INTENTAR ABRIR EL ARCHIVO.\n", 15);
        setColor(BLACK);
        return;
    }

    centrarTexto("Ingrese la fecha que desea buscar:\n", 10);
    fe.Cargar();

    bool encontrado = false;

    cls();

    int count = 0;
    // CONFIGURACIÓN DE LA GRILLA
    const int boxW = 48;   // ancho total visual (ajustado para tu caja)
    const int boxH = 9;    // alto total (debe coincidir con boxH usado en Alquiler::mostrar)
    const int cols = 3;    // columnas por fila
    const int startX = 2;
    const int startY = 2;
    const int gapX = 4;    // separación horizontal
    const int gapY = 2;    // separación vertical

    while (fread(&obj, sizeof(Alquiler), 1, p) == 1)
    {
        Fecha f = obj.getFechaAlquiler();
        if (f.getDia() == fe.getDia() &&
                f.getMes() == fe.getMes() &&
                f.getAnio() == fe.getAnio())
        {

            encontrado = true;
            int col = count % cols;
            int row = count / cols;

            int x = startX + col * (boxW + gapX);
            int y = startY + row * (boxH + gapY);


            obj.mostrar(x, y);

            count++;
        }
    }

    anykey();
    if (!encontrado)
    {
        cout << "\nNo se encontraron alquileres en esa fecha.\n";
    }

    fclose(p);
}

int SistemaArchivos::CantidadRegistros()
{
    FILE *p = fopen(rutaArchivo, "rb");
    if(p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cantidadRegistros = ftell(p) / sizeof(Alquiler);
    fclose(p);
    return cantidadRegistros;
}
bool SistemaArchivos::estaAlquilada(int idCancha, Fecha& fecha, int hora)
{
    FILE *p = fopen(rutaArchivo, "rb");
    if (p == nullptr)
    {
        return false;
    }

    Alquiler reg;
    while (fread(&reg, sizeof(Alquiler), 1, p) == 1)
    {

        if (reg.getIdCancha() == idCancha &&
                reg.getFechaAlquiler().getDia() == fecha.getDia() &&
                reg.getFechaAlquiler().getMes() == fecha.getMes() &&
                reg.getFechaAlquiler().getAnio() == fecha.getAnio() &&
                reg.getHora() == hora)
        {

            fclose(p);
            return true; //Está alquilada.
        }
    }

    fclose(p);
    return false;
}

Alquiler SistemaArchivos::leerRegistro(int pos)
{
    Alquiler reg;

    FILE *p = fopen(rutaArchivo, "rb");
    if (p == nullptr)
    {
        return reg;
    }

    fseek(p, pos * (int)sizeof(Alquiler), SEEK_SET);
    fread(&reg, sizeof(Alquiler), 1, p);
    fclose(p);

    return reg;
}


bool SistemaArchivos::modificarRegistro(int pos, const Alquiler& reg)
{
    FILE* p = fopen(rutaArchivo, "rb+");
    if (p == nullptr) return false;

    fseek(p, pos * (int)sizeof(Alquiler), SEEK_SET);
    bool ok = (fwrite(&reg, sizeof(Alquiler), 1, p) == 1);

    fclose(p);
    return ok;
}

int SistemaArchivos::elegirAlquiler()
{
    FILE* p = fopen(rutaArchivo, "rb");
    if (!p) return -1;

    vector<string> opciones;
    vector<int> posiciones;  // guarda el indice real en archivo

    Alquiler reg;
    int index = 0;

    while (fread(&reg, sizeof(Alquiler), 1, p) == 1)
    {
        char buf[200];
        Fecha f = reg.getFechaAlquiler();

        sprintf(buf, "ID: %d | Cancha %d | %02d/%02d/%04d | %d:00",
                reg.getIdCliente(),
                reg.getIdCancha(),
                f.getDia(), f.getMes(), f.getAnio(),
                reg.getHora()
        );

        opciones.push_back(string(buf));
        posiciones.push_back(index);

        index++;
    }

    fclose(p);

    if (opciones.size() == 0) return -1;

    // agregamos opcion VOLVER ---
    opciones.push_back(" Volver ");

    int sel = menuConFlechas(opciones, "SELECCIONE ALQUILER");

    // si eligió "Volver", devolver -1
    if (sel == (int)opciones.size() - 1) {
        return -1;
    }
    // si eligió un alquiler, devolver su posición real
    return posiciones[sel];
}

bool SistemaArchivos::eliminarAlquiler(int pos)
{
    FILE* p = fopen(rutaArchivo, "rb");
    FILE* temp = fopen("TEMP.dat", "wb");

    if (!p || !temp) return false;

    Alquiler reg;
    int index = 0;

    while (fread(&reg, sizeof(Alquiler), 1, p) == 1)
    {
        if (index != pos)
            fwrite(&reg, sizeof(Alquiler), 1, temp);

        index++;
    }

    fclose(p);
    fclose(temp);

    remove(rutaArchivo);
    rename("TEMP.dat", rutaArchivo);
    return true;
}

