#include "Stack.h"
using namespace std;

void Stack::push(int add)
{
	if (size == 0) //if list is empty
	{
		head = new Node(add); //create head
		tail = head;
	}
	else
	{
		Node* curr = new Node(add);
		curr->before = tail;
		tail->next = curr;
		tail = curr;  //set new tail
	}
	size++;
}

size_t Stack::get_size()
{
	return size;
}

int Stack::pop()
{
	int cont;
	if (size == 1)
	{
		size = 0;  //setup zero position
		cont = tail->content;
		head = NULL;
		tail = NULL;

	}
	else if (size > 1) //if list is not empty
	{
		cont = tail->content;
		tail = tail->before; //set new tail
		delete tail->next;
		tail->next = NULL;
		size--;
	}
	else  //else return error
		throw out_of_range("Segmentation fault");
	return cont;
}

void Stack::clear()
{
	if (head != NULL)
	{
		while (head->next != NULL)  //delete all item
		{
			head = head->next;
			delete head->before;
		}
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
}

bool Stack::isEmpty()
{
	if (head == NULL)
		return true;
	return false;
}
