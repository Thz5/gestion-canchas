#ifndef CLIENTEMANAGER_H_INCLUDED
#define CLIENTEMANAGER_H_INCLUDED

#include "ClienteArchivo.h"
#include "Cliente.h"

class ClienteManager {
private:
    ClienteArchivo archivo;
    bool clienteExisteActivo(int idCliente);

public:
    ClienteManager(const char* ruta = "Clientes.dat");

    void altaCliente();
    void modificarCliente();
    void eliminarCliente();
    void buscarPorId();
    void buscarPorDni();
    void listarClientes();
    void recuperarCliente();
};

#endif // CLIENTEMANAGER_H_INCLUDED
