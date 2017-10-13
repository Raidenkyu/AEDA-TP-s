/*
 * zoo.h
 */

#ifndef ZOO_H_
#define ZOO_H_

#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Veterinario {
	string nome;
	long codOrdem;
	//...
public:
	string getInformacao() const;
	string getNome() const;
	Veterinario(string name, long cod);
	//...
};

class Animal {
protected:
	string nome;
	int idade;
	Veterinario *vet;
	static int maisJovem;
public:
	Animal(string nome, int idade);
	virtual ~Animal();
	string getNome() const;
	int getIdade();
	virtual string getInformacao() const;  // informacao sobre nome animal, idade animal, nome do veterinario
	virtual bool eJovem() const = 0;
	static int getMaisJovem();
	void setVet(Veterinario * vet);
	Veterinario * getVet();
};



class Cao: public Animal {
	string raca;
public:
	Cao(string nome, int idade, string raca);
	bool eJovem() const;
	string getInformacao() const;
};



class Voador {
protected:
	int velocidade_max;
	int altura_max;
public:
	Voador(int vmax, int amax);
	virtual ~Voador();
	virtual string getInformacao() const;  // informacao sobre velocidade, altitude maxima
	//...
};


class Morcego: public Animal, public Voador {
public:
	Morcego(string nome, int idade, int vmax, int amax);
	bool eJovem() const;
	string getInformacao() const;
};


class Zoo {
	vector<Animal *> animais;
	vector<Veterinario *> veterinarios;
public:
	int numAnimais() const;
	int numVeterinarios() const;
	vector<Animal *> getAnimais();
	void adicionaAnimal(Animal *a1);
	string getInformacao() const;
	bool animalJovem(string nomeA);
	void alocaVeterinarios(istream &isV);
	bool removeVeterinario(string nomeV);
	bool operator < (Zoo& zoo2) const;
};


#endif /* ZOO_H_ */
