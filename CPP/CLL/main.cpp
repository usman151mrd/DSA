#include <iostream>
using namespace std;
class CLL
{
    struct Node
    {
        int data;
        Node *next;

        Node(int data) : data(data) {
            next = NULL;
        }

        Node(int data, Node *next) : data(data), next(next) {}
    }*head,*tail;
    Node *temp;
public:
    CLL() {
        head = tail = NULL;
    }
    void Add(int data)
    {
        if (head==NULL)
        {
            head = tail = new Node(data);
            tail->next = head;
        } else if (head->data > data)
        {
            head = new Node(data,head);
            tail->next = head;
        }
        else if(tail->data < data)
        {
            tail->next = new Node(data,head);
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
            prvs->next = new Node(data,temp);
        }
    }
    void Display()
    {
        temp = head;
        do
        {
            cout<<temp->data<<"\t";
            temp = temp->next;
        }
        while (temp->next != head);
        cout<<endl;
    }
    void Search(int key)
    {
        if (head->data > key || tail->data < key)
        {
            cout<<key<<"Data not found : \n";
        } else if(head->data == key)
        {
            cout<<key<<" Exist in database : "<<endl;
        }else
        {
            temp = head->next ;
            bool flag = false;
            while(temp != head)
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
            tail->next = head;
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
                delete temp;
            }
        }
    }
};
int main() {
    CLL cll;
    cll.Add(6);
    cll.Add(10);
    cll.Add(12);
    cll.Add(1);
    cll.Add(4);
    cll.Add(8);
    cll.Add(15);
    cll.Display();
    cll.Search(0);
    cll.Search(20);
    cll.Search(10);
    cll.Search(9);
    cll.Delete(1);
    cll.Delete(10);
    cout<<"After delete 1 and 10 "<<endl;
    cll.Display();
    return 0;
}
