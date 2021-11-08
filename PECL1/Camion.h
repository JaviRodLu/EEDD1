#ifndef Camion
#define Camion
#include <iostream>
using namespace std;
#include "PilasColas.h"
//Definici�n del tipo Camion:

class Truck
{
private:
    Pila *pilaCamion;
    int nPaquetes;
    int maxPaquetes;
public:
    Truck(int maxPaquetes); //Constructor del camion
    ~Truck();
    bool anadirPaquete(Paquete p);
};

#endif
