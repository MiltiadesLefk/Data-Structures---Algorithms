#include "hash.h"
#include <iostream>

HashList::HashList() {
	root=nullptr;
}

HashList::~HashList() {
	Node *current = root;
    while(current) {
        current = current->next;
        delete root;
        root = current;
    }
}

bool HashList::isEmpty() const {
    if(root==nullptr)
        return true;
    return false;
}

bool HashList::insert(int v) {
    struct Node *newnode=new (std::nothrow) Node;
    if(!newnode)
        return false;
    newnode->data=v;
    newnode->next=root;
	root=newnode;
    return true;
}

bool HashList::searchList(int x) {
    if(!root)
        return false;
    if(root->data==x)
        return true;
    struct Node *current=root;
    while(current->next!=nullptr) {
        if(current->data==x)
            return true;
        current=current->next;
    }
    if(current->data==x)
            return true;
    return false;
}

void HashList::printList() {
	struct Node *current = root;
	while(current!=nullptr) {
		std::cout<<current->data<<" ";
		current=current->next;
	}
	std::cout<<std::endl;
}

void HashList::destroyList() {
	struct Node *current;
	while(root!=nullptr) {
		current=root;
		root=root->next;
		delete current;
	}
}


// initializes the hash table
Hash::Hash() {
    array=nullptr;
    size=0;
}

// destroys the hash table
Hash::~Hash() {
    delete[] array;
    array=nullptr;
}

// returns the hash value of a number
// h(x) = (2x + 1) mod 193
int Hash::getHash(int x) {
    return (2*x+1)%MAX_SIZE;
}

// searches the hash table for a key
bool Hash::searchHash(int key) {
    if(array==nullptr || size==0)      // if hash table is empty
        return false;       // complete unsuccessfully
    int pos=getHash(key);   // find the position of the key
    if(array[pos].searchList(key)==true)    // if key exists in the list
        return true;        // complete unsuccessfully
    return false;           // complete unsuccessfully
}

// returns the size of the hash table
int Hash::getSize() {
    return size;
}

// prints the hash table
void Hash::printHash() const {
    for(int i=0; i<MAX_SIZE; i++) {
        if(!array[i].isEmpty()) {
            std::cout<<i<<": ";
            array[i].printList();
        }
    }
    std::cout << "No of elements: " << size << std::endl;
}

// deletes all data in the hash table
void Hash::destroyHash() {
    for (int i=0; i<size; i++)
        array[i].destroyList();
    size=0;
    delete[] array;
    array=nullptr;
}

// inserts an element in the hash table
bool Hash::insertHash(int data) {
    if(array==nullptr)  // if hash table hasn't been built yet
        return false;   // complete unsuccessfully
    int pos=getHash(data);  // find the position to store the element
    if(array[pos].searchList(data)==true)   // if the element already exists
        return false;   // complete successfully
    array[pos].insert(data);    // inserts the element in the hash table
    size++;             // increases the size of the hash table
    return true;        // complete successfully
}

// allocates memory for the hash table
bool Hash::buildHash() {
    array=new (std::nothrow) HashList[MAX_SIZE];
    if(!array)          // if memory allocation unsuccessful
        return false;   // complete unsuccessfully
    return true;        // complete unsuccessfully
}
