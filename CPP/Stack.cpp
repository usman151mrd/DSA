#include <iostream>
using  namespace std;
class Stack
{
    struct Node
    {
        int data;
        Node *next;

        Node(int data) : data(data) {
            next = NULL;
        }

        Node(int data, Node *next) : data(data), next(next) {}
    }*top;

public:
    Stack() {
        top = NULL;
    }
    void Push(int data)
    {
        top = new Node(data,top);
    }
    void Pop()
    {
        if(top == NULL)
            cout<<"Stack is empty "<<endl;
        else
        {
            Node *temp = top;
            top = top->next;
            cout<<temp->data<<" is poped"<<endl;
            delete temp;
        }
    }
    void Display()
    {
        Node *temp = top;
        while(temp!= NULL)
        {
            cout<<temp->data<<"\t";
            temp = temp->next;
        }
        cout<<endl;
    }
};
int main() {
    Stack stack;
    stack.Push(5);
    stack.Push(4);
    stack.Push(3);
    stack.Push(2);
    stack.Push(1);
    stack.Display();
    stack.Pop();
    cout<<"Stack after pop one value"<<endl;
    stack.Display();


    return 0;
}
