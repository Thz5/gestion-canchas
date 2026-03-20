#include "AlquilerCancha.h"
#include "CanchaArchivo.h"
#include "rlutil.h"
#include "ConfiguracionMenu.h"
#include <cstring>
#include <iostream>

using namespace std;
using namespace rlutil;

// - pide tipo y tamaño usando tus funciones Cancha::seleccionarTipo()/seleccionarTamanio()
// - busca coincidencias en Canchas.dat
// - muestra el menu con flechas para elegir entre coincidencias
// - si no hay coincidencias o el usuario cancela, muestra el mensaje y devuelve -1
// - si elige una cancha, copia la cancha en 'salida' y devuelve 0
int buscarYSeleccionarCanchaPorTipoYTam(Cancha &salida)
{
    // 1) pedir tipo
    Cancha criterio;
    cls();
    criterio.seleccionarTipo();

    // 2) abrir Canchas.dat y agrupar por tamaño solo para el tipo elegido
    FILE* p = fopen("Canchas.dat", "rb");
    if (!p) {
        cls();
        setColor(RED);
        centrarTexto("No se pudo abrir Canchas.dat", 15);
        setColor(LIGHTCYAN);
        anykey();
        return -1;
    }

    // Estructuras: para cada tamaño guardamos vector<Cancha>
    vector<int> tamanios;                 // lista de tamaños encontrados (ej: 5,6,7,11)
    vector< vector<Cancha> > grupos;      // grupos[i] -> canchas del tamanio tamanios[i]

    Cancha reg;
    while (fread(&reg, sizeof(Cancha), 1, p) == 1)
    {
        // solo nos interesan canchas del tipo elegido y activas
        if (strcmp(reg.getTipo(), criterio.getTipo()) != 0) continue;
        if (!reg.getActivo()) continue;

        int t = reg.getTamanio();
        // buscar si ya existe grupo para este tamanio
        int idx = -1;
        for (size_t i = 0; i < tamanios.size(); ++i) if (tamanios[i] == t) { idx = (int)i; break; }

        if (idx == -1) {
            // nuevo tamaño
            tamanios.push_back(t);
            vector<Cancha> nuevo;
            nuevo.push_back(reg);
            grupos.push_back(nuevo);
        } else {
            // agregar al grupo existente
            grupos[idx].push_back(reg);
        }
    }
    fclose(p);

    // 3) si no hay tamaños (no hay canchas de ese tipo)
    if (tamanios.size() == 0) {
        cls();
        setColor(RED);
        centrarTexto("No hay canchas registradas para ese tipo.", 15);
        setColor(LIGHTCYAN);
        anykey();
        return -1;
    }

    // 4) construir etiquetas para tamaños: "Tamaño 5 - $150/h (2 canchas)"
    vector<string> etiquetasTamanio;
    for (size_t i = 0; i < tamanios.size(); ++i) {
        // calcular precio minimo entre las canchas del grupo
        float minPrecio = grupos[i][0].getPrecioHora();
        for (size_t j = 1; j < grupos[i].size(); ++j)
            if (grupos[i][j].getPrecioHora() < minPrecio) minPrecio = grupos[i][j].getPrecioHora();

        char buf[200];
        // mostramos precio con 2 decimales
        sprintf(buf, "Tamaño %d - $%.2f/h (%d cancha%s)",
                tamanios[i], minPrecio, (int)grupos[i].size(), (grupos[i].size()>1? "s": ""));
        etiquetasTamanio.push_back(string(buf));
    }

    // 5) mostrar menu de tamaños y permitir elegir
    int selTam = menuConFlechas(etiquetasTamanio, "Seleccione el Tamanio (ENTER confirma, ESC cancela)");
    if (selTam < 0 || selTam >= (int)tamanios.size()) {
        cls();
        setColor(RED);
        centrarTexto("Seleccion cancelada.", 15);
        setColor(LIGHTCYAN);
        anykey();
        return -1;
    }

    // 6) construir lista de canchas para el tamaño elegido: mostrar ID y un ordinal (#1,#2) y precio
    vector<string> etiquetasCanchas;
    vector<Cancha> &grupoSeleccion = grupos[selTam];
    for (size_t k = 0; k < grupoSeleccion.size(); ++k) {
        char buf[200];

        const char* nombre = grupoSeleccion[k].getTipo();
        sprintf(buf, "ID %d - %s #%d - $%.2f/h",
                grupoSeleccion[k].getIdCancha(), nombre, (int)k+1, grupoSeleccion[k].getPrecioHora());
        etiquetasCanchas.push_back(string(buf));
    }

    // 7) mostrar menu de canchas y elegir la concreta
    int selCancha = menuConFlechas(etiquetasCanchas, "Seleccione la Cancha (ENTER confirma, ESC cancela)");
    if (selCancha < 0 || selCancha >= (int)grupoSeleccion.size()) {
        cls();
        setColor(RED);
        centrarTexto("Seleccion cancelada.", 15);
        setColor(LIGHTCYAN);
        anykey();
        return -1;
    }

    // 8) devolver la cancha seleccionada
    salida = grupoSeleccion[selCancha];
    return 0;
}
