#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
};
class List
{
    Node *head[10];
public:
    List(int size=10)
    {
        for (int i = 0; i < 10; ++i) {
            head[i] = nullptr;
        }
    }
    void Add(int key)
    {
        auto temp = new Node;
        temp->data = key;
        temp->next = NULL;
        if(head[key%10]==NULL)
        {
            head[key%10] = temp;
        } else
        {
            auto pNode = head[key % 10];
            while(pNode->next != NULL)
            {
                pNode = pNode->next;
            }
            pNode->next = temp;
        }
    }
    void display()
    {
        for (int i = 0; i < 10; ++i) {
            auto pNode = head[i];
            printf("head[%d] -> : ",i);
            while (pNode!=NULL)
            {
                cout<<pNode->data<<"->";
                pNode = pNode->next;
            }
            cout<<endl;
        }
    }

};
int main() {
    List list;
    for (int i = 0; i < 100; ++i) {
        list.Add(i);
    }
    list.display();
    return 0;
}
