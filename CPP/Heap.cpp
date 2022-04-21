#include <iostream>
using  namespace std;
class Heap
{
    int *arr;
    int size;
    int count;
public:
    Heap(int size=15)
    {
        this->size = size;
        arr = new int[size];
        count = 0;
    }
    int left(int index)
    {
        return 2 * index +1;
    }
    int right(int index)
    {
        return 2 * index + 2;
    }
    int parent(int index)
    {
        return (index - 1) / 2;
    }
    int max(int l, int r)
    {
        return arr[l] > arr[r] ? l : r;
    }
    void insert(int key)
    {
        if (count==size)
        {
            cout<<"Heap is full"<<endl;
            return;
        }
        arr[count++] = key;
        int index = count - 1;
        while(index!=0 and (arr[parent(index)] < arr[index]))
        {
            swap(arr[index],arr[parent(index)]);
            index = parent(index);
        }
    }
    void display()
    {
        for (int i = 0; i < count; ++i) {
            cout<<i<<"\t";
        }
        cout<<endl;
        for (int j = 0; j < count; ++j) {
            cout<<arr[j]<<"\t";
        }
        cout<<endl;
    }
    void Delete()
    {
        if (count==0)
        {
            cout<<"Heap is already empty"<<endl;
            return;
        }
        arr[0] = arr[count-1];
        int i = 0,m;
        while(i/2<count and (arr[i] < arr[max(left(i),right(i))]))
        {
            m = max(left(i),right(i));
            swap(arr[i],arr[m]);
            i = m;
        }
        count--;
    }
};
int main() {

    Heap heap;
    for (int i = 0; i  <15; ++i) {
        heap.insert(i);
    }
    heap.insert(0);
    heap.display();
    cout<<"After delete a value"<<endl;
    heap.Delete();
    heap.display();
//    heap.insert(5);
//    heap.insert(3);
//    heap.insert(10);
//    heap.insert(1);
//    heap.insert(4);
//    heap.insert(7);
//    heap.insert(15);
    cout<<"version "<<__cplusplus<<endl;

    return 0;
}
