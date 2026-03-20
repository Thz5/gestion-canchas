// Validaciones.cpp  - versión simple PROG1
#include "Validaciones.h"
#include "ClienteArchivo.h"
#include "Alquiler.h"
#include "Cancha.h"
#include "SistemaArchivos.h"
#include "cargarCadena.h"
#include "Fecha.h"
#include "rlutil.h"
#include "ConfiguracionMenu.h"
#include <iostream>
#include <cstring>
#include <cctype>
#include <vector>
#include <cmath>

using namespace std;
using namespace rlutil;

// ------------------ pedirEntero (simple) ------------------
int pedirEntero(const char* mensaje, int minVal, int maxVal)
{
    int valor;

    while (true)
    {
        cls();

        int cols = getConsoleWidth();
        if (cols <= 0) cols = 120;

        int fila = 10;
        setColor(LIGHTCYAN);
        centrarTexto(mensaje, fila);
        fila += 2;

        string prompt = ">> ";
        int x = (cols - (int)prompt.size() - 5) / 2; // un pequeño margen
        if (x < 1) x = 1;

        locate(x, fila);
        cout << prompt;

        if (!(cin >> valor))
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

        if (valor < minVal || valor > maxVal)
        {
            fila += 2;
            setColor(RED);
            centrarTexto("ERROR: numero fuera de rango.", fila);
            fila += 1;
            centrarTexto(
                "Rango permitido: " + to_string(minVal) + " - " + to_string(maxVal),
                fila
            );
            setColor(LIGHTCYAN);
            anykey();
            continue;
        }

        return valor;
    }
}

// ------------------ pedirDni ------------------
int pedirDni()
{
    return pedirEntero("Ingrese DNI (solo números):", 0, 99999999);
}


// ================================
// VALIDAR EMAIL
// ================================
bool esEmailValido(const char *email)
{
    int len = strlen(email);
    if (len < 5) return false;

    int cantArrobas = 0;
    int posArroba = -1;

    for (int i = 0; i < len; i++)
    {
        char c = email[i];
        if (c == ' ') return false;
        if (c == '@')
        {
            cantArrobas++;
            posArroba = i;
        }
    }

    if (cantArrobas != 1) return false;
    if (posArroba == 0) return false;           // nada antes del @
    if (posArroba >= len - 3) return false;     // casi nada después del @

    bool hayPunto = false;
    for (int i = posArroba + 1; i < len; i++)
    {
        if (email[i] == '.')
        {
            hayPunto = true;
            break;
        }
    }

    return hayPunto;
}

void pedirEmailValido(const char* mensaje, char* destino, int tam)
{
    while (true)
    {
        cout << mensaje;
        cargarCadena(destino, tam);

        if (esEmailValido(destino)) return;

        cout << "\nERROR: email invalido.\n";
        anykey();
        cls();
    }
}


// ================================
// VALIDAR FECHA (día/mes/año)
// ================================
bool esFechaValida(int dia, int mes, int anio)
{
    // Rango razonable de años "en general"
    if (anio < 2000 || anio > 2100) return false;

    if (mes < 1 || mes > 12) return false;

    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    // Año bisiesto
    bool bisiesto = ( (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0) );
    if (bisiesto) diasMes[1] = 29;

    if (dia < 1 || dia > diasMes[mes - 1]) return false;

    return true;
}

// ================================
// PEDIR FECHA VALIDA USANDO Fecha
// ================================
Fecha pedirFechaValida(const string& mensaje)
{
    int d, m, a;

    while (true)
    {
        cls();
        cout << mensaje << " (DD MM AAAA)\n";
        cout << ">> ";

        if (!(cin >> d >> m >> a))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nERROR: debe ingresar numeros.\n";
            cout << "Presione una tecla para continuar...";
            anykey();
            continue;
        }

        cin.ignore(1000, '\n');

        if (!esFechaValida(d, m, a))
        {
            cout << "\nERROR: fecha invalida.\n";
            cout << "Presione una tecla para continuar...";
            anykey();
            continue;
        }

        Fecha f;
        f.setDia(d);
        f.setMes(m);
        f.setAnio(a);
        return f;
    }
}
