#include <iostream>
using namespace std;

int main()
{
	int num = 31;
	while (num >= 30 || num < 1)
	{
		cout << "Ingrese un numero natural menor a 30" << endl;
		cin >> num;
	}

	int vec[30] = { 0 }, a = 0;

	for (int i = 0; i < num; i++)
	{
		a += 2;
		vec[i] = a;
	}

	for (int i = 0; i < num; i++)
	{
		cout << "Pos " << i +1 << ": " << vec[i] << endl;
	}
}