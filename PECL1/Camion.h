#ifndef Camion
#define Camion
#include <iostream>
#include "PilasColas.h"
using namespace std;
//Definición del tipo Camion:

class Truck
{
private:
    Pila *pilaCamion;
    int nPaquetes;
    int maxPaquetes;

public:
    string zona;
    Truck(int maxPaquetes,string zona); //Constructor del camion
    ~Truck();
    bool anadirPaquete(Paquete p);
    Paquete sacarPaquete();
    bool estaVacio();
};

#endif
