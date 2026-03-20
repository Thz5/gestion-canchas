#ifndef CANCHA_H_INCLUDED
#define CANCHA_H_INCLUDED

#include "Cliente.h"

class Cancha {
private:
    int idCancha;
    char tipo[20];
    int tamanio;
    float precioHora;
    bool activo = true;

public:
    Cancha() { activo = true; }

    // SETTERS
    void setIdCancha(int id);
    void setTipo(const char *tipoDeCancha);
    void setPrecioHora(float p);
    void setTamanio ();
    void setActivo(bool a);
    void seleccionarTamanio();
    void seleccionarTipo();

    //GETTERS
    int getIdCancha() const;
    const char* getTipo() const;
    float getPrecioHora() const;
    int getTamanio() const;
    bool getActivo() const;

    // OTROS MÉTODOS
    void cargar();
    void mostrar(int, int);
    void idAutomatizado();
};

#endif // CANCHA_H_INCLUDED

