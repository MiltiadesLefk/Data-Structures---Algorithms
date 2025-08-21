#ifndef HEAP_H
#define HEAP_H

// class that holds a priority queue
class PriorityQueue {
protected:
    const int MAX_SIZE=100; // initial size of a default priority queue
    int *data;
    int N;                   // number of nodes in the priority queue
    int SIZE;                // size of the priority queue
    void swap(int&, int&);
    virtual int compare(int, int) const;
    bool heapify(int);
    bool resize();
public:
    PriorityQueue();                // default constructor
    PriorityQueue(int);             // constructor with custom size
    PriorityQueue(PriorityQueue&);  // copy constructor
    ~PriorityQueue();               // destructor
    bool buildHeap(int[], int);
    int getSize() const;
    bool findElement(int&) const;
    bool insertElement(int);
    bool deleteElement(int&);
    void printPQ();
};

// subclass of a priority queue that holds a minimum heap
class minHeap : public PriorityQueue {
protected:
    int compare(int, int) const;
};

// subclass of a priority queue that holds a maximum heap
class maxHeap : public PriorityQueue {
protected:
    int compare(int, int) const;
};

#endif // HEAP_H
