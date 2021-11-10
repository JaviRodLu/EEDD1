#include <iostream>
#include <ctime>
#include <iomanip>
#include <vector>
#include "PilasColas.h"
#include "Camion.h"

#define N1 100
#define N2 10
#define N3 5

using namespace std;

string padTo(std::string &str, const size_t num, const char paddingChar = '0')//Funcion que sirve para rellenar con 0 cuando la division de los numeros aleatorios generados para el id entre 99 y 9999 sale de menos numeros
{
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
    return str;
}

string generarIdPaquete()//Funcion que genera el ID del paquete
{
    string id;
    char abecedario[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    std::string parte1 = to_string(rand()%99);
    std::string parte2 = to_string(rand()%9999);
    id= padTo(parte1,2)+  abecedario[rand()%26] + padTo(parte2,4);

    return id;
}

string generarNIF()//Funcion que genera el NIF del paquete
{
    int numero;
    string NIF;
    char letras[] = {'T','R','W','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};

    for (int i=0; i<6; i++)
    {
        numero = numero*10 + rand()%10;
    }

    NIF = to_string(numero) + letras[numero%23];

    return NIF;
}

CoordenadasGPS generarCoordenadas()//Funcion que genera las coordenadas del paquete
{
    CoordenadasGPS c;
    int gradLat, minLat, segLat, gradLong, minLong, segLong;

   gradLat = 40;
    minLat = 28 + rand()%4;
    segLat = rand()%60;
    gradLong = -3;
    minLong = 19 + rand()%7;
    segLong = rand()%60;

    c.latitud[0] = gradLat;
    c.latitud[1] = minLat;
    c.latitud[2] = segLat;
    c.longitud[0] = gradLong;
    c.longitud[1] = minLong;
    c.longitud[2] = segLong;


    return c;
}

Paquete generarPaquete()//Funcion que genera un paquete
{
    Paquete p;

    p.idPaquete = generarIdPaquete();
    p.coordenadas = generarCoordenadas();
    p.NIF = generarNIF();

    return p;
}

void sigInstruccion()//Método para ir paso a paso con la ejecución del programa
{
    cout << '\n' << "Presiona Enter para realizar la siguiente instruccion..." << '\n' << endl;
    getchar();

}

int main()
{
    srand(time(NULL));
    Cola almacen;
    Truck *camionNO,*camionNE,*camionSO,*camionSE;
    camionNO = new Truck(N3);
    camionNE = new Truck(N3);
    camionSO = new Truck(N3);
    camionSE = new Truck(N3);
    int paquetesGenerados=0, paquetesCogidosNO=0,paquetesCogidosNE=0,paquetesCogidosSO=0,paquetesCogidosSE=0;
    int numCamionesNO=1,numCamionesNE=1,numCamionesSO=1,numCamionesSE=1;
    int gradLat=0, minLat=0, segLat=0, gradLong=0, minLong=0, segLong=0;
    Paquete p, pNO, pNE, pSO, pSE;
    int j=0, n=0;
    int contador=0;
    int contadorPaquetes=N1;

    cout << string(33, '#') << "ALMACEN DE PAQUETES" << string(33, '#') << endl;
    cout << string(27, '=') << "LISTADO DE PAQUETES ALMACENADOS" << string(27, '=') << endl;
    cout << setw(4) << " No." << "|" << setw(7) << "ID Paq " << "|" << setw(9) << "   NIF   " << "|" << setw(21) << "     Coordenadas     " << "|" << endl;
    cout << string(22, ' ') << "|" << setw(10) << " Latitud  " << "|"<< setw(10) << " Longitud " << "|" << endl;
    cout << string(45, '-') << endl;

    for (j=0; j<N1; j++)//Crea los 100 paquetes y los muestra por pantalla
    {
        p = generarPaquete();
        almacen.encolar(p);
        ++paquetesGenerados;
        n=j+1;
        cout << setw(4)<< n << " " << setw(7) << p.idPaquete << " " << setw(9) << p.NIF << " " << setw(2) << p.coordenadas.latitud[0] << "*" << setw(2) << p.coordenadas.latitud[1] << "'" << setw(2) << p.coordenadas.latitud[2] << "''" << " " << setw(2) << p.coordenadas.longitud[0] << "*"<< setw(2) << p.coordenadas.longitud[1] << "'" << setw(2) << p.coordenadas.longitud[2] << "''" << endl;
    }

    cout << string(34, '=') << "Envio de paquetes" << string(34, '=') <<endl;

    while(contadorPaquetes>0)
    {
        sigInstruccion();
        ++contador;
        int paquetesCogidos=0;
        cout << "Paquetes escogidos en la ronda " << contador << ":"<<endl;
        while (paquetesCogidos++ < N2)
        {
            //Cogemos el siguiente paquete del almacen
            p = almacen.desencolar();
            //Discriminamos por zona el destino del paquete
            gradLat = p.coordenadas.latitud[0];
            minLat = p.coordenadas.latitud[1];
            segLat = p.coordenadas.latitud[2];
            gradLong = p.coordenadas.longitud[0];
            minLong = p.coordenadas.longitud[1];
            segLong = p.coordenadas.longitud[2];

            if (((minLat >=29) && (segLat >= 30)) || (minLat >=30))//Envio de los paquetes a cada muelle según la direccion
            {
                //Omitimos los grados porque son siempre los mismos (al menos en esta aplicación)
                if (minLong >= 22)//Paquetes que van a la zona NO
                {

                    if(!camionNO->anadirPaquete(p))
                    {
                        camionNO=new Truck(N3);
                        camionNO->anadirPaquete(p);
                        numCamionesNO++;
                    }
                    cout << setw(7) << p.idPaquete << endl;
                    ++paquetesCogidosNO;
                } else {//Paquetes que van a la zona NE
                    if(!camionNE->anadirPaquete(p))
                    {
                        camionNE=new Truck(N3);
                        camionNE->anadirPaquete(p);
                        numCamionesNE++;
                    }
                    cout << setw(7) << p.idPaquete << endl;
                    ++paquetesCogidosNE;
                }
            } else {
                if (minLong >=22)//Paquetes que van a la zona SO
                {
                    if(!camionSO->anadirPaquete(p))
                    {
                        camionSO=new Truck(N3);
                        camionSO->anadirPaquete(p);
                        numCamionesSO++;
                    }
                    cout << setw(7) << p.idPaquete << endl;
                    ++paquetesCogidosSO;
                } else {//Paquetes que van a la zona SE
                    if(!camionSE->anadirPaquete(p))
                    {
                        camionSE=new Truck(N3);
                        camionSE->anadirPaquete(p);
                        numCamionesSE++;
                    }
                    cout << setw(7) << p.idPaquete << endl;
                    ++paquetesCogidosSE;
                }
            }
        }

        cout << endl;

        cout << "Paquetes entregados en NO: " << endl;
        while (!camionNO->estaVacio()){
            pNO= camionNO-> sacarPaquete();
            if (!pNO.esVacio()){
                cout << pNO.idPaquete << endl;
            }
            camionNO->anadirPaquete(pNO);
        }
        cout << endl;

        cout << "Paquetes entregados en NE: " << endl;
        while (!camionNE->estaVacio()){
            pNE= camionNE-> sacarPaquete();
            if (!pNE.esVacio()){
                cout << pNE.idPaquete << endl;
            }
        }
        cout << endl;

        cout << "Paquetes entregados en SO: " << endl;
        while (!camionSO->estaVacio()){
            pSO= camionSO-> sacarPaquete();
            if (!pSO.esVacio()){
                cout << pSO.idPaquete << endl;
            }
        }
        cout << endl;

        cout << "Paquetes entregados en SE: " << endl;
        while (!camionSE->estaVacio()){
            pSE= camionSE-> sacarPaquete();
            if (!pSE.esVacio()){
                cout << pSE.idPaquete << endl;
            }
        }
        cout << endl;

        contadorPaquetes-=paquetesCogidos;
        cout << string(33, '=') << "Estadistica ronda " << contador << string(33, '=') << endl;
        cout << string(26, ' ') << "Camiones enviados a zona NO : " <<setw(3) << numCamionesNO << string(26, ' ') << endl;
        cout << string(26, ' ') << "Camiones enviados a zona NE : " <<setw(3) << numCamionesNE << string(26, ' ') << endl;
        cout << string(26, ' ') << "Camiones enviados a zona SO : " <<setw(3) << numCamionesSO << string(26, ' ') << endl;
        cout << string(26, ' ') << "Camiones enviados a zona SE : " <<setw(3) << numCamionesSE << string(26, ' ') << endl;

        cout << string(30, ' ') << "Paquetes en zona NO : " << setw(3) << paquetesCogidosNO << string(30, ' ') << endl;
        cout << string(30, ' ') << "Paquetes en zona NE : " << setw(3) << paquetesCogidosNE << string(30, ' ') << endl;
        cout << string(30, ' ') << "Paquetes en zona SO : " << setw(3) << paquetesCogidosSO << string(30, ' ') << endl;
        cout << string(30, ' ') << "Paquetes en zona SE : " << setw(3) << paquetesCogidosSE << string(30, ' ') << endl;
        cout << endl;
    }

    cout << string(30, '=') << "Informe estadistico final" << string(30, '=') << endl;
    cout << string(27, ' ') << "Paquetes enviados a zona NO: " << paquetesCogidosNO << string(25, ' ') << endl;
    cout << string(27, ' ') << "Paquetes enviados a zona NE: " << paquetesCogidosNE << string(25, ' ') << endl;
    cout << string(27, ' ') << "Paquetes enviados a zona SO: " << paquetesCogidosSO << string(25, ' ') << endl;
    cout << string(27, ' ') << "Paquetes enviados a zona SE: " << paquetesCogidosSE << string(25, ' ') << endl;
    cout << string(26, ' ') << "Camiones enviados a zona NO : " << setw(3) << numCamionesNO << string(26, ' ') << endl;
    cout << string(26, ' ') << "Camiones enviados a zona NE : " << setw(3) << numCamionesNE << string(26, ' ') << endl;
    cout << string(26, ' ') << "Camiones enviados a zona SO : " << setw(3) << numCamionesSO << string(26, ' ') << endl;
    cout << string(26, ' ') << "Camiones enviados a zona SE : " << setw(3) << numCamionesSE << string(26, ' ') << endl;

    if(paquetesCogidosNO>paquetesCogidosNE && paquetesCogidosNO>paquetesCogidosSE && paquetesCogidosNO>paquetesCogidosSO)
    {
        cout << "La zona con mayor numero de paquetes entregados ha sido la Noroeste con: " << paquetesCogidosNO << " paquetes entregados." << endl;
    }
    else if(paquetesCogidosNE>paquetesCogidosSE&&paquetesCogidosNE>paquetesCogidosSO)
    {
        cout << "La zona con mayor numero de paquetes entregados ha sido la Noreste con: " << paquetesCogidosNE << " paquetes entregados." << endl;
    }
    else if(paquetesCogidosSO>paquetesCogidosSE)
    {
        cout << "La zona con mayor numero de paquetes entregados ha sido la Suroeste con: " << paquetesCogidosSO << " paquetes entregados." << endl;
    }
    else
    {
        cout << "La zona con mayor numero de paquetes entregados ha sido la Sureste con: " << paquetesCogidosSE << " paquetes entregados." << endl;
    }

    return 0;
}
