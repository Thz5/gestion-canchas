#include "AlquilerCliente.h"
#include "ClienteArchivo.h"
#include "ConfiguracionMenu.h"
#include <iostream>
using namespace std;
using namespace rlutil;

int pedirClienteValido()
{
    ClienteArchivo archivoClientes("Clientes.dat");
    int idCliente;

    while (true)
    {
        cls();

        int cols = getConsoleWidth();
        if (cols <= 0) cols = 120;

        int fila = 8;

        setColor(LIGHTCYAN);
        centrarTexto("=== SELECCION DE CLIENTE PARA ALQUILER ===", fila);
        fila += 2;


        string label = "Ingrese ID del cliente: ";
        int total = (int)label.size() + 6;

        int x = (cols - total) / 2;
        if (x < 1) x = 1;

        locate(x, fila);
        cout << label;
        locate(x + (int)label.size(), fila);
        cin >> idCliente;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            fila += 2;
            setColor(RED);
            centrarTexto("ERROR: debe ingresar un numero.", fila);
            setColor(LIGHTCYAN);
            anykey();
            continue;
        }
        cin.ignore(1000, '\n');

        if (archivoClientes.existeClientePorID(idCliente))
            return idCliente;

        fila += 2;
        setColor(RED);
        centrarTexto("ERROR: no existe un cliente activo con ese ID.", fila);
        setColor(LIGHTCYAN);
        anykey();
    }
}

