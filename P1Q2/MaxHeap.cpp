#include "node.h"
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class Heap {
    vector<Node> list;
    void swap(int child, int parent) {
        Node t; //temp node
        t = list[child];
        list[child] = list[parent];
        list[parent] = t;
    }
    
    int getParent(int child) {
        if (child % 2 == 0)
            return (child / 2) - 1;
        else
            return child / 2;
    }
    
    int leftChild(int parent) { return 2 * parent + 1; }
    int rightChild(int parent) { return 2 * parent + 2; }
    
    void heapify_up() {
        int child = list.size() - 1;
        int parent = getParent(child);
        while (((list[child].priority > list[parent].priority) || ((list[child].priority == list[parent].priority) && (list[child].address > list[parent].address)))&& child >=0 && parent >= 0) {
            swap(child, parent);
            child = parent;
            parent = getParent(child);    
        }
    }
    
    void heapify_down() {
        int parent = 0;
        while (1) {
            int left = leftChild(parent);
            int right = rightChild(parent);
            int length = list.size();
            int max = parent;
            
            if (left < length && ((list[left].priority > list[max].priority) || (list[left].priority == list[max].priority && list[left].address > list[max].address)))
                max = left;
            
            if (right < length && ((list[right].priority > list[max].priority) || (list[right].priority == list[max].priority &&list[right].address > list[max].address)))
                max = right;

            if (max != parent) {
                swap(max, parent);
                parent = max;
            } else
                break;
        }
    }
public:
Heap() {}

void clear() {
   list.clear();
}
void insert(Node value) {
        list.push_back(value);
        heapify_up();
}

Node getTop() { return list[0]; }

Node pop() {
        int child = list.size() - 1;
        swap(child, 0);
        Node value = list.back();
        list.pop_back();
        heapify_down();
        return value;
    }
    
int getSize() { return list.size(); }

bool get(int address, int &value) {
        int length = list.size();
        bool found = false;
        for (int i = 0; i < length; i++) {
            if (list[i].address == address) {
                found = true;
                value = list[i].value;
                list[i].priority += 1;
             heapify(i); // priority increase and need to adjust maxheap because order is based on priority
                break;
            }
        }
        return found;
}
    
bool heapify(int index) {
        while (index != 0 && ((list[getParent(index)].priority < list[index].priority) || (list[getParent(index)].priority == list[index].priority && list[getParent(index)].address < list[index].address))) {
            swap(index, getParent(index));
            index = getParent(index);
        }
    }
    
void display(ofstream &outFile) {
        int length = list.size();
        for (int i = 0; i < length; i++)
            outFile << list[i].address << " ";
        outFile << endl;
    }
};
