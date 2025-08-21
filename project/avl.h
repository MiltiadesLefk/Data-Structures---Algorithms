#ifndef AVL_H
#define AVL_H

class AVL {
protected:
	struct Node {				// struct with the nodes of the AVL tree
        int data;				// holds the data
        int height;				// holds the height of the subtree
        Node *left;				// points to the left child
        Node *right;			// points to the right child
    } *root;
    int size;					// number of nodes
	void printSubTree(Node*);
	int getData(Node*) const;
	bool insertAVL(Node*&, int);
	bool deleteAVL(Node*&, int);
	bool deleteBST(Node*&, int);
	bool insertRoot(Node*&, int);
	bool deleteRoot(int&);
	bool deleteLeft(Node*, int&);
	bool deleteRight(Node*, int&);
	int height(Node*);
	Node* rotateR(Node*);
	Node* rotateL(Node*);
	Node* rotateLR(Node*);
	Node* rotateRL(Node*);
	void clearBST(Node*);
public:
	AVL();						// constructor
	~AVL();						// destructor
	bool isEmpty() const;
	int getSize() const;
	bool findMin(int&) const;
	bool searchElement(int) const;
	bool insertElement(int);
	bool deleteElement(int);
	void printAVL();
};

#endif // AVL_H
