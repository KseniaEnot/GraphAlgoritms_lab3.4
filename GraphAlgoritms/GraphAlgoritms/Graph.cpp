#include "Graph.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

Graph::Graph(int choice, string filename) {
	//choice 1 -> reading from console
	//choice 2-> reading from file

	//int choice;
	fstream f;
	std::cout << "Hello, choose input method\n 1 - console\n2 - file\n";
	//cin >> choice;

	//reading vertices
	if (choice == 1) {
		cout << "Number of vertices: ";
		cin >> V;
	}
	else if (choice == 2) {
		//string filename = "in.txt";
		//cout << "Input file name: "; cin >> filename;
		f.open(filename, ios::in);
		if (f.bad()) throw std::out_of_range("File cannot be opened");
		f >> V;
	}
	else { 
		cout << "Wrong input. Try again\n"; 
		throw std::invalid_argument("Invalid Option");
		return; 
	}

	//memory
	int** p;
	p = (int**)malloc(sizeof(int*) * V);
	if (!p) {
		throw std::out_of_range("Allocation error");
		return;
	}
	else {
		G = p;
	}

	//reading graph
	if (choice == 1) {
		for (int i = 0; i < V; i++)
		{
			p[i] = (int*)malloc(V * sizeof(int));
			if (!p[i]) { throw std::out_of_range("Allocation error"); return; }
			else G[i] = p[i];
			//reading
			for (int j = 0; j < V; j++)
			{
				int temp; cin >> temp;
				if (temp == 0 || temp == 1) G[i][j] = temp;
				else { 
					throw std::invalid_argument("Input error");
					for (int k = 0; k < i; k++)
						free(G[k]);
					free(G);
					V = 0; 
				}
				if (i == j) G[i][j] = 0;
			}
		}
		cout << "Sucessfully read.\n";
	}
	else if (choice == 2) {
		//f >> noskipws;
		//we believe that people can write input properly i guess
		for (int i = 0; i < V; i++)
		{
			p[i] = (int*)malloc(V * sizeof(int));
			if (!p[i]) { throw std::out_of_range("Allocation error"); return; }
			else G[i] = p[i];
			//reading
			for (int j = 0; j < V; j++)
			{
				if (f.eof()) {
					throw std::invalid_argument("End of file"); //+clean graph to 0
				}
				int temp; f >> temp;
				if (temp == 0 || temp == 1) G[i][j] = temp;
				else {
					throw std::invalid_argument("Input error");
					for (int k = 0; k < i; k++)
						free(G[k]);
					free(G);
					V = 0;
				}
				if (i == j) G[i][j] = 0;
			}
		}
		cout << "Sucessfully read." << V << endl;
		f.close();
	}
	//checking if graph is directed
	Directed = DirectedCheck();
}


bool Graph::DirectedCheck() {
	for (size_t i = 0; i < V; i++)
		for (size_t j = i; j < V; j++)
			if (G[i][j] != G[j][i])
				return true;  //symmetry check
	return false;
}

bool Graph::IfCycle() {
	if (Directed) {
		Iterator* g_dft_iterator = create_dft_iterator(0);
		bool* visited = new bool[V];
		for (size_t i = 0; i < V; i++)
			visited[i] = false;
		int cur;
		while (g_dft_iterator->has_next())
		{
			cur = g_dft_iterator->next();
			visited[cur] = true;
			for (size_t i = 0; i < V; i++)
				if ((G[cur][i] == 1) && (visited[i] == true)) //we can go to the already visited peak
					return true;
		}
	}
	else {
		Iterator* g_dft_iterator = create_dft_iterator(0);
		bool* visited = new bool[V];
		for (size_t i = 0; i < V; i++)
			visited[i] = false;
		int cur,bef;
		while (g_dft_iterator->has_next())
		{
			bef = g_dft_iterator->beforecur();
			cur = g_dft_iterator->next();
			visited[cur] = true;
			for (size_t i = 0; i < V; i++)
				if ((G[cur][i] == 1) && (visited[i] == true) && (i != bef)) //we can go to the already visited peak, but not to the previous one 
					return true;
		}
	}
	return false;
}

bool Graph::IfEulerian() {
	//check for connections
	Iterator* g_dft_iterator = create_dft_iterator(0);
	int max_connect = 0, cur_connect = 0;
	while (g_dft_iterator->has_next())
	{
		std::cout << g_dft_iterator->next() << " ";
		if (!g_dft_iterator->newconnection()) cur_connect++;
		else {
			if (max_connect > 1) { if (cur_connect > 1) return false; }
			if (cur_connect > max_connect) max_connect = cur_connect;
			cur_connect = 0;
		}
	}
	cout << cur_connect << " " << max_connect << endl;
	if (cur_connect > 1 && max_connect > 1) return false;

	//count
	int* count_rows, *count_col;
	count_rows = new int[V];
	count_col = new int[V];
	for (int j = 0; j < V; j++) count_col[j] = 0;
	for (int i = 0; i < V; i++) {
		count_rows[i] = 0;
		for (int j = 0; j < V; j++) {
			if (G[i][j] == 1) { count_rows[i]++; count_col[j]++; }
		}
	}

	for (int i = 0; i < V; i++)
		if (!Directed && (count_col[i] + count_rows[i]) % 2 != 0) return false;
		else if (Directed && (count_col[i] != count_rows[i])) return false;
	return true;
}

bool Graph::IfBipartite() {
	int* color = new int[V];
	for (size_t i = 0; i < V; i++)
		color[i] = 2; //1-black,0-white,2-grey
	Iterator* g_bft_iterator = create_bft_iterator(0);
	int cur;
	while (g_bft_iterator->has_next())
	{
		if (g_bft_iterator->newconnection())  //if switched to another connected component
		{
			cur = g_bft_iterator->next();
			color[cur] = 1;  //paint in black
		}
		else
			cur = g_bft_iterator->next();
		for (size_t i = 0; i < V; i++)
			if (G[cur][i] == 1)
			{
				switch (color[i])
				{
				case 2:  //if painted gray
					if (color[cur] == 1)  //paint in the opposite color
						color[i] = 0;
					else color[i] = 1;
					break;
				default:
					if (color[i] == color[cur])  //if the colors match
					{
						return false;
					}
					break;
				}
			}
	}
	return true;
}

bool Graph::IfTree() {
	if (IfCycle()) return false;  //no cycles
	Iterator* g_dft_iterator = create_dft_iterator(0);
	if (Directed)
	{
		int countDeg;
		int count = 0;
		for (size_t i = 0; i < V; i++)
		{
			countDeg = 0;
			for (size_t j = 0; j < V; j++)
				countDeg += G[j][i];
			if (countDeg>1)  //entry degree greater than 1
			{
				return false;
			}
			else if (countDeg==0)
			{
				count++;
				if (count > 1)  //entry degree 0 only at one vertex
					return false;
			}
		}
	}
	else {
		while (g_dft_iterator->has_next())
		{
			g_dft_iterator->next();
			if (g_dft_iterator->newconnection()) return false;  //one component of connectivity
		}
	}
	return true;
}

int* Graph::PruferCode() {
	if (!IfTree() || Directed) throw std::invalid_argument("Invalid Graph Type");
	if (V <= 2) return NULL;
	int* PrufC = new int[V - 2]; 
	int** G_copy = new int*[V];
	for (int i = 0; i < V; i++)
	{
		G_copy[i] = new int[V];
		for (int j = 0; j < V; j++)
			G_copy[i][j] = G[i][j];
	}
	
	int cur_ver = 0, connect_num = 0, next_ver = 0, cur_Pruf = 0;
	bool exit = false;
	while (cur_Pruf < V - 2) {
		for (int j = 0; j < V; j++) {
			if (G_copy[cur_ver][j] == 1) {
				connect_num++;
				if (connect_num > 1) { cur_ver++; exit = true; break; }
				next_ver = j;
			}
		}
		if (!exit) {
				G_copy[next_ver][cur_ver] = 0;
				G_copy[cur_ver][next_ver] = 0;
				PrufC[cur_Pruf] = next_ver;
				cout << next_ver << " ";
				if (next_ver < cur_ver) cur_ver = next_ver;
				else cur_ver++;
				cur_Pruf++;
		}
		connect_num = 0, next_ver = 0; exit = false;
	}
	return PrufC;
}

void Graph::PruferDecode(int* PrufC, int Pruf_length) {
	for (int i = 0; i < Pruf_length; i++)
		if (PrufC[i] >= Pruf_length + 2) throw std::invalid_argument("Invalid Prufer Code");

	V = Pruf_length + 2;
	int* ver_num = new int[V];
	int** p = (int**)malloc(sizeof(int*) * V);
	int pos = 0, pos_pruf = 0;
	for (int i = 0; i < V; i++)
	{
		ver_num[i] = i;
		p[i] = (int*)malloc(V * sizeof(int));
		for (int j = 0; j < V; j++) p[i][j] = 0;
	}
	for (; pos_pruf < V - 2; pos_pruf++) {
		for (int i = pos_pruf; i < V - 2; i++) {
			if (ver_num[pos] == PrufC[i] || ver_num[pos] == -1) { i = pos_pruf -1; pos++; }
		}
		p[ver_num[pos]][PrufC[pos_pruf]] = 1;
		p[PrufC[pos_pruf]][ver_num[pos]] = 1;
		ver_num[pos] = -1;
		pos = 0;
	}

	int row = -1, col = -1;
	for (int i = 0; i < V; i++)
		if (ver_num[i] != -1 && row == -1) row = ver_num[i];
		else if (ver_num[i] != -1) { col = ver_num[i]; break; }
	p[row][col] = 1; p[col][row] = 1;
	G = (int**)realloc(G, sizeof(int*) * V);
	G = p;
	/*for (int i = 0; i < V; i++)
	{
		cout << endl;
		for (int j = 0; j < V; j++)
			cout << p[i][j] << " ";
	}*/
}

dualList* Graph::StrongConnected() {
	int* number = new int[V];
	bool* visited = new bool[V];
	dualList* Stack = new dualList();
	int backcur;
	bool canGo=true;
	int Icurrent = 0, count = 0,temp;
	Stack->push_back(Icurrent);
	for (size_t i = 0; i < V; i++) {
		number[i] = -1;
		visited[i] = false;
	}
	cout << endl;
	while (canGo)  //depth-first traversal in a transposed graph
	{
		visited[Icurrent] = true;
		temp = Icurrent;
		for (size_t i = 0; i < V; i++)
			if ((visited[i] == false) && (G[i][Icurrent] == 1))
			{
				Icurrent = i;
				Stack->push_back(Icurrent);
				break;
			}
		if (count > 0) {  //number the vertices upon exit
			if ((temp == Icurrent) && (number[count - 1] != Icurrent))
			{
				number[count] = Icurrent;
				count++;
			}
		}
		else {
			if (temp == Icurrent)
			{
				number[count] = Icurrent;
				count++;
			}
		}
		while ((temp == Icurrent) && !Stack->isEmpty())
		{
			backcur = Stack->at(Stack->get_size() - 1);
			Stack->pop_back();
			for (size_t i = 0; i < V; i++)
				if ((visited[i] == false) && (G[i][backcur] == 1))
				{
					Icurrent = i;
					Stack->push_back(backcur);
					Stack->push_back(Icurrent);
					break;
				}
			if (count > 0) {  //number the vertices upon exit
				if ((temp == Icurrent) && (number[count - 1] != backcur))
				{
					number[count] = backcur;
					count++;
				}
			}else{
				if (temp == Icurrent)
				{
					number[count] = backcur;
					count++;
				}
			}
				
		}
		if (temp == Icurrent)
		{
			for (size_t i = 0; i < V; i++)
				if (visited[i] == false)
				{
					Icurrent = i;
					Stack->push_back(Icurrent);
					break;
				}
		}
		canGo = false;
		if (!Stack->isEmpty())
			canGo = true;
		else {
			for (size_t i = 0; i < V; i++)
				if (visited[i] == false) {
					canGo = true;
					break;
				}
		}
	}
	for (size_t i = 0; i < V; i++) {
		visited[i] = false;
	}
	canGo = true;
	int countSv = 0;
	Icurrent = number[count-1];  //starting with the last one on the way out
	Stack->clear();
	dualList* Result = new dualList[V];
	Stack->push_back(Icurrent);
	while (canGo)  //number the vertices upon exit
	{
		visited[Icurrent] = true;
		for (size_t i = 0; i < V; i++)
			if (number[i] == Icurrent)
			{
				Result[countSv].push_back(Icurrent);  //add to list
				number[i] = -1;
				break;
			}
		temp = Icurrent;
		for (size_t i = 0; i < V; i++)
			if ((visited[i] == false) && (G[Icurrent][i] == 1))
			{
				Icurrent = i;
				Stack->push_back(Icurrent);
				break;
			}
		int backcur;
		while ((temp == Icurrent) && !Stack->isEmpty())
		{
			backcur = Stack->at(Stack->get_size() - 1);
			Stack->pop_back();
			for (size_t i = 0; i < V; i++)
				if ((visited[i] == false) && (G[backcur][i] == 1))
				{
					Icurrent = i;
					Stack->push_back(backcur);
					Stack->push_back(Icurrent);
					break;
				}
		}
		if (temp == Icurrent)
		{
			for (int i = V-1; i >= 0; i--)
				if (number[i] != -1)  //we go to the next not visited from the last one on the way out
				{
					if (visited[number[i]] == false)
					{
						countSv++;  //came out of the tree
						Icurrent = number[i];
						Stack->push_back(Icurrent);
						break;
					}
				}
		}
		canGo = false;
		if (!Stack->isEmpty())
			canGo = true;
		else {
			for (size_t i = 0; i < V; i++)
				if (visited[i] == false) {
					canGo = true;
					break;
				}
		}
	}
	return Result;
}

int Graph::GetSize() {
	return V;
}

int* Graph::Dijkstra(int A) {  
	int* distance = new int[V];
	bool* visited = new bool[V];
	for (size_t i = 0; i < V; i++) {
		distance[i] = G[A][i];
		visited[i] = false;
	}
	int u=0,index=0,min;
	distance[A] = 0;
	for (size_t i = 0; i < V; i++)
	{
		min = INT_MAX;
		for (size_t j = 0; j < V; j++)
		{
			if ((visited[j]==false)&&(distance[j]<min))  //finding a shortcut
			{
				min = distance[j];
				index = j;
			}
		}
		u = index;
		visited[u] = true;
		for (size_t j = 0; j < V; j++)
		{
			if ((visited[i]==false)&&(G[u][j]!=INT_MAX)&&(distance[u]+G[u][j] < distance[j])) //if shorter bypass
			{
				distance[j] = distance[u] + G[u][j];
			}
		}
	}
	return distance;  //if distance[i] == INT_MAX, the way doesn't exist
}

Iterator* Graph::create_dft_iterator(int start = 0) {
	return new dft_Iterator(G,V,start);
}

std::ostream& operator << (std::ostream& out, const Graph& Gr) {
	cout << "Graph: " << endl;
	for (int i = 0; i < Gr.V; i++) {
		for (int j = 0; j < Gr.V; j++) {
			cout << Gr.G[i][j] << " ";
		}
		cout << endl;
	}
	return out;
}

bool Graph::dft_Iterator::has_next() {
	if (!Stack->isEmpty())
		return true;
	for (size_t i = 0; i < sizeV; i++)
		if (visited[i] == false)
			return true;
	return false;
}

int Graph::dft_Iterator::next() {
	if (!has_next()) {
		throw std::out_of_range("No more elements");
	}
	visited[Icurrent] = true;
	int temp = Icurrent;
	for (size_t i = 0; i < sizeV; i++)
		if ((visited[i] == false) && (ItrG[Icurrent][i] == 1))  //go deeper
		{
			before = Icurrent;
			Icurrent = i;
			Stack->push_back(Icurrent);
			connection = false;
			break;
		}
	int backcur;
	while ((temp == Icurrent) && !Stack->isEmpty())
	{
		backcur = Stack->at(Stack->get_size() - 1);  //pop the top off the stack
		Stack->pop_back();
		for (size_t i = 0; i < sizeV; i++)
			if ((visited[i] == false) && (ItrG[backcur][i] == 1))  //go deeper
			{
				before = backcur;
				Icurrent = i;
				Stack->push_back(backcur);
				Stack->push_back(Icurrent);
				connection = false;
				break;
			}
	}
	if (temp == Icurrent)
	{
		for (size_t i = 0; i < sizeV; i++)
			if (visited[i] == false)  //go to the next component of connectivity
			{
				before = -1;
				Icurrent = i;
				Stack->push_back(Icurrent);
				connection = true;
				break;
			}
	}
	return temp;
}

int  Graph::dft_Iterator::beforecur() {
	return before;
}

bool  Graph::dft_Iterator::newconnection() {
	return connection;
}

Iterator* Graph::create_bft_iterator(int start = 0) {
	return new bft_Iterator(G, V, start);
}

bool Graph::bft_Iterator::has_next() {
	if (!Queue->isEmpty())
		return true;
	for (size_t i = 0; i < sizeV; i++)
		if (visited[i] == false)
			return true;
	return false;
}

int Graph::bft_Iterator::next() {
	if (!has_next()) {
		throw std::out_of_range("No more elements");
	}
	visited[Icurrent] = true;
	int temp = Icurrent;
	for (size_t i = 0; i < sizeV; i++)
		if ((visited[i] == false) && (ItrG[Icurrent][i] == 1)) {  //put all unvisited neighboring vertices in the queue
			Queue->push_back(i);
		}
	while (!Queue->isEmpty())  //deleted " && (visited[Icurrent] == true)"
	{
		Icurrent = Queue->at(0);  //getting the top out of the queue
		connection = false;
		Queue->pop_front();
	}
	if (Queue->isEmpty() && (visited[Icurrent] == true))
	{
		for (size_t i = 0; i < sizeV; i++)
			if (visited[i] == false)  //go to the next component of connectivity
			{
				Icurrent = i;
				Queue->push_back(Icurrent);
				connection = true;
				break;
			}
	}
	return temp;
}

int  Graph::bft_Iterator::beforecur() {
	return before;
}

bool  Graph::bft_Iterator::newconnection() {
	return connection;
}

