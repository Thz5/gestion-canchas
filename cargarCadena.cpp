#include <iostream>
using namespace std;

void cargarCadena(char *palabra, int tam)
{
    cin.getline(palabra, tam);

    // Si quedó un salto de línea pendiente por un cin >> anterior
    if (palabra[0] == '\0')
        cin.getline(palabra, tam);
}
