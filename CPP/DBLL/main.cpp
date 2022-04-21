#include <iostream>
using namespace std;
class DLL
{
    struct Node
    {
        int data;
        Node *next;
        Node *back;

        Node() {
            data =0;
            next = NULL;
            back = NULL;
        }

        Node(int data) : data(data) {
            next = back = NULL;
        }

        Node(int data, Node *next) : data(data), next(next) {
            back = NULL;
        }

        Node(int data, Node *next, Node *back) : data(data), next(next), back(back) {}

    }*head,*tail;
    Node *temp;
public:
    DLL() {
        head = tail = NULL;
    }
    void Add(int data)
    {
        if (head==NULL)
        {
            head = tail = new Node(data);
        } else if (head->data > data)
        {
            temp = new Node(data,head);
            head->back = temp;
            head = temp;
        }
        else if(tail->data < data)
        {
            tail->next = new Node(data);
            tail->next->back = tail;
            tail = tail->next;
        } else
        {
            Node * prvs = head;
            temp = head->next;
            while (temp->data < data)
            {
                prvs = temp;
                temp = temp->next;
            }
            Node *NNode = new Node(data);
            prvs->next = NNode;
            NNode->back = prvs;
            NNode->next = temp;
            temp->back = NNode;
        }
    }
    void Display()
    {
        temp = tail;
        while (temp != NULL)
        {
            cout<<temp->data<<"\t";
            temp = temp->back;
        }
        cout<<endl;
    }
    void Search(int key)
    {
        if (head->data > key || tail->data < key)
        {
            cout<<key<<" Data not found : \n";
        } else
        {
            temp = head ;
            bool flag = false;
            while(temp != NULL)
            {
                if(temp ->data == key)
                {
                    flag = true;
                }
                temp = temp->next;
            }
            if (flag)
            {
                cout<<key<<" Exist in database : "<<endl;
            } else
            {
                cout<<key<<" Not exit in database : "<<endl;
            }
        }
    }
    void Delete(int key)
    {
        if (head->data == key)
        {
            temp = head;
            head = head->next;
            delete temp;
            head->back = NULL;
        } else
        {
            temp = head->next ;
            Node *prvs = head;
            while(temp != NULL && temp ->data != key)
            {
                prvs = temp;
                temp = temp->next;
            }
            if (temp==NULL)
            {
                cout<<key<<" Exist in database : "<<endl;
            } else
            {
                prvs->next = temp->next;
                temp->next->back = prvs;
                delete temp;
            }
        }
    }
};
int main() {
    DLL dll;
    dll.Add(6);
    dll.Add(10);
    dll.Add(12);
    dll.Add(1);
    dll.Add(4);
    dll.Add(8);
    dll.Add(15);
    dll.Display();
    dll.Search(0);
    dll.Search(20);
    dll.Search(10);
    dll.Search(9);
    dll.Delete(1);
    dll.Delete(10);
    cout<<"After delete 1 and 10 "<<endl;
    dll.Display();
    return 0;
}
