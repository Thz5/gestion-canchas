#ifndef ALQUILER_H_INCLUDED
#define ALQUILER_H_INCLUDED
#include "Cliente.h"
#include "Cancha.h"
#include "Fecha.h"



class Alquiler {
private:
    int idCliente;       // relaci¢n con la clase Cliente
    int idCancha;        // relaci¢n con la clase Cancha
    char metodoPago[30];
    int senia;
    float montoPago;
    float montoRestante;
    bool estadoPago = false;
    Fecha fechaAlquiler;
    int hora;
    int duracionHoras;

public:
    // SETTERS
    void setIdCliente(int);
    void setIdCancha(int);
    void setMetodoPago();
    void setSenia(float);
    void setMontoPago(float);
    void setMontoRestante(float);
    void setEstadoPago(bool);
    void setFechaAlquiler(Fecha);
    void setHora(int hs);
    void setDuracionHoras(int d);

    // GETTERS
    int getIdCliente();
    int getIdCancha();
    const char* getMetodoPago();
    float getSenia();
    float getMontoPago();
    float getMontoRestante();
    bool getEstadoPago();
    Fecha getFechaAlquiler();
    int getHora();
    int getDuracionHoras() const;


    // OTROS MêTODOS
    void cargar();
    void mostrar(int, int);
};

#endif // ALQUILER_H_INCLUDED
