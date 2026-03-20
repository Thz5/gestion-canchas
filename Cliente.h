#ifndef CLIENTE_H_INCLUDED
#define CLIENTE_H_INCLUDED

#include "Fecha.h"

class Cliente
{
private:
    int idCliente;
    int dni;
    char nombre [20];
    char apellido [20];
    char telefono [20];
    char email [50];
    bool activo;
    Fecha fechaAlta;

public:
    Cliente();

    // SETTERS

    void setIdCliente(int ID);
    void setDni(int dni);
    void setNombre(const char *n);
    void setApellido(const char *a);
    void setTelefono(const char *tel);
    void setEmail(const char *e);
    void setActivo(bool a);
    void setFechaAlta(Fecha f);


    // GETTERS

    int getIdCliente();
    int getDni();
    const char *getNombre();
    const char *getApellido();
    const char *getTelefono();
    const char *getEmail();
    bool getActivo();
    Fecha getFechaAlta();

    // OTROS MÉTODOS
    void idAutomatizado();
    void cargar();
   void mostrar(int baseX, int baseY);
};
#endif // CLIENTE_H_INCLUDED
