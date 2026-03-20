#ifndef ALQUILERMANAGER_H_INCLUDED
#define ALQUILERMANAGER_H_INCLUDED

#include "SistemaArchivos.h"
#include "ClienteArchivo.h"
#include "Alquiler.h"

class AlquilerManager {
private:
    SistemaArchivos archivos;

public:
    AlquilerManager(const char* ruta = "alquileres.dat");

    void registrarAlquiler();
    void mostrarAlquileres();
    void buscarAlquilerPorFecha();
    void registrarPago();
    void modificarAlquiler();
    void cancelarAlquiler();
};

#endif // ALQUILERMANAGER_H_INCLUDED
