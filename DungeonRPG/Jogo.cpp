#include "Jogo.h"

Jogo::Jogo(int lin,int col,bool pre)
{
	mapa = new Mapa(lin, col, pre);
	aDecorrer = false;
	jogoCriado = true;
}



Jogo::Jogo()
{
	aDecorrer = false;
	jogoCriado = false;
}
void Jogo::addJogador(Jogador j) 
{
	jogEmJogo.push_back(j);
}

bool Jogo::removeJogador(Jogador j)
{
	int pos = -1;

	for (int i = 0; i < (int)jogEmJogo.size(); i++)
	{
		if (jogEmJogo[i].getNome() == j.getNome())
			pos = i;
	}

	if (pos != -1)
	{
		jogEmJogo.erase(jogEmJogo.begin() + pos);
		return true;
	}
	return false;
		
}

void Jogo::setJogoCriado(bool jogoCriado)
{
	this->jogoCriado = jogoCriado;
}

bool Jogo::getJogoCriado()
{
	return jogoCriado;
}

bool Jogo::getJogoADecorrer()
{
	return aDecorrer;
}

void Jogo::setADecorrer(bool aDecorrer)
{
	this->aDecorrer = aDecorrer;
}

bool Jogo::verificaJogador(Jogador j) {
	for (int i = 0; i < (int)jogEmJogo.size();i++)
	{
		if (j.getNome() == jogEmJogo[i].getNome())
			return true;
	}
	return false;
}

int Jogo::getNumJogadores()
{
	return (int)jogEmJogo.size();
}

void Jogo::setPredefinido(bool predefinido)
{
	this->predefinido = predefinido;
}

bool Jogo::getPredefinido()
{
	return predefinido;
}

bool Jogo::jogadorInPos(int x,int y)
{
	for (int i = 0; i < (int)jogEmJogo.size();i++)
	{
		if (jogEmJogo[i].getPosX() == x && jogEmJogo[i].getPosY() == y)
			return true;
	}
	return false;
}

Jogador Jogo::getJogadorByNome(Jogador j)
{
	for (int i = 0; i < (int)jogEmJogo.size();i++)
	{
		if (j.getNome() == jogEmJogo[i].getNome())
			return jogEmJogo[i];
	}
	return Jogador();
}

Jogador Jogo::getJogadorByPos(int x, int y)
{
	for (int i = 0; i < (int)jogEmJogo.size();i++)
	{
		if (jogEmJogo[i].getPosX() == x && jogEmJogo[i].getPosY() == y)
			return jogEmJogo[i];
	}
	return Jogador();
}

Jogador Jogo::getJogadorByPosInArray(int pos)
{
	return jogEmJogo[pos];
}
void Jogo::actualizaVector(Jogador jogador,int j)
{
	int pos = -1;
	for (int i = 0; i < (int)jogEmJogo.size(); i++)
	{
		if (jogEmJogo[i].getHPipeReceber() == jogador.getHPipeReceber())
			pos = i;
	}

	if (pos != -1)
	{
		jogEmJogo.erase(jogEmJogo.begin() + pos);
		jogEmJogo.insert(jogEmJogo.begin() + j,jogador);
	}
}

tstring Jogo::lutaEntreJogadores(Jogador jAtacante, Jogador jAtacado)
{
	tstringstream aux;

	if (!jAtacado.getErro())
	{
		aux << jAtacado.getNome() << TEXT(" em [ ") << jAtacado.getPosX() << TEXT(" ][ ") << jAtacado.getPosY() << TEXT(" ]");
		
		//Ataque do atacante
		if (jAtacante.getPedra() && jAtacante.removePedra())
		{
			jAtacado.sofreDano(2);
			aux << TEXT(" sofreu 2 de dano!") << TEXT(" Tem ") << jAtacado.getVida() << TEXT(" de vida!") << endl;

		}
		else
		{
			jAtacado.sofreDano(1);
			aux << TEXT(" sofreu 1 de dano!") << TEXT(" Tem ") << jAtacado.getVida() << TEXT(" de vida!") << endl;
		}

		enviaMensagem(aux.str(), jAtacado.getHPipeEnviar());
		
		//Ataque do atacado

		if (!jAtacado.isMorto())
		{
			if (jAtacado.getPedra() && jAtacado.removePedra())
			{
				jAtacante.sofreDano(2);
				aux << TEXT("Sofreu 2 de dano tem ") << jAtacante.getVida() << TEXT(" de vida!") << endl;
			}
			else
			{
				jAtacante.sofreDano(1);
				aux << TEXT("Sofreu 1 de dano tem ") << jAtacante.getVida() << TEXT(" de vida!") << endl;
			}
		}
		else
		{
			aux << TEXT("Matou ") << jAtacado.getNome() << endl;
			jAtacado.setEstado(QUEROJOGAR);
			enviaMensagem(TEXT("Perdeu o jogo!"), jAtacado.getHPipeEnviar());
			removeJogador(jAtacado);
		}

		if (jAtacante.isMorto()) 
		{
			aux << TEXT("Foi morto por ") << jAtacado.getNome() << TEXT("! Perdeu o jogo!");
			jAtacante.setEstado(QUEROJOGAR);
			removeJogador(jAtacante);
		}

	}
	else
		aux << TEXT("");

	actualizaVector(jAtacado, 0);
	actualizaVector(jAtacante, 0);

	return aux.str();
}

tstring Jogo::lutaJogador(Jogador j)
{
	tstringstream aux;
	Jogador jog = getJogadorByNome(j);

	int posX = jog.getPosX();
	int posY = jog.getPosY();

	//Norte
	aux << lutaEntreJogadores(getJogadorByNome(j), getJogadorByPos(posX, posY + 1));
	//Nordeste
	aux << lutaEntreJogadores(getJogadorByNome(j), getJogadorByPos(posX + 1, posY + 1));
	//Este
	aux << lutaEntreJogadores(getJogadorByNome(j), getJogadorByPos(posX + 1, posY));
	//Sudeste
	aux << lutaEntreJogadores(getJogadorByNome(j), getJogadorByPos(posX + 1, posY - 1));
	//Sul
	aux << lutaEntreJogadores(getJogadorByNome(j), getJogadorByPos(posX, posY - 1));
	//Sudoeste
	aux << lutaEntreJogadores(getJogadorByNome(j), getJogadorByPos(posX - 1, posY - 1));
	//Oeste
	aux << lutaEntreJogadores(getJogadorByNome(j), getJogadorByPos(posX - 1, posY));
	//Noroeste
	aux << lutaEntreJogadores(getJogadorByNome(j), getJogadorByPos(posX - 1, posY + 1));

	return aux.str();


}

tstring Jogo::moveJogador(Jogador j,tstring mov,int posX,int posY)
{
	tstringstream aux;

	if (!mapa->verificaParede(posX, posY))
	{
		if (!jogadorInPos(posX, posY))
		{
			j.setPosX(posX);
			j.setPosY(posY);
			actualizaVector(j, 0);
			aux << TEXT("Moveu-se para [" << j.getPosX()) << TEXT("][") << j.getPosY() << TEXT("]! ");
		}
		else
		{
			aux << TEXT("Já existe um jogador em [") << posX << TEXT("][") << posY << TEXT("]! ");
		}
	}
	else
	{
		aux << TEXT("Não pode mover-se para ") << mov << TEXT("! ");
	}

	return aux.str();
}

tstring Jogo::apanharObjecto(Jogador jog)
{
	tstringstream aux;

	Jogador j = getJogadorByNome(jog);

	int posX = j.getPosX();
	int posY = j.getPosY();

	Objectos obj = mapa->getObjecto(posX, posY);

	if (obj.getNomeObjecto() == TEXT("Pedra"))
	{
		if (j.addPedra(obj))
			aux << TEXT("Apanhou ") << obj.getNomeObjecto() << TEXT("!") << endl;
		else
		{
			aux << TEXT("Não pode apanhar mais pedras!");
			return aux.str();
		}
	}
	else if (obj.getNomeObjecto() == TEXT("Vitaminas"))
	{
		j.usarVitaminas();
		aux << TEXT("Comsumiu vitaminas!");
	}
	else if (obj.getNomeObjecto() == TEXT("Garrafa de OrangeBull"))
	{
		j.usarRedbull();
		aux << TEXT("Comsumiu Garrafa de OrangeBull!");
	}
	else if (obj.getNomeObjecto() == TEXT("Rebuçado de Cafeína"))
	{
		j.usarRebucado();
		aux << TEXT("Comsumiu Rebuçado de Cafeína!");
	}
	else
	{
		aux << TEXT("");
		return aux.str();
	}

	actualizaVector(j, 0);
	mapa->removeObjecto(posX, posY);

	return aux.str();
}

tstring Jogo::proxMovimento(Jogador jog)
{
	Jogador j = getJogadorByNome(jog);

	tstringstream aux;

	int posX = j.getPosX();
	int posY = j.getPosY();

	aux << endl;
	//Verifica para a esquerda
	if (!jogadorInPos(posX - 1, posY) && !mapa->verificaParede(posX - 1, posY))
		aux << TEXT(" Esquerda!");
	//Verifica para a direita
	if (!jogadorInPos(posX + 1, posY) && !mapa->verificaParede(posX + 1, posY))
		aux << TEXT(" Direita!");
	//Verifica para a cima
	if (!jogadorInPos(posX, posY + 1) && !mapa->verificaParede(posX, posY + 1))
		aux << TEXT(" Cima!");
	//Verifica para baixo
	if (!jogadorInPos(posX, posY - 1) && !mapa->verificaParede(posX, posY - 1))
		aux << TEXT(" Baixo!");
	aux << endl;

	return aux.str();
}

tstring Jogo::açãoJogador(tstring movimento,Jogador jog)
{
	tstringstream aux;

	Jogador j = getJogadorByNome(jog);

	int posX = j.getPosX();
 	int posY = j.getPosY();

	//Movimento
	if (movimento == TEXT("esq"))
		aux << moveJogador(j, TEXT("esquerda"), posX - 1, posY);
	else if (movimento == TEXT("dir"))
		aux << moveJogador(j, TEXT("direita"), posX + 1, posY);
	else if (movimento == TEXT("cima"))
		aux << moveJogador(j,movimento, posX, posY + 1);
	else if (movimento == TEXT("baixo"))		
		aux << moveJogador(j,movimento, posX, posY - 1);
	else
	{
		aux << TEXT("Comando inválido!");
		return aux.str();
	}
	//Apanha objecto automaticamente
	aux << apanharObjecto(j);

	//Mostra proximos movimentos
	aux << proxMovimento(j);
	
	//Luta com jogadores
	aux << lutaJogador(j);
	

	return aux.str();
}

tstring Jogo::posActual(Jogador jog)
{
	tstringstream aux;

	Jogador j = getJogadorByNome(jog);

	aux << TEXT("Jogador na posição [ ") << j.getPosX() << TEXT(" ][ ") << j.getPosY() << TEXT(" ]! ") << endl;
	aux << proxMovimento(j);

	return aux.str();
}

tstring Jogo::usarPedra(Jogador jog, tstring cmd)
{
	tstringstream aux;

	Jogador j = getJogadorByNome(jog);

	if (cmd == TEXT("on"))
	{
		j.setPedra(true);
		actualizaVector(j, 0);
		aux << TEXT("Uso pedra activo!");
	}
	else if (cmd == TEXT("off"))
	{
		j.setPedra(false);
		actualizaVector(j, 0);
		aux << TEXT("Uso pedra desactivo!");
	}
	else
		aux << TEXT("Comando inválido!");
	return aux.str();
}

void Jogo::colocaJogadores()
{
	srand(time(NULL));
	int posX, posY;
	
	for (int i = 0; i < (int)jogEmJogo.size(); i++)
	{
		do {
			posX = rand() % (mapa->getLinhas()) + 1;
			posY = rand() % (mapa->getColunas()) + 1;
		} while (mapa->verificaParede(posX, posY) && jogadorInPos(posX, posY));
		
		jogEmJogo[i].setPosX(posX);
		jogEmJogo[i].setPosY(posY);
		actualizaVector(jogEmJogo[i], i);
	}

}

void Jogo:: enviaMensagem(tstring cmd, HANDLE hPipeEnviar)
{
	Msg msg;

	if (hPipeEnviar == NULL)
		return;
	wcscpy_s(msg.cmd,cmd.c_str());
	msg.erro = true;

	DWORD n;
	WriteFile(hPipeEnviar, &msg, sizeof(msg), &n, NULL);
}