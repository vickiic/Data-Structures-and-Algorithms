#include "MaxHeap.cpp"
#include <iostream>
#include <limits.h>
#include <fstream>
#include <string>
#include <vector>
#include "node.h"
using namespace std;

class HashTable
{
Node **arr;
int maxsize;
int size;
Node *x; 

public:
HashTable(int maxsize) {
  this->maxsize = maxsize;  // Initial maxsize of hash array
  size = 0;
  arr = new Node *[maxsize];
  for (int i = 0; i < maxsize; i++)  {
    arr[i] = new Node(INT_MIN, 0, 0);   // INT_MIN, Minimum value for an object of type int included in limit.h
  }
  x = new Node(-1, -1, 0);   // x node with value and key -1
}

int hashCode(int address) { return address % maxsize; }//find key's index

void insertNode(int address, int value, int priority) { //insert key value pair

  Node *temp = new Node(address, value, priority);

  int hashIndex = hashCode(address);

  while (arr[hashIndex]->address != INT_MIN && arr[hashIndex]->address != address &&
         arr[hashIndex]->address != -1) {
    hashIndex++;
    hashIndex %= maxsize;
  }

  if (arr[hashIndex]->address == INT_MIN || arr[hashIndex]->address == -1)
    size++;    // increase size when inserting new node
  arr[hashIndex] = temp;
}

bool deleteNode(int address) {   //delete a key value pair
  int hashIndex = hashCode(address);//apply hash and find node
  while (arr[hashIndex]->address != INT_MIN) {
    if (arr[hashIndex]->address == address) {
      Node *temp = arr[hashIndex];
      arr[hashIndex] = x;
      size--; //decrease size after deleting

      return true;
    }
    hashIndex++;
    hashIndex %= maxsize;
  }

  return false; //else return false
}

// Function to search the value for a given key
Node minPriority() {
	int priority = INT_MAX;
	Node y;
	for (int index= 0; index<maxsize; index++) {
		if (arr[index]->address != INT_MIN) {
			if (arr[index]->priority < priority) {
				priority = arr[index]->priority;
				y = *arr[index];
			}
		}
	}
		
   return y;
}
bool get(int address, int &value) { //search for value for a given key
  int hashIndex = hashCode(address);    // Apply hash function to find index for given key
  bool current = false;
  int round = 0;
  while (arr[hashIndex]->address != INT_MIN) {   //loop to find node with key
    if (arr[hashIndex]->address == address) {      // return value of current node
      arr[hashIndex]->priority += 1;
      value = arr[hashIndex]->value;
      current = true;
      break;
    }
    hashIndex++;
    hashIndex %= maxsize;
    if (hashIndex == (address%maxsize)) //maxsize reached, search ends
	break;
  }
  return current;
}

bool isEmpty() { return size == 0; }  //true if size is 0

void display(ofstream &outFile) {   //display keys
  for (int i = 0; i < maxsize; i++) {
    if (arr[i]->address != INT_MIN && arr[i]->address != -1)
      outFile << arr[i]->address <<" ";
  }
      outFile <<endl;
}
};

int access(int key, Heap &MH, HashTable *HT, int &value);
void display(Heap &MH, HashTable *HT, ofstream &outFile);
void load_mh(vector<Node> &data, Heap &MH);
void load_ht(Heap &MH, HashTable *HT, int k);


int main(int argc, char **argv) {
    string line;
    bool ret;
    Heap MH;
    HashTable *HT = NULL;
    int nT;  //# of test cases
    int sHT; // HashTable size
    int nI;  // # of inputs for testcases
    int nQ;  //# of queries
    vector<Node> data;
    ifstream input(argv[1]); //  input file name
    ofstream myFile;
    myFile.open(argv[2]); // output file name
    input >> nT; //Testcases
    for (int i = 0; i < nT; i++) { //get # of testcase
        data.clear();         
        MH.clear();
        if (HT != NULL)
            delete HT;

        input >> sHT; //size of hashtable
        HT = new HashTable(sHT); //create Hash Table with size sHT
        input >> nI; //# of Inputs
        input >> nQ;//# of Queries
        for (int i = 0; i < nI; i++) { //reads file input
            int address, value; //nI lines contain number of test cases in format : address, value
            input >> address >> value;
             //cout << address << " " << value << endl;
            data.push_back(Node(address, value, 0)); // priority is initialized 0
        }
        load_mh(data, MH); //load data into max heap
        for (int i = 0; i < sHT; i++) {         // move top top K (size of HT) from Max heap to Hash Table
            Node y;//temp node
            y = MH.pop();
            HT->insertNode(y.address, y.value, y.priority);
        }
     
        // each Query has diff functions/cases
        for (int j = 0; j < nQ; j++) { // run queries
            int query;
            int key;
            int value;
            int current;
            input >> query;
            switch (query) {
                case 0: // Load_MH
                    cout << "Query (0) -> Load_MH" << endl;
                    load_mh(data, MH);
                    break;
                case 1: // Load_HT
                    cout << "Query (1) -> Load_HT" << endl;
                    load_ht(MH, HT, sHT);
                    break;
                case 2: // Access
                    input >> key;
                    cout << "Query (2) -> Access(" << key << ")" << endl;
                    current = access(key, MH, HT, value);
                    if (current == 0) {
                        cout << "0"<< " " << value << endl;
                        myFile << "0" << " " << value << endl;
                    } else if (current == 1) {
                        cout << "1" << " " << value << endl;
                        myFile << "1" << " " << value << endl;
                    } else if (current == -1) {
                        cout << "-1" << endl;
                        myFile << "-1" << endl;
                    }
                    break;
                case 3: 
                    cout << "Query (3) -> display" << endl;
                    display(MH, HT, myFile);
                    break;
            }
        }
        cout << endl;
        myFile << endl;
    }
}
void load_mh(vector<Node> &data, Heap &MH) {
    for (int i = 0; i < data.size(); i++)
        MH.insert(data[i]);

}
int access(int key, Heap &MH, HashTable *HT, int &value) {
    bool current;        // check whether data is in HT, then MH
    if (!HT->isEmpty()) {
        current = HT->get(key, value);
        if (current) { // current in HT
            return 0;
        }
    }
    current = MH.get(key, value);
    if (current) { // current in MH
        return 1;
    }
    return -1;
}
void display(Heap &MH, HashTable *HT, ofstream &outFile) {
    HT->display(outFile);
    MH.display(outFile);
}
void load_ht(Heap &MH, HashTable *HT, int k) {
    int maxPriority; // max priority  in MH
    Node maxN, minN, y;
    for (int i = 0; i < k; i++) {
        maxN = MH.getTop();
        minN = HT->minPriority();
        if (minN.priority < maxN.priority ||
            (minN.priority == maxN.priority && minN.address <maxN.address)) { //check priority
                y = MH.pop();
                HT->deleteNode(minN.address);
                MH.insert(minN);
                HT->insertNode(maxN.address, maxN.value, maxN.priority);
            }
    }
}

