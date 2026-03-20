#include "Horario.h"
#include <iostream>

using namespace std;

void Horario::setHora(int hor)
{
    hora = hor;
}

void Horario::setDisponibilidad(bool dispo)
{
    disponibilidad = dispo;
}

int Horario::getHora()
{
    return hora;
}

bool Horario::getDisponibilidad()
{
    return disponibilidad;
}

void Horario::cargar() {
    cout << "\n--- CARGAR HORARIO ---\n";
    cout << "Hora (0-23): ";
    cin >> hora;
    cout << "Disponible (1=SI, 0=NO): ";
    cin >> disponibilidad;
}

void Horario::mostrar() {
    cout << "Hora: " << hora << ":00" << endl;
    cout << "Disponibilidad: " << (disponibilidad ? "SI" : "NO") << endl;
}
