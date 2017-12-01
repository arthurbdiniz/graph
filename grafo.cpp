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

	// obtém o grau de saída de um dado vértice
	// grau de saída é o número de arcos que saem de "v"
	int obterGrauDeSaida(int v);

	bool existeVizinho(int v1, int v2); // verifica se v2 é vizinho de v1
	void imprimirGrafo();
	int dijkstra(int v1, int v2); // calcula o menor caminho entre dois nós
};

Grafo::Grafo(int V) {
	this->V = V; // atribui o número de vértices
	adj = new list< std::pair<int,int> >[V]; // cria as listas
}

void Grafo::adicionarAresta(int v1, int v2, int distance) {
	// adiciona vértice v2 à lista de vértices adjacentes de v1
	adj[v1].push_back(make_pair(v2, distance));
	// como o grafo é unidirecional, deve-se adicionar v1 na lista de v2
	adj[v2].push_back(make_pair(v1, custo));
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
 
void Grafo::imprimirGrafo() {
	for (int i = 0; i < V; i++) {
		for(pair<int,int> item : adj[i]) {
			cout << i << " - ";
			cout << item.first;
			cout << " distancia: " << item.second << endl;
		}

	}
}

// bool Grafo::existeVizinho(int v1, int v2) {
// 	if(find(adj[v1].begin(), adj[v1].end(), v2) != adj[v1].end())
// 		return true;
// 	return false;
// }

// int Grafo::obterGrauDeSaida(int v) {
// 	// basta retornar o tamanho da lista que é a quantidade de vizinhos
// 	return adj[v].size();
// }
//

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

	//grafo.imprimirGrafo();
	cout << grafo.dijkstra(1,0) << endl;

	// mostrando os graus de saída
	//cout << "Grau de saida do vertice 1: " << grafo.obterGrauDeSaida(1);
	//cout << "\nGrau de saida do vertice 3: " << grafo.obterGrauDeSaida(3);

	// verifica se existe vizinhos
	// if(grafo.existeVizinho(0, 1))
	// 	cout << "\n\n1 eh vizinho de 0\n";
	// else
	// 	cout << "\n\n1 NAO eh vizinho de 0\n";
	//
	// if(grafo.existeVizinho(0, 2))
	// 	cout << "2 eh vizinho de 0\n";
	// else
	// 	cout << "2 NAO eh vizinho de 0\n";

	return 0;
}
