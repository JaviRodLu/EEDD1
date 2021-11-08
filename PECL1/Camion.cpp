#include <iostream>

#include "Camion.h"

Truck::Truck(int maxCamion)
{
    pilaCamion = new Pila();
    nPaquetes=0;
    maxPaquetes=maxCamion;
}

Truck::~Truck()
{
    delete pilaCamion;
}

bool Truck::anadirPaquete(Paquete p)//Añadir paquete en el camion
{
    if(nPaquetes>=maxPaquetes){
    return false;
    }
    ++nPaquetes;
    pilaCamion->apilar(p);

    return true;
}
