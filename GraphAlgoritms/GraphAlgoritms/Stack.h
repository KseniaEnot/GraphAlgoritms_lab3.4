#pragma once
#include <iostream>

class Stack
{
private:
    class Node
    {
    public:
        Node(int content = 0, Node* before = NULL, Node* next = NULL)
        {
            this->content = content;
            this->before = before;
            this->next = next;
        };
        ~Node()
        {  }
        int content;
        Node* next;
        Node* before;
    private:

    };

    Node* head; //head list
    Node* tail;  //tail list
    size_t size;  //list size

public:
    Stack(Node* head = NULL, Node* tail = NULL) {
        this->head = head;
        this->tail = tail;
        size = 0;
    };
    void push(int); // add item to end
    size_t get_size(); // get list size
    int pop(); // delete last item
    void clear(); // clear list
    bool isEmpty(); // test for emptiness
    ~Stack()
    {
        while (head->next != NULL) //while we can go next
        {
            head = head->next;
            delete head->before;
        }
        size = 0;
        delete head;
    };
};

