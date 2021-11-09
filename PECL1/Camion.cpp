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
    } else {
        ++nPaquetes;
        pilaCamion->apilar(p);
        return true;
    }
}

Paquete Truck::sacarPaquete()
{
    Paquete p;
    Paquete vacio {"0", {{0,0,0},{0,0,0}},"0"};
    if (nPaquetes > 0)
    {
        --nPaquetes;
        p=pilaCamion->desapilar();
        return p;
    }else{
        return vacio;
    }
}
