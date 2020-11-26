#pragma once
#include "Iterator.h"
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

	~Graph() {
		for (size_t i = 0; i < V; i++)
			free(G[i]);
		free(G);
	}

};
