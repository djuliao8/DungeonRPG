#include "CelulaMapa.h"


CelulaMapa::CelulaMapa()
{	
	objecto = Objectos(TEXT("Vazio"));
}


void CelulaMapa::setParede(){
	parede = 1;
}

void CelulaMapa::setPorta(){
	porta = 1;
}

void CelulaMapa::setObjecto(){
	int aux = rand() % 100;
	
	if (aux > 60)// 60%
	{
		aux = rand() % 100;
		if (aux >= 0 && aux < 40) // 40%
			objecto = Objectos(TEXT("Pedra"));
		else if (aux >= 40 && aux < 60) // 20%
			objecto = Objectos(TEXT("Rebuçado de Cafeína"));
		else if (aux >= 60 && aux < 90) // 30%
			objecto = Objectos(TEXT("Vitaminas"));
		else if (aux >= 90 && aux < 100) // 10%
			objecto = Objectos(TEXT("Garrafa de OrangeBull"));
	}

}

Objectos CelulaMapa:: getObjecto() 
{
	return objecto;
}

void CelulaMapa::removeObjecto() 
{
	objecto = Objectos(TEXT("Vazio"));
}

int CelulaMapa::getPorta()
{
	return porta;
}

bool CelulaMapa::asParede(){
	if (parede == 1)
		return true;
	return false;
}

