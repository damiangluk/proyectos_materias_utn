#include <iostream>
using namespace std;

int main()
{
	int tablaDeMultiplicar[10][10];
	for (int i = 0; i < 10; i++)
	{
		for (int a = 0; a < 10; a++)
		{
			tablaDeMultiplicar[i][a] = (i + 1) * (a + 1);
		}
	}

	for (int i = 0; i < 10; i++)
	{
		cout << "Tabla del " << i + 1 << ": ";
		for (int a = 0; a < 10; a++)
		{
			cout << (a + 1) * (i + 1);
			if (a != 9)
			{
				cout << " - ";
			}
		}
		cout << endl;
	}
}