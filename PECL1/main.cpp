#include <iostream>
#include <ctime>
#include "PilasColas.h"
#include <iomanip>
#include <vector>
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
    char letras[] = {'T','R','w','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};

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
    cout<<string(33, '#')<<"ALMACEN DE PAQUETES"<<string(33, '#')<<endl;
    cout<<string(27, '=')<<"LISTADO DE PAQUETES ALMACENADOS"<<string(27, '=')<<endl;
    srand(time(NULL));
    Cola almacen;
    Truck *camionNO,*camionNE,*camionSO,*camionSE;
    camionNO=new Truck(N3);
    camionNE=new Truck(N3);
    camionSO=new Truck(N3);
    camionSE=new Truck(N3);
    int paquetesGenerados=0, paquetesCogidosNO=0,paquetesCogidosNE=0,paquetesCogidosSO=0,paquetesCogidosSE=0;
    int paquetesCargadosNO=0,paquetesCargadosNE=0,paquetesCargadosSO=0,paquetesCargadosSE=0;
    int numCamionesNO=0,numCamionesNE=0,numCamionesSO=0,numCamionesSE=0;
    int gradLat=0, minLat=0, segLat=0, gradLong=0, minLong=0, segLong=0;
    Paquete p;
    int n;
    int contador=0;
    int contadorPaquetes=N1;
    //int contadorAux=0
    for (int j=0; j<N1; j++)//Crea los 100 paquetes y los muestra por pantalla
    {
        p = generarPaquete();
        almacen.encolar(p);
        ++paquetesGenerados;
        n=j+1;
        cout <<setw(3)<< n <<". " <<"ID: " <<setw(7)<<p.idPaquete <<" NIF: "<<setw(9)<<p.NIF<<" Coordenadas: Latitud: "<<setw(2)<<p.coordenadas.latitud[0]<<"*"<<setw(2)<<p.coordenadas.latitud[1]<<"'"<<setw(2)<<p.coordenadas.latitud[2]<<"''"<< " Longitud: "<<setw(2)<<p.coordenadas.longitud[0]<<"*"<<setw(2)<<p.coordenadas.longitud[1]<<"'"<<setw(2)<<p.coordenadas.longitud[2]<<"''"<< endl; //Prueba
    }
    cout<<string(34, '=')<<"Envio de paquetes"<<string(34, '=')<<endl;
    while(contadorPaquetes>0)
    {
        sigInstruccion();
        ++contador;
        int paquetesCogidos=0;
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
                        numCamionesNO++;
                    }

                    ++paquetesCogidosNO;


                }
                else//Paquetes que van a la zona NE
                {
                    if(!camionNE->anadirPaquete(p))
                    {
                        camionNE=new Truck(N3);
                        numCamionesNE++;
                    }
                    ++paquetesCogidosNE;
                }
            }
            else
            {
                if (minLong >=22)//Paquetes que van a la zona SO
                {
                    if(!camionSO->anadirPaquete(p))
                    {
                        camionSO=new Truck(N3);
                        numCamionesSO++;

                    }
                    ++paquetesCogidosSO;

                }
                else//Paquetes que van a la zona SE
                {
                    if(!camionSE->anadirPaquete(p))
                    {
                        camionSE=new Truck(N3);
                        numCamionesSE++;

                    }
                    ++paquetesCogidosSE;
                }
            }

        }
        contadorPaquetes-=paquetesCogidos;
        cout<<string(33, '=')<<"Estadistica ronda "<<contador<<string(33, '=')<<endl;
        cout<<string(26, ' ')<<"Camiones enviados a zona NO : "<<setw(3)<< numCamionesNO<<string(26, ' ')<< endl;
        cout<<string(26, ' ')<<"Camiones enviados a zona NE : "<<setw(3)<< numCamionesNE<<string(26, ' ')<< endl;
        cout<<string(26, ' ')<<"Camiones enviados a zona SO : "<<setw(3)<< numCamionesSO<<string(26, ' ')<< endl;
        cout<<string(26, ' ')<<"Camiones enviados a zona SE : "<<setw(3)<< numCamionesSE<<string(26, ' ')<< endl;

        cout<<string(30, ' ')<<"Paquetes en zona NO : "<<setw(3)<<paquetesCogidosNO<<string(30, ' ')<<endl;
        cout<<string(30, ' ')<<"Paquetes en zona NE : "<<setw(3)<<paquetesCogidosNE<<string(30, ' ')<<endl;
        cout<<string(30, ' ')<<"Paquetes en zona SO : "<<setw(3)<<paquetesCogidosSO<<string(30, ' ')<<endl;
        cout<<string(30, ' ')<<"Paquetes en zona SE : "<<setw(3)<<paquetesCogidosSE<<string(30, ' ')<<endl;
    }

    return 0;
}
