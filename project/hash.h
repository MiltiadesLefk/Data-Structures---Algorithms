#ifndef HASH_H
#define HASH_H

class HashList {
private:
    struct Node {
        int data;
        struct Node *next;
    } *root;
public:
    HashList();
	~HashList();
    bool isEmpty() const;
    bool insert(int);
    bool searchList(int);
    void printList();
    void destroyList();
};


class Hash {
private:
    const int MAX_SIZE=193; // size of the hash table
    HashList *array;		// the hash table
    int size;               // size of the elements stored in the hash table
    int getHash(int);       // calculates the hash value
public:
    Hash();                 // constructor
    ~Hash();                // destructor
    bool insertHash(int);
    bool buildHash();
    void destroyHash();
    void printHash() const;
    int getSize();
    bool searchHash(int);
};

#endif // HASH_H
