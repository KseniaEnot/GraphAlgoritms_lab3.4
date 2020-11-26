#pragma once
#include "Iterator.h";
#include "dualList.h"
#include <stdlib.h>
#include <iostream>

class Graph
{
private:
	int** G;
	int V;
public:
	Graph(int count = 0){
		this->V = count;
		int** p;
		p = (int**)malloc(sizeof(int) * count * count);
		if (!p) {
			throw std::out_of_range("Allocation error");
			return;
		}
		else {
			G = p;
		}
	};

	void initGraph(); 
	bool IfEulerian();
	bool IfBipartite();
	bool IfTree();
	int* PruferCode();
	void PruferDecode(int*);
	void StrongConnected();
	int* Dijkstra(int,int);
	Iterator* create_dft_iterator(); // depth-first traverse iterator
	Iterator* create_bft_iterator(); // breadth-first traverse iterator

	class dft_Iterator : public Iterator // depth-first traverse
	{
	private:
		bool* visited;
		int** ItrG;
		dualList* Stack;
		int Icurrent;
		int sizeV;
	public:
		dft_Iterator(int** Gr, int max) {
			sizeV = max;
			ItrG = Gr;
			Icurrent = 0;
			visited = new bool[max];
			visited[0] = true;
			Stack->push_back(Icurrent);
			for (size_t i = 1; i < max; i++)
				visited[i] = false;
		};
		int next();
		bool has_next();
		~dft_Iterator() {
			delete visited;
			delete* ItrG; //??norm
		}
	};


	~Graph() {
		for (size_t i = 0; i < V; i++)
			free(G[i]);
		free(G);
	}

};
