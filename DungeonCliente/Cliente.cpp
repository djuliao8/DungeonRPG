
#include "DungeonComunicacao\Comunicacao.h"

void criarjogo(){
	Comunicacao* c = new Comunicacao();
	system("cls");
	int op = 0, tamX=0, tamY=0;
	tcout << "1 - Jogar com mapa pré-definido \n";
	tcout << "2 - Escolher dimensões do mapa \n";
	tcout << "3 - Sair \n";
	while (op <= 0 || op >= 4){
		tcout << "Opção: ";
		tcin >> op;
		if (op > 0 && op < 4){
			switch (op){
			case 1:c->enviaComando(TEXT("criar pre"));
				break;
			case 2: tcout << "Escolha dimensões: (Minimo 70/70)\n";
					while (tamX < 70 || tamY < 70){
						tcout << "Escreva respectivamente o tamanho X e Y: ";
						tcin >> tamX >> tamY;
					}
					
					c->enviaComando(TEXT("criar" + tamX + tamY));
					break;
			case 3:exit(0);
			default: exit(0);
			}
		}
	}
}

int _tmain(int argc, LPTSTR argv[]){
	Comunicacao* c = new Comunicacao();
	utils();
	int op = 0;
	tcout <<"Dungeon RPG \n\n\n";
	tcout << "1 - Criar Jogo \n";
	tcout << "2 - Juntar a Jogo \n";
	tcout << "3 - Sair \n";
	while (op <= 0 || op >= 4){
		tcout << "Opcao: ";
		tcin >> op;
		if (op > 0 && op < 4){
			switch (op){
			case 1:criarjogo();
					break;
			case 2: c->enviaComando(TEXT("juntar"));
					break;
			case 3:exit(0);
			default: exit(0);
			}
		}
	}
	system("pause");
}

