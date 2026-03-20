#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#include <string>
#include "Fecha.h"

using namespace std;

int pedirEntero(const char* mensaje, int minVal = -2147483647, int maxVal = 2147483647);
int pedirDni();
bool esEmailValido(const char *email);
void pedirEmailValido(const char* mensaje, char* destino, int tam);
bool esFechaValida(int dia, int mes, int anio);
Fecha pedirFechaValida(const string& mensaje);






#endif // VALIDACIONES_H_INCLUDED
