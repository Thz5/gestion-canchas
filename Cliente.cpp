#include "Cliente.h"
#include "ClienteArchivo.h"
#include "ConfiguracionMenu.h"
#include "Validaciones.h"
#include "cargarCadena.h"
#include <iomanip>
#include <cstring>
#include <iostream>

using namespace std;
using namespace rlutil;

Cliente::Cliente()
{
    activo = true;
}

void Cliente::setIdCliente(int ID)
{
    idCliente = ID;
}

void Cliente::setDni(int DNI)
{
    dni = DNI;
}

void Cliente::setNombre(const char *nom)
{
    strcpy(nombre, nom);
}

void Cliente::setApellido(const char *ape)
{
    strcpy(apellido, ape);
}

void Cliente::setTelefono(const char *tel)
{
    strcpy(telefono, tel);
}

void Cliente::setEmail(const char *ema)
{
    strcpy(email, ema);
}

void Cliente::setActivo(bool a)
{
    activo = a;
}

void Cliente::setFechaAlta(Fecha f)
{
    fechaAlta = f;
}

int Cliente::getIdCliente()
{
    return idCliente;
}

int Cliente::getDni()
{
    return dni;
}

const char *Cliente::getNombre()
{
    return nombre;
}

const char *Cliente::getApellido()
{
    return apellido;
}

const char *Cliente::getTelefono()
{
    return telefono;
}

const char *Cliente::getEmail()
{
    return email;
}

void Cliente::idAutomatizado()
{
    if (idCliente <=0)
    {
        idCliente=1;
    }
    // calcular ID automáticamente
    ClienteArchivo arch("Clientes.dat");
    idCliente = arch.cantidadRegistros() + 1;  // próximo ID

}

bool Cliente::getActivo()
{
    return activo;
}

Fecha Cliente::getFechaAlta()
{
    return fechaAlta;
}

void Cliente::cargar()
{
    cls();

    int cols = getConsoleWidth();
    if (cols <= 0) cols = 120;

    int fila = 6;

    setColor(LIGHTCYAN);
    centrarTexto("REGISTRO DE CLIENTE", fila);
    fila += 2;


    auto pedirCampo = [&](const string& etiqueta, char* destino, int tam)
    {
        string label = etiqueta + ": ";
        int anchoEstimado = tam + 2;              // “espacio” para escribir
        int total = (int)label.size() + anchoEstimado;

        int x = (cols - total) / 2;
        if (x < 1) x = 1;

        locate(x, fila);
        cout << label;
        locate(x + (int)label.size(), fila);
        cargarCadena(destino, tam);

        fila += 2;
    };

    // Campos centrados
    pedirCampo("NOMBRE",   nombre,   20);
    pedirCampo("APELLIDO", apellido, 20);
    pedirCampo("TELEFONO", telefono, 20);

    {
        string label = "EMAIL: ";
        int anchoEstimado = 30;
        int total = (int)label.size() + anchoEstimado;

        int x = (cols - total) / 2;
        if (x < 1) x = 1;

        locate(x, fila);
        // pedirEmailValido escribe a partir de donde esté el cursor
        pedirEmailValido(label.c_str(), email, 50);
        fila += 2;
    }

    fechaAlta.Cargar();

    activo = true;
}

void Cliente::mostrar(int baseX, int baseY)
{
    const int ancho = 42;
    const int boxH  = 9;

    if (baseX < 1) baseX = 1;
    if (baseY < 1) baseY = 1;


    gotoxy(baseX, baseY);
    cout << char(201);
    for (int i = 0; i < ancho; i++)
        cout << char(205);
    cout << char(187);


    auto printLeftRight = [&](int lineIndex, const string& etiqueta, const string& valorIn)
    {
        string valor = valorIn;
        int innerW = ancho;

        string left = etiqueta + " ";
        string right = valor;

        if ((int)left.size() > innerW)
        {
            left  = left.substr(0, innerW);
            right = "";
        }
        else
        {
            int espacioValor = innerW - (int)left.size();
            if ((int)right.size() > espacioValor)
                right = right.substr(0, espacioValor);
        }

        int pad = innerW - (int)left.size() - (int)right.size();
        if (pad < 0) pad = 0;

        gotoxy(baseX, baseY + 1 + lineIndex);
        cout << char(186);

        cout << left;
        for (int s = 0; s < pad; s++) cout << ' ';
        cout << right;


        int totalLen = (int)left.size() + pad + (int)right.size();
        for (int s = totalLen; s < innerW; s++) cout << ' ';

        cout << char(186);
    };

    // --------- CARGAR CAMPOS ---------
    char buf[64];

    sprintf(buf, "%d", getIdCliente());
    printLeftRight(0, "ID Cliente:", string(buf));

    sprintf(buf, "%d", getDni());
    printLeftRight(1, "DNI:", string(buf));

    Fecha f = getFechaAlta();

    sprintf(buf, "%02d/%02d/%04d", f.getDia(),f.getMes(),f.getAnio());
    printLeftRight(2, "Fecha de Registro:", string(buf));

    printLeftRight(3, "Nombre:",  string(getNombre()));

    printLeftRight(4, "Apellido:", string(getApellido()));

    printLeftRight(5, "Telefono:", string(getTelefono()));

    printLeftRight(6, "Email:",    string(getEmail()));

    // --------- BORDE INFERIOR ---------
    gotoxy(baseX, baseY + boxH - 1);
    cout << char(200);                // └
    for (int i = 0; i < ancho; i++)
        cout << char(205);            // ─
    cout << char(188);                // ┘
}
