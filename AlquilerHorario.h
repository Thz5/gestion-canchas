#ifndef ALQUILERHORARIO_H_INCLUDED
#define ALQUILERHORARIO_H_INCLUDED

#include "Cancha.h"
#include "Fecha.h"

void marcarHorasOcupadas(const Cancha &cancha,const Fecha &fecha,bool ocupados[24]);

bool mostrarHorariosDisponiblesYSeleccionar(const Cancha &cancha,const Fecha &fecha,int &horaSalida);

bool pedirDuracionHoras(const Cancha &cancha,const Fecha &fecha,int horaInicio,int &durOut);

bool pedirFechaYHoraDisponibles(const Cancha &cancha,Fecha &f,int &h,int &durOut);

#endif // ALQUILERHORARIO_H_INCLUDED
