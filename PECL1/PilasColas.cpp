#include <iostream>
#include "PilasColas.h"

using namespace std;

//Métodos de tipos de datos:

//Destructor de la Pila
Pila::~Pila()
{
    while(cima) desapilar();
}

//Destructor de la Cola
Cola::~Cola()
{
    while(frente) desencolar();
}

//Meter elemento en la Pila
void Pila::apilar(Paquete p)
{
    pnodo nuevo; //Var aux para manipular el nuevo nodo
    nuevo = new Nodo(p, cima); //Se crea un nodo nuevo
    cima = nuevo; //El comienzo de la pila es el nuevo nodo
}

//Sacar elemento de la Pila
Paquete Pila::desapilar()
{
    pnodo nodo; //Var aux para manipular el nodo
    Paquete p; //Var aux para el retorno del valor del nodo
    Paquete vacio {"0", {{0,0,0},{0,0,0}},"0"};
    if(!cima) return vacio; // Si no hay nodos en la pila se devuelve 0
    nodo = cima;// Nodo apunta al primer elemento de la pila
    cima= nodo->siguiente; //Se asigna a pila toda la pila menos el primer elemento
    p = nodo->valor; //Se guarda el retorno del valor del nodo
    delete nodo; //Se borra el nodo
    //cout<<p.idPaquete<<endl;
    return p;
}

void Pila::mostrarCima()
{
    if (!cima) cout << "Cima: pila vacía" << endl;
    else cout << "Cima: " << cima->valor.idPaquete << endl;
}

//Comprobar si un paquete está vacío
bool Paquete::esVacio()
{
     if (idPaquete=="0")
    {
        return true;
    }
    else
    {
        return false;
    }
}
//Añadir elemento en la cola
void Cola::encolar(Paquete p)
{
    pnodo nuevo;
    nuevo = new Nodo(p); // Se crea un nodo nuevo
    if(final) final->siguiente = nuevo; // Si cola no vacía, se añade el nuevo a continuación de ultimo
    final = nuevo; //El último elemento de la cola es el nuevo nodo
    if(!frente) frente = nuevo; // Si frente es NULL, la cola está vacía y el nuevo nodo pasa a ser el primero
}

//Leer elemento de la cola
Paquete Cola::desencolar()
{
    pnodo nodo; //Var aux para manipular nodo
    Paquete p; //Var aux para retorno del valor
    Paquete vacio {"0", {{0,0,0},{0,0,0}},"0"};
    nodo = frente; // Nodo apunta al primer elemento de la cola
    if(!nodo) return vacio; // Si no hay nodos en la cola se devuelve 0
    frente = nodo->siguiente; //Se asigna a frente la dirección del segundo nodo
    p = nodo->valor; //Se guarda el valor de retorno
    delete nodo; // Se borra el nodo
    if(!frente) final = NULL; // Si cola vacía, ultimo debe ser NULL también
    return p;
}

void Cola::recorrer()
{
    pnodo nodo;
    nodo = frente;
    while (nodo) //mientras nodo no sea nulo
    {
        //cout << nodo->valor.idPaquete << endl;
        nodo = nodo->siguiente;
    }
}

