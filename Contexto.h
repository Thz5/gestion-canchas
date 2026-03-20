#ifndef CONTEXTO_H_INCLUDED
#define CONTEXTO_H_INCLUDED

#include "Cliente.h"
#include "Cancha.h"
#include "Sistema.h"

struct Contexto
{
    Cliente Cliente;
    Cancha Cancha;
    Sistema Alquiler;
};

#endif // CONTEXTO_H_INCLUDED
