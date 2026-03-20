#include "AlquilerManager.h"
#include "ClienteManager.h"
#include "ClienteArchivo.h"
#include "CanchaArchivo.h"
#include "Cancha.h"
#include "AlquilerCancha.h"
#include "AlquilerHorario.h"
#include "Validaciones.h"
#include "ConfiguracionMenu.h"
#include "rlutil.h"
#include "AlquilerCliente.h"


using namespace std;
using namespace rlutil;

AlquilerManager::AlquilerManager(const char* ruta) : archivos(ruta) {}

// ================== REGISTRAR ALQUILER ==================


void AlquilerManager::registrarAlquiler()
{
    ClienteArchivo archClientes("Clientes.dat");
    Alquiler alquiler;

    //  Validar / elegir cliente
    int idCliente = pedirClienteValido();
    alquiler.setIdCliente(idCliente);

    //  Seleccionar cancha
    Cancha canchaElegida;
    if (buscarYSeleccionarCanchaPorTipoYTam(canchaElegida) != 0) return;

    //  Validar fecha y hora disponibles
    Fecha fAlquiler;
    int hAlquiler;
    int durAlquiler;
    pedirFechaYHoraDisponibles(canchaElegida, fAlquiler, hAlquiler, durAlquiler);
    if (hAlquiler == -1) return;  // usuario canceló o no hay horarios

    //  Cargar datos básicos en el alquiler
    alquiler.setIdCancha(canchaElegida.getIdCancha());
    alquiler.setFechaAlquiler(fAlquiler);
    alquiler.setHora(hAlquiler);
    alquiler.setDuracionHoras(durAlquiler);

    //  Calcular monto total (precioHora * duracion)
    float montoTotal = canchaElegida.getPrecioHora() * durAlquiler;
    alquiler.setMontoPago(montoTotal);

    // Pedir datos del pago (seña + método)
    cls();
    centrarTexto("--- INGRESE DATOS DEL PAGO ---", 10);
    alquiler.cargar();  // aca se setean la seña y el método de pago

    //  Calcular monto restante Y estado del pago
    float restante = alquiler.getMontoPago() - alquiler.getSenia();

    if (restante <= 0.0f)
    {
        restante = 0.0f;
        alquiler.setEstadoPago(true);   // seña cubre todo - pagado
    }
    else
    {
        alquiler.setEstadoPago(false);  // todavía queda saldo - pendiente
    }
    alquiler.setMontoRestante(restante);

    archivos.guardarAlquiler(alquiler);

    setColor(LIGHTCYAN);
    centrarTexto("Alquiler registrado correctamente.", 15);
    setColor(LIGHTCYAN);
    anykey();
}


// ================== MOSTRAR ALQUILERES ==================

void AlquilerManager::mostrarAlquileres()
{
    archivos.mostrarAlquileres();
}

// ================== BUSCAR ALQUILER POR FECHA ==================

void AlquilerManager::buscarAlquilerPorFecha()
{
    archivos.buscarPorFecha();
}


void AlquilerManager::modificarAlquiler()
{
    while (true)
    {
        // 1) Elegir alquiler
        int pos = archivos.elegirAlquiler();
        if (pos < 0) return;

        Alquiler a = archivos.leerRegistro(pos);

        // 2) Menú de modificaciones
        vector<string> opciones {
            " Cambiar cancha ",
            " Cambiar fecha y hora ",
            " Cambiar duracion ",
            " Cambiar metodo de pago ",
            " Guardar cambios ",
            " Volver a elegir otro alquiler ",
            " Volver al menu de alquileres "
        };

        int op = menuConFlechas(opciones, "MODIFICAR ALQUILER");

        switch(op)
        {
            case 0: {
                // Cambiar cancha
                Cancha nueva;
                if (buscarYSeleccionarCanchaPorTipoYTam(nueva) == 0)
                    a.setIdCancha(nueva.getIdCancha());
            } break;

            case 1: {
    // Cambiar fecha y hora
    // Obtenemos la cancha actual desde el archivo por su ID
    CanchaArchivo archivoCanchas("Canchas.dat");
    Cancha canchaActual = archivoCanchas.leerCanchaPorID(a.getIdCancha());
    if (canchaActual.getIdCancha() == -1) {
        cls();
        cout << "No se encontro la cancha asociada al alquiler.\n";
        anykey();
        break;
    }

    Fecha f;
    int h, dur;
    if (pedirFechaYHoraDisponibles(canchaActual, f, h, dur))
    {
        a.setFechaAlquiler(f);
        a.setHora(h);
        a.setDuracionHoras(dur);
    }
} break;

            case 2: {

    CanchaArchivo archivoCanchas("Canchas.dat");
    Cancha canchaActual = archivoCanchas.leerCanchaPorID(a.getIdCancha());
    if (canchaActual.getIdCancha() == -1) {
        cls();
        cout << "No se encontro la cancha asociada al alquiler.\n";
        anykey();
        break;
    }

    int dur;
    Fecha f = a.getFechaAlquiler();
    if (pedirDuracionHoras(canchaActual, f, a.getHora(), dur)) {
        a.setDuracionHoras(dur);
    }
} break;


            case 3:
                // Cambiar metodo de pago
                a.setMetodoPago();
                break;

            case 4:
                // Guardar cambios y volver al menú de alquileres
                archivos.modificarRegistro(pos, a);
                centrarTexto("Alquiler modificado correctamente.", 15);
                anykey();
                return;

            case 5:
                // Volver a elegir otro alquiler (no guardamos nada, repetimos el while)
                continue;

            case 6:
                // Volver al menu de alquileres sin guardar cambios
                return;
        }
    }
}

void AlquilerManager::cancelarAlquiler()
{
    int pos = archivos.elegirAlquiler();
    if (pos < 0) return;

    if (archivos.eliminarAlquiler(pos))
        centrarTexto("Alquiler cancelado.", 15);
    else
        centrarTexto("Error cancelando.", 15);

    anykey();
}

void AlquilerManager::registrarPago()
{
    while (true)
    {
        // 1) Elegir alquiler desde la grilla
        int pos = archivos.elegirAlquiler();
        if (pos < 0) return;

        Alquiler a = archivos.leerRegistro(pos);

        // 2) FILTRO: si ya está pagado o no tiene restante, no dejar seguir
        if (a.getMontoRestante() <= 0.0f || a.getEstadoPago())
        {
            cls();
            setColor(LIGHTCYAN);
            centrarTexto("El alquiler seleccionado ya se encuentra PAGADO.", 10);
            centrarTexto("No es posible registrar mas pagos sobre este alquiler.", 11);
            centrarTexto("Seleccione otro alquiler o vuelva al menu.", 13);
            setColor(LIGHTCYAN);
            anykey();
            continue;
        }

        // 3) Mostrar resumen + pedir pago
        cls();

        int baseX = 2;
        int baseY = 2;
        a.mostrar(baseX, baseY);

        float restanteActual = a.getMontoRestante();

        int cols = getConsoleWidth();
        if (cols <= 0) cols = 120;

        int filaInfo = baseY + 13;

        setColor(LIGHTCYAN);
        string lineaRest = "Monto restante actual: $" + to_string(restanteActual);
        centrarTexto(lineaRest, filaInfo);
        filaInfo += 2;

        // Pedir monto a pagar centrado
        string label = "Ingrese cuanto paga: ";
        int x = (cols - (int)label.size() - 10) / 2;
        if (x < 1) x = 1;

        locate(x, filaInfo);
        cout << label;

        float pago;
        cin >> pago;

        if (cin.fail() || pago < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            filaInfo += 2;
            setColor(RED);
            centrarTexto("ERROR: monto invalido.", filaInfo);
            setColor(LIGHTCYAN);
            anykey();
            continue;
        }

        // 4) Actualizar restante y estado
        float nuevo = restanteActual - pago;
        if (nuevo < 0.0f) nuevo = 0.0f;

        a.setMontoRestante(nuevo);
        if (nuevo == 0.0f) a.setEstadoPago(true);

        archivos.modificarRegistro(pos, a);

        // 5) Mensaje final
        cls();
        setColor(LIGHTGREEN);
        centrarTexto("Pago registrado correctamente.", 10);

        string lineaPend = "Monto pendiente actual: $" + to_string(a.getMontoRestante());
        setColor(LIGHTCYAN);
        centrarTexto(lineaPend, 12);

        anykey();
        return;
    }
}




