#include "Objectos.h"


Objectos::Objectos(){
	int aux = rand() % 10; //4/10 - Pedras --- 2/10 - Rebuçados --- 3/10 - Vitaminas --- 1/10 - OrangeBull
	if (aux == 0 || aux == 1 || aux == 2 || aux == 3) //Pedra
		Objecto = TEXT("Pedra");
	else{
		if (aux == 4 || aux == 5 || aux == 6) //Rebuçados de Cafeína
			Objecto = TEXT("Rebuçado de Cafeína");
		else{
			if (aux == 7 || aux == 8) //Vitaminas
				Objecto = TEXT("Vitaminas");
			else
				Objecto = TEXT("Garrafa de OrangeBull"); //OrangeBull
		}
	}
}

Objectos Objectos::getObjecto(){
	 return *this;
 }

tstring Objectos::getNomeObjecto(){
	return Objecto;
}


