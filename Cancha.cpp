#include "Cancha.h"
#include "CanchaArchivo.h"
#include "ConfiguracionMenu.h"
#include "Validaciones.h"
#include <iomanip>
#include <iostream>
#include <cstring>
#include <limits>

using namespace std;
using namespace rlutil;

void Cancha::setIdCancha(int id)
{
    idCancha = id;
}

void Cancha::setTipo(const char *tam)
{
    strcpy (tipo, tam);
}


void Cancha::setActivo(bool a)
{
    activo = a;
}

void Cancha::seleccionarTamanio()
{
    cls();
    vector<string> opciones
    {
        "Cancha de 5",
        "Cancha de 6",
        "Cancha de 7",
        "Cancha de 11"
    };

    cout << "Seleccione el tama"<< char (164)<<"o"<<endl;

    int opciontam = menuConFlechas(opciones, "Seleccione el Tamanio");
    switch (opciontam)
    {
    case 0:
        tamanio=5;
        break;
    case 1:
        tamanio=6;
        break;
    case 2:
        tamanio=7;
        break;
    case 3:
        tamanio=11;
        break;

    default:
        cls();
        setColor(RED);
        centrarTexto("ERROR: OPCION INVALIDA.\n",15);
        setColor(LIGHTCYAN);
        anykey();
        break;
    }
}
void Cancha::seleccionarTipo()
{
    vector<string> opciones
    {
        " CESPED SINTETICO ",
        " CESPED NATURAL ",
        " PISO "
    };
    int opcion = menuConFlechas(opciones, "Seleccione el tipo de cancha:");

    switch (opcion)
    {
    case 0:
        strcpy(tipo, "Cesped sintetico");
        break;
    case 1:
        strcpy(tipo, "Cesped natural");
        break;
    case 2:
        strcpy(tipo, "Piso");
        break;
    default:
        cls();
        setColor(RED);
        centrarTexto("ERROR: OPCION INVALIDA.\n", 15);
        setColor(LIGHTCYAN);
        anykey();
        break;
    }
}

float Cancha::getPrecioHora() const
{
    return precioHora;
}

int Cancha::getIdCancha() const
{
    return idCancha;
}

const char *Cancha::getTipo() const
{
    return tipo;
}

int Cancha::getTamanio() const
{
    return tamanio;
}

bool Cancha::getActivo() const
{
    return activo;
}
void Cancha::idAutomatizado()
{
    CanchaArchivo arch("Canchas.dat");
    idCancha = arch.cantidadRegistros() + 1;
}

void Cancha::cargar()
{
    seleccionarTipo();
    seleccionarTamanio();
    cls();
    precioHora = pedirEntero("Ingrese el precio por hora:", 1, 1000000);
}
void Cancha::mostrar(int baseX, int baseY)
{
    const int ancho = 42;
    const int boxH  = 6;
    if (baseX < 1) baseX = 1;
    if (baseY < 1) baseY = 1;


    gotoxy(baseX, baseY);
    cout << char(201);
    for (int i = 0; i < ancho; ++i) cout << char(205);
    cout << char(187);


    auto printLeftRight = [&](int lineIndex, const string& etiqueta, const string& valor)
    {
        int innerW = ancho;
        string left = etiqueta + " ";
        string right = valor;
        if ((int)left.size() > innerW)
        {
            left = left.substr(0, innerW);
            right = "";
        }
        else
        {
            int espacioParaValor = innerW - (int)left.size();
            if ((int)right.size() > espacioParaValor) right = right.substr(0, espacioParaValor);
        }


        int pad = innerW - (int)left.size() - (int)right.size();
        if (pad < 0) pad = 0;

        gotoxy(baseX, baseY + 1 + lineIndex);
        cout << char(186);


        cout << left;
        for (int s = 0; s < pad; ++s) cout << ' ';
        cout << right;


        for (int s = (int)left.size() + pad + (int)right.size(); s < innerW; ++s) cout << ' ';

        cout << char(186);
    };


    char buf[64];

    sprintf(buf, "%d", getIdCancha());
    printLeftRight(0, "ID:", string(buf));

    printLeftRight(1, "Cancha:", string(getTipo()));

    sprintf(buf, "%d", getTamanio());
    printLeftRight(2, "De:", string(buf));

    sprintf(buf, "$%.0f", getPrecioHora());
    printLeftRight(3, "Precio:", string(buf));


    gotoxy(baseX, baseY + boxH - 1);
    cout << char(200);
    for (int i = 0; i < ancho; ++i) cout << char(205);
    cout << char(188);


}
