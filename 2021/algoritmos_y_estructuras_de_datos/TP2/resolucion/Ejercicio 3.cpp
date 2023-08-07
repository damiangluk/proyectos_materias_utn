#include <iostream>
using namespace std;

float CantidadMinutosExcedidos(float, float);
float montoTotal(float, float, float);


void main()
{
	float costo, cargoExceso, minutosLibres, minutosUsados;

	cout << "Ingrese el costo del abono telefonico: ";
	cin >> costo;
	cout << "Ingrese los minutos libres que incluye el abono: ";
	cin >> minutosLibres;
	cout << "Ingrese el cargo en pesos por minuto excedente: ";
	cin >> cargoExceso;
	cout << "Ingrese los minutos usados durante el mes: ";
	cin >> minutosUsados;


	float minutosExcedidos = CantidadMinutosExcedidos(minutosUsados, minutosLibres);
	float montoAbonar = montoTotal(costo, cargoExceso, minutosExcedidos);

	minutosExcedidos != 0 ? cout << "Se excedio en " << minutosExcedidos << " minutos" << endl : cout << "No hubo exceso" << endl;
	cout << "El monto total a abonar es: $" << montoAbonar << endl;

}


float CantidadMinutosExcedidos(float minutosUsados, float minutosLibres)
{
	if (minutosUsados > minutosLibres) {
		return  minutosUsados - minutosLibres;
	}
	else {
		return 0;
	}

}
float montoTotal(float costo, float cargoExceso, float minutosExcedidos)
{
	float abonar = costo + minutosExcedidos * cargoExceso;
	abonar += (abonar * 21/100);
	return abonar;
}