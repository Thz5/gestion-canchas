#include "ConfiguracionMenu.h"
#include "windows.h"
#include <vector>
#include<iostream>
#include <cstring>
using namespace std;
using namespace rlutil;

int getConsoleWidth()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}

int getConsoleHeight()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

string dibujoIntro[] =
{
    "           ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    "           ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    "    ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    "  ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    " ¶¶¶¶       ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶       ¶¶¶¶",
    " ¶¶¶        ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶        ¶¶¶",
    " ¶¶¶        ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶        ¶¶¶",
    " ¶¶¶      ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶      ¶¶¶",
    " ¶¶¶     ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶     ¶¶¶",
    "  ¶¶¶    ¶¶¶ ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶ ¶¶¶    ¶¶¶",
    "  ¶¶¶¶    ¶¶¶ ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶ ¶¶¶    ¶¶¶¶",
    "   ¶¶¶¶    ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶    ¶¶¶¶",
    "     ¶¶¶¶¶¶¶¶ ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶ ¶¶¶¶¶¶¶¶¶",
    "      ¶¶¶¶¶¶   ¶¶¶¶¶¶¶¶¶¶¶¶¶¶   ¶¶¶¶¶¶",
    "                ¶¶¶¶¶¶¶¶¶¶¶¶",
    "                  ¶¶¶¶¶¶¶¶",
    "                    ¶¶¶¶",
    "                    ¶¶¶¶",
    "                    ¶¶¶¶",
    "                    ¶¶¶¶",
    "                ¶¶¶¶¶¶¶¶¶¶¶¶",
    "             ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    "             ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    "             ¶¶¶____________¶¶¶",
    "             ¶¶¶BOCA JUNIORS¶¶¶",
    "             ¶¶¶____________¶¶¶",
    "             ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    "             ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    "           ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶",
    "          ¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶"
};

void mostrarInicio()
{
    hidecursor();
    SetConsoleOutputCP(437);
    setColor(LIGHTCYAN);

    int cols = getConsoleWidth();
    int rows = getConsoleHeight();

    int cantLineas = (int)(sizeof(dibujoIntro) / sizeof(dibujoIntro[0]));

    // Calcular el ancho máximo del dibujo
    int maxAncho = 0;
    for (int i = 0; i < cantLineas; i++)
    {
        int len = (int)dibujoIntro[i].length();
        if (len > maxAncho) maxAncho = len;
    }

    // X fijo centrado según el ancho máximo del trofeo
    int posX = (cols - maxAncho) / 2;
    if (posX < 1) posX = 1;

    // Centro vertical de la pantalla
    int centroPantalla = rows / 2;

    // ---------- ANIMACIÓN "ZOOM" DESDE EL CENTRO ----------
    int centroDibujo = cantLineas / 2;

    for (int frame = 1; frame <= cantLineas; frame++)
    {
        cls();

        // cantidad de líneas a mostrar en este frame
        int half = frame / 2;
        int startIdx = centroDibujo - half;
        int endIdx   = centroDibujo + half;

        if (startIdx < 0) startIdx = 0;
        if (endIdx >= cantLineas) endIdx = cantLineas - 1;

        int lineasVisibles = endIdx - startIdx + 1;

        // centrar verticalmente el bloque visible
        int fila = centroPantalla - (lineasVisibles / 2);
        if (fila < 1) fila = 1;

        for (int idx = startIdx; idx <= endIdx; idx++)
        {
            locate(posX, fila);

            if (idx == 24) // línea "¶¶¶BOCA JUNIORS¶¶¶"
            {
                imprimirBocaColor(posX, fila);
            }
            else
            {
                cout << dibujoIntro[idx];
            }

            fila++;
        }

        Sleep(60); // velocidad del "zoom"
    }

    // ---------- PANTALLA FINAL ESTÁTICA + PARPADEO DEL TEXTO ----------
    bool visible = true;
    int frame = 0;

    while (true)
    {
        // si cambia el tamaño de la consola, recalculamos
        int newCols = getConsoleWidth();
        int newRows = getConsoleHeight();
        if (newCols != cols || newRows != rows)
        {
            cols = newCols;
            rows = newRows;

            posX = (cols - maxAncho) / 2;
            if (posX < 1) posX = 1;
            centroPantalla = rows / 2;
        }

        cls();

        // Dibujar el trofeo completo centrado
        int filaDibujo = centroPantalla - (cantLineas / 2);
        if (filaDibujo < 1) filaDibujo = 1;

        for (int i = 0; i < cantLineas; i++)
        {
            locate(posX, filaDibujo + i);

            if (i == 24)
            {
                imprimirBocaColor(posX, filaDibujo + i);
            }
            else
            {
                cout << dibujoIntro[i];
            }
        }

        // ---------- Cuadro de información debajo del trofeo ----------
        int filaTexto = filaDibujo + cantLineas + 1;

        // líneas que van dentro del cuadro
        vector<string> info;
        info.push_back("COMPLEJO DEPORTIVO");

        // calcular ancho máximo del texto del cuadro
        int anchoInfo = 0;
        for (const string &s : info)
            if ((int)s.size() > anchoInfo) anchoInfo = (int)s.size();

        // AHORA lo centramos respecto al TROFEO, no a toda la pantalla
        // posX  = columna donde empieza el trofeo
        // maxAncho = ancho máximo del trofeo (ya lo calculaste arriba)
        int baseX = posX + (maxAncho - (anchoInfo + 2)) / 2; // +2 por bordes del cuadro
        if (baseX < 1) baseX = 1;

        int baseY = filaTexto;

        // dibujar el cuadro alineado con el trofeo
        dibujarCuadroEnPos(info, baseX, baseY, anchoInfo);

        // dejamos una línea en blanco debajo del cuadro
        filaTexto = baseY + (int)info.size() + 2;

        // ---------- Texto que parpadea ----------
        if (visible)
        {
            centrarTexto("PRESIONA ESPACIO PARA CONTINUAR", filaTexto);
        }

        frame++;
        if (frame % 4 == 0) visible = !visible; // cambia cada pocos frames

        // Si se presiona alguna tecla, salimos
        if (kbhit())
        {
            getch(); // consumir tecla
            break;
        }

        Sleep(120);
    }

    showcursor();
}

void imprimirBocaColor(int x, int y)
{
    using namespace rlutil;

    const string izquierda = "             ¶¶¶";
    const string texto     = "BOCA JUNIORS";
    const string derecha   = "¶¶¶";

    // Imprimir parte izquierda en cian claro
    locate(x, y);
    setColor(LIGHTCYAN);
    cout << izquierda;

    // Ahora las letras de "BOCA JUNIORS" en azul/amarillo
    bool azul = true;
    for (char c : texto)
    {
        if (c == ' ')
        {
            // El espacio lo dejamos en cian para que no moleste
            setColor(LIGHTCYAN);
            cout << c;
        }
        else
        {
            setColor(azul ? BLUE : YELLOW);
            cout << c;
            azul = !azul;
        }
    }

    // Parte derecha del dibujito en cian de nuevo
    setColor(LIGHTCYAN);
    cout << derecha;
}


void centrarTexto(const string& texto, int fila)
{
    int columnas = tcols();              // ancho de la consola
    int posX = (columnas - (int)texto.length()) / 2;
    if (posX < 1) posX = 1;              // por seguridad
    locate(posX, fila);                  // ubica el cursor
    cout << texto;
}

int menuConFlechas(const vector<string>& opciones, const string& titulo)
{
    int seleccion = 0;
    int cantidad = (int)opciones.size();

    while (true)
    {
        cls();
        setColor(LIGHTCYAN);

        // Armamos las líneas que van adentro del cuadro
        vector<string> lineas;

        // Línea de título centrado dentro del cuadro
        lineas.push_back(titulo);

        // Línea en blanco de separación
        lineas.push_back("");

        // Opciones del menú (resaltamos la seleccionada)
        for (int i = 0; i < cantidad; i++)
        {
            string texto = opciones[i];

            if (i == seleccion)
            {
                // Agregamos flechitas y lo dejamos "marcado"
                texto = string(1, char(175)) + " " + texto + " " + string(1, char(174));
            }

            lineas.push_back(texto);
        }

        // Calculamos el ancho máximo para el cuadro
        int anchoInterior = 0;
        for (const string &s : lineas)
        {
            if ((int)s.size() > anchoInterior) anchoInterior = (int)s.size();
        }

        // Medidas de la pantalla de consola
        int cols = tcols();
        int rows = trows();
        if (cols <= 0) cols = 120;
        if (rows <= 0) rows = 30;

// Centrado horizontal perfecto
        int baseX = (cols - (anchoInterior + 2)) / 2;
        if (baseX < 1) baseX = 1;

// Centrado vertical perfecto
        int altoCuadro = (int)lineas.size() + 2; // 2 = bordes
        int baseY = (rows - altoCuadro) / 2;
        if (baseY < 1) baseY = 1;

        // Dibujamos el cuadro con las líneas armadas
        dibujarCuadroEnPos(lineas, baseX, baseY, anchoInterior);

        // Leemos la tecla
        int tecla = getkey();

        switch (tecla)
        {
        case KEY_UP:
            seleccion--;
            if (seleccion < 0) seleccion = cantidad - 1;
            break;

        case KEY_DOWN:
            seleccion++;
            if (seleccion >= cantidad) seleccion = 0;
            break;

        case KEY_ENTER:
            return seleccion;  // devolvemos el índice de la opción elegida
        }
    }
}

int menuConFlechasEnZona(const vector<string>& opciones,
                         const string& titulo,
                         int filaTitulo)
{
    int seleccion = 0;
    int cantidad = (int)opciones.size();

    while (true)
    {
        int cols = tcols();
        if (cols <= 0) cols = 120;

        // Armamos las líneas que van dentro del cuadro
        vector<string> lineas;

        // Título
        lineas.push_back(titulo);
        // Línea en blanco
        lineas.push_back("");

        // Opciones (resaltamos la seleccionada con flechitas)
        for (int i = 0; i < cantidad; i++)
        {
            string texto = opciones[i];

            if (i == seleccion)
            {
                texto = string(1, char(175)) + " " + texto + " " + string(1, char(174));
            }

            lineas.push_back(texto);
        }

        // Calculamos ancho interior
        int anchoInterior = 0;
        for (const string &s : lineas)
            if ((int)s.size() > anchoInterior) anchoInterior = (int)s.size();

        // Altura del cuadro (líneas + bordes)
        int altoCuadro = (int)lineas.size() + 2;

        // Centramos horizontalmente, pero la altura la fija filaTitulo
        int baseX = (cols - (anchoInterior + 2)) / 2;
        if (baseX < 1) baseX = 1;
        int baseY = filaTitulo;   // acá empieza el cuadro

        // --- Limpiar solo la zona del menú (no tocamos el cliente de arriba) ---
        for (int y = baseY - 1; y <= baseY + altoCuadro; y++)
        {
            if (y < 1) continue;
            rlutil::locate(1, y);
            for (int x = 0; x < cols; x++) cout << ' ';
        }

        // Dibujamos el cuadro con las líneas armadas
        setColor(LIGHTCYAN);
        dibujarCuadroEnPos(lineas, baseX, baseY, anchoInterior);

        // Leemos tecla
        int tecla = rlutil::getkey();

        switch (tecla)
        {
        case KEY_UP:
            seleccion--;
            if (seleccion < 0) seleccion = cantidad - 1;
            break;

        case KEY_DOWN:
            seleccion++;
            if (seleccion >= cantidad) seleccion = 0;
            break;

        case KEY_ENTER:
            return seleccion;
        }
    }
}

void mostrarListaEnCuadro(const vector<string>& lineas, int filaInicio)
{
    if (lineas.empty()) return;

    // 1) Longitud máxima de las líneas
    int maxLen = 0;
    for (const string& s : lineas)
        if ((int)s.size() > maxLen) maxLen = (int)s.size();

    int anchoInterior = maxLen + 2;        // 1 espacio a cada lado
    int cols = rlutil::tcols();            // ancho de la consola
    if (cols <= 0) cols = 120;             // por si acaso

    int x = (cols - (anchoInterior + 2)) / 2; // columna donde empieza el borde izquierdo
    if (x < 1) x = 1;

    int filaTop = filaInicio - 1;                  // borde superior
    int filaBottom = filaInicio + (int)lineas.size(); // borde inferior

    // ---------- BORDE SUPERIOR ----------
    gotoxy(x, filaTop);
    cout << char(201);
    for (int i = 0; i < anchoInterior; i++) cout << char(205);
    cout << char(187);

    // ---------- CONTENIDO ----------
    for (size_t i = 0; i < lineas.size(); ++i)
    {
        string s = lineas[i];
        if ((int)s.size() > maxLen) s = s.substr(0, maxLen);

        // centrado dentro del cuadro
        int espaciosTotales = maxLen - (int)s.size();
        int leftPad  = espaciosTotales / 2;
        int rightPad = espaciosTotales - leftPad;

        int y = filaInicio + (int)i;
        gotoxy(x, y);
        cout << char(186);              // borde izquierdo

        cout << ' ';                    // margen interno izquierdo
        for (int k = 0; k < leftPad;  ++k) cout << ' ';
        cout << s;
        for (int k = 0; k < rightPad; ++k) cout << ' ';
        cout << ' ';                    // margen interno derecho

        cout << char(186);              // borde derecho
    }

    // ---------- BORDE INFERIOR ----------
    gotoxy(x, filaBottom);
    cout << char(200);
    for (int i = 0; i < anchoInterior; i++) cout << char(205);
    cout << char(188);
}

void dibujarCuadroEnPos(const vector<string>& lineas,
                        int baseX, int baseY, int anchoInterior)
{
    if (lineas.empty()) return;

    // asegurar ancho interior mínimo
    if (anchoInterior < 10) anchoInterior = 10;

    // borde superior
    gotoxy(baseX, baseY);
    cout << char(201);
    for (int i = 0; i < anchoInterior; i++) cout << char(205);
    cout << char(187);

    // contenido
    for (size_t i = 0; i < lineas.size(); ++i)
    {
        string s = lineas[i];
        if ((int)s.size() > anchoInterior) s = s.substr(0, anchoInterior);
        int pad = anchoInterior - (int)s.size();

        gotoxy(baseX, baseY + 1 + (int)i);
        cout << char(186);          // borde izquierdo
        cout << s;
        for (int k = 0; k < pad; ++k) cout << ' ';
        cout << char(186);          // borde derecho
    }

    // borde inferior
    gotoxy(baseX, baseY + 1 + (int)lineas.size());
    cout << char(200);
    for (int i = 0; i < anchoInterior; i++) cout << char(205);
    cout << char(188);
}




