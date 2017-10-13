#include <iostream>
#include <vector>

using namespace std;

/**
 * Vers�o da classe generica Grafo usando a classe vector
 */

template <class N, class A> class Aresta;

template <class N, class A>
class No {
public:
	N info;
	vector< Aresta<N,A> > arestas;
	No(N inf) {
		info = inf;
	}
};

template <class N, class A>
class Aresta {
public:
	A valor;
	No<N,A> *destino;
	Aresta(No<N,A> *dest, A val) {
		valor = val;
		destino = dest;
	}
};

template <class N, class A> 
class Grafo { 
	vector< No<N,A> *> nos;
  public: 
    Grafo();
    ~Grafo(); 
    Grafo & inserirNo(const N &dados);
    Grafo & inserirAresta(const N &inicio, const N &fim, const A &val);
    Grafo & eliminarAresta(const N &inicio, const N &fim);
    A & valorAresta(const N &inicio, const N &fim);
    int numArestas(void) const;
    int numNos(void) const;
    void imprimir(std::ostream &os) const; 
};

template <class N, class A> 
std::ostream & operator<<(std::ostream &out, const Grafo<N,A> &g);

// excecao  NoRepetido
template <class N>
class NoRepetido
{
public:
   N info;
   NoRepetido(N inf) { info=inf; }
};
template <class N>
std::ostream & operator<<(std::ostream &out, const NoRepetido<N> &no)
{ out << "No repetido: " << no.info; return out; }


// excecao NoInexistente
template <class N>
class NoInexistente {
public:
	N info;
	NoInexistente(N inf) {
		info = inf;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const NoInexistente<N> &ni)
{ out << "No inexistente: " << ni.info; return out; }

template <class N>
class ArestaRepetida {
public:
	N inicio, fim;
	ArestaRepetida(N inicio, N fim) {
		this->inicio = inicio;
		this->fim = fim;
	}
};

template <class N>
std::ostream & operator<<(std::ostream &out, const ArestaRepetida<N> &ar)
{ out << "Aresta repetida: " << ar.inicio << " , " << ar.fim; return out; }

template <class N, class A>
Grafo<N,A>::Grafo() {}

template <class N, class A>
Grafo<N,A>::~Grafo(){
	typename vector <No <N,A>*> ::const_iterator it;
	for(it = this->nos.begin(); it != nos.end(); it++){
		delete *it;
	}
}

template <class N, class A>
int Grafo<N,A>::numArestas(void) const{
	unsigned int numArestas = 0;
	for(unsigned int i = 0;i < this->nos.size(); i++)
	{
		numArestas += this->nos[i]->arestas.size();
	}
	return numArestas;
}

template <class N, class A>
int Grafo<N,A>::numNos(void) const{
	return this->nos.size();
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirNo(const N &dados){

	for(unsigned int i = 0; i < this->nos.size(); i++){
		if(dados == this->nos[i]->info){
			throw NoRepetido<N> (dados);
			return *this;
		}
	}
	No<N,A> * no = new No<N,A>(dados);
	this->nos.push_back(no);
	return *this;
}

template <class N, class A>
Grafo<N,A> & Grafo<N,A>::inserirAresta(const N &inicio, const N &fim, const A &val){
	Aresta<N,A> *a;
	for(unsigned int i = 0; i < this->nos.size(); i++){
		if(this->nos.at(i)->info == inicio){
			for(unsigned int j = 0; j < this->nos[i]->arestas.size(); j++){
				if(this->nos[i]->arestas[j].destino->info == fim){
					throw ArestaRepetida<N>(inicio, fim);
				}
			}
			for(unsigned int j = 0; j < this->nos.size();j++){
				if(this->nos.at(i)->info == fim){
					a = new Aresta<N,A>(this->nos[j],val);
					this->nos.at(i)->arestas.push_back(*a);
					return *this;
				}
			}
		}
		throw NoInexistente<N>(fim);
	}
	throw NoInexistente<N>(inicio);
	return *this;
}


