#include<iostream>
#include<vector>
#include<array>
#include<exception>
#include<algorithm>
using namespace std;
using st1 = string;

template <typename T>
struct singlynode{
    T data;
    singlynode * next;
    singlynnode * prev;
    singlynode *top;
    singlynode *down;
};

template <typename T>
class dlinklist{
    public:
        using node = singlynode<T>;
        using nodeptr = node*;
    private:
        nodeptr head;
    
    public:
        void push_front(const T & val){
            nodeptr newnode = new node;
            newnode->data = val;
            newnode->next = head;
            head = newnode;
        }
        void push_back(const T & val){
            nodeptr newnode = new node;
            newnode->data = val;
            newnode->next = nullptr;
            newnode->prev = nullptr;
            newnode->top = nullptr;
            newnode->down = nullptr;
            if(!head){
                head = newnode;
                return;
            }
            nodeptr temp = head;
            while(temp->next){
                temp = temp->next;
            }
            temp->next = newnode;
        }

}
