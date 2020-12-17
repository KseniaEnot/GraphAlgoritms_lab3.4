#include "Queue.h"
using namespace std;

void Queue::push(int add) // add item to end
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

size_t Queue::get_size() // get list size
{
	return size;
}

int Queue::pop() // delete first item
{
	int cont;
	if (size == 1)
	{
		cont = head->content;
		size = 0;  //setup zero position
		head = NULL;
		tail = NULL;
	}
	else if (size > 1) //if list is not empty
	{
		cont = head->content;
		head = head->next; //set new head
		delete head->before;
		head->before = NULL;
		size--;
	}
	else //else return error
		throw out_of_range("Segmentation fault");
	return cont;
}

void Queue::clear() // clear list
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

bool Queue::isEmpty() // test for emptiness
{
	if (head == NULL)
		return true;
	return false;
}
