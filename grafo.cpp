// Grafos - Lista de adjacência

#include <iostream>
#include <list>
#include <algorithm> // função find
#include <list>
#include <queue>
#include <cstring>

#include <utility>      // std::pair, std::make_pair
#include <string>       // std::string
#include <iostream>     // std::cout
#define MAX 1000000 // distância exacerbada 

using namespace std;

class Grafo {
	int V; // número de vértices
	list<std::pair<int,int> > *adj; // ponteiro para um array contendo as listas de adjacências

public:
	Grafo(int V); // construtor
	void adicionarAresta(int v1, int v2, int distancia); // adiciona uma aresta no grafo
	void imprimirGrafo(std::string *nomes);
	int dijkstra(int v1, int v2); // calcula o menor caminho entre dois nós
	void print_nomes(std::string *nomes);
};

/* Algoritmos do Grafo */

Grafo::Grafo(int V) {
	this->V = V; // atribui o número de vértices
	adj = new list< std::pair<int,int> >[V]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2, int distance) {
	// adiciona vértice v2 à lista de vértices adjacentes de v1
	adj[v1].push_back(make_pair(v2, distance));
	// como o grafo é unidirecional, deve-se adicionar v1 na lista de v2
	adj[v2].push_back(make_pair(v1, distance));
}


int Grafo::dijkstra(int v1, int v2) {

	int vetor_distancia[V];/* vetor de distância */
	bool nos_visitados[V];/* vetor de nós visitados */

	priority_queue < pair<int, int>,
		vector<pair<int, int> >, greater<pair<int, int> > > dist_vertice;

	for(int i = 0; i < V; i++) {
			vetor_distancia[i] = MAX;
			nos_visitados[i] = false;
	}

	vetor_distancia[v1] = 0; // a distancia da origem igual a 0

	dist_vertice.push(make_pair(vetor_distancia[v1], v1));
	
	while(!dist_vertice.empty()) {
		pair<int, int> par_aux = dist_vertice.top();

		int vertice = par_aux.second;
		dist_vertice.pop();

		if(nos_visitados[vertice] == false){
			
			nos_visitados[vertice] = true;
			list<pair<int, int>>::iterator j;

			for(j = adj[vertice].begin(); j != adj[vertice].end(); j++) {

				int vertice_adj = j->first;
				int valor_aresta = j->second;

				if(vetor_distancia[vertice_adj] > (vetor_distancia[vertice] + 
					valor_aresta)) {

					vetor_distancia[vertice_adj] = vetor_distancia[vertice] + 
						valor_aresta;

					dist_vertice.push(make_pair(vetor_distancia[vertice_adj], 
						vertice_adj));
				}	
			}

		}

	}	

	return vetor_distancia[v2];
}

/* Para melhor apresentação do algoritmo */

void Grafo::imprimirGrafo(std::string *nomes) {
	for (int i = 0; i < V; i++) {
		for(pair<int,int> item : adj[i]) {
			cout << nomes[i] << " - ";
			cout << nomes[item.first];
			cout << ": " << item.second << endl;
		}

	}
}

void Grafo::print_nomes(std::string *nomes) {

	for(int index = 0; index < V; index++) {
		cout << index << ". "<< nomes[index] << endl;
	}
}

void menu(Grafo grafo, std::string *nomes) {

	cout << "**********************************************************************" << endl;
	cout << "			LATAM Airlines Brasil					 " << endl;

	cout << "	Bem vindo a LATAM Airlines Brasil!						 " << endl;
	cout << "	Aqui estao listados os aeroportos do Brasil e as distancia\n        entre eles." << endl;
	cout << "	Lembre-se: Nem todos os aeroportos possuem voos diretos.\n"<< endl;
	cout << "		Por isso decidiremos a melhor rota para voce!!		 " << endl;

	cout << "**********************************************************************" << endl;


	cout << "		Aeroportos e seus voos diretos				 \n" << endl;
	grafo.imprimirGrafo(nomes);

	cout << "		\nIndice dos aeroportos  				 " << endl;
	grafo.print_nomes(nomes);

	cout << "		Escolha seu origem e destino  				 " << endl;

	int orig = 0, dest = 0;
	cout << " Origem: ";
	cin >> orig;
	cout << " Destino: ";
	cin >> dest;

	cout << "	\nMenor distancia entre " << nomes[orig] << " - " << nomes[dest] << endl;
	cout << "	" << grafo.dijkstra(orig, dest) << endl;

	exit(0);
}

int main(){

	// criando um grafo de 4 vértices
	Grafo grafo(4);

	//adicionando as arestas
	//parametros: nó inicial, nó final e distancia entre eles.
	grafo.adicionarAresta(0, 1, 100);
	grafo.adicionarAresta(0, 3, 500);
	grafo.adicionarAresta(1, 2, 350);
	grafo.adicionarAresta(3, 1, 50);
	grafo.adicionarAresta(3, 2, 800);

	string nomes[4] = {"Brasilia", "Sao Paulo", "Florianopolis", "Bahia"};

	menu(grafo, nomes);

	return 0;
}
