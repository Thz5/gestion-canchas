#include "Fecha.h"
#include "Validaciones.h"
#include "ConfiguracionMenu.h"
#include <iostream>

using namespace std;
using namespace rlutil;

void Fecha::setDia(int d)
{
    dia = d;
}

void Fecha::setMes(int m)
{
    mes = m;
}
void Fecha::setAnio(int a)
{
    anio = a;
}

int Fecha::getDia()const{
    return dia;
}
int Fecha::getMes()const{
    return mes;
}
int Fecha::getAnio()const{
    return anio;
}
void Fecha::Cargar()
{
    while (true)
    {
        cls();
        setColor(LIGHTCYAN);

        centrarTexto("INGRESO DE FECHA", 12);
        centrarTexto("-----------------", 13);

        // DIA
        centrarTexto("DIA (1 - 31): ", 15);
        cin >> dia;

        // MES
        centrarTexto("MES (1 - 12): ", 16);
        cin >> mes;

        // ANIO
        // Mostramos "AÑO (AAAA): " usando la Ñ con el código 165
        locate(1, 17);
        int cols = getConsoleWidth();
        string etiqueta = "A";
        etiqueta.push_back(char(165));  // Ñ
        etiqueta += "O (AAAA): ";

        int x = (cols - (int)etiqueta.size()) / 2;
        if (x < 1) x = 1;
        locate(x, 17);
        cout << etiqueta;
        cin >> anio;


        if (esFechaValida(dia, mes, anio))
        {
            return;
        }

        centrarTexto("FECHA INVALIDA. INTENTE NUEVAMENTE.", 19);
        anykey();
    }
}

void Fecha::Mostrar(){
    cout<<dia<<"/"<<mes<<"/"<<anio <<endl;
}
