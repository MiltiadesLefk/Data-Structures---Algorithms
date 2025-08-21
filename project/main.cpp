#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>
#include <iomanip>

#include "hash.h"
#include "graph.h"
#include "avl.h"
#include "heap.h"

#define BUFF_SIZE 100

using namespace std;

bool createArray(ifstream&, int*&, int&);

int main(int argc, char *arg[]) {
    ifstream fin;
    fin.open("commands.txt");
    ofstream fout;
    fout.open("output.txt");
    string s1, s2, str, filename;
    int n1, n2, n3;
    clock_t time_req;
    minHeap myminheap;
    maxHeap mymaxheap;
    AVL myavl;
    Graph mygraph;
    Hash myhash;

    while(!fin.eof() && fin >> s1 >> s2) {
        if (s1=="END") break;                   // for DEBUG purposes
        if (s1=="BUILD") {
            fin >> filename;
            ifstream datafile;
            datafile.open(filename);
            int n, *array;
            fout << fixed << setprecision(3);


            if (s2=="MINHEAP") {         // BUILD MINHEAP
                time_req = clock();
                if ( createArray(datafile, array, n) && myminheap.buildHeap(array, n) ) {
                    cout << "Min heap built with elements:" << endl;
                    for (int i=0; i<n; i++)
                        cout << array[i] << " ";
                        cout << endl << endl;
                    fout << "SUCCESS" << endl;
                }
                else {
                    cout << "FAILURE" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                datafile.close();
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if (s2=="MAXHEAP") {    // BUILD MAXHEAP
                time_req = clock();
                if ( createArray(datafile, array, n) && mymaxheap.buildHeap(array, n) )
                    cout << "Max heap built with elements:" << endl;
                    for (int i=0; i<n; i++)
                        cout << array[i] << " ";
                        cout << endl;
                cout << endl;
                datafile.close();
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if (s2=="AVLTREE") {    // BUILD AVLTREE
                time_req = clock();
                while ( !datafile.eof() && datafile >> str ) {
                    n1 = atoi(str.c_str());
                    if(myavl.insertElement(n1))
                        cout << n1 << " inserted to AVL tree" << endl;
                }
                cout << "AVL tree built" << endl << endl;
                fout << "SUCCESS" << endl;
                datafile.close();
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if (s2=="GRAPH") {     // BUILD GRAPH
                time_req = clock();
                datafile >> n1;
                mygraph.buildGraph(n1);
                cout << "Graph built with " << n1 << " vertices" << endl;
                fout << "SUCCESS" << endl;
                char line[BUFF_SIZE];
                while(!datafile.eof()) {
                    datafile.getline(line, BUFF_SIZE, '\n');
                    if(!line[0]) continue;
                    string s;
                    int i=0;
                    while(line[i]!=' ')
                        s+=line[i++];
                    n1 = stoi(s);
                    s.clear(); i++;
                    while(line[i]!=' ')
                        s+=line[i++];
                    n2 = stoi(s);
                    s.clear(); i++;
                    while(line[i]!=0)
                        s+=line[i++];
                    n3 = stoi(s);
                    mygraph.addEdge(n1, n2, n3);
                }
                cout << endl;
                datafile.close();
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="HASHTABLE") {  // BUILD HASHTABLE
                time_req = clock();
                myhash.buildHash();
                while ( !datafile.eof() && datafile >> str ) {
                    n1 = atoi(str.c_str());
                    if(myhash.insertHash(n1))
                        cout << n1 << " inserted into the hash table" << endl;
                }
                cout << "Hash table built" << endl << endl;
                fout << "SUCCESS" << endl;
                datafile.close();
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
        }
        else if(s1=="GETSIZE") {
            if(s2=="MINHEAP") {         // GETSIZE MINHEAP
                time_req = clock();
                cout << "Min heap size: " << myminheap.getSize() << endl << endl;
                fout << myminheap.getSize() << endl;
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="MAXHEAP") {    // GETSIZE MAXHEAP
                time_req = clock();
                cout << "Max heap size: " << mymaxheap.getSize() << endl << endl;
                fout << mymaxheap.getSize() << endl;
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="AVLTREE") {    // GETSIZE AVLTREE
                time_req = clock();
                cout << "AVL tree size: " << myavl.getSize() << endl << endl;
                fout << myavl.getSize() << endl;
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="GRAPH") {      // GETSIZE GRAPH
                time_req = clock();
                cout << "Graph consists of " << mygraph.getN() << " vertices and " << mygraph.getM() << " edges" << endl << endl;
                fout << mygraph.getN() << " " << mygraph.getM() << endl;
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="HASHTABLE") {  // GETSIZE HADHTABLE
                time_req = clock();
                cout << "Hash table size: " << myhash.getSize() << endl << endl;
                fout << myhash.getSize() << endl;
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
        }
        else if(s1=="FINDMIN") {
            if(s2=="MINHEAP") {         // FINDMIN MINHEAP
                time_req = clock();int min;
                if (myminheap.findElement(min)) {
                    cout << "Min in heap: " << min << endl << endl;
                    fout << min << endl;
                }
                else {
                    cout << "Min heap empty" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="AVLTREE") {    // FINDMIN AVLTREE
                time_req = clock();
                int min;
                if (myavl.findMin(min)) {
                    cout << "Min in AVL tree: " << min << endl << endl;
                    fout << min << endl;
                }
                else {
                    cout << "AVL tree empty" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
        }
        else if(s1=="FINDMAX") {    // FINDMAX MAXHEAP
            time_req = clock();
            int max;
            if (mymaxheap.findElement(max)) {
                cout << "Max in heap: " << max << endl << endl;
                fout << max << endl;
            }
            else {
                cout << "Max heap empty" << endl << endl;
                fout << "FAILURE" << endl;
            }
            time_req = clock() - time_req;
            fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
        }
        else if(s1=="SEARCH") {
            if(s2=="AVLTREE") {     // SEARCH AVLTREE
                time_req = clock();
                fin >> n1;
                if(myavl.searchElement(n1)) {
                    cout << n1 << " found in AVL tree" << endl << endl;
                    fout << "SUCCESS" << endl;
                    time_req = clock() - time_req;
                    fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
                }
                else {
                    time_req = clock();
                    cout << n1 << " not found in AVL tree" << endl << endl;
                    fout << "FAILURE" << endl;
                    time_req = clock() - time_req;
                    fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
                }
            }
            if(s2=="HASHTABLE") {   // SEARCH HASHTABLE
                time_req = clock();
                fin >> n1;
                if(myhash.searchHash(n1)) {
                    cout << n1 << " found in hash table" << endl << endl;
                    fout << "SUCCESS" << endl;
                }
                else {
                    time_req = clock();
                    cout << n1 << " not found in hash table" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
        }
        else if(s1=="COMPUTESHORTESTPATH") {    // COMPUTESHORTESTPATH GRAPH
            time_req = clock();
            fin >> n1 >> n2;
            int *arr, size, cost=0;
            mygraph.computeShortestPath(n1, n2, arr, size, cost);
            cout << "Shortest path from " << n1 << " to " << n2 << " cost: " << cost << endl << endl;
            fout << cost << endl;
            time_req = clock() - time_req;
            fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;

        }
        else if(s1=="COMPUTESPANNINGTREE") {    // COMPUTESPANNINGTREE GRAPH
            time_req = clock();
            Graph st;
            int cost;
            mygraph.computeSpanningTree(st, cost);
            cout << "MST cost: " << cost << endl << endl;
            fout << cost << endl;
            time_req = clock() - time_req;
            fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
        }
        else if(s1=="FINDCONNECTEDCOMPONENTS") {    // FINDCONNECTEDCOMPONENTS GRAPH
            time_req = clock();
            int n;
            mygraph.findConnectedComponents(n);
            cout << "Connected components: " << n << endl << endl;
            fout << n << endl;
            time_req = clock() - time_req;
            fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
        }
        else if(s1=="INSERT") {
            if(s2=="MINHEAP") {         // INSERT MINHEAP
                time_req = clock();
                fin >> n1;
                if (myminheap.insertElement(n1)) {
                    cout << n1 << " inserted into min heap" << endl << endl;
                    fout << "SUCCESS" << endl;
                }
                else {
                    cout << "FAILURE" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="MAXHEAP") {    // INSERT MAXHEAP
                time_req = clock();
                fin >> n1;
                if (mymaxheap.insertElement(n1)) {
                    cout << n1 << " inserted into max heap" << endl << endl;
                    fout << "SUCCESS" << endl;
                }
                else {
                    cout << "FAILURE" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="AVLTREE") {    // INSERT AVLTREE
                time_req = clock();
                fin >> n1;
                myavl.insertElement(n1);
                cout << n1 << " inserted into AVL tree" << endl << endl;
            }
            else if(s2=="GRAPH") {      // INSERT GRAPH
                time_req = clock();
                fin >> n1 >> n2 >> n3;
                if (mygraph.addEdge(n1, n2, n3)) {
                    cout << n1 << "-" << n2 << " (" << n3 << ") inserted in the graph" << endl << endl;
                    fout << "SUCCESS" << endl;
                }
                else {
                    cout << "FAILURE" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            else if(s2=="HASHTABLE") {  // INSERT HASHTABLE
                time_req = clock();
                fin >> n1;
                if (myhash.insertHash(n1)) {
                    cout << n1 << " inserted into hash table" << endl << endl;
                    fout << "SUCCESS" << endl;
                }
                else {
                    cout << "FAILURE" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
        }
        else if(s1=="DELETEMIN") {      // DELETEMIN MINHEAP
            time_req = clock();
            int min;
            if (myminheap.deleteElement(min)) {
                cout << min << " deleted from min heap" << endl << endl;
                fout << "SUCCESS" << endl;
            }
            else {
                cout << "Min heap empty" << endl;
                fout << "FAILURE" << endl;
            }
            time_req = clock() - time_req;
            fout << (float)time_req * 1000.0 / CLOCKS_PER_SEC<< " millisecond(s)" << endl << endl;
        }
        else if(s1=="DELETEMAX") {      // DELETEMAX MAXHEAP
            time_req = clock();
            int max;
            if (mymaxheap.deleteElement(max)) {
                cout << max << " deleted from max heap" << endl << endl;
                fout << "SUCCESS" << endl;
            }
            else {
                cout << "Max heap empty" << endl << endl;
                fout << "FAILURE" << endl;
            }
            time_req = clock() - time_req;
            fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
        }
        else if(s1=="DELETE") {
            if(s2=="AVLTREE") {         // DELETE AVLTREE
                time_req = clock();
                fin >> n1;
                if (myavl.deleteElement(n1)) {
                    cout << n1 << " deleted from AVL tree" << endl << endl;
                    fout << "SUCCESS" << endl;
                }
                else {
                    cout << "FAILURE" << endl << endl;
                    fout << "FAILURE" << endl;
                }
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
            if(s2=="GRAPH") {           // DELETE GRAPH
                time_req = clock();
                fin >> n1 >> n2;
                mygraph.deleteEdge(n1, n2);
                cout << n1 << " deleted from graph" << endl << endl;
                time_req = clock() - time_req;
                fout << 1000.0 * time_req / CLOCKS_PER_SEC << " millisecond(s)" << endl << endl;
            }
        }
    }
    fin.close();
    fout.close();
    return 0;
}


bool createArray(ifstream& datafile, int* &array, int& n) {
	int N=5;
	array = new (nothrow) int[N];
	if (!array)
		return false;

	int n1, i=0;
	string str;
	while ( !datafile.eof() && datafile >> str ) {
		n1 = atoi(str.c_str());
		if (i==N) {
			int* temp = new (nothrow) int[2*N];
			if (!temp)
				return false;
			for (int j=0; j<N; j++)
				temp[j] = array[j];
			N = 2*N;
			delete[] array;
			array = temp;
		}
		array[i++]=n1;
	}
	n=i;
	return true;
}
