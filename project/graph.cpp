#include "graph.h"
#include <iostream>

Stack::Stack() {
    size = 10;
    pos = 0;
    data = new Edge[size];
};

Stack::Stack(int n) {
    size = n;
    pos = 0;
    data = new Edge[size];
};

Stack::Stack(const Stack &other) {
    size = other.size;
    pos = other.pos;
    data = new Edge[size];
    for (int i = 0; i < size; i++)
    {
        data[i].node = other.data[i].node;
        data[i].parent = other.data[i].parent;
    }
};

Stack::~Stack() { delete[] data; };

bool Stack::isEmpty() { return (pos == 0); };

bool Stack::pop(Edge &element) {
    if (isEmpty())
        return false; // Stack empty
    pos--;
    element.node = data[pos].node;
    element.parent = data[pos].parent;
    return true; // completed normally
};

bool Stack::push(Edge &element) {
    if (pos == size)
        resize(10);
    data[pos].node = element.node;
    data[pos].parent = element.parent;
    pos++;
    return true; // completed normally
};

void Stack::resize(int n) {
    Edge *temp;
    temp = new Edge[size + n];
    for (int i = 0; i < size; i++) {
        temp[i].node = data[i].node;
        temp[i].parent = data[i].parent;
    }
    delete[] data;
    data->node = temp->node;
    data->parent = temp->parent;
    size = size + n;
};


// creates a new list
List::List() {
	root=nullptr;   // initializes the list
	size=0;         // initial size is zero
}

// destroys the list
List::~List() {
    destroyList();      // deletes all nodes
}

// insert a new node at the end of the list
bool List::insertNode(int d, int w) {
    if(!root) {             // list is empty
        struct Node *newnode = new (std::nothrow) Node;
        if(!newnode)        // if memory was unsuccessfully allocated
            return false;   // competed unsuccessfully

        newnode->id=d;          // inserts data
        newnode->weight=w;      // inserts weight
        newnode->next=nullptr;  // new node is the last node
        root=newnode;           // new node becomes the root node
        size++;                 // size of list increases
        return true;
    }

    struct Node *current=root;
    // traverse the list
    while(current->id!=d && current->next)
            current = current->next;
    if(current->id==d)  // if edge already exists
        return false;   // competed unsuccessfully

    struct Node *newnode = new (std::nothrow) Node;
    if(!newnode)        // if memory was unsuccessfully allocated
        return false;

    newnode->id=d;          // inserts data
    newnode->weight=w;      // inserts weight
    newnode->next=nullptr;  // new node is the last node
	current->next=newnode;  // new node becomes the root node
    size++;                 // size of list increases
    return true;            // competed successfully
}

// deletes a node from the list
bool List::deleteNode(int key)
{
	struct Node *current = root;    // new node shows the root node
	if(current==nullptr)    // if memory was unsuccessfully allocated
        return false;

    if(current->id==key) {  // the node we want to delete is the root node
        root=current->next; // the second node becomes the root node
        delete current;     // the old root node is deleted
        size--;                 // size of list decreases
        return true;
    }

    struct Node *prev;
    while(true) {           // searches for the key in the rest of the list
        prev=current;       // prev is an index pointer pointing to the previous node
        current=current->next;  // current is an index pointer pointing to the node after previous

        if(current==nullptr)    // the key was not found within the list
            return false;

        if(current->id==key) {    // the key exists in the current node
            prev->next=current->next;   // previous node points to the next node after current
            delete current;         // current node is deleted
            size--;                 // size of list decreases
            return true;
        }
    }
}

// prints the list
void List::printList() {
	struct Node *current = root;
	while(current!=nullptr) {
		std::cout<<current->id<<"("<<current->weight<<") ";
		current=current->next;
	}
}

// deletes every node in the list
void List::destroyList() {
	struct Node *current;
	while (root!=nullptr) { // while the list is not empty
		current=root;       // current is an index pointer pointing to the root node
		root=root->next;    // the node after root becomes the root node
		delete current;     // the old root node is deleted
	}
	size=0;
}

// creates an array with all the nodes of the list
bool List::arrayList(int &length, struct Node* &arr) {
    arr=new (std::nothrow) struct Node[size];   // allocated memory for the array
    if(!arr)                                    // if memory was unsuccessfully allocated
        return false;               // competed unsuccessfully
    struct Node *current=root;      // current is an index pointer pointing to the root node
    int i=0;                        // index for the position within the array
    current=root;                   // we start from the root node
    while (current!=nullptr) {      // while we haven't reached the end of the list
        arr[i].id = current->id;            // inserts the node in the array
        arr[i++].weight = current->weight;  // inserts the node in the array
        current = current->next;            // proceeds to the next node
    }
    length=size;    //the size of the array
    return true;    // competed successfully
}

// initializes an empty graph
Graph::Graph() {
    array=nullptr;
    N = M = 0;
}

// destroys a graph
Graph::~Graph() {
    this->destroyGraph();
}

// creates an array with the neighbors of a vertex
bool Graph::findNeighbors(int v, int& length, struct Node* &arr) {
    array[v].arrayList(length, arr);
    return true;
}

// returns the number of vertices in the graph
int Graph::getN() {
    return N;
}

// returns the number of edges in the graph
int Graph::getM() {
    return M;
}

// builds the graph
bool Graph::buildGraph(int size) {
	N=size;
	array = new (std::nothrow) List[N];  // allocates memory for the array with the adjacency lists
	if(!array)      // if memory was unsuccessfully allocated
		return false;
    return true;
}

// prints the graph
void Graph::printGraph() {
    for (int i=0; i<N; i++) {
	    std::cout<<i<<": ";
        array[i].printList();
		std::cout<<std::endl;
	}
}

// adds an edge between two vertices within the graph
bool Graph::addEdge(int v1, int v2, int w) {
	if (v1<0 || v1>N-1 || v2<0 || v2>N-1)   // if vertix ID is out of range
		return false;                       // competed unsuccessfully

    if(array[v1].insertNode(v2, w)) {   // creates the edge from v1 to v2
        array[v2].insertNode(v1, w);    // creates the edge from v2 to v1
        M++;                            // increases size of edges
        std::cout << "Edge " << v1 << "-" << v2 << " (" << w << ") added" << std::endl;
        return true;                    // competed successfully
    }
    std::cout << "Edge already exists" << std::endl;
    return false;   // competed unsuccessfully
}

// removes an edge between two vertices within the graph
bool Graph::deleteEdge(int v1, int v2) {
	if (v1<0 || v1>N-1 || v2<0 || v2>N-1)   // if vertix ID is out of range
		return false;                       // competed unsuccessfully

    if(array[v1].deleteNode(v2)) {      // removes the edge from v1 to v2
        array[v2].deleteNode(v1);       // removes the edge from v1 to v2
        M--;                            // decreases size of edges
        std::cout << "Edge " << v1 << "-" << v2 << " deleted" << std::endl;
        return true;                        // competed successfully
    }
    std::cout << "Edge does not exist" << std::endl;
    return false;   // competed unsuccessfully
}

// destroys the graph
void Graph::destroyGraph() {
    for (int v=0; v<N; v++)
        array[v].destroyList();     // removes all the edges between vertices
    delete[] array;                 // deallocates the memory of the array
    N = M = 0;
}

bool Graph::computeShortestPath(int start,              // starting vertex
                                int target,             // target vertex
                                int* &shortest_path,    // array with the path from source to target
                                int &path_size,         // number of vertices from source to target
                                int &path_length        // length of shortest path
                                ) {
	int v;
    int vertices=N;             // number of vertices
    int infinity=0;             // we consider infinity as the sum of the weights of all edges
    struct Node *neighbors;     // an array that will store the neighbors of each vertex
    int neighbors_length;       // the number of neighbors of each vertex
    for (v=0; v<vertices; v++) {                        // for each vertex
        findNeighbors(v, neighbors_length, neighbors);  // we store their neighbors in an array
        for (int i=0; i<neighbors_length; i++)			// for every neighbor of the vertex
            infinity += neighbors[i].weight;            // we sum up the edges
        delete[] neighbors;                             // we deallocate the memory for the array
    }

    int *L=new (std::nothrow) int[vertices];   // array with the length of each vertex from the source vertex
    if (!L)                     // if memory was unsuccessfully allocated
        return false;
    for (int i=0; i<vertices; i++)  // for each vertex
        L[i] = infinity;            // we set the starting distance from the source vertex to infinity
    L[start] = 0;                   // the distance of the source vertex from itself is set to zero

    int *P=new (std::nothrow) int[vertices];   // array with parents of each vertex in the shortest path
    if (!P)                     // if memory was unsuccessfully allocated
        return false;
    for (int i=0; i<vertices; i++)  // for each vertex
        P[i] = -1;              // the starting parent in the shortest path is unknown (-1)
    P[start] = start;           // the parent of the source vertex is the source vertex itself

    // Q will contain all the vertices.
    // false means the vertex isn't finalized yet; true means the vertex is already finalized.
    bool *Q=new (std::nothrow) bool[vertices];     // array with all the vertices
    if (!Q)                         // if memory was unsuccessfully allocated
        return false;
    for (int i=0; i<vertices; i++)  // each vertex
        Q[i] = false;               // is initialized with false (not finalized)

    int count=0;                // the number of vertices we have finalized
    while(count<vertices) {     // while there are vertices unfinalized
        int min=infinity;       // the length of the shortest path from the source vertex (infinity originally)
        for (int i=0; i<vertices; i++)      // we locate the next vertex we should visit (source vertex the first time)
            if (L[i]<min && Q[i]==false) {  // for every unfinalized vertex closest to the current path
                v=i;                        // we mark the vertex
                min = L[i];                 // the new minimum is the distance of the vertex we found to the current path
            }
        count++;                // we increase the number of finalized vertices
        Q[v]=true;              // the visited vertex becomes finalized
        if (v==target)          // if it was the target vertex
            break;              // we don't have to continue

        findNeighbors(v, neighbors_length, neighbors);  // we find the neighbors of the vertex we are examining
        for (int x=0; x<neighbors_length; x++) {        // for each neighbor of the vertex being examined
            if(Q[neighbors[x].id]==false && L[v]+neighbors[x].weight<L[neighbors[x].id]) { // for each unvisited neighbor
                L[neighbors[x].id] = L[v] + neighbors[x].weight;  // we calculate the new distance to the current path
                P[neighbors[x].id] = v;                           // for each neighbor we set the current vertex as its parent
            }
        }
        delete[] neighbors; // deallocate the memory for the array
    }


    path_size = 2;          // the minimum length of the shortest path is two when source and target vertices are neighbors
    v = target;             // starting from the target vertex
    while(P[v]!=start) {    // we calculate the size of the shortest path
        v = P[v];           // going backwards using the parent's array
        path_size++;        // for each hop we increase the size of the shortest path
    }

    shortest_path = new (std::nothrow) int[path_size]; // we allocate memory for the array containing the shortest path
    if (!shortest_path)                 // if memory was unsuccessfully allocated
        return false;

    v = target;                             // starting from the target vertex
    for (int i=path_size-1; i>=0; i--) {    // going backwards using the parent's array
        shortest_path[i] = v;               // we construct the shortest path array
        v = P[v];                           // using the parent's array
    }
    path_length = L[target];

    delete[] L; // we deallocate the memory for the array
    delete[] Q; // we deallocate the memory for the array
    delete[] P; // we deallocate the memory for the array

    return true;
}

// computes the length of the minimum spanning tree
bool Graph::computeSpanningTree(Graph &st, int &length) {
	int i, v;
    int neighbors_length;   // the number of neighbors of each vertex
	int start = 0;          // we arbitrarily set vertex 0 as the starting vertex
    struct Node *neighbors; // an array that will store the neighbors of each vertex

    int vertices=N;             // number of vertices
    st.buildGraph(vertices);    // we initialize the MST

    int *C = new (std::nothrow) int[vertices]; // array with the minimum edge of a vertex
    if (!C)                     // if memory was unsuccessfully allocated
        return false;

    int infinity=0;             // we consider infinity as the edge with the maximum weight plus one
    for(v=0; v<vertices; v++) {                         // for every vertex
        findNeighbors(v, neighbors_length, neighbors);  // we find its neighbors
        for (i=0; i<neighbors_length; i++)              // for every neighbor
            if(infinity < neighbors[i].weight)          // if its edge weights more than the current maximum edge
                infinity = neighbors[i].weight;         // we set infinity as the weight of that edge
        delete[] neighbors;
    }
    infinity++;                 // infinity is set as the maximum edge wight plus one
    for (i=0; i<vertices; i++)  // for each vertex
        C[i] = infinity;        // we set the starting distance of each vertex to the MST to infinity
    C[start] = 0;               // the distance of the starting vertex from the MST is set to zero

    struct Edge *E = new (std::nothrow) Edge[vertices];    // array with the optimum edge to connect to the MST
    if (!E)                 // if memory was unsuccessfully allocated
        return false;

    bool *Q = new (std::nothrow) bool[vertices];   // array with all the vertices
    if (!Q)                         // if memory was unsuccessfully allocated
        return false;
    for (i=0; i<vertices; i++)      // each vertex
        Q[i] = false;               // is initialized with false (not finalized)

    findNeighbors(start, neighbors_length, neighbors);  // we find the neighbors of the starting vertex
    for (int x=0; x<neighbors_length; x++) {            // for each neighbor
        C[neighbors[x].id] = neighbors[x].weight;		// its distance is set to the weight of the edge connecting it to the starting vertex
        E[neighbors[x].id].parent = start;				// an edge is created containing the starting vertex
        E[neighbors[x].id].node = neighbors[x].id;		// and its neighbor
    }
    delete[] neighbors; // we deallocate the memory for the array
    Q[start]=true;      // the starting vertex becomes finalized

    int count=1;        // the number of vertices we have finalized
    length=0;           // we initialize the length of the MST to zero
    while(count<vertices) { // while there are vertices unexamined
        int min=infinity;   // the minimum edge connecting the remaining vertices to the MST (infinity originally)
        for (i=0; i<vertices; i++)          // for each vertex
            if (Q[i]==false && C[i]<min) {  // for every unfinalized vertex closest to the MST
                v=i;                        // we mark the vertex
                min = C[i];                 // the new minimum is the distance of the vertex we found to the MST
            }
        count++;        // we increase the number of finalized vertices
        Q[v]=true;      // the visited vertex becomes finalized
        length += C[v];
        st.addEdge(E[v].node, E[v].parent, C[v]);
        std::cout << "Added: " << E[v].node << "-" << E[v].parent << " with weight " << C[v] << std::endl;

        findNeighbors(v, neighbors_length, neighbors);  // we find the neighbors of the vertex we are examining
        for(int x=0; x<neighbors_length; x++) {         // for each neighbor of the vertex being examined
            if(Q[neighbors[x].id]==false && neighbors[x].weight<C[neighbors[x].id]) {   // for each unvisited neighbor
                C[neighbors[x].id] = neighbors[x].weight;       // we calculate the new distance to the MST
                E[neighbors[x].id].node = v;                 // an edge is created containing the current vertex
                E[neighbors[x].id].parent = neighbors[x].id;   // and the neighbor
            }
        }
        delete[] neighbors; // we deallocate the memory for the array
    }

    delete[] C;  // we deallocate the memory for the array
    delete[] E;  // we deallocate the memory for the array
    delete[] Q;  // we deallocate the memory for the array

    return true;
}

// performs a Depth First Search of the graph
void Graph::DFS(int start, bool visited[], int& count) {
    visited[start] = true;  // starting vertex is marked as visited
    count++;                // number of visited vertices increases
    int neighbors_length;   // the number of neighbors of each vertex
    struct Node *neighbors; // an array that will store the neighbors of each vertex
    findNeighbors(start, neighbors_length, neighbors);  // we find the neighbors of the start vertex
    for (int i=0; i<neighbors_length; i++)              // for each neighbor of the start vertex
        if (!visited[neighbors[i].id])                  // if we haven't visited the vertex
            DFS(neighbors[i].id, visited, count);       // start a new DSF from the vertex
    free(neighbors);     // we deallocate the memory for the array
}

// calculates the number of disconnected subgraphs
bool Graph::findConnectedComponents(int &n) {
    bool *visited = new (std::nothrow) bool[N]; // array with all the vertices
    if(!visited)            // if memory was unsuccessfully allocated
        return false;       // competed unsuccessfully
    for(int i=0; i<N; i++)  // each vertex
        visited[i] = false; // is initialized with false (not finalized)

    int count=0;    // the number of vertices we have visited
    n=0;            // number of subgraphs
    while(count<N) {    // while there are vertices unvisited
        for (int i=0; i<N; i++) // locate the first unvisited vertex
            if(!visited[i]) {   // for the next unvisited vertex
                n++;            // number of subgraphs increases
                DFS(i, visited, count); // perform a DSF starting from that vertex
            }
    }
	delete[] visited;    // deallocate the memory for the array
	return true;        // competed successfully
}
