#include "Alquiler.h"
#include "Cancha.h"
#include "ConfiguracionMenu.h"
#include "Validaciones.h"
#include <cstring>
#include <iostream>
#include <limits>
#include "rlutil.h"

using namespace rlutil;
using namespace std;

void Alquiler::setMetodoPago()
{
    vector<string> opciones
    {
        " Efectivo ",
        " Transferencia ",
        " Debito ",
        " Credito "
    };

    int opcion = menuConFlechas(opciones, "SELECCIONE EL METODO DE PAGO");

    cls();

    switch (opcion)
    {
    case 0:
        strcpy(metodoPago, "Efectivo");
        break;
    case 1:
        strcpy(metodoPago, "Transferencia");
        break;
    case 2:
        strcpy(metodoPago, "Debito");
        break;
    case 3:
        strcpy(metodoPago, "Credito");
        break;
    default:
        strcpy(metodoPago, "Efectivo");
        break;
    }
}
void Alquiler::setSenia(float sn)
{
    senia = sn;
}

void Alquiler::setMontoPago(float MonP)
{
    montoPago = MonP;
}

void Alquiler::setMontoRestante(float MontR)
{
    montoRestante = MontR;
}

void Alquiler::setEstadoPago(bool EstP)
{
    estadoPago = EstP;
}

void Alquiler::setFechaAlquiler(Fecha FI)
{
    fechaAlquiler = FI;
}

void Alquiler::setHora(int hs)
{
    hora = hs;
}

void Alquiler::setIdCancha(int id)
{
    idCancha = id;
}

void Alquiler::setIdCliente(int id)
{
    idCliente = id;
}

void Alquiler::setDuracionHoras(int d)
{
    duracionHoras = d;
}

const char* Alquiler::getMetodoPago()
{
    return metodoPago;
}

float Alquiler::getSenia()
{
    return senia;
}

float Alquiler::getMontoPago()
{
    return montoPago;
}

bool Alquiler::getEstadoPago()
{
    return estadoPago;
}

Fecha Alquiler::getFechaAlquiler()
{
    return fechaAlquiler;
}
float Alquiler::getMontoRestante()
{
    return montoRestante;
}

int Alquiler::getHora()
{
    return hora;
}
int Alquiler::getIdCancha()
{
    return idCancha;
}

int Alquiler::getIdCliente()
{
    return idCliente;
}
int Alquiler::getDuracionHoras() const
{
    return duracionHoras;
}
void Alquiler::cargar()
{
    // Seleccion del metodo de pago
    setMetodoPago();

    centrarTexto("Se",13);
    cout<< char(164) <<"a: " << endl;


    senia = pedirEntero("Ingrese la seña (valor numerico): ", 0, 1000000);

    estadoPago = false;
}

void Alquiler::mostrar(int baseX, int baseY)
{
    const int ancho = 42;
    const int boxH  = 11;

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

    sprintf(buf, "%d", getIdCliente());
    printLeftRight(0, "ID Cliente:", string(buf));

    sprintf(buf, "%d", getIdCancha());
    printLeftRight(1, "ID Cancha:", string(buf));
    Fecha f = getFechaAlquiler();

    sprintf(buf, "%02d/%02d/%04d", f.getDia(), f.getMes(), f.getAnio());
    printLeftRight(2, "Fecha:", string(buf));


    printLeftRight(3, "Metodo de Pago:", string(metodoPago));

    sprintf(buf, "$%.0f", getSenia());
    printLeftRight(4, "Se¤a:", string(buf));

    sprintf(buf, "$%.0f", getMontoPago());
    printLeftRight(5, "Monto Total:", string(buf));

    sprintf(buf, "$%.0f", getMontoRestante());
    printLeftRight(6, "Restante a pagar:", string(buf));

    printLeftRight(7, "Estado de Pago:", getEstadoPago() ? "Pagado" : "Pendiente");

    int horaInicio = getHora();
    int horaFin    = horaInicio + getDuracionHoras();

    sprintf(buf, "%d:00 a %d:00", horaInicio, horaFin);
    printLeftRight(8, "Horario:", string(buf));


    gotoxy(baseX, baseY + boxH - 1);
    cout << char(200);
    for (int i = 0; i < ancho; ++i) cout << char(205);
    cout << char(188);


}


