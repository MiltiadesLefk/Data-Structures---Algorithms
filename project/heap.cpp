#include "heap.h"
#include <iostream>
#include <cmath>


// default constructor
PriorityQueue::PriorityQueue() {
    SIZE=MAX_SIZE;
    data=new int[SIZE];
    N=0;
}

// constructor with custom size
PriorityQueue::PriorityQueue(int a) {
    SIZE=a;
    data=new int[SIZE];
    N=0;
}

// copy constructor
PriorityQueue::PriorityQueue(PriorityQueue&other) {
    N=other.N;
    SIZE=other.SIZE;
    data=new int[SIZE];
    for(int i=0; i<N; i++)
        data[i]=other.data[i];
}

// destructor
PriorityQueue::~PriorityQueue() {
    delete[] data;
    data=nullptr;
    SIZE=N=0;
}

// returns the size of the priority queue
int PriorityQueue::getSize() const {
    return N;
}

// returns the minimum value in a minheap or the maximum value in a maxheap
bool PriorityQueue::findElement(int&a) const {
    if(N) {
        a=data[0];
        return true;
    }
    return false;
}

// creates a priority queue from an array
bool PriorityQueue::buildHeap(int array[], int n) {
    if (N)                       // if heap not empty
        N = 0;                   // consider heap as empty

    for(int i=0; i<n; i++) {
        if(i==SIZE && !resize())    // resizes the priority queue to hold the data
            return false;           // fails if memory allocation unsuccessful
        data[N++]=array[i];         // inserts the cell data in the priority queue
    }

    int left, right=N-1, child, parent=(right-1)/2;
    if(N%2==0) {  // if the last leaf has no right left child
        if(compare(data[N-1], data[parent])>0)  // if left child smaller than parent
            swap(data[N-1], data[parent]);      // swaps child with parent
        right--;                                // proceeds to the previous leaf (now a right child)
        parent=(right-1)/2;                     // finds its parent
    }

    while(right>=2) {       // while we have a parent with two children
        left=right-1;       // we find the left child
        if (compare(data[left], data[right])<0)  // if right child smaller that left child
            child=right;    // we should check the parent with the right child
        else
            child=left;     // we should check the parent with the right child

        if(compare(data[parent], data[child])<0) {  // if parent greater than the smallest child
            swap(data[parent], data[child]);        // swap parent and smallest child
            heapify(child);                         // check if parent needs to go further down
        }
        right-=2;               // proceeds to the previous right child
        parent=(right-1)/2;     // finds its parent
    }
    return true;    // completed successfully
}

// swaps two nodes
void PriorityQueue::swap(int&a, int&b) {
	int temp;
	temp=a;
	a=b;
	b=temp;
}

// compares two nodes
// returns <0 if a<b, 0 if a==b, 0 if a>b
// priority queue works as a minimum heap
int PriorityQueue::compare(int a, int b) const {
    return b-a;
}

// compares two nodes
// returns <0 if a<b, 0 if a==b, >0 if a>b
int minHeap::compare(int a, int b) const {
    return b-a;
}

// compares two nodes
// returns >0 if a<b, 0 if a==b, <0 if a>b
// we can use the priority queue code as a maximum heap
int maxHeap::compare(int a, int b) const {
    return a-b;
}

// inserts a new node in the priority queue
bool PriorityQueue::insertElement(int a) {
	int parentindex, elementindex;

	if(N==SIZE && !resize())    // resizes the size of the priority queue if needed
		return false;           // resize unsuccessful
	data[N]=a;                  // inserts new node if the end of the heap

	elementindex=N++;       // position of the new node
	while(elementindex) {   // while new node not in root
		parentindex=(elementindex-1)/2; // find the parent of the new node
		if(compare(data[elementindex], data[parentindex])>0) {  // if new node smaller that its parent
			swap(data[elementindex],data[parentindex]);         // swap node and parent
			elementindex=parentindex;                           // current position of the new node
		}
		else                // node in correct position
			return true;    // completed successfully
	}
    return true;            // completed successfully
}

// deletes root node from the priority queue
bool PriorityQueue::deleteElement(int&a) {
	if(N==0)            // if priority queue is empty
		return false;   // completed unsuccessfully
	a=data[0];          // return value of root node
	data[0]=data[--N];  // place last node in root
    if(N==0)            // there was only root
        return true;    // completed successfully
	return heapify(0);  // check if new root is in correct position
}

// checks if a node is in correct position
bool PriorityQueue::heapify(int a) {
	int parent, left, right, child;
	parent=a;              // consider the node in question as the parent
	while(true) {
		left=2*parent+1;    // find its left child
		right=2*parent+2;   // find its right child
		if(left>=N)         // if it has no left child
			left=-1;
		if(right>=N)	    // if it has no right child
			right=-1;
		if(left==right)     // if it has no children
			return true;    // completed successfully

		if(right==-1) {     // if is has only one child (a left child)
			if(compare(data[parent], data[left])<0) // compare the parent with the child
				swap(data[parent], data[left]);     // swap them if necessary
            return true;    // completed successfully
		}

		// if it has two children
        if (compare(data[left], data[right])<0)  // find the smallest child
            child=right;
        else
            child=left;
        if(compare(data[parent], data[child])<0) {  // if parent is greater than the smallest child
            swap(data[parent], data[child]);        // swap parent with the smallest child
            parent=child;                           // track the current position of the node in question
        }
        else
            return true;    // completed successfully
	}
}

// print the priority queue
void PriorityQueue::printPQ() {
    for(int i=0; i<=log2(N); i++) {
        for(int j=0; j<pow(2, i); j++) {
            int pos=(int)pow(2, i)-1+j;
            if(pos==N)
                break;
            std::cout << data[pos] << ' ';
        }
        std::cout << std::endl;
    }
}

// resize the priority queue
bool PriorityQueue::resize() {
    int *temp = new (std::nothrow) int[2*SIZE];  // allocate double the space for the priority queue
    if(!temp)               // memory allocation unsuccessfully
        return false;       // completed unsuccessfully
    for(int i=0; i<N; i++)  // copy the nodes of the original priority queue to the new one
        temp[i]=data[i];
    delete[] data;          // deallocate the memory of the original priority queue
    data=temp;              // newly allocated memory now stores the priority queue
    SIZE *= 2;              // with double the size
    return true;
}
