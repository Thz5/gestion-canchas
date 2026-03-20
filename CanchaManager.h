#ifndef CANCHAMANAGER_H_INCLUDED
#define CANCHAMANAGER_H_INCLUDED

#include "CanchaArchivo.h"
#include "Cancha.h"

class CanchaManager {
private:
    CanchaArchivo archivo;

public:
    CanchaManager(const char* ruta = "Canchas.dat");

    void registrarCancha();
    void listarCanchas();
    void modificarCancha();
    void eliminarCancha();
};

#endif // CANCHAMANAGER_H_INCLUDED

