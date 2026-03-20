#include "CanchaManager.h"
#include "ConfiguracionMenu.h"
#include <iostream>

using namespace std;
using namespace rlutil;

CanchaManager::CanchaManager(const char* ruta) : archivo(ruta) {}

void CanchaManager::listarCanchas()
{
    archivo.mostrarCanchas();
}

void CanchaManager::registrarCancha()
{
    cls();
    Cancha nueva;
    nueva.idAutomatizado();
    cout << "ID asignado: " << nueva.getIdCancha() << endl;
    nueva.cargar();
    archivo.guardarCancha(nueva);
    centrarTexto("Cancha registrada correctamente con ID: ", 18);
    cout << nueva.getIdCancha() << endl;
    anykey();
}

void CanchaManager::modificarCancha()
{
    int id;
    cls();
    centrarTexto("Ingrese el ID de la cancha a modificar: ", 10);
    cin >> id;
    cin.ignore(1000, '\n');

    int pos = archivo.buscarPorId(id);
    if (pos < 0)
    {
        cout << "\nERROR: No existe una cancha con ese ID.\n";
        anykey();
        return;
    }

    Cancha nuevoDatos;
    cls();
    centrarTexto("\n--- Ingrese los NUEVOS DATOS para la Cancha ---", 10);

    nuevoDatos.cargar();
    nuevoDatos.setIdCancha(id);
    nuevoDatos.setActivo(true);

    if (archivo.guardarRegistro(pos, nuevoDatos))
    {
        cout << "\nCancha ID " << id << " modificada correctamente.\n";
    }
    else
    {
        cout << "\nERROR: No se pudo modificar la cancha.\n";
    }
    anykey();
}

void CanchaManager::eliminarCancha()
{
    int id;
    cls();
    cout << "Ingrese el ID de la cancha a ELIMINAR: ";
    cin >> id;
    cin.ignore(1000, '\n');

    int pos = archivo.buscarPorId(id);
    if (pos < 0)
    {
        cout << "\nERROR: No existe una cancha con ese ID.\n";
        anykey();
        return;
    }

    Cancha reg = archivo.leerRegistro(pos);
    if (!reg.getActivo())
    {
        cout << "\nLa cancha ya estaba inactiva.\n";
        anykey();
        return;
    }

    reg.setActivo(false);

    if (archivo.guardarRegistro(pos, reg))
    {
        cout << "\nCancha ID " << id << " eliminada (baja logica) correctamente.\n";
    }
    else
    {
        cout << "\nERROR: No se pudo eliminar la cancha.\n";
    }
    anykey();
}
