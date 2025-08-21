#ifndef GRAPH_H
#define GRAPH_H

struct Edge {   // accessory struct to hold an edge between two vertices
    int node;
    int parent;
};


struct Node {   // accessory struct to hold a vertex and the weight of its edge
    int id;
    int weight;
    struct Node *next;
};


class Stack {   // accessory stack
private:
    int size;
    int pos;
    Edge *data;
public:
    Stack();
    Stack(int);
    Stack(const Stack&);
    ~Stack();
    bool isEmpty();
    bool pop(Edge&);
    bool push(Edge&);
    void resize(int);
};


class List {    // accessory linked list
private:
    struct Node *root;
    unsigned int size;
public:
    List();     // constructor
    ~List();    // destructor
    bool insertNode(int, int);
    bool deleteNode(int);
    void printList();
    void destroyList();
    bool arrayList(int&, struct Node*&);
};


// class containing a graph
class Graph {
private:
    List *array;    // Adjacency lists
    int N;          // number of vertices within the graph
    int M;          // number of edges within the graph
    bool findNeighbors(int, int&, struct Node*&);
public:
    Graph();    // constructor
	~Graph();	// destructor
    bool buildGraph(int);
    int getN();
    int getM();
    void printGraph();
    bool addEdge(int, int, int);
    bool deleteEdge(int, int);
    void destroyGraph();
    bool computeShortestPath(int, int, int*&, int&, int&);
    bool computeSpanningTree(Graph&, int&);
    void DFS(int, bool[], int&);
    bool findConnectedComponents(int&);
};

#endif // GRAPH_H
