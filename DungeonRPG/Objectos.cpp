#include "Objectos.h"


Objectos::Objectos()
{

}
Objectos::Objectos(tstring nome)
{
	this->nome = nome;
}

tstring Objectos::getNomeObjecto()
{
	return nome;
}


