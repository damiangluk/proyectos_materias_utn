#include <iostream>
using namespace std;
void main()
{
	int fecha;
	int cifras[8 + 1];
	int i = 0;

	cout << "Ingrese una fecha con el formato (AAAAMMDD): ";
	cin >> fecha;

	while (fecha > 0)
	{
		cifras[i] = fecha % 10;
		fecha = fecha / 10;
		i++;
	}
	cout << "El anio es: " << cifras[7] << cifras[6] << cifras[5] << cifras[4] << endl;
	cout << "El mes es: " << cifras[3] << cifras[2] << endl;
	cout << "El dia es: " << cifras[1] << cifras[0];

}