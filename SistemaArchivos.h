#ifndef SISTEMAARCHIVOS_H_INCLUDED
#define SISTEMAARCHIVOS_H_INCLUDED

#include "Alquiler.h"
#include "Fecha.h"

class SistemaArchivos
{
private:
    const char* rutaArchivo;

public:
    SistemaArchivos(const char* ruta = "alquileres.dat");
    void guardarAlquiler(const Alquiler &obj);
    void mostrarAlquileres();
    void buscarPorFecha();
    void eliminar(int id);
    int CantidadRegistros();
    bool estaAlquilada(int idCancha, Fecha& fecha, int hora);
    Alquiler leerRegistro(int pos);
    int  elegirAlquiler();
    bool modificarRegistro(int pos, const Alquiler& reg);
    bool eliminarAlquiler(int pos);


};


#endif // SISTEMAARCHIVOS_H_INCLUDED
