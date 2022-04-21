#include <iostream>
using namespace std;
class Node
{
    int data;
    Node *back;
    Node *next;
public:
    Node(int data) : data(data) {
        next = NULL;
        back= NULL;
    }

    Node(int data, Node *next) : data(data), next(next) {
        back = NULL;
    }

    Node(int data, Node *back, Node *next) : data(data), back(back), next(next) {

    }

    Node *getBack() const {
        return back;
    }

    void setBack(Node *back) {
        Node::back = back;
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
    }
};
class CList
{
    Node *head;
    Node *tail;
    Node *temp;
public:
    CList() {
        head = tail = NULL;
    }
    void Append(int data)
    {
        // 5 6
        if (head == NULL)
        {
            head = tail = new Node(data);
        } else
        {
            // 2  3  6 <-> 7
            temp = new Node(data);
            tail->setNext(temp);
            temp->setBack(tail);
            tail = tail->getNext();
        }
    }
    void AddAtStart(int data)
    {
        if(head==NULL)
        {
            head = tail = new Node(data);
        } else
        { // 2 3 4 5 6
            temp = new Node(data);
            temp->setNext(head);
            head->setBack(temp);
            head = temp;
        }
    }
    void Dispaly()
    {
        if(head==NULL)
        {
            cout<<"List is emply "<<endl;
            return;
        }
        temp = head;
        // 1 2 3 5 7 9
        while(temp!=NULL)
        {
            cout<<temp->getData()<<"\t";
            temp = temp->getBack();
        }
        cout<<temp->getData()<<"\n";
        // tail
    }
    void Delete(int key)
    {
        if (head==NULL)
        {
            cout<<"List is empty\n";
            return;
        }
        if(head->getData() ==key)
        {
            temp = head;
            head = head->getNext();
            delete temp;
            tail->setNext(head);
        } else
        {
            // 1 2 3 4 5 6 7
            temp = head->getNext();
            Node *prvs = head;
            bool flag = false;
            while(temp->getNext() != head)
            {
                if(temp->getData()==key)
                {
                    flag = true;
                    break;
                } //key =8
                // 1 2 3 4 5 6 7
                prvs = temp;
                temp = temp->getNext();
            }
            if(flag)
            {
                prvs->setNext(temp->getNext());
                delete temp;
            } else
            {
                if (tail->getData()==key)
                {
                    prvs->setNext(temp->getNext());
                    delete temp;
                    tail = prvs;
                } else
                {
                    cout<<key<<" not exist in link list"<<endl;
                }
            }
        }
    }
    void DeleteAll()
    {
        // 1 2 3 4 5 6
        while(head!=tail)
        {
            temp = head;
            head = head->getNext();
            delete temp;
        }
        delete tail;
        head = tail = NULL;

    }
};
int main() {
    CList cList;
    cList.Append(4);
    cList.Append(5);
    cList.Append(6);
    cList.Append(7);
    cList.AddAtStart(3);
    cList.AddAtStart(2);
   // cList.Dispaly();

    return 0;
}
