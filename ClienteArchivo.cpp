#include "ConfiguracionMenu.h"
#include "ClienteArchivo.h"
#include "rlutil.h"
#include <iostream>
using namespace std;
using namespace rlutil;

ClienteArchivo::ClienteArchivo(const char* ruta)
{
    rutaArchivo = ruta;
}

void ClienteArchivo::guardarCliente(const Cliente& obj) {
    FILE* p = fopen(rutaArchivo, "ab");
    if (p == nullptr)
    {
        cout << "Error al guardar el cliente.";
        return;
    }
    fwrite(&obj, sizeof(Cliente), 1, p);
    fclose(p);
}

void ClienteArchivo::mostrarClientes()
{
    FILE* p = fopen(rutaArchivo, "rb");
    if (p == nullptr)
    {
        centrarTexto("No hay clientes registrados o no se pudo abrir el archivo.", 15);
        anykey();
        return;
    }

    Cliente reg;
    int count = 0;

    const int boxW  = 48;
    const int boxH  = 8;
    const int cols  = 3;
    const int startX = 2;
    const int startY = 2;
    const int gapX   = 4;
    const int gapY   = 1;

    cls();

    while (fread(&reg, sizeof(Cliente), 1, p) == 1)
    {
        if (!reg.getActivo()) continue;

        int col = count % cols;
        int row = count / cols;

        int x = startX + col * (boxW + gapX);
        int y = startY + row * (boxH + gapY);

        reg.mostrar(x, y);
        count++;
    }

    fclose(p);

    int filas = (count + cols - 1) / cols;
    int finalY = startY + filas * (boxH + gapY) + 1;
    gotoxy(2, finalY);
    cout << "Presione cualquier tecla para volver.";
    anykey();
}

bool ClienteArchivo::modificarCliente(int idBuscado, const Cliente& nuevo) {
    FILE* p = fopen(rutaArchivo, "rb+");
    if (p == nullptr) return false;

    Cliente reg;
    while (fread(&reg, sizeof(Cliente), 1, p)) {
        if (reg.getIdCliente() == idBuscado) {
            fseek(p, -(long)sizeof(Cliente), SEEK_CUR);
            fwrite(&nuevo, sizeof(Cliente), 1, p);
            fclose(p);
            return true;
        }
    }

    fclose(p);
    return false; // no se encontró
}

bool ClienteArchivo::eliminarCliente(int idBuscado) {
    int pos = buscarPorId(idBuscado);
    if (pos < 0) return false;

    Cliente reg = leerRegistro(pos);
    reg.setActivo(false);

    FILE* p = fopen(rutaArchivo, "rb+");
    fseek(p, pos * sizeof(Cliente), SEEK_SET);
    fwrite(&reg, sizeof(Cliente), 1, p);
    fclose(p);
    return true;
}


int ClienteArchivo::cantidadRegistros() {
    FILE* p = fopen(rutaArchivo, "rb");
    if (p == nullptr) return 0;

    fseek(p, 0, SEEK_END);
    int bytes = ftell(p);
    fclose(p);
    return bytes / sizeof(Cliente);
}

int ClienteArchivo::buscarPorId(int idBuscado) {
    FILE* p = fopen(rutaArchivo, "rb");
    if (p == nullptr) return -1;

    Cliente reg;
    int pos = 0;
    while (fread(&reg, sizeof(Cliente), 1, p)) {
        if (reg.getIdCliente() == idBuscado) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1; // No encontrado
}

Cliente ClienteArchivo::leerRegistro(int pos) {
    Cliente reg;
    FILE* p = fopen(rutaArchivo, "rb");
    if (p == nullptr) return reg;

    fseek(p, pos * sizeof(Cliente), SEEK_SET);
    fread(&reg, sizeof(Cliente), 1, p);
    fclose(p);
    return reg;
}

int ClienteArchivo::buscarPorDni(int dniBuscado) {
    FILE* p = fopen(rutaArchivo, "rb");
    if (p == nullptr) return -1;

    Cliente reg;
    int pos = 0;
    while (fread(&reg, sizeof(Cliente), 1, p)) {
        if (reg.getDni() == dniBuscado) {
            fclose(p);
            return pos;
        }
        pos++;
    }

    fclose(p);
    return -1; // No encontrado
}

void ClienteArchivo::mostrarClientePorId(int idBuscado)
{
    int pos = buscarPorId(idBuscado);
    if (pos < 0) {
        setColor(RED);
        centrarTexto("No se encontro un cliente con ese ID.", 18);
        setColor(LIGHTCYAN);
        return;
    }

    Cliente reg = leerRegistro(pos);
    if (!reg.getActivo()) {
        setColor(RED);
        centrarTexto("El cliente con ese ID no esta activo.", 18);
        setColor(LIGHTCYAN);
        return;
    }

    int cols = getConsoleWidth();
    int rows = getConsoleHeight();

    int baseX = (cols - (42 + 2)) / 2;
    int baseY = (rows - 8) / 2;
    if (baseX < 1) baseX = 1;
    if (baseY < 1) baseY = 1;

    cls();
    reg.mostrar(baseX, baseY);
}

bool ClienteArchivo::recuperarCliente(int idBuscado) {
    int pos = buscarPorId(idBuscado);
    if (pos < 0) return false;

    Cliente reg = leerRegistro(pos);
    reg.setActivo(true);

    FILE* p = fopen(rutaArchivo, "rb+");
    fseek(p, pos * sizeof(Cliente), SEEK_SET);
    fwrite(&reg, sizeof(Cliente), 1, p);
    fclose(p);
    return true;
}

bool ClienteArchivo::existeClientePorID(int idBuscado) {
    Cliente obj;
    FILE *p = fopen(rutaArchivo, "rb");
    if (p == nullptr) {
        return false;  // error al abrir, asumir que no existe
    }
    while (fread(&obj, sizeof(Cliente), 1, p) == 1) {
        if (obj.getIdCliente() == idBuscado && obj.getActivo()) {  // suponiendo que Cliente tiene getIdCliente() y getActivo()
            fclose(p);
            return true;
        }
    }
    fclose(p);
    return false;
}
