#include <cstdlib>
#include <list>
#include <math.h>
#include <vector>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;
int perfectHash(int **hashMatrix, vector<int> data, int row, int col, int modnum);//perfect hashing
int int2dec(vector<int> x); // convert given values to decimal
int readData(vector<vector<int> > &data, char*filename);//reads data from txt file
int getTableSize(vector<std::list<vector<int> > >&table);//gets size of the matrix
int nextBin(int n);//finds next bin if collision occurs
void newHash(int **&hashMatrix, int row, int col);
void outHM(int **hashMatrix, int row, int col, ofstream &outFile);
void outHT(vector<std::list<vector<int> > >&table, ofstream &outFile);


int main(int argc, char **argv)
{
    vector<vector<int> > inputdata;
    vector<std::list<vector<int> > > l1;
    vector<std::list<vector<int> > > l2;
    srand(time(NULL)); //sets the seed of the random number generator algorithm used by the function rand()
    int inputSize = readData(inputdata, argv[1]);//first argument is the input txt file 
    ofstream myFile;
    myFile.open(argv[2]);//generates new txt file with the name of the second argument
    int b = nextBin(inputdata.size());
    int m = inputdata.size(); // number of entries of hashTable based on # of input data
    int n = inputdata[0].size(); // number of bits of input data
    int hashValues;
    int spaceUsed; //intializing value for counting space usage
    int **lvl1Matrix;
    vector<int **> lvl2Matrix;

   while(1)
    {   
        newHash(lvl1Matrix, b, n);
        l1.resize(m);
        for (int i = 0; i < inputdata.size(); i++)
        {
            hashValues = perfectHash(lvl1Matrix,inputdata[i], b, n, m);
         l1[hashValues].push_back(inputdata[i]);
        }
         spaceUsed = 0;
        for (int i = 0; i < l1.size(); ++i)
        {
         spaceUsed += l1[i].size() * l1[i].size();
        }
        cout << "Total Space Usage is: " << spaceUsed << " and 4n is: " << (4 * inputSize) << endl;//total space usage should be less than 4*input size
        if  (spaceUsed < 4 * inputSize)
        {
            cout << "Perfect Hashing Complete" << endl;
            break;
        }
        else
        {
         l1.clear();// clear hashTable and regenerate lvl1Matrix
        }
    }
    
    outHM(lvl1Matrix, b, n, myFile);//outputs results in txt file
    for (int i = 0; i < l1.size(); ++i)
    {
        if(l1[i].size() <= 1)
        {
            myFile << "NULL" << endl;//if bin doesnt require further hashing, print NULL
            myFile << endl;
        }
        else
        {
            int size = l1[i].size();
            int m2 = size * size; // generates new m = nj^2
            int b2 = nextBin(m2); 
            while (1)
            {
                int **temp;
                l2.resize(m2);
                newHash(temp, b2, n);
                for (list<vector<int> >::iterator it = l1[i].begin(); it != l1[i].end(); ++it)
                {
                hashValues = perfectHash(temp, *it,b2, n, m2);
                 l2[hashValues].push_back(*it);
                }
                int collisionfound = 0;
                for (int j = 0; j < l2.size(); ++j)
                {
                    if  (l2[j].size() > 1)
                    {
                        collisionfound = 1;//if there are more than 1 value found in a bin, clear hashtable
                        break;
                    }
                }
                if (collisionfound)
                {
                 l2.clear();
                }
                else
                {
                    outHM(temp, b2, n, myFile);
                    break;
                }
            }
        }
    }
    myFile << spaceUsed << endl;
    myFile << endl;
    for (int i = 0; i < inputdata.size(); i++)
    {
        hashValues = perfectHash(lvl1Matrix, inputdata[i], b, n, m);
        if  (l1[hashValues].size() > 1)
        {
            myFile << "2" << endl;  //if level 2 is needed for value, output 2 to indicate
        }
        else
        {
            myFile << "1" << endl; //only level 1 needed
            }
        }
    myFile << endl;
}

int getTableSize(vector<std::list<vector<int> > > &table)//returns size of Hash Table
{
    return table.size();
}

int perfectHash(int **hashMatrix, vector<int> data, int row, int col, int modnum)//perfect hashing function
{
    vector<int> val;
    for (int i = 0; i < row; i++)
    {
        int sum = 0;
        for (int j = 0; j < col; j++)
        {
            sum = sum + hashMatrix[i][j] * data[j];
        }
        val.push_back(sum);
    }
    return (int2dec(val) % modnum); //h(x) = dec(Hx)mod m where x is they key with size u bits 
}

int int2dec(vector<int> x)//function to convert binary keys to decimals
{
    int val = 0;
    int len = x.size();
    for (int i = 0; i < len; i++)
    {
        val += x[i] * pow(2, (len - i - 1));
    }
    return val;
}

int readData(vector<vector<int> > &data, char *filename)
{
    ifstream input(filename);
    int i = 0;
    for (string line; getline(input, line);)
    {
        vector<int> val;
        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == '0')
            {
                val.push_back(0);
            }
            else if (line[j] == '1')
            {
                val.push_back(1);
            }
        }
        data.push_back(val);
        i++;
    }
    cout << "There are " << i <<" inputs" <<endl;
    return i;
}

int nextBin(int n) //finds next power of 2
{
    double x = log2((double)n);
    int m = (int)x;
    if (x != m)
    {
        m = m + 1;
    }
    return m;
}

void outHT(vector<std::list<vector<int> > > &table, ofstream &outFile)
{
    for (int i = 0; i < table.size(); ++i)
    {
        for (list<vector<int> >::iterator it = table[i].begin(); it != table[i].end(); ++it)
        {
            outFile << int2dec(*it) << ' ';
        }
        outFile << endl;
    }
}


void newHash(int **&hashMatrix, int row, int col)
{
    hashMatrix = new int *[row];
    for (int i = 0; i < row; i++)
    {
        hashMatrix[i] = new int[col];
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            hashMatrix[i][j] = (int)rand() % 2; 
        }
    }
}

void outHM(int **hashMatrix, int row, int col, ofstream &outFile)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            outFile << hashMatrix[i][j]; //outputs hash matrix
        }
        outFile << endl;
    }
    outFile << endl;
}
