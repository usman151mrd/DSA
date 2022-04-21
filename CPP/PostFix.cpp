#include <iostream>
using namespace std;
template<class T>
class Node
{
    T data;
    Node<T> *next;
public:
    Node(T data=0, Node<T> *next=NULL) : data(data), next(next) {

    }

    T getData() const {
        return data;
    }

    void setData(T data) {
        Node::data = data;
    }

    Node<T> *getNext() const {
        return next;
    }

    void setNext(Node<T> *next) {
        Node::next = next;
    }
};
// stack class
template<class T>
class Stack
{
    Node<T> *top;
public:
    Stack(Node<T> *top=NULL) : top(top) {

    }
    void Push(T data)
    {
        top = new Node(data,top);
    }
    void Pop()
    {
        if(!isEmpty())
        {
            auto temp = top;
            top = top->getNext();
            delete temp;
        }
    }
    bool isEmpty()
    {
        return top==NULL? true: false;
    }
    T Top()
    {
        if(!isEmpty())
        {
            return top->getData();
        }
        return 0;
    }
    void show()
    {
        auto temp = top;
        while (temp!=NULL)
        {
            cout<<temp->getData()<<" ";
            temp = temp->getNext();
        }
        cout<<endl;
    }
};

template<class T>
class Queue
{
    Node<T> *front, *rear;
public:
    Queue() {
        front = rear = NULL;
    }
    bool isEmpty()
    {
        return front==NULL? true: false;
    }
    void enQueue(T data) {
        if (isEmpty()) {
            front = rear = new Node(data);
        } else {
            rear->setNext(new Node(data));
            rear = rear->getNext();
        }
    }
    void deQueue()
    {
        if(!isEmpty())
        {
            auto item = front;
            front = front->getNext();
            delete item;
        }
    }
    T Top()
    {
        return isEmpty()? 0: front->getData();
    }
    void show()
    {
        auto temp = front;
        while (temp!=NULL)
        {
            cout<<temp->getData()<<" ";
            temp = temp->getNext();
        }
        cout<<endl;
    }
};
bool isOperator(char ch)
{
    return ch=='+' or ch=='-' or ch=='*' or ch=='/' or ch=='%' ? true : false;
}
unsigned priority(char ch)
{
    if(ch=='+' or ch=='-')
        return 1;
    else if(ch=='*' or ch=='/' or ch=='%')
        return 2;
    else
        return 0;
}
int main() {
    Stack<char> stack;
    Queue<char> queue;
    //char input[] = "3+4-5*(6+7)/8";
    char input[] = " 1*3-4/(5+6-7)*8";
    char post[100];
    int i=0,p=0;
    while (input[i]!='\0')
    {
        if(isdigit(input[i]))
        {
            queue.enQueue(input[i]);
            post[p++] = input[i];
        }
        else if(isOperator(input[i]))
        {
            while(!stack.isEmpty() and ( priority(stack.Top()) >= priority(input[i])))
            {
                queue.enQueue(stack.Top());
                post[p++] = stack.Top();
                stack.Pop();
            }
            stack.Push(input[i]);
        }
        else if(input[i] == '(')
        {
            stack.Push(input[i]);
        }
        else if(input[i]==')')
        {
            while (!stack.isEmpty() and stack.Top()!='(')
            {
                queue.enQueue(stack.Top());
                post[p++] = stack.Top();
                stack.Pop();
            }
            stack.Pop();
        }
        i++;
    }
    while (!stack.isEmpty())
    {
        queue.enQueue(stack.Top());
        post[p++] = stack.Top();
        stack.Pop();
    }
    cout<<input<<endl;
    cout<<"Queue : \n";
    queue.show();
    cout<<"post : "<<post<<endl;
    cout<<"Sol : 13*456+7-/8*-"<<endl;
    return 0;
}
