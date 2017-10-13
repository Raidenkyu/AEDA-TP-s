#include "Parque.h"
#include <vector>

using namespace std;

ParqueEstacionamento::ParqueEstacionamento(unsigned int lot, unsigned int nMaxCli): lotacao(lot), numMaximoClientes(nMaxCli), vagas(lot) {

};

unsigned int ParqueEstacionamento::getNumLugares() const{
	return this->lotacao;
};

unsigned int ParqueEstacionamento::getNumMaximoClientes() const {
	return this->numMaximoClientes;
}

int ParqueEstacionamento::posicaoCliente(const string & nome) const {
	for (unsigned int i = 0; i < this->clientes.size(); i++)
	{
		if(this->clientes[i].nome == nome)
			return i;
	}
	return -1;
};

bool ParqueEstacionamento::adicionaCliente(const string & nome)
{
	if(clientes.size() == this->numMaximoClientes)
		return false;
	for (unsigned int i = 0; i < this->clientes.size(); i++){
				if(this->clientes[i].nome == nome)
				{
					return false;
				}
		}
	InfoCartao c;
	c.nome = nome;
	c.presente = false;
	this->clientes.push_back(c);
	return true;

};

bool ParqueEstacionamento::entrar(const string & nome){
	if(vagas == 0)
		return false;
	for (unsigned int i = 0; i < clientes.size(); i++)
	{
		if(this->clientes[i].nome == nome)
			{
			if(this->clientes[i].presente)
				return false;
		    else
			{
				this->clientes[i].presente = true;
				vagas--;
				return true;
			}
	}

}
	return false;
};

bool ParqueEstacionamento::retiraCliente(const string & nome){
	for(unsigned int i =0; i < clientes.size(); i++){
		if(this->clientes[i].nome == nome)
		{
			if(this->clientes[i].presente)
			    return false;
			else {
				this->clientes.erase(this->clientes.begin()+i);
				return true;
			}
		}
	}
	return false;
};

bool ParqueEstacionamento::sair(const string & nome){
	for(unsigned int i = 0; i < clientes.size(); i++){
		if(this->clientes[i].nome == nome){
			if(this->clientes[i].presente){
				this->clientes[i].presente = false;
				vagas++;
				return true;
			}
			else return false;
		}
	}
	return false;
}

unsigned int ParqueEstacionamento::getNumLugaresOcupados() const{
	return (this->lotacao - this->vagas);
}

unsigned int ParqueEstacionamento::getNumClientesAtuais() const{
	return this->clientes.size();
}

const ParqueEstacionamento & ParqueEstacionamento::operator += (const
 ParqueEstacionamento & p2){
	for(unsigned int i = 0; i < p2.getNumClientesAtuais() && this->clientes.size() != this->numMaximoClientes;i++){
		this->clientes.push_back(p2.clientes[i]);
	}
};




