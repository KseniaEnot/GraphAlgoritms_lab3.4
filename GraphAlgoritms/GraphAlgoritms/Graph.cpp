#include "Graph.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

Graph::Graph(int choice, string filename) {
	//choice 1 -> reading from console
	//choice 2-> reading from file
	
	fstream file;

	//reading vertices
	if (choice == 1) {
		cout << "Number of vertices: ";
		cin >> Vertices;
	}
	else if (choice == 2) {
		file.open(filename, ios::in);
		file >> Vertices;
		if (file.eof() || Vertices == 0) throw std::out_of_range("Graph is empty");
	}
	else { 
		cout << "Wrong input. Try again\n"; 
		throw std::invalid_argument("Invalid Option");
		return; 
	}

	//memory
	int** arr_check;
	arr_check = (int**)malloc(sizeof(int*) * Vertices);
	if (!arr_check) {
		throw std::out_of_range("Allocation error");
		return;
	}
	else {
		Graph_Matrix = arr_check;
	}

	//reading graph
	if (choice == 1) {
		for (int i = 0; i < Vertices; i++)
		{
			arr_check[i] = (int*)malloc(Vertices * sizeof(int));
			if (!arr_check[i]) { throw std::out_of_range("Allocation error"); return; }
			else Graph_Matrix[i] = arr_check[i];
			//reading
			for (int j = 0; j < Vertices; j++)
			{
				int temp; cin >> temp;
				if (temp == 0 || temp == 1) Graph_Matrix[i][j] = temp;
				else { 
					throw std::invalid_argument("Input error");
					for (int k = 0; k < i; k++)
						free(Graph_Matrix[k]);
					free(Graph_Matrix);
					Vertices = 0;
				}
				if (i == j) Graph_Matrix[i][j] = 0;
			}
		}
		cout << "Sucessfully read.\n";
	}
	else if (choice == 2) {
		//we believe that people can write input properly i guess
		for (int i = 0; i < Vertices; i++)
		{
			arr_check[i] = (int*)malloc(Vertices * sizeof(int));
			if (!arr_check[i]) { throw std::out_of_range("Allocation error"); return; }
			else Graph_Matrix[i] = arr_check[i];
			//reading
			for (int j = 0; j < Vertices; j++)
			{
				if (file.eof()) {
					throw std::invalid_argument("End of file"); 
				}
				int temp; file >> temp;
				if (temp == 0 || temp == 1) Graph_Matrix[i][j] = temp;
				else {
					throw std::invalid_argument("Input error");
					for (int k = 0; k < i; k++)
						free(Graph_Matrix[k]);
					free(Graph_Matrix);
					Vertices = 0;
				}
				if (i == j) Graph_Matrix[i][j] = 0;
			}
		}
		cout << "Sucessfully read." << Vertices << endl;
		file.close();
	}
	//checking if graph is directed
	Directed = DirectedCheck();
}

bool Graph::DirectedCheck() {
	for (size_t i = 0; i < Vertices; i++)
		for (size_t j = i; j < Vertices; j++)
			if (Graph_Matrix[i][j] != Graph_Matrix[j][i])
				return true;  //symmetry check
	return false;
}

bool Graph::IfCycleNoDir() {
	if (Directed) {
		throw std::invalid_argument("Invalid Graph Type");
	}
	else {
		Iterator* g_dft_iterator = create_dft_iterator(0);
		bool* visited = new bool[Vertices];
		for (size_t i = 0; i < Vertices; i++)
			visited[i] = false;
		int cur,bef;
		while (g_dft_iterator->has_next())
		{
			bef = g_dft_iterator->beforecur();
			cur = g_dft_iterator->next();
			visited[cur] = true;
			for (size_t i = 0; i < Vertices; i++)
				if ((Graph_Matrix[cur][i] == 1) && (visited[i] == true) && (i != bef)) //we can go to the already visited peak, but not to the previous one 
					return true;
		}
	}
	return false;
}
void Graph::TrZam() {
	for (size_t w = 0; w < Vertices; w++)
		for (size_t u = 0; u < Vertices; u++)
			for (size_t v = 0; v < Vertices; v++)
				if ((Graph_Matrix[u][w] == 1) && (Graph_Matrix[w][v] == 1) && (Graph_Matrix[u][v] == 0))
				{
					//cout << "For w=" << w + 1 << " add (" << u + 1 << "," << v + 1 << ")" << endl;
					Graph_Matrix[u][v] = 1;
				}
}

bool Graph::IfEulerian() {
	//check for connections
	Iterator* g_dft_iterator = create_dft_iterator(0);
	int max_connect = 0, cur_connect = 0;
	while (g_dft_iterator->has_next())
	{
		g_dft_iterator->next();
		if (!g_dft_iterator->newconnection()) cur_connect++;
		else {
			if (max_connect > 1) { if (cur_connect > 1) return false; }
			if (cur_connect > max_connect) max_connect = cur_connect;
			cur_connect = 0;
		}
	}
	if (cur_connect > 1 && max_connect > 1) return false;

	//count
	int* count_rows, *count_col;
	count_rows = new int[Vertices];
	count_col = new int[Vertices];
	for (int j = 0; j < Vertices; j++) count_col[j] = 0;
	for (int i = 0; i < Vertices; i++) {
		count_rows[i] = 0;
		for (int j = 0; j < Vertices; j++) {
			if (Graph_Matrix[i][j] == 1) { count_rows[i]++; count_col[j]++; }
		}
	}

	for (int i = 0; i < Vertices; i++)
		if (!Directed && (count_col[i] + count_rows[i]) % 2 != 0) return false;
		else if (Directed && (count_col[i] != count_rows[i])) return false;
	return true;
}

bool Graph::IfBipartite() {
	int* color = new int[Vertices];
	for (size_t i = 0; i < Vertices; i++)
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
		for (size_t i = 0; i < Vertices; i++)
			if (Graph_Matrix[cur][i] == 1)
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
	Iterator* g_dft_iterator = create_dft_iterator(0);
	if (Directed)
	{
		int countDeg;
		int count = 0;
		for (size_t i = 0; i < Vertices; i++)
		{
			countDeg = 0;
			for (size_t j = 0; j < Vertices; j++)
				countDeg += Graph_Matrix[j][i];
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
		if (count==0)  //no root
		{
			return false;
		}
	}
	else {
		if (IfCycleNoDir()) return false;  //no cycles
		while (g_dft_iterator->has_next())
		{
			g_dft_iterator->next();
			if (g_dft_iterator->newconnection()) return false;  //one component of connectivity
		}
	}
	return true;
}

int* Graph::PruferCode() {
	//code only for not directed trees
	if (!IfTree() || Directed) throw std::invalid_argument("Invalid Graph Type");
	if (Vertices <= 2) return NULL;
	int* PrufC = new int[Vertices - 2];
	int** G_copy = new int*[Vertices];
	//copy the array to work with
	for (int i = 0; i < Vertices; i++)
	{
		G_copy[i] = new int[Vertices];
		for (int j = 0; j < Vertices; j++)
			G_copy[i][j] = Graph_Matrix[i][j];
	}
	
	int cur_ver = 0, connect_num = 0, next_ver = 0, cur_Pruf = 0;
	bool exit = false;
	while (cur_Pruf < Vertices - 2) {
		for (int j = 0; j < Vertices; j++) { //searching for the smallest 'leaf' with 1 connection
			if (G_copy[cur_ver][j] == 1) {
				connect_num++;
				if (connect_num > 1) { cur_ver++; exit = true; break; }
				next_ver = j;
			}
		}
		if (connect_num == 0) { exit = true; cur_ver++; }
		if (!exit) { //found the leaf, deleting it and adding number to prufer code
				G_copy[next_ver][cur_ver] = 0;
				G_copy[cur_ver][next_ver] = 0;
				PrufC[cur_Pruf] = next_ver;
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

	Vertices = Pruf_length + 2;
	int* ver_num = new int[Vertices];
	int** graph_temp = (int**)malloc(sizeof(int*) * Vertices);
	int pos = 0, pos_pruf = 0;
	//two arrays; prufer code and vertices in order
	for (int i = 0; i < Vertices; i++)
	{
		ver_num[i] = i;
		graph_temp[i] = (int*)malloc(Vertices * sizeof(int));
		for (int j = 0; j < Vertices; j++) graph_temp[i][j] = 0;
	}
	for (; pos_pruf < Vertices - 2; pos_pruf++) {
		//connecting a vertex from prufer with smallest vertex from other array
		//second vertex shouldn't be in prufer code
		for (int i = pos_pruf; i < Vertices - 2; i++) {
			if (ver_num[pos] == PrufC[i] || ver_num[pos] == -1) { i = pos_pruf -1; pos++; }
		}
		graph_temp[ver_num[pos]][PrufC[pos_pruf]] = 1;
		graph_temp[PrufC[pos_pruf]][ver_num[pos]] = 1;
		ver_num[pos] = -1;
		pos = 0;
	}

	int row = -1, col = -1;
	for (int i = 0; i < Vertices; i++)
		if (ver_num[i] != -1 && row == -1) row = ver_num[i];
		else if (ver_num[i] != -1) { col = ver_num[i]; break; }
	graph_temp[row][col] = 1; graph_temp[col][row] = 1;
	Graph_Matrix = (int**)realloc(Graph_Matrix, sizeof(int*) * Vertices);
	Graph_Matrix = graph_temp;
}

dualList* Graph::StrongConnected() {
	int* number = new int[Vertices];
	bool* visited = new bool[Vertices];
	Stack* stack = new Stack();
	int backcur;
	bool canGo=true;
	int Icurrent = 0, count = 0,temp;
	stack->push(Icurrent);
	for (size_t i = 0; i < Vertices; i++) {
		number[i] = -1;
		visited[i] = false;
	}
	cout << endl;
	while (canGo)  //depth-first traversal in a transposed graph
	{
		visited[Icurrent] = true;
		temp = Icurrent;
		for (size_t i = 0; i < Vertices; i++)
			if ((visited[i] == false) && (Graph_Matrix[i][Icurrent] == 1))
			{
				Icurrent = i;
				stack->push(Icurrent);
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
		while ((temp == Icurrent) && !stack->isEmpty())
		{
			backcur = stack->pop();
			for (size_t i = 0; i < Vertices; i++)
				if ((visited[i] == false) && (Graph_Matrix[i][backcur] == 1))
				{
					Icurrent = i;
					stack->push(backcur);
					stack->push(Icurrent);
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
			for (size_t i = 0; i < Vertices; i++)
				if (visited[i] == false)
				{
					Icurrent = i;
					stack->push(Icurrent);
					break;
				}
		}
		canGo = false;
		if (!stack->isEmpty())
			canGo = true;
		else {
			for (size_t i = 0; i < Vertices; i++)
				if (visited[i] == false) {
					canGo = true;
					break;
				}
		}
	}
	for (size_t i = 0; i < Vertices; i++) {
		visited[i] = false;
	}
	canGo = true;
	int countSv = 0;

	Icurrent = number[count-1];  //starting with the last one on the way out
	stack->clear();
	dualList* Result = new dualList[Vertices];
	stack->push(Icurrent);
	while (canGo)  //number the vertices upon exit
	{
		visited[Icurrent] = true;
		for (size_t i = 0; i < Vertices; i++)
			if (number[i] == Icurrent)
			{
				Result[countSv].push_back(Icurrent);  //add to list
				number[i] = -1;
				break;
			}
		temp = Icurrent;
		for (size_t i = 0; i < Vertices; i++)
			if ((visited[i] == false) && (Graph_Matrix[Icurrent][i] == 1))
			{
				Icurrent = i;
				stack->push(Icurrent);
				break;
			}
		while ((temp == Icurrent) && !stack->isEmpty())
		{
			backcur = stack->pop();
			for (size_t i = 0; i < Vertices; i++)
				if ((visited[i] == false) && (Graph_Matrix[backcur][i] == 1))
				{
					Icurrent = i;
					stack->push(backcur);
					stack->push(Icurrent);
					break;
				}
		}
		if (temp == Icurrent)
		{
			for (int i = Vertices -1; i >= 0; i--)
				if (number[i] != -1)  //we go to the next not visited from the last one on the way out
				{
					if (visited[number[i]] == false)
					{
						countSv++;  //came out of the tree
						Icurrent = number[i];
						stack->push(Icurrent);
						break;
					}
				}
		}
		canGo = false;
		if (!stack->isEmpty())
			canGo = true;
		else {
			for (size_t i = 0; i < Vertices; i++)
				if (visited[i] == false) {
					canGo = true;
					break;
				}
		}
	}
	return Result;
}

int Graph::GetSize() {
	return Vertices;
}

int* Graph::Dijkstra(int start_point) {  
	int* distance = new int[Vertices];
	bool* visited = new bool[Vertices];
	
	int** G_copy = new int* [Vertices];
	for (int i = 0; i < Vertices; i++)
	{
		G_copy[i] = new int[Vertices];
		for (int j = 0; j < Vertices; j++)
			if (Graph_Matrix[i][j] == 0)
			{
				G_copy[i][j] = INT_MAX;
			}
			else {
				G_copy[i][j] = Graph_Matrix[i][j];
			}
	}

	for (size_t i = 0; i < Vertices; i++) {
		distance[i] = G_copy[start_point][i];
		visited[i] = false;
	}
	int u=0,index=0,min;
	distance[start_point] = 0;
	for (size_t i = 0; i < Vertices; i++)
	{
		min = INT_MAX;
		for (size_t j = 0; j < Vertices; j++)
		{
			if ((visited[j]==false)&&(distance[j]<min))  //finding a shortcut
			{
				min = distance[j];
				index = j;
			}
		}
		u = index;
		visited[u] = true;
		for (size_t j = 0; j < Vertices; j++)
		{
			if ((visited[j]==false)&&(G_copy[u][j]!=INT_MAX) && (distance[u] != INT_MAX) &&((distance[u]+G_copy[u][j]) < distance[j])) //if shorter bypass
			{
				distance[j] = distance[u] + G_copy[u][j];
			}
		}
	}

	for (size_t i = 0; i < Vertices; i++)
	{
		delete G_copy[i];
	}
	delete G_copy;
	return distance;  //if distance[i] == INT_MAX, the way doesn't exist
}

Iterator* Graph::create_dft_iterator(int start = 0) {
	return new dft_Iterator(Graph_Matrix, Vertices,start);
}

std::ostream& operator << (std::ostream& out, const Graph& Gr) {
	cout << "Graph: " << endl;
	for (int i = 0; i < Gr.Vertices; i++) {
		for (int j = 0; j < Gr.Vertices; j++) {
			cout << Gr.Graph_Matrix[i][j] << " ";
		}
		cout << endl;
	}
	return out;
}

bool Graph::dft_Iterator::has_next() {
	if (!stack->isEmpty())
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
			stack->push(Icurrent);
			connection = false;
			break;
		}
	int backcur;
	while ((temp == Icurrent) && !stack->isEmpty())
	{
		backcur = stack->pop();  //pop the top off the stack
		for (size_t i = 0; i < sizeV; i++)
			if ((visited[i] == false) && (ItrG[backcur][i] == 1))  //go deeper
			{
				before = backcur;
				Icurrent = i;
				stack->push(backcur);
				stack->push(Icurrent);
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
				stack->push(Icurrent);
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
	return new bft_Iterator(Graph_Matrix, Vertices, start);
}

bool Graph::bft_Iterator::has_next() {
	if (!queue->isEmpty())
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
			queue->push(i);
		}
	while (!queue->isEmpty() && (visited[Icurrent] == true))
	{
		Icurrent = queue->pop();  //getting the top out of the queue
		connection = false;
	}
	if (queue->isEmpty() && (visited[Icurrent] == true))
	{
		for (size_t i = 0; i < sizeV; i++)
			if (visited[i] == false)  //go to the next component of connectivity
			{
				Icurrent = i;
				queue->push(Icurrent);
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

