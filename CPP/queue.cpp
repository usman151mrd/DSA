#include <iostream>
using namespace std;
class Node
{
    int data;
    Node *next;
public:
    Node(int data) : data(data) {
        next = NULL;
    }

    int getData() const {
        return data;
    }

    void setData(int data) {
        Node::data = data;
    }

    Node *getNext() const {
        return next;
    }

    void setNext(Node *next) {
        Node::next = next;
       // this->next = next;
    }
};
class Queue
{
    Node *front; //head
    Node *rear; // tail
public:
    Queue()
    {
        front = rear = NULL;
    }
    void enQueue(int value)
    {
        if(front==NULL)
        { // 1 -> 2 -> 3 -> 4 -> 5
            front = rear = new Node(value);
        } else
        { // append value
            Node * temp = new Node(value);
            rear->setNext(temp);
            rear = temp;
        }
    }
    void deQueue() {
        if (front == NULL) {
            cout << "Queue is empty " << endl;
        } else {
            Node *temp = front;
            front = front->getNext();
            cout << temp->getData() << " has deQueue" << endl; //optional
            delete temp;

        }
    }
    void Display()
    {
        Node *temp=front;
        while(temp!=NULL)
        {
            cout<<temp->getData()<<"\t";
            temp = temp->getNext();
        }
        cout<<endl;
    }
};
int main() {
    Queue queue;
    queue.enQueue(1);
    queue.enQueue(2);
    queue.enQueue(3);
    queue.enQueue(4);
    queue.deQueue();
    queue.Display();
    return 0;
}
