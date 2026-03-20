#include "Informes.h"
#include "ConfiguracionMenu.h"
#include "Alquiler.h"
#include "Cancha.h"
#include "CanchaArchivo.h"
#include "Fecha.h"
#include "ClienteArchivo.h"
#include <cstdio>
#include <vector>
#include <iomanip>
#include <cstring>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;
using namespace rlutil;

// ================= INFORME 1 =================

void Informe::mesMayorDemanda()
{
    cls();
    setColor(LIGHTCYAN);
    centrarTexto("==========================================", 13);
    centrarTexto("     INFORME: MES CON MAYOR DEMANDA      ", 14);
    centrarTexto("==========================================", 15);

    int cantidadPorMes[13] = {0};

    FILE* p = fopen("alquileres.dat", "rb");
    if (p == nullptr)
    {
        centrarTexto("No se pudo abrir el archivo de alquileres.", 7);
        anykey();
        return;
    }

    Alquiler aux;

    while (fread(&aux, sizeof(Alquiler), 1, p) == 1)
    {
        Fecha f = aux.getFechaAlquiler();
        int mes = f.getMes();
        if (mes >= 1 && mes <= 12)
        {
            cantidadPorMes[mes]++;
        }
    }

    fclose(p);

    int mesMax   = -1;
    int maxCant  = 0;

    for (int m = 1; m <= 12; m++)
    {
        if (cantidadPorMes[m] > maxCant)
        {
            maxCant = cantidadPorMes[m];
            mesMax  = m;
        }
    }

    if (mesMax == -1 || maxCant == 0)
    {
        centrarTexto("No hay alquileres registrados.", 9);
        anykey();
        return;
    }

    string nombresMes[] = {
        "", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    const int anchoInterior = 52;   // mismo estilo que los otros cuadros
    vector<string> lineas;


    auto addLR = [&](string left, string right)
    {
        int espacio = anchoInterior - (int)left.size() - (int)right.size();
        if (espacio < 1) espacio = 1;
        lineas.push_back(left + string(espacio, ' ') + right);
    };

    // armamos el contenido del cuadro
    addLR("Mes con mayor demanda:", nombresMes[mesMax]);
    addLR("Cantidad de alquileres:", to_string(maxCant));

    // centramos el cuadro verticalmente
    int filasConsola = rlutil::trows();
    int altoLista    = (int)lineas.size() + 2;   // +2 bordes
    int filaInicio   = (filasConsola - altoLista) / 2;
    if (filaInicio < 9) filaInicio = 9;         // que no pise el título

    mostrarListaEnCuadro(lineas, filaInicio);

    anykey();
}


// ================= INFORME 2 =================

void Informe::tamanoMenosAlquilado()
{
    cls();
    setColor(LIGHTCYAN);
    centrarTexto("==========================================", 13);
    centrarTexto("    INFORME: TAMANO MENOS ALQUILADO       ", 14);
    centrarTexto("==========================================", 15);

    // --- cargar canchas ---
    vector<Cancha> canchas;

    FILE* fc = fopen("Canchas.dat", "rb");
    if (fc == nullptr)
    {
        centrarTexto("No se pudo abrir el archivo de canchas.", 7);
        anykey();
        return;
    }

    Cancha cAux;
    while (fread(&cAux, sizeof(Cancha), 1, fc) == 1)
        canchas.push_back(cAux);
    fclose(fc);

    if (canchas.empty())
    {
        centrarTexto("No hay canchas cargadas.", 9);
        anykey();
        return;
    }

    // --- contar alquileres por TAMANIO ---
    FILE* fa = fopen("alquileres.dat", "rb");
    if (fa == nullptr)
    {
        centrarTexto("No se pudo abrir el archivo de alquileres.", 9);
        anykey();
        return;
    }

    struct Contador { std::string tam; int cant; };
    std::vector<Contador> lista;
    Alquiler alq;

    while (fread(&alq, sizeof(Alquiler), 1, fa) == 1)
    {
        int idCancha = alq.getIdCancha();

        int tamanio = -1;

        // buscar la cancha y obtener su tamanio
        for (auto& c : canchas)
        {
            if (c.getIdCancha() == idCancha)
            {
                tamanio = c.getTamanio();
                break;
            }
        }

        if (tamanio == -1) continue;


        std::string tamStr = std::to_string(tamanio);
        bool encontrado = false;

        for (auto& t : lista)
        {
            if (t.tam == tamStr)
            {
                t.cant++;
                encontrado = true;
                break;
            }
        }

        if (!encontrado)
            lista.push_back({tamStr, 1});
    }

    fclose(fa);

    if (lista.empty())
    {
        centrarTexto("No hay alquileres registrados.", 11);
        anykey();
        return;
    }

    // --- buscar el minimo ---
    int minCant = lista[0].cant;
    for (auto& t : lista)
        if (t.cant < minCant) minCant = t.cant;

    // --- armar lineas para el cuadro ---
    const int anchoInterior = 52;   // mismo estilo que los otros informes
    std::vector<std::string> lineas;

    lineas.push_back("Tamano(s) menos alquilado(s):");
    lineas.push_back("");

    auto addLR = [&](std::string left, std::string right)
    {
        int espacio = anchoInterior - (int)left.size() - (int)right.size();
        if (espacio < 1) espacio = 1;
        lineas.push_back(left + std::string(espacio, ' ') + right);
    };

    for (auto& t : lista)
    {
        if (t.cant == minCant)
        {
            // ej: "5 jugadores:", "6 jugadores:"
            std::string etiqueta = "F" + t.tam + ":";
            std::string valor    = std::to_string(t.cant) + " alquiler(es)";
            addLR(etiqueta, valor);
        }
    }

    // --- centrar el cuadro en la pantalla ---
    int filasConsola = rlutil::trows();
    int altoLista    = (int)lineas.size() + 2;   // +2 bordes
    int filaInicio   = (filasConsola - altoLista) / 2;
    if (filaInicio < 11) filaInicio = 11;       // que no pise el título

    mostrarListaEnCuadro(lineas, filaInicio);

    anykey();
}

// ================= INFORME 3 =================
// Variacion porcentual respecto al mes anterior

void Informe::variacionPorcentual()
{
    cls();
    setColor(LIGHTCYAN);
    centrarTexto("=====================================================", 9);
    centrarTexto(" INFORME: VARIACION PORCENTUAL MES A MES ", 10);
    centrarTexto("=====================================================", 11);

    // --- 1) Contador de alquileres por mes (0..11) ---
    int cantMes[12] = {0};

    FILE* p = fopen("alquileres.dat", "rb");
    if (p == nullptr)
    {
        centrarTexto("No se pudo abrir el archivo alquileres.dat", 7);
        anykey();
        return;
    }

    Alquiler aux;

    while (fread(&aux, sizeof(Alquiler), 1, p) == 1)
    {
        int mes = aux.getFechaAlquiler().getMes();   // 1..12
        if (mes >= 1 && mes <= 12)
            cantMes[mes - 1]++;                      // 0..11
    }

    fclose(p);

    const char* nombreMes[12] = {
        "Enero","Febrero","Marzo","Abril","Mayo","Junio",
        "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
    };

    // --- 2) Armar las lineas para el cuadro ---
    const int anchoInterior = 52;   // mismo estilo que los otros cuadros
    vector<string> lineas;

    lineas.push_back("Variacion respecto al mes anterior:");
    lineas.push_back("");

    auto addLR = [&](string left, string right)
    {
        int espacio = anchoInterior - (int)left.size() - (int)right.size();
        if (espacio < 1) espacio = 1;
        lineas.push_back(left + string(espacio, ' ') + right);
    };

    // Recorremos de Febrero (1) a Diciembre (11)
    for (int m = 1; m < 12; m++)
    {
        int anterior = cantMes[m - 1]; // mes anterior
        int actual   = cantMes[m];     // mes actual

        string left  = string(nombreMes[m]) + " vs " + nombreMes[m - 1] + ":"; // ej: "Febrero vs Enero:"
        string right;

        if (anterior == 0 && actual == 0)
        {
            right = "sin datos";
        }
        else if (anterior == 0 && actual > 0)
        {
            right = "aumento infinito";
        }
        else
        {
            float variacion = ((actual - anterior) / (float)anterior) * 100.0f;

            char buf[32];
            sprintf(buf, "%.2f%%", variacion);   // ej: "25.00%"
            right = buf;
        }

        addLR(left, right);
    }

    // --- 3) Centrar el cuadro en la pantalla ---
    int filasConsola = rlutil::trows();
    int altoLista    = (int)lineas.size() + 2;   // +2 bordes
    int filaInicio   = (filasConsola - altoLista) / 2;
    if (filaInicio < 9) filaInicio = 9;          // que no pise el título

    mostrarListaEnCuadro(lineas, filaInicio);

    anykey();
}

// ================= INFORME 4 =================
// Cantidad de alquileres por mes en un anio ingresado

void Informe::alquileresPorMesEnAnio()
{
    setColor(LIGHTCYAN);
    centrarTexto("=====================================================", 8);
    centrarTexto(" INFORME: ALQUILERES POR MES EN UN ANIO ", 9);
    centrarTexto("=====================================================", 10);

    int anio;
    centrarTexto("Ingrese el anio a analizar: ", 12);
    cin >> anio;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        centrarTexto("Anio invalido.", 23);
        return;
    }

    // 1) Contador de alquileres por mes para ese anio (0..11)
    int cantMes[12] = {0};

    FILE* p = fopen("alquileres.dat", "rb");
    if (p == nullptr)
    {
        centrarTexto("No se pudo abrir el archivo alquileres.dat", 23);
        return;
    }

    Alquiler aux;

    while (fread(&aux, sizeof(Alquiler), 1, p) == 1)
    {
        Fecha f = aux.getFechaAlquiler();
        int mes  = f.getMes();   // 1..12
        int anioReg = f.getAnio();

        if (anioReg == anio && mes >= 1 && mes <= 12)
        {
            cantMes[mes - 1]++;  // 0..11
        }
    }

    fclose(p);

    const char* nombreMes[12] =
    {
        "Enero","Febrero","Marzo","Abril","Mayo","Junio",
        "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
    };

    // Ver si hay datos para ese anio
    bool hayDatos = false;
    for (int i = 0; i < 12; i++)
        if (cantMes[i] != 0)
        {
            hayDatos = true;
            break;
        }

    if (!hayDatos)
    {
        string msg = "No hay alquileres registrados en el anio " + to_string(anio) + ".";
        centrarTexto(msg, 23);
        return;
    }

    vector<string> lineas;
    for (int i = 0; i < 12; i++)
    {
        ostringstream oss;
        oss << left  << setw(12) << nombreMes[i]
            << " : "
            << right << setw(3)  << cantMes[i]
            << " alquiler(es)";
        lineas.push_back(oss.str());
    }

    // calcular fila de inicio para centrar verticalmente
    int filasConsola = rlutil::trows();
    int altoLista    = (int)lineas.size() + 2;  // +2 por bordes del cuadro
    int filaInicio   = (filasConsola - altoLista) / 2;

    if (filaInicio < 3) filaInicio = 3;  // por si la consola es muy chica

    mostrarListaEnCuadro(lineas, filaInicio);

    anykey();

}

// ================= INFORME 5 =================
// Alquileres con senia > 50% del monto del alquiler
void Informe::alquileresConSeniaMayor50()
{
    cls();
    setColor(LIGHTCYAN);
    centrarTexto("================================================================", 3);
    centrarTexto(" INFORME: ALQUILERES CON SENIA MAYOR AL 50% DEL MONTO ", 4);
    centrarTexto("================================================================", 5);

    // --- pedir año ---
    int anio;
    centrarTexto("Ingrese el anio a analizar: ", 7);
    cin >> anio;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        centrarTexto("Anio invalido.", 9);
        anykey();
        return;
    }

    FILE* p = fopen("alquileres.dat", "rb");
    if (p == nullptr)
    {
        centrarTexto("No se pudo abrir el archivo alquileres.dat", 9);
        anykey();
        return;
    }

    Alquiler aux;
    int contador = 0;

    // Guardamos las cajitas (cada alquiler que cumple)
    vector<vector<string>> cajas;

    while (fread(&aux, sizeof(Alquiler), 1, p) == 1)
    {
        float monto = aux.getMontoPago();
        float senia = aux.getSenia();
        Fecha f = aux.getFechaAlquiler();
        int anioReg = f.getAnio();

        // filtramos por año y por condición de seña > 50%
        if (anioReg == anio && monto > 0 && senia > monto * 0.5f)
        {
            contador++;

            // CONSTANTE: debe coincidir con anchoInterior que uses abajo en la grilla
            const int anchoInterior = 52;

            vector<string> lineas;

            // helper para "Etiqueta a la izquierda" y "Valor a la derecha"
            auto addLR = [&](string left, string right)
            {
                int espacio = anchoInterior - (int)left.size() - (int)right.size();
                if (espacio < 1) espacio = 1;
                lineas.push_back(left + string(espacio, ' ') + right);
            };

            // --- Primera sección (IDs) ---
            addLR("ID Cliente:", to_string(aux.getIdCliente()));
            addLR("ID Cancha:",  to_string(aux.getIdCancha()));
            lineas.push_back("");   // línea en blanco

            // --- Segunda sección (Fecha / Hora) ---
            string fecha = to_string(f.getDia()) + "/" +
                           to_string(f.getMes()) + "/" +
                           to_string(f.getAnio());
            addLR("Fecha:", fecha);
            addLR("Hora:",  to_string(aux.getHora()));
            lineas.push_back("");   // línea en blanco

            // --- Tercera sección (Montos y método) ---
            char bufMonto[32], bufSenia[32];
            sprintf(bufMonto, "$%.2f", monto);
            sprintf(bufSenia, "$%.2f", senia);

            addLR("Monto:",  string(bufMonto));
            addLR("Seña:",   string(bufSenia));
            addLR("Metodo:", string(aux.getMetodoPago()));

            // guardamos esta "caja" en el vector general
            cajas.push_back(lineas);
        }
    }

    fclose(p);

    if (contador == 0)
    {
        string msg = "No hay alquileres con senia > 50% en el anio " + to_string(anio) + ".";
        centrarTexto(msg, 11);
        anykey();
        return;
    }

    // -------- DIBUJAR LAS CAJAS EN GRILLA 2xN --------
    const int cols = 2;              // 2 columnas
    const int anchoInterior = 52;    // mismo valor usado arriba en addLR
    const int boxH = 9;              // 7 lineas + 2 bordes = 9 alto aprox.
    const int startY = 11;           // fila donde empiezan los cuadros (debajo del texto)

    int pantallaAncho = rlutil::tcols();
    if (pantallaAncho <= 0) pantallaAncho = 120;

    int boxW = anchoInterior + 2;                         // ancho total del cuadro
    int gapX = 4;                                         // espacio horizontal entre cuadros
    int gapY = 2;                                         // espacio vertical entre filas
    int totalWidthDos = cols * boxW + (cols - 1) * gapX;  // ancho ocupado por 2 columnas
    int startX = (pantallaAncho - totalWidthDos) / 2;     // centrar la grilla
    if (startX < 1) startX = 1;

    for (size_t i = 0; i < cajas.size(); ++i)
    {
        int col = (int)(i % cols);        // 0 ó 1
        int row = (int)(i / cols);        // 0,1,2...

        int x = startX + col * (boxW + gapX);
        int y = startY + row * (boxH + gapY);

        dibujarCuadroEnPos(cajas[i], x, y, anchoInterior);
    }

    // -------- Mensaje final con el total, debajo de la grilla --------
    int filasGrilla = (int)((cajas.size() + cols - 1) / cols);
    int yFinal = startY + filasGrilla * (boxH + gapY) + 1;

    string resumen = "Total de alquileres con senia > 50% en " +
                     to_string(anio) + ": " + to_string(contador);
    centrarTexto(resumen, yFinal);

    anykey();
}


// ================= INFORME 6 =================
// Recaudacion por tipo de cancha (3 tipos fijos, usando CanchaArchivo)

void Informe::recaudacionPorTipoCancha()
{
    cls();
    setColor(LIGHTCYAN);
    centrarTexto("=====================================================", 11);
    centrarTexto(" INFORME: RECAUDACION POR TIPO DE CANCHA ", 12);
    centrarTexto("=====================================================", 13);

    float recNat  = 0;   // Cesped natural
    float recSint = 0;   // Cesped sintetico
    float recPiso = 0;   // Piso

    CanchaArchivo archCan("Canchas.dat");

    FILE* fa = fopen("alquileres.dat", "rb");
    if (fa == nullptr)
    {
        centrarTexto("No se pudo abrir alquileres.dat", 7);
        anykey();
        return;
    }

    Alquiler alq;

    while (fread(&alq, sizeof(Alquiler), 1, fa) == 1)
    {
        float monto = alq.getMontoPago();
        if (monto <= 0) continue;

        int idC = alq.getIdCancha();


        int pos = archCan.buscarPorId(idC);
        if (pos < 0) continue;   // no se encontro la cancha

        Cancha cancha = archCan.leerRegistro(pos);
        const char* tipo = cancha.getTipo();

        if (strcmp(tipo, "Cesped natural") == 0)
            recNat += monto;
        else if (strcmp(tipo, "Cesped sintetico") == 0)
            recSint += monto;
        else if (strcmp(tipo, "Piso") == 0)
            recPiso += monto;
    }

    fclose(fa);


    if (recNat == 0 && recSint == 0 && recPiso == 0)
    {
        centrarTexto("No hay recaudacion registrada por tipo de cancha.", 9);
        anykey();
        return;
    }

    // -------- armar lineas con etiqueta a la izquierda y monto a la derecha --------
    const int anchoInterior = 52;   // mismo estilo que los otros cuadros
    vector<string> lineas;

    auto addLR = [&](string left, string right)
    {
        int espacio = anchoInterior - (int)left.size() - (int)right.size();
        if (espacio < 1) espacio = 1;
        lineas.push_back(left + string(espacio, ' ') + right);
    };

    char bufNat[32], bufSint[32], bufPiso[32], bufTot[32];
    sprintf(bufNat,  "$%.2f", recNat);
    sprintf(bufSint, "$%.2f", recSint);
    sprintf(bufPiso, "$%.2f", recPiso);
    sprintf(bufTot,  "$%.2f", (recNat + recSint + recPiso));

    addLR("Cesped natural:",   string(bufNat));
    addLR("Cesped sintetico:", string(bufSint));
    addLR("Piso:",             string(bufPiso));
    lineas.push_back("");  // linea en blanco
    addLR("Total recaudado:", string(bufTot));

    // -------- mostrar cuadro centrado en la pantalla --------
    int filasConsola = rlutil::trows();
    int altoLista    = (int)lineas.size() + 2;      // +2 bordes
    int filaInicio   = (filasConsola - altoLista) / 2;
    if (filaInicio < 9) filaInicio = 9;            // que no tape el titulo

    mostrarListaEnCuadro(lineas, filaInicio);

    anykey();
}

// ================= INFORME 7 =================
// Metodo de pago mas utilizado

void Informe::metodoPagoMasUtilizado()
{
    cls();
    setColor(LIGHTCYAN);
    centrarTexto("=====================================================", 13);
    centrarTexto(" INFORME: METODO DE PAGO MAS UTILIZADO ", 14);
    centrarTexto("=====================================================", 15);

    FILE* p = fopen("alquileres.dat", "rb");
    if (p == nullptr)
    {
        centrarTexto("No se pudo abrir alquileres.dat", 7);
        anykey();
        return;
    }

    // Contadores para cada metodo de pago
    int cEfectivo      = 0;
    int cDebito        = 0;
    int cCredito       = 0;
    int cTransferencia = 0;

    Alquiler aux;

    while (fread(&aux, sizeof(Alquiler), 1, p) == 1)
    {
        const char* mp = aux.getMetodoPago();
        if (mp == nullptr || mp[0] == '\0') continue;

        if (strcmp(mp, "Efectivo") == 0)
            cEfectivo++;
        else if (strcmp(mp, "Debito") == 0)
            cDebito++;
        else if (strcmp(mp, "Credito") == 0)
            cCredito++;
        else if (strcmp(mp, "Transferencia") == 0)
            cTransferencia++;
    }

    fclose(p);

    // Ver si hay algo cargado
    if (cEfectivo == 0 && cDebito == 0 && cCredito == 0 && cTransferencia == 0)
    {
        centrarTexto("No hay metodos de pago registrados.", 9);
        anykey();
        return;
    }

    // Buscar el maximo
    int maxCant = cEfectivo;
    if (cDebito        > maxCant) maxCant = cDebito;
    if (cCredito       > maxCant) maxCant = cCredito;
    if (cTransferencia > maxCant) maxCant = cTransferencia;

    // ---------- armar lineas para el cuadro ----------
    const int anchoInterior = 52;   // mismo estilo que los demas informes
    vector<string> lineas;

    // titulo dentro del cuadro
    lineas.push_back("Metodo(s) de pago mas utilizado(s):");
    lineas.push_back("");   // linea en blanco

    auto addMetodo = [&](const string& nombre, int cant)
    {
        string right = to_string(cant) + " alquiler(es)";
        int espacio = anchoInterior - (int)nombre.size() - (int)right.size();
        if (espacio < 1) espacio = 1;
        lineas.push_back(nombre + string(espacio, ' ') + right);
    };

    if (cEfectivo == maxCant)      addMetodo("Efectivo",      cEfectivo);
    if (cDebito == maxCant)        addMetodo("Debito",        cDebito);
    if (cCredito == maxCant)       addMetodo("Credito",       cCredito);
    if (cTransferencia == maxCant) addMetodo("Transferencia", cTransferencia);

    // ---------- mostrar el cuadro centrado ----------
    int filasConsola = rlutil::trows();
    int altoLista    = (int)lineas.size() + 2;      // +2 por los bordes
    int filaInicio   = (filasConsola - altoLista) / 2;
    if (filaInicio < 9) filaInicio = 9;            // que no tape el titulo

    mostrarListaEnCuadro(lineas, filaInicio);

    anykey();
}

// ===============================================================
// 8) CLIENTES NUEVOS POR MES EN UN AÑO INGRESADO
// ===============================================================

void Informe::clientesNuevosPorMesEnAnio()
{
    cls();
    setColor(LIGHTCYAN);
    centrarTexto("=====================================================", 8);
    centrarTexto(" INFORME: CLIENTES NUEVOS POR MES EN UN", 9);
    cout<< " A" << char(165) << "O"<<endl;
    centrarTexto("=====================================================", 10);

    // --- pedir anio ---
    int anio;
    centrarTexto("Ingrese el anio a analizar: ", 12);
    cin >> anio;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        centrarTexto("Anio invalido.", 14);
        anykey();
        return;
    }

    ClienteArchivo arch("Clientes.dat");
    int total = arch.cantidadRegistros();

    if (total == 0)
    {
        centrarTexto("No hay clientes registrados.", 9);
        anykey();
        return;
    }

    int clientesMes[12] = {0};

    for (int i = 0; i < total; i++)
    {
        Cliente cli = arch.leerRegistro(i);
        if (!cli.getActivo()) continue;

        Fecha f = cli.getFechaAlta();

        if (f.getAnio() == anio)
        {
            int m = f.getMes();
            if (m >= 1 && m <= 12)
                clientesMes[m - 1]++;
        }
    }

    // Ver si hay clientes nuevos en ese anio
    bool hayDatos = false;
    for (int i = 0; i < 12; i++)
        if (clientesMes[i] != 0) { hayDatos = true; break; }

    if (!hayDatos)
    {
        string msg = "No hay clientes nuevos en el anio " + to_string(anio) + ".";
        centrarTexto(msg, 11);
        anykey();
        return;
    }

    const char* nombreMes[12] =
    {
        "Enero","Febrero","Marzo","Abril","Mayo","Junio",
        "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"
    };

    // --- armar lineas ordenadas para el cuadro ---
    vector<string> lineas;

    for (int i = 0; i < 12; i++)
    {
        ostringstream oss;
        // mes alineado a la izquierda, número alineado a la derecha
        oss << left  << setw(10) << nombreMes[i]   // nombre del mes
            << " : "
            << right << setw(3)  << clientesMes[i] // cantidad
            << " cliente(s) nuevo(s)";

        lineas.push_back(oss.str());
    }

    // --- centrar el cuadro verticalmente ---
    int filasConsola = rlutil::trows();
    int altoLista    = (int)lineas.size() + 2;      // +2 por los bordes
    int filaInicio   = (filasConsola - altoLista) / 2;
    if (filaInicio < 11) filaInicio = 11;          // que no pise el título / texto

    mostrarListaEnCuadro(lineas, filaInicio);

    anykey();
}
