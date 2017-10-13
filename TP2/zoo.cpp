#include "zoo.h"

int Animal::maisJovem = 9999;

Veterinario::Veterinario(string name, long cod):nome(name),codOrdem(cod){};

Animal::Animal(string nome, int idade): nome(nome), idade(idade) {
	this->vet = NULL;
	if(this->idade < maisJovem)
		maisJovem = this->idade;
};

Animal::~Animal(){};

Cao::Cao(string nome, int idade, string raca):Animal(nome,idade), raca(raca) {
	this->vet = NULL;
};

Voador::Voador(int vmax, int amax): velocidade_max(vmax), altura_max(amax) {};

Voador::~Voador(){};

Morcego::Morcego(string nome, int idade, int vmax, int amax):Animal(nome,idade),Voador(vmax, amax){
	this->vet = NULL;
};

string Animal::getNome() const {
	return nome;
};



string Veterinario::getNome() const {
	return nome;
};


int Zoo::numAnimais() const {
	return animais.size();
};

int Zoo::numVeterinarios() const {
	return veterinarios.size();
};

int Animal::getIdade(){
	return this->idade;
}

int Animal::getMaisJovem(){
	return maisJovem;
};

string Animal::getInformacao() const{
	return this->nome+ ", " + to_string(this->idade);
};

string Cao::getInformacao() const{
	return this->nome + ", " + to_string(this->idade) + ", " + (this->vet != NULL? this->vet->getInformacao() + ", "  : "") +  this->raca;
};

string Voador::getInformacao() const{
	return to_string(this->velocidade_max) + ", " + to_string(this->altura_max);
};

string Morcego::getInformacao() const{
	return this->nome + ", " + to_string(this->idade) + ", " + (this->vet != NULL? this->vet->getInformacao() + ", "  : "") + to_string(this->velocidade_max) + ", " + to_string(this->altura_max);
};
string Zoo::getInformacao() const{
	string info;
	for(unsigned int i = 0; i < this->animais.size();i++){
		info = info + this->animais.at(i)->getInformacao() + "\n";
	}
	return info;
}

string Veterinario::getInformacao() const {
	return this->nome + ", " + to_string(this->codOrdem);
}


bool Cao::eJovem()const{
	if (this->idade < 5)
		return true;
	else return false;
};

bool Morcego::eJovem()const{
	if (this->idade < 4)
		return true;
	else return false;
};

void Zoo::adicionaAnimal(Animal *a1){
	this->animais.push_back(a1);
}

vector<Animal *> Zoo::getAnimais(){
	return this->animais;
}

bool Zoo::animalJovem(string nomeA){
	for(unsigned int i = 0; i < this->animais.size(); i++){
		if(this->animais.at(i)->getNome() == nomeA)
			return true & this->animais.at(i)->eJovem();
	}
}

void Animal::setVet(Veterinario * vet){
	this->vet = vet;
}

Veterinario * Animal::getVet(){
	return this->vet;
}

void Zoo::alocaVeterinarios(istream &isV){
	string name;
	string ord;
	Veterinario * vet;
	for(unsigned int i = 0;i < this->animais.size() && getline(isV, name);i++){
		getline(isV, ord);
		name = name.erase(name.size() -1);
		vet = new Veterinario(name, stoi(ord));
		this->animais.at(i)->setVet(vet);
		this->veterinarios.push_back(vet);
	}
}

bool Zoo::removeVeterinario (string nomeV){
	unsigned int i;
	bool found = false;
	for (i = 0; i < this->veterinarios.size(); i++){
		if(this->veterinarios[i]->getNome() == nomeV){
			this->veterinarios.erase(this->veterinarios.begin() +i);
			found = true;
			break;
		}
	}
	if(!found)
		return false;
	for (unsigned int j = 0; j < this->animais.size(); j++){
		if(this->animais[j]->getVet()->getNome() == nomeV && i < this->veterinarios.size()){
			this->animais[j]->setVet(this->veterinarios[i]);
			return true;
		}
	}
	return false;
}

bool Zoo::operator < (Zoo& zoo2) const{
	int total = 0, total2 = 0;
	for(unsigned int i = 0; i < this->animais.size();i++){
		total += this->animais[i]->getIdade();
	}
	for(unsigned int i = 0; i < zoo2.animais.size();i++){
			total2 += zoo2.getAnimais().at(i)->getIdade();
	}
	return total < total2;
}
