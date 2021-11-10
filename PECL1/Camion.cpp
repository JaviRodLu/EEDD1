#include <iostream>

#include "Camion.h"

Truck::Truck(int maxCamion,string _zona)
{
    pilaCamion = new Pila();
    nPaquetes=0;
    maxPaquetes=maxCamion;
    zona=_zona;
}

Truck::~Truck()
{
    delete pilaCamion;
}

bool Truck::anadirPaquete(Paquete p)//Añadir paquete en el camion
{
    if(nPaquetes>=maxPaquetes)
    {
        return false;
    }
    else
    {
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
    }
    else
    {
        return vacio;
    }
}

bool Truck::estaVacio()
{
    if (nPaquetes == 0){
        return true;}
    else{
        return false;}
}
