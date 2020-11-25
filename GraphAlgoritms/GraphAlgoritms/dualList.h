#pragma once
#include <iostream>

class dualList
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
    dualList(Node* head = NULL, Node* tail = NULL) {
        this->head = head;
        this->tail = tail;
        size = 0;
    };
    void push_back(int); // add item to end
    void push_front(int); //add to begin
    size_t get_size(); // get list size
    void pop_back(); // delete last item
    void pop_front(); // delete first item
    int at(size_t); // get item by index
    void remove(size_t); // delete item by index
    void insert(int, size_t); // add item before "size_t" item
    void print_to_console(); // print item to console
    void clear(); // clear list
    void set(size_t, int); // change "size_t" item to "int"
    bool isEmpty(); // test for emptiness
    void push_back(dualList); // add another list to end
    ~dualList()
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


