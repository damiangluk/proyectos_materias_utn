#include <iostream>
using namespace std;

struct DESTINO {
    float Distancia;
    int NumeroDestino;
};
struct VIAJE {
    int NumeroChofer;
    int NumeroDestino;
    char Patente[6 + 1];
};
int Busqueda(DESTINO[], int, int);

void main() 
{
    cout << "INGRESO DESTINOS" << endl;
    FILE* f2;
    errno_t pFile2 = fopen_s(&f2, "DESTINOS.DAT", "wb+");
    DESTINO destino;
    int CantDestinos = 0;
    for (int CantDestinos = 0; CantDestinos < 10; CantDestinos++)
    {
        do {
            cout << "Ingrese el numero del destino: ";
            cin >> destino.NumeroDestino;;
        } while (destino.NumeroDestino > 999);

        if (destino.NumeroDestino <= 0)
        {
            break;
        }

        do {
            cout << "Ingrese la distancia en kilometros: ";
            cin >> destino.Distancia;
        } while (destino.Distancia < 1);

        fwrite(&destino, sizeof(DESTINO), 1, f2);
    }

    cout << endl << "INGRESO VIAJES" << endl;
    FILE* f;
    errno_t pfile = fopen_s(&f, "VIAJES.DAT", "wb+");
    int CantViajes = 0;
    VIAJE viaje;
    for (CantViajes = 0; CantViajes < 10; CantViajes++)
    {
        do {
            cout << "Ingrese el numero del chofer: ";
            cin >> viaje.NumeroChofer;
        } while (viaje.NumeroChofer > 150);

        if (viaje.NumeroChofer <= 0)
        {
            break;
        }

        do {
            cout << "Ingrese el numero del destino: ";
            cin >> viaje.NumeroDestino;
        } while (viaje.NumeroDestino < 1 || viaje.NumeroDestino > 1000);

        do {
            cout << "Ingrese la patente del camion: ";
            cin >> viaje.Patente;
        } while (strlen(viaje.Patente) != 6);

        fwrite(&viaje, sizeof(VIAJE), 1, f);
    }

    fseek(f, 0, SEEK_SET);
    fseek(f2, 0, SEEK_SET);

    DESTINO dests[10];
    fread(&dests, sizeof(DESTINO), CantDestinos, f2);

    VIAJE viajes[10];
    fread(&viajes, sizeof(VIAJE), CantViajes, f);

    int ViajesPorDestino[10] = { 0 }; // Punto 1
    int choferes[10], KMPorChofer[10], CantChoferes = 0; // Punto 2
    char patentes[10][6 + 1]; int CantPatentes = 0; // Punto 3
    for (int i = 0; i < CantViajes; i++)
    {
        //Recorro viajes para punto 1
        int posDestino = Busqueda(dests, viajes[i].NumeroDestino, CantDestinos);
        if (posDestino != -1)
        {
            ViajesPorDestino[posDestino]++;
        }
        
        ////Recorro viajes para punto 2
        int posChofer = -1;
        for (int a = 0; a < CantChoferes; a++)
        {
            if (choferes[a] == viajes[i].NumeroChofer)
            {
                posChofer = a;
                break;
            }
        }

        if (posChofer == -1)
        {
            choferes[CantChoferes] = viajes[i].NumeroChofer;
            KMPorChofer[CantChoferes] = dests[posDestino].Distancia;
            CantChoferes++;
        }
        else
        {
            KMPorChofer[posChofer] += dests[posDestino].Distancia;
        }
        
        //Recorro viajes para punto 3
        if (viajes[i].NumeroDestino == 116)
        {
            bool EstaLaPatente = false;
            for (int a = 0; a < CantPatentes; a++)
            {
                if (!strcmp(patentes[a],viajes[i].Patente))
                {
                    EstaLaPatente = true;
                    break;
                }
            }
            if (!EstaLaPatente)
            {
                strcpy_s(patentes[CantPatentes], viajes[i].Patente);
                CantPatentes++;
            }
        }
    }

    cout << endl << "RESULTADOS" << endl;
    //Resultado punto 1
    for (int i = 0; i < CantDestinos; i++)
    {
        cout << "El destino " << dests[i].NumeroDestino << " tiene " << ViajesPorDestino[i] << " viajes realizados" << endl;
    }
    
    int MenorChofer = choferes[0], MenorKM = KMPorChofer[0];
    for (int i = 1; i < CantChoferes; i++)
    {
        if (KMPorChofer[i] < MenorKM)
        {
            MenorKM = KMPorChofer[i];
            MenorChofer = choferes[i];
        }
    }

    //Resultado punto 2
    cout << endl << "El chofer con menos distancia recorrida es el numero " << MenorChofer << endl;

    //Resultado punto 3
    if (CantPatentes == 0)
    {
        cout << endl << "No hubo camiones que se dirijan al destino 116" << endl;
    }
    else
    {
        cout << endl << "Las patentes que se dirigieron al destino 116 son: ";
        for (int i = 0; i < CantPatentes; i++)
        {
            cout << patentes[i] << " ";
        }
        cout << endl;
    }
}

int Busqueda(DESTINO v[], int buscado, int N) {

    for (int i = 0; i < N; i++)
    {
        if (buscado == v[i].NumeroDestino)
        {
            return i;
        }
    }
    return -1;
}