#include "Jogador.h"


Jogador::Jogador(){
	lentidao = 5;
	saude = 10;
	nome = TEXT("");
	obj.clear();
}

Jogador::Jogador(tstring n){
	lentidao = 5;
	saude = 10;
	nome = n;
	obj.clear();
}

void Jogador::addObjecto(){ //No m�ximo 15 pedras
}


void Jogador::efeitosObjectos(){
	for (int i = 0; i < obj.size(); i++){
		if (obj[i].getNomeObjecto() == TEXT("Rebu�ado de Cafe�na")){
			obj.pop_back();
			lentidao -= 2;
		}
		if (obj[i].getNomeObjecto() == TEXT("Vitaminas") && saude < 20){
				obj.pop_back();
				saude++;
		}else{
			if (obj[i].getNomeObjecto() == TEXT("Vitaminas") && saude >= 20)
				obj.pop_back();
			}
		if (obj[i].getNomeObjecto() == TEXT("Garrafa de OrangeBull") && saude < 20){
			obj.pop_back();
			saude += 3;
		}
		else{
			if (obj[i].getNomeObjecto() == TEXT("Garrafa de OrangeBull") && saude >= 20)
				obj.pop_back();
		}	
	}
}
