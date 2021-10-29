#include <iostream>
#include <ctime>
#include "PilasColas.h"
#define N1 100
#define N2 10
#define N3 5

using namespace std;

string generarIdPaquete()
{
    string id;
    int numero1, numero2;
    char abecedario[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    for (int i=0; i<2; i++)
    {
        numero1 = numero1*10 + rand()%10;
    }
    for (int j=0; j<4; j++)
    {
        numero2 = numero2*10 + rand()%10;
    }

    id = numero1 +  abecedario[rand()%26] + numero2;

    return id;
}

string generarNIF()
{
    int numero;
    string NIF;
    char letras[] = {'T','R','w','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E'};

    for (int i=1;i<9;i++)
    {
        numero = numero*10 + rand()%10;
    }

    NIF = to_string(numero) + letras[numero%23];

    return NIF;
}

CoordenadasGPS generarCoordenadas()
{
    CoordenadasGPS c;
    int gradLat, minLat, segLat, gradLong, minLong, segLong;

    gradLat = 40;
    minLat = 29 + rand()%3;
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

Paquete generarPaquete()
{
    Paquete p;

    p.idPaquete = generarIdPaquete();
    p.coordenadas = generarCoordenadas();
    p.NIF = generarNIF();

    return p;
}

int main()
{
    srand(time(NULL));
    Cola almacen, muelleNO, muelleNE, muelleSO, muelleSE, zonaNO, zonaNE, zonaSO, zonaSE;
    int paquetesGenerados, paquetesCogidos, paquetesCargados, contador;
    while (paquetesGenerados < N1)
    {
        Paquete p = generarPaquete();
        cout << "Generado paquete con ID" << p.idPaquete << endl; //Código de prueba
        almacen.encolar(p);
        ++paquetesGenerados;
    }

    while (paquetesCogidos < N2)
    {
        int gradLat, minLat, segLat, gradLong, minLong, segLong;
        Paquete p = almacen.desencolar();
        gradLat = p.coordenadas.latitud[0];
        minLat = p.coordenadas.latitud[1];
        segLat = p.coordenadas.latitud[2];
        gradLong = p.coordenadas.longitud[0];
        minLong = p.coordenadas.longitud[1];
        segLong = p.coordenadas.longitud[2];

        if ((minLat >=29) && (segLat >= 30)) || (minLat >=30){
            //Omitimos los grados porque son siempre los mismos (al menos en esta aplicación)
            if (minLong >= 22) muelleNO.encolar(p);
            else muelleNE.encolar(p);
        } else {
            if (minLong >=22) muelleSO.encolar(p);
            else muelleSE.encolar(p);
        }
        ++paquetesCogidos;

        //while (paquetesCargados < N3)
    }

    return 0;
}
