#ifndef PilasColas
#define PilasColas

#include <iostream>

using namespace std;

//Definición de tipos de datos:

struct CoordenadasGPS
{
    int latitud[3];
    int longitud[3];
};

struct Paquete
{
    string idPaquete;
    CoordenadasGPS coordenadas;
    string NIF;
};
/*struct Zona
{
    Cola recibidos;

};*/
class Nodo
{
    private:
        Paquete valor;
        Nodo *siguiente;
        friend class Pila;
        friend class Cola;
    public:
        Nodo(Paquete v, Nodo *sig = NULL)
        {
            valor = v;
            siguiente = sig;
        }
};

typedef Nodo *pnodo;

class Pila
{
    private:
        pnodo cima;
    public:
        Pila() : cima(NULL) {} //Constructor de la Pila
        ~Pila();
        void apilar(Paquete v);
        Paquete desapilar();
        void mostrarCima();
};

class Cola
{
    public:
        Cola() : frente(NULL), final(NULL) {}
        ~Cola();
        void encolar(Paquete v);
        Paquete desencolar();
        void recorrer();
    private:
        pnodo frente, final;
};

#endif
