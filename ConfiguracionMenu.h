#ifndef CONFIGURACIONMENU_H_INCLUDED
#define CONFIGURACIONMENU_H_INCLUDED

#include "rlutil.h"
#include <cstring>
#include <vector>

int getConsoleWidth();
int getConsoleHeight();
void mostrarInicio();
void centrarTexto(const std::string& texto, int fila);
void imprimirBocaColor(int x, int y);
int menuConFlechas (const std::vector<std::string>& opciones, const std::string& titulo);
int menuConFlechasEnZona(const std::vector<std::string>& opciones, const std::string& titulo, int filaTitulo);
void mostrarListaEnCuadro(const std::vector<std::string>& lineas, int filaInicio);
void dibujarCuadroEnPos(const std::vector<std::string>& lineas, int baseX, int baseY, int anchoInterior);

#endif // CONFIGURACIONMENU_H_INCLUDED
