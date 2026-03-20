#include "ClienteManager.h"
#include "Validaciones.h"
#include "ConfiguracionMenu.h"
#include "rlutil.h"
#include "cargarCadena.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace rlutil;

ClienteManager::ClienteManager(const char* ruta) : archivo(ruta) {}

// ================== ALTA ==================

void ClienteManager::altaCliente()
{
    cls();
    int cols = getConsoleWidth();
    if (cols <= 0) cols = 120;

    int fila = 6;
    setColor(LIGHTCYAN);
    centrarTexto("ALTA DE CLIENTE", fila);
    fila += 2;
    centrarTexto("Ingrese DNI del cliente:", fila);
    fila += 2;

    int dni = pedirDni();

    Cliente nuevo;
    nuevo.idAutomatizado();
    nuevo.setDni(dni);

    nuevo.cargar();
    archivo.guardarCliente(nuevo);

    setColor(LIGHTGREEN);
    centrarTexto("Cliente registrado correctamente.", 18);
    setColor(LIGHTCYAN);
}

// ================== MODIFICAR ==================

void ClienteManager::modificarCliente()
{
    int id = pedirEntero("Ingrese el ID del cliente a modificar: ");
    if (!clienteExisteActivo(id))
    {
        setColor(RED);
        centrarTexto("No se encontro un cliente activo con ese ID.", 18);
        setColor(LIGHTCYAN);
        return;
    }

    int pos = archivo.buscarPorId(id);
    Cliente reg = archivo.leerRegistro(pos);

    const int anchoCaja = 42;
    const int altoCaja  = 8;

    while (true)
    {
        cls();

        int cols = getConsoleWidth();
        int rows = getConsoleHeight();

        // Posición de la tarjeta de cliente
        int cardX = (cols - (anchoCaja + 2)) / 2;
        if (cardX < 1) cardX = 1;
        int cardY = 3;

        // Dibujamos el cliente arriba
        reg.mostrar(cardX, cardY);

        // Fila donde empieza el título del menú (debajo de la tarjeta)
        int filaMenuTitulo = cardY + altoCaja + 2;

        vector<string> opciones
        {
            " Modificar Nombre ",
            " Modificar Apellido ",
            " Modificar Telefono ",
            " Modificar Email ",
            " Modificar Fecha de Alta ",
            " Guardar cambios ",
            " Cancelar "
        };

        // Menú que se dibuja DEBAJO del cuadro del cliente
        int opcion = menuConFlechasEnZona(opciones, "MODIFICAR CLIENTE", filaMenuTitulo);


        cls();
        switch (opcion)
        {
        case 0:     // Nombre
        {
            char nuevoNombre[20];
            cout << "NUEVO NOMBRE: ";
            cargarCadena(nuevoNombre, 20);
            reg.setNombre(nuevoNombre);
            setColor(LIGHTGREEN);
            centrarTexto("Nombre actualizado.", 18);
            setColor(LIGHTCYAN);
            anykey();
        }
        break;

        case 1:     // Apellido
        {
            char nuevoApellido[20];
            cout << "NUEVO APELLIDO: ";
            cargarCadena(nuevoApellido, 20);
            reg.setApellido(nuevoApellido);
            setColor(LIGHTGREEN);
            centrarTexto("Apellido actualizado.", 18);
            setColor(LIGHTCYAN);
            anykey();
        }
        break;

        case 2:     // Telefono
        {
            char nuevoTel[20];
            cout << "NUEVO TELEFONO: ";
            cargarCadena(nuevoTel, 20);
            reg.setTelefono(nuevoTel);
            setColor(LIGHTGREEN);
            centrarTexto("Telefono actualizado.", 18);
            setColor(LIGHTCYAN);
            anykey();
        }
        break;

        case 3:     // Email
        {
            char nuevoEmail[50];
            pedirEmailValido("NUEVO EMAIL: ", nuevoEmail, 50);
            reg.setEmail(nuevoEmail);
            setColor(LIGHTGREEN);
            centrarTexto("Email actualizado.", 18);
            setColor(LIGHTCYAN);
            anykey();
        }
        break;

        case 4:     // Fecha de alta
        {
            Fecha f;
            centrarTexto("NUEVA FECHA DE ALTA:", 10);
            cout << "\n";
            f.Cargar();
            reg.setFechaAlta(f);
            setColor(LIGHTGREEN);
            centrarTexto("Fecha de alta actualizada.", 18);
            setColor(LIGHTCYAN);
            anykey();
        }
        break;

        case 5:     // Guardar cambios
        {
            reg.setIdCliente(id);  // por las dudas
            archivo.modificarCliente(id, reg);

            setColor(LIGHTGREEN);
            centrarTexto("Cliente modificado correctamente.", 18);
            setColor(LIGHTCYAN);
            anykey();
            return;
        }

        case 6:     // Cancelar
            setColor(RED);
            centrarTexto("Modificacion cancelada. No se guardaron cambios.", 18);
            setColor(LIGHTCYAN);
            anykey();
            return;
        }
        // al terminar el switch, vuelve al while: se redibuja tarjeta + menú
    }
}

// ================== ELIMINAR (BAJA LÓGICA) ==================

void ClienteManager::eliminarCliente()
{
    int id = pedirEntero("Ingrese el ID del cliente a eliminar: ");
    if (!clienteExisteActivo(id))
    {
        setColor(RED);
        centrarTexto("No se encontro un cliente activo con ese ID.", 18);
        setColor(LIGHTCYAN);
        return;
    }

    archivo.eliminarCliente(id);

    setColor(LIGHTGREEN);
    centrarTexto("Cliente eliminado correctamente.", 18);
    setColor(LIGHTCYAN);
}

// ================== BUSCAR POR ID ==================

void ClienteManager::buscarPorId()
{
    int id = pedirEntero("Ingrese ID: ");
    if (!clienteExisteActivo(id))
    {
        setColor(RED);
        centrarTexto("No se encontro un cliente activo con ese ID.", 18);
        setColor(LIGHTCYAN);
        return;
    }

    archivo.mostrarClientePorId(id);
}

// ================== BUSCAR POR DNI ==================

void ClienteManager::buscarPorDni()
{
    int dni = pedirEntero("Ingrese DNI: ");
    int pos = archivo.buscarPorDni(dni);

    if (pos < 0)
    {
        setColor(RED);
        centrarTexto("No se encontro un cliente con ese DNI.", 18);
        setColor(LIGHTCYAN);
    }
    else
    {
        Cliente reg = archivo.leerRegistro(pos);
        if (reg.getActivo())
        {
            int cols = getConsoleWidth();
            int rows = getConsoleHeight();

            int baseX = (cols - (42 + 2)) / 2;
            int baseY = (rows - 8) / 2;
            if (baseX < 1) baseX = 1;
            if (baseY < 1) baseY = 1;

            cls();
            reg.mostrar(baseX, baseY);
        }
        else
        {
            setColor(RED);
            centrarTexto("El cliente con ese DNI no esta activo.", 18);
            setColor(LIGHTCYAN);
        }
    }
}


// ================== LISTAR TODOS ==================

void ClienteManager::listarClientes()
{
    archivo.mostrarClientes();
}

// ================== RECUPERAR CLIENTE ==================

void ClienteManager::recuperarCliente()
{
    int id = pedirEntero("Ingrese el ID del CLIENTE que desea recuperar: ");
    if (archivo.recuperarCliente(id))
    {
        setColor(LIGHTGREEN);
        centrarTexto("Cliente recuperado correctamente.", 18);
    }
    else
    {
        setColor(RED);
        centrarTexto("No se pudo recuperar el cliente.", 18);
    }
    setColor(LIGHTCYAN);
}


bool ClienteManager::clienteExisteActivo(int idCliente)
{
    return archivo.existeClientePorID(idCliente);
}

