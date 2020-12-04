#pragma once
#include "Iterator.h";
#include "dualList.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

class Graph
{
private:
	int** G;
	int V;
	bool Directed;
	bool DirectedCheck();
	bool IfCycle();
public:
	Graph(int count = 0){
		initGraph();
	};

	void initGraph(); 
	bool IfEulerian();
	bool IfBipartite();
	bool IfTree();
	int* PruferCode();
	void PruferDecode(int*);
	void StrongConnected();
	int* Dijkstra(int,int);
	friend std::ostream& operator << (std::ostream&, const Graph&);
	Iterator* create_dft_iterator(int); // depth-first traverse iterator
	Iterator* create_bft_iterator(int); // breadth-first traverse iterator

	class dft_Iterator : public Iterator // depth-first traverse
	{
	private:
		bool* visited;
		int** ItrG;
		dualList* Stack;
		int Icurrent;
		int sizeV;
	public:
		dft_Iterator(int** Gr, int max, int start = 0) {
			Stack = new dualList();
			sizeV = max;
			ItrG = Gr;
			Icurrent = start;
			visited = new bool[max];
			Stack->push_back(Icurrent);
			for (size_t i = 0; i < max; i++)
				visited[i] = false;
			visited[Icurrent] = true;
		};
		int next();
		bool has_next();
		~dft_Iterator() {
			delete visited;
			delete* ItrG;
		}
	};

	class bft_Iterator : public Iterator // depth-first traverse
	{
	private:
		bool* visited;
		int** ItrG;
		dualList* Queue;
		int Icurrent;
		int sizeV;
	public:
		bft_Iterator(int** Gr, int max, int start = 0) {
			Queue = new dualList();
			sizeV = max;
			ItrG = Gr;
			Icurrent = start;
			visited = new bool[max];
			Queue->push_back(Icurrent);
			for (size_t i = 0; i < max; i++)
				visited[i] = false;
			visited[Icurrent] = true;
		};
		int next();
		bool has_next();
		~bft_Iterator() {
			delete visited;
			delete* ItrG; 
		}
	};

	~Graph() {
		for (size_t i = 0; i < V; i++)
			free(G[i]);
		free(G);
	}
};
