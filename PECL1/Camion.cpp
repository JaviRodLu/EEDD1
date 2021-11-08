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

bool Truck::anadirPaquete(Paquete p)//A�adir paquete en el camion
{
    if(nPaquetes>=maxPaquetes){
        return false;
    } else {
        ++nPaquetes;
        pilaCamion->apilar(p);
        return true;
    }
}

Paquete Truck::sacarPaquete()
{
    if (nPaquetes > 0){
        pilaCamion->desapilar();
    }
}
