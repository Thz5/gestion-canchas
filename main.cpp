#include "MainMenu.h"
#include "Contexto.h"
#include <iostream>
#include "Cliente.h"
#include "ConfiguracionMenu.h"
using namespace std;

int main() {

    mostrarInicio();
    MainMenu app;
    Contexto obj;
    app.mostrar(obj);
    return 0;
}
