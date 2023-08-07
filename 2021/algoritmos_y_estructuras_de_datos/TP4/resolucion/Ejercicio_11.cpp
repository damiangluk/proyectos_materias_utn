#include <iostream>
using namespace std;

void main11() 
{
    struct VENTA {
        int Modelo;
        char Color;
        int CantVendida;
    };

    VENTA v[35] =
    {
        {1,'A',20},{1,'B',5},{1,'C',43},{1,'D',0},{1,'E',8},
        {2,'A',55},{2,'B',0},{2,'C',33},{2,'D',2},{2,'E',1},
        {3,'A',26},{3,'B',6},{3,'C',3},{3,'D',46},{3,'E',25},
        {4,'A',10},{4,'B',4},{4,'C',18},{4,'D',68},{4,'E',31},
        {5,'A',17},{5,'B',9},{5,'C',4},{5,'D',12},{5,'E',0},
        {6,'A',24},{6,'B',28},{6,'C',35},{6,'D',2},{6,'E',36},
        {7,'A',45},{7,'B',9},{7,'C',34},{7,'D',21},{7,'E',7}
    };

    char colores[5] = { 'A', 'B', 'C', 'D', 'E' };

    FILE* f;
    errno_t pFile = fopen_s(&f, "VENTAS.DAT", "wb+");
    fwrite(v, sizeof(VENTA), 35, f);
    fseek(f, 0, SEEK_SET);

    //EMPIEZA EL EJERICIO
    VENTA ventas[35];
    fread(&ventas, sizeof(VENTA), 35, f);
    int totalModelo[7] = { 0 }, totalColor[5] = { 0 }, totales = 0;
    cout << "VENTAS POR MODELO Y COLOR" << endl;
    for (int i = 0; i < 35; i++)
    {
        cout << "El modelo "<< ventas[i].Modelo << " de color " << ventas[i].Color << " tuvo " << ventas[i].CantVendida << " ventas" << endl;
        if ((i+1) % 5 == 0) cout << endl;

        totales += ventas[i].CantVendida;
        totalModelo[ventas[i].Modelo - 1] += ventas[i].CantVendida;
        if (ventas[i].Color == 'A') {
            totalColor[0] += ventas[i].CantVendida;
        }
        else if (ventas[i].Color == 'B') {
            totalColor[1] += ventas[i].CantVendida;
        }
        else if (ventas[i].Color == 'C') {
            totalColor[2] += ventas[i].CantVendida;
        }
        else if (ventas[i].Color == 'D') {
            totalColor[3] += ventas[i].CantVendida;
        }
        else if (ventas[i].Color == 'E') {
            totalColor[4] += ventas[i].CantVendida;
        }
    }

    cout << "VENTAS POR MODELO" << endl;
    for (int i = 0; i < 7; i++)
    {
        cout << "El modelo " << (i + 1) << " tuvo " << totalModelo[i] << " ventas" << endl;

    }

    cout << endl << "VENTAS POR COLOR" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << "El color " << colores[i] << " tuvo " << totalColor[i] << " ventas" << endl;
    }

    cout << endl << "VENTAS TOTALES" << endl;
    cout << "Las ventas totales son " << totales << endl;
}