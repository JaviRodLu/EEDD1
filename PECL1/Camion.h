#ifndef Camion
#define Camion
#include <iostream>
#include "PilasColas.h"
using namespace std;
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
    Paquete sacarPaquete();
};

#endif
