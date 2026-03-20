#include "AlquilerHorario.h"
#include "SistemaArchivos.h"
#include "ConfiguracionMenu.h"
#include "Validaciones.h"
#include "rlutil.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace rlutil;

// -------------------------
//   MARCAR HORAS OCUPADAS
// -------------------------
void marcarHorasOcupadas(const Cancha &cancha, const Fecha &fecha, bool ocupados[24])
{
    for (int i = 0; i < 24; i++) ocupados[i] = false;

    SistemaArchivos arch("Alquileres.dat");
    int cant = arch.CantidadRegistros();

    for (int i = 0; i < cant; i++)
    {
        Alquiler a = arch.leerRegistro(i);

        if (a.getIdCancha() != cancha.getIdCancha()) continue;

        Fecha fa = a.getFechaAlquiler();
        if (fa.getDia() == fecha.getDia() &&
                fa.getMes() == fecha.getMes() &&
                fa.getAnio() == fecha.getAnio())
        {
            int hi = a.getHora();
            int dur = a.getDuracionHoras();

            for (int h = hi; h < hi + dur && h < 24; h++)
                ocupados[h] = true;
        }
    }
}

// -----------------------------------------
//   MOSTRAR HORARIOS DISPONIBLES + SELECCIÓN
// -----------------------------------------
bool mostrarHorariosDisponiblesYSeleccionar(const Cancha &cancha,
        const Fecha &fecha,
        int &horaSalida)
{
    bool ocupados[24];
    marcarHorasOcupadas(cancha, fecha, ocupados);

    vector<int> horas;
    vector<bool> libres;

    // usamos horarios de 8 a 23
    for (int h = 8; h <= 23; h++)
    {
        horas.push_back(h);
        libres.push_back(!ocupados[h]);
    }

    bool hayLibre = false;
    for (bool x : libres) if (x) hayLibre = true;

    if (!hayLibre)
    {
        cls();
        setColor(RED);
        centrarTexto("No hay horarios disponibles en esta fecha.", 15);
        setColor(LIGHTCYAN);
        anykey();
        return false;
    }

    // configuración de la grilla de cuadritos
    const int innerW   = 10;   // ancho interior de cada caja
    const int boxW     = innerW; // cantidad de '─' (205)
    const int boxH     = 3;    // borde sup, contenido, borde inf
    const int gridCols = 4;    // columnas en la grilla
    const int gapX     = 4;    // espacios horizontales entre cajas
    const int gapY     = 1;    // espacios verticales entre cajas

    int colsPant = getConsoleWidth();
    int rowsPant = getConsoleHeight();
    if (colsPant <= 0) colsPant = 120;
    if (rowsPant <= 0) rowsPant = 30;

    int totalGridW = gridCols * (boxW + 2) + (gridCols - 1) * gapX;
    int startX = (colsPant - totalGridW) / 2;
    if (startX < 1) startX = 1;

    int startY = 6;

    int sel = 0;
    while (sel < (int)libres.size() && !libres[sel]) sel++;

    while (true)
    {
        cls();

        // título y fecha centrados
        setColor(LIGHTCYAN);
        centrarTexto("=== HORARIOS DISPONIBLES ===", 2);

        char bufFecha[64];
        sprintf(bufFecha, "Fecha: %02d/%02d/%04d",
                fecha.getDia(), fecha.getMes(), fecha.getAnio());
        centrarTexto(bufFecha, 4);

        centrarTexto("Use FLECHAS para elegir, ENTER para confirmar.",
                     rowsPant - 2);

        // dibujar todas las cajas
        for (int i = 0; i < (int)horas.size(); i++)
        {
            int col = i % gridCols;
            int row = i / gridCols;

            int x = startX + col * ((boxW + 2) + gapX);
            int y = startY + row * (boxH + gapY);

            bool disponible = libres[i];
            bool seleccionado = (i == sel);

            // elegir color según estado
            if (!disponible)
                setColor(RED);
            else if (seleccionado)
                setColor(YELLOW);
            else
                setColor(LIGHTCYAN);

            char etiqueta[32];
            sprintf(etiqueta, "%02d:00", horas[i]);

            string contenido = etiqueta;

            if (!disponible)
                contenido += " X";

            if ((int)contenido.size() > innerW)
                contenido = contenido.substr(0, innerW);

            int espaciosTotales = innerW - (int)contenido.size();
            int leftPad  = espaciosTotales / 2;
            int rightPad = espaciosTotales - leftPad;

            // ┌──────────┐
            gotoxy(x, y);
            cout << char(201);
            for (int k = 0; k < boxW; k++) cout << char(205);
            cout << char(187);

            // │ 08:00 X  │
            gotoxy(x, y + 1);
            cout << char(186);
            for (int k = 0; k < leftPad; k++) cout << ' ';
            cout << contenido;
            for (int k = 0; k < rightPad; k++) cout << ' ';
            cout << char(186);

            // └──────────┘
            gotoxy(x, y + 2);
            cout << char(200);
            for (int k = 0; k < boxW; k++) cout << char(205);
            cout << char(188);
        }

        int k = getkey();

        if (k == KEY_UP || k == KEY_LEFT)
        {
            int i = sel;
            do
            {
                i--;
                if (i < 0) i = (int)horas.size() - 1;
            }
            while (!libres[i]);
            sel = i;
        }
        else if (k == KEY_DOWN || k == KEY_RIGHT)
        {
            int i = sel;
            do
            {
                i++;
                if (i >= (int)horas.size()) i = 0;
            }
            while (!libres[i]);
            sel = i;
        }
        else if (k == KEY_ENTER)
        {
            horaSalida = horas[sel];
            return true;
        }
        else if (k == KEY_ESCAPE)
        {
            return false;
        }
    }
}

// ----------------------
//   PEDIR DURACIÓN
// ----------------------
bool pedirDuracionHoras(const Cancha &cancha,
                        const Fecha &fecha,
                        int horaInicio,
                        int &durOut)
{
    bool ocupados[24];
    marcarHorasOcupadas(cancha, fecha, ocupados);

    if (horaInicio < 8 || horaInicio > 23)
    {
        cls();
        setColor(RED);
        centrarTexto("ERROR: la hora de inicio debe estar entre 08:00 y 23:00.", 10);
        setColor(LIGHTCYAN);
        anykey();
        return false;
    }

    while (true)
    {
        cls();

        int cols = getConsoleWidth();
        if (cols <= 0) cols = 120;

        int fila = 8;

        setColor(LIGHTCYAN);
        centrarTexto("=== DURACION DEL ALQUILER ===", fila);
        fila += 2;

        // Info de contexto: fecha y hora elegida
        string infoFecha = "Fecha: " +
                           to_string(fecha.getDia()) + "/" +
                           to_string(fecha.getMes()) + "/" +
                           to_string(fecha.getAnio());
        centrarTexto(infoFecha, fila);
        fila++;

        string infoHora = "Hora de inicio: " + to_string(horaInicio) + ":00";
        centrarTexto(infoHora, fila);
        fila++;

        int durMax = 24 - horaInicio;

        string infoRec = "Recuerde: el ultimo alquiler permitido es de 23:00 a 00:00.";
        centrarTexto(infoRec, fila);
        fila++;

        string infoMax = "Duracion maxima para esta hora: " + to_string(durMax) + " hora(s).";
        centrarTexto(infoMax, fila);
        fila += 2;

        // Texto centrado para pedir la duracion
        string label = "Ingrese duracion (en horas): ";
        int total = (int)label.size() + 4;  // espacio para escribir
        int x = (cols - total) / 2;
        if (x < 1) x = 1;

        locate(x, fila);
        cout << label;
        locate(x + (int)label.size(), fila);
        cin >> durOut;

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

        if (durOut <= 0)
        {
            fila += 2;
            setColor(RED);
            centrarTexto("ERROR: la duracion debe ser mayor que 0.", fila);
            setColor(LIGHTCYAN);
            anykey();
            continue;
        }

        int horaFin = horaInicio + durOut;

        // No pasar de las 00:00
        if (horaFin > 24)
        {
            fila += 2;
            setColor(RED);
            centrarTexto("ERROR: el alquiler no puede superar las 00:00 hs.", fila);
            fila++;
            string msgMax = "Para empezar a las " + to_string(horaInicio) +
                            ":00, la duracion maxima es de " + to_string(24 - horaInicio) +
                            " hora(s).";
            centrarTexto(msgMax, fila);
            setColor(LIGHTCYAN);
            anykey();
            continue;
        }

        // Verificar superposicion con otros alquileres
        bool ok = true;
        for (int h = horaInicio; h < horaFin; h++)
        {
            if (ocupados[h])
            {
                ok = false;
                break;
            }
        }

        if (ok) return true;

        fila += 2;
        setColor(RED);
        centrarTexto("ERROR: se superpone con otro alquiler.", fila);
        setColor(LIGHTCYAN);
        anykey();
    }
}

// ----------------------------------------------
//   PROCESO COMPLETO: FECHA + HORA + DURACIÓN
// ----------------------------------------------
bool pedirFechaYHoraDisponibles(const Cancha &cancha, Fecha &f, int &h, int &durOut)
{
    int d, m, a;

    while (true)
    {
        cls();

        int cols = getConsoleWidth();
        if (cols <= 0) cols = 120;

        int fila = 6;

        setColor(LIGHTCYAN);
        centrarTexto("=== FECHA DEL ALQUILER ===", fila);
        fila += 2;

        centrarTexto("Ingrese la fecha de alquiler:", fila);
        fila += 2;

        // DIA
        string labelDia = "Dia (DD): ";
        int totalDia = (int)labelDia.size() + 4;
        int xDia = (cols - totalDia) / 2;
        if (xDia < 1) xDia = 1;

        locate(xDia, fila);
        cout << labelDia;
        locate(xDia + (int)labelDia.size(), fila);
        cin >> d;
        fila += 2;

        // MES
        string labelMes = "Mes (MM): ";
        int totalMes = (int)labelMes.size() + 4;
        int xMes = (cols - totalMes) / 2;
        if (xMes < 1) xMes = 1;

        locate(xMes, fila);
        cout << labelMes;
        locate(xMes + (int)labelMes.size(), fila);
        cin >> m;
        fila += 2;

        // ANIO
        string labelAnio = "Anio (AAAA): ";
        int totalAnio = (int)labelAnio.size() + 6;
        int xAnio = (cols - totalAnio) / 2;
        if (xAnio < 1) xAnio = 1;

        locate(xAnio, fila);
        cout << labelAnio;
        locate(xAnio + (int)labelAnio.size(), fila);
        cin >> a;

        // Validaciones
        if (!esFechaValida(d, m, a))
        {
            fila += 2;
            setColor(RED);
            centrarTexto("FECHA INVALIDA. Intente nuevamente.", fila);
            setColor(LIGHTCYAN);
            anykey();
            continue;
        }
        if (a != 2025 && a != 2026)
        {
            fila += 2;
            setColor(RED);
            centrarTexto("Solo se permiten fechas de los años 2025 o 2026.", fila);
            setColor(LIGHTCYAN);
            anykey();
            continue;
        }

        f.setDia(d);
        f.setMes(m);
        f.setAnio(a);
        break;
    }

    if (!mostrarHorariosDisponiblesYSeleccionar(cancha, f, h))
        return false;

    if (!pedirDuracionHoras(cancha, f, h, durOut))
        return false;

    return true;
}
