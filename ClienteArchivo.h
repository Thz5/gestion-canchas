#ifndef CLIENTEARCHIVO_H_INCLUDED
#define CLIENTEARCHIVO_H_INCLUDED

#include "Cliente.h"

class ClienteArchivo {
private:
    const char* rutaArchivo;

public:
    ClienteArchivo(const char* ruta = "Clientes.dat");

    void guardarCliente(const Cliente &obj);
    void mostrarClientes();
    bool modificarCliente(int idBuscado, const Cliente& nuevo);
    bool eliminarCliente(int idBuscado);
    int cantidadRegistros();
    bool recuperarCliente(int idBuscado);

    int buscarPorId(int idBuscado);
    Cliente leerRegistro(int pos);

    int buscarPorDni(int dniBuscado);
    void mostrarClientePorId(int idBuscado);
    bool dniExiste(int dniBuscado);
    bool existeClientePorID(int idBuscado);

};
#endif // CLIENTEARCHIVO_H_INCLUDED
