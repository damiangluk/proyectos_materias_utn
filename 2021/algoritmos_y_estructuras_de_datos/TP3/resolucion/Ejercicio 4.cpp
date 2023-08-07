#include <iostream>
using namespace std;

int main()
{
	int A[10] = { 10,53,23,56,-34,-21,45,6,12,-65 }, B[10] = { 4,3,23,56,-1,-21, 0, 33, 12, 7 };

	cout << "El vector A es el siguiente: ";
	for (int i = 0; i < 10; i++)
	{
		cout << A[i] << " ";
	}
	cout << endl;
	cout << "El vector B es el siguiente: ";
	for (int i = 0; i < 10; i++)
	{
		cout << B[i] << " ";
	}
	cout << endl;
	cout << "El vector C es el siguiente: ";
	for (int i = 0; i < 10; i++)
	{
		i % 2 == 0 ? cout << B[i] << " " : cout << A[i] << " ";
	}
	cout << endl;
	cout << "El vector D es el siguiente: ";
	for (int i = 0; i < 10; i++)
	{
		A[i] == B[i] ? cout << "0 " : cout << "null ";
	}
	cout << endl;
}