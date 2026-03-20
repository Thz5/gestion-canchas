#ifndef CANCHAARCHIVO_H_INCLUDED
#define CANCHAARCHIVO_H_INCLUDED

#include "Cancha.h"

class CanchaArchivo
{
private:
    const char* rutaArchivo;

public:
    CanchaArchivo(const char* ruta = "Canchas.dat");

    void guardarCancha(const Cancha &reg);
    void mostrarCanchas();
    int cantidadRegistros();
    Cancha leerRegistro(int pos);
    bool guardarRegistro(int pos, const Cancha &reg);

    int buscarPorId(int idBuscado);

    bool existeCanchaPorID(int id);
    Cancha leerCanchaPorID(int id);
};

#endif // CANCHAARCHIVO_H_INCLUDED

