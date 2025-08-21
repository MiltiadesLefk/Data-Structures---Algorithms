#include "avl.h"
#include <iostream>


// initialized the tree
AVL::AVL() {
	root=nullptr;
	size=0;
}

// destroys the tree
AVL::~AVL() {
	if(root)
		clearBST(root);
}

// finds the minimum element of the tree
bool AVL::findMin(int &a) const {
	if(!root)				// if tree is empty
		return false;		// completes unsuccessfully
	Node *current = root;	// index points to root node
	while(current->left)	// while there is a left child (smaller element)
		current=current->left;	// index points to the next left child
	a = current->data;		// returns the data of the leftmost element
	return true;			// completes successfully
}

// returns if the AVL tree is empty
bool AVL::isEmpty() const {
   return root==nullptr;
}

// returns the size of the AVL tree
int AVL::getSize() const {
	return size;
}

// returns the data of a node
int AVL::getData(Node* p) const {
   return p->data;
}

// inserts a new node in the AVL tree
bool AVL::insertElement(int a) {
	return insertAVL(root, a);	// insert new node starting from the root node and finding the proper position
}

// deletes a node from the AVL tree
bool AVL::deleteElement(int key) {
	return deleteAVL(root, key);	// deletes the node starting from the root node and finding the proper position
}

// accessory method; inserts a new node as root of a subtree
bool AVL::insertRoot(Node* &root, int a) {
	if(root)					// the root of the subtree already exists
		return false;			// completes unsuccessfully
	Node *newnode = new (std::nothrow) Node;	// allocates the memory for the new node
	if (!newnode)				// if memory allocation failed
		return false;			// completes unsuccessfully
	newnode->data=a;			// stores the data in the new node
	newnode->left = newnode->right = nullptr;	// the new node doesn't have any kids
	root=newnode;				// the starting node now is the new node
	size++;						// the size increases
	return true;				// completes successfully
}

// accessory method; deletes the root of the AVL tree
bool AVL::deleteRoot(int& a) {
	if(root->left || root->right)	// if the root has any children
		return false;				// completes unsuccessfully
	a=root->data;					// returns the data of the root
	delete root;					// deallocates the memory used by the root
	root=nullptr;					// root now points to null
	size = 0;						// tree is empty
	return true;					// completes successfully
}

// accessory method; deletes the left child of a node
bool AVL::deleteLeft(Node *parent, int& a) {
	if(!parent->left)				// the node doesn't have a left child
		return false;				// completes unsuccessfully
	Node *current=parent->left;		// temporary stores the left child
	if(current->left || current->right)	// the left child has children
		return false;				// completes unsuccessfully
	a=current->data;				// returns the data of the left child
	delete current;					// deallocates the memory of the left child
	parent->left=nullptr;			// the parent node now has no left child
	return true;					// completes successfully
}

// accessory method; deletes the right child of a node
bool AVL::deleteRight(Node *parent, int& a) {
	if(!parent->right)				// the node doesn't have a right child
		return false;				// completes unsuccessfully
	Node *current=parent->right;	// temporary stores the right child
	if(current->left || current->right)	// the right child has children
		return false;				// completes unsuccessfully
	a=current->data;				// returns the data of the left child
	delete current;					// deallocates the memory of the left child
	parent->right=nullptr;			// the parent node now has no right child
	return true;					// completes successfully
}

// accessory method; returns the height the subtree of a node
int AVL::height(Node* R) {
	if(!R)
		return 0;
	else
		return R->height;
}

// accessory method; performs a right rotation
AVL::Node* AVL::rotateR(Node* C) {
	Node* L = C->left;
	C->left = L->right;	// the right child of the left child becomes the left child of the parent node
	L->right = C;		// the parent node becomes the right child of the left child
	C->height = std::max(height(C->left), height(C->right))+1; // the height of the parent is one greater than the maximum height of its children
	L->height = std::max(height(L->left), height(L->right))+1; // the height of the left child is one greater than the maximum height of its children
	return L;			// the left child will become the parent
}

// accessory method; performs a left rotation
AVL::Node* AVL::rotateL(Node* C) {
   Node* R = C->right;
   C->right = R->left;	// the left child of the right child becomes the right child of the parent node
   R->left = C;			// the parent node becomes the left child of the right child
   C->height = std::max(height(C->left), height(C->right))+1;	// the height of the parent is one greater than the maximum height of its children
   R->height = std::max(height(R->left), height(R->right))+1;	// the height of the right child node is one greater than the maximum height of its children
   return R;			// the right child will become the parent
}

// accessory method; performs a left-right rotation
AVL::Node* AVL::rotateLR(Node* C) {
   C->left = rotateL(C->left);	// a left rotation is performed
   return rotateR(C);			// a right rotation is performed
}

// accessory method; performs a right-left rotation
AVL::Node* AVL::rotateRL(Node* C) {
   C->right = rotateR(C->right);	// a right rotation is performed
   return rotateL(C); 				// a left rotation is performed
}

// accessory method; inserts a new node starting from the root of a subtree
bool AVL::insertAVL(Node* &root, int a) {
	if (!root) {					// if subtree is empty
		insertRoot(root, a);	// insert the new node as root
		root->height=1;				// height becomes one
		return true;				// root is the new node
	}
	else if(a<root->data) {			// if data is smaller than the current node
		insertAVL(root->left, a);	// insert the new node at the left subtree
		if(height(root->left)-height(root->right)==2) {	// if tree becomes unbalanced
			if(a<root->left->data)	// if data inserted in the left of the left child
				root=rotateR(root);	// perform a right rotation to balance the tree
			else					// if data inserted in the right of the left child
				root=rotateLR(root);	// perform a left-right rotation to balance the tree
		}
	}
	else if (a>root->data) {		// if data is greater than the current node
		insertAVL(root->right, a);	// insert the new node at the right subtree
		if(height(root->left)-height(root->right)==-2) {	// if tree becomes unbalanced
			if(a>root->right->data)	// if data inserted in the right of the right child
				root=rotateL(root);	// perform a left rotation to balance the tree
			else					// if data inserted in the left of the right child
				root=rotateRL(root);	// perform a right-left rotation to balance the tree
		}
	}
	// if new element already exists we do nothing

	root->height = std::max(height(root->left), height(root->right))+1;	// the height of the parent is one greater than the maximum height of its children
	return true;
}

// accessory method; finds the path to a node, deletes the node and corrects possible imbalances
bool AVL::deleteAVL(Node* &root, int key) {
	Node* pred[size];	// array storing the path till we find the node to be deleted
	int orient[size];	// for each node of the path, we store 0 for left, 1 for right
	int i=0;			// number of nodes from root to node containing the key value

	if (!root)			// if tree is empty
		return false;	// completes unsuccessfully

	// Finds all the node from the root to the node to be deleted so that we can later check for imbalances
	Node *current=root;		// index points to the root
	while(current) {	// while current exists
		if(key == current->data)	// if it holds the key
			break;					// stop searching
		else if(key < current->data) {	// if key in the left subtree
			orient[i]=0;			// store that we traveled left
			pred[i++]=current;		// current node is next in the path traveled
			current=current->left;	// proceed to the left child
		}
		else { // x > current->data
			orient[i]=1;			// store that we traveled right
			pred[i++]=current;		// current node is next in the path traveled
			current=current->right;	// proceed to the right child
		}
	}

	if(!current)		// key not found
		return false;	// completes unsuccessfully

	// we have found the node to be deleted

	// case 1: the node to be deleted has two children
	// the deleted node will be replaced by the leftmost child of its right child
	// we continue storing the path according to the inorder traversal
	if(current->left && current->right) {
		orient[i]=1;			// store that we traveled right
		pred[i++]=current;		// current node is next in the path traveled
		current=current->right;	// proceed to the right child

		while (current->left) {
			orient[i]=0;		// store that we traveled left
			pred[i++]=current;	// current node is next in the path traveled
			current=current->left;	// proceed to the left child
		}
	}

	// delete the node as if was a node in a standard BST
	if(deleteBST(root, key))
		size--;

	// check for imbalances caused by the deletion
	Node *new_root;
	for(int j=i-1; j>=0; j--) {		// go backwards the path
		if(height(pred[j]->left)-height(pred[j]->right)==2) {				// left subtree taller
			if(height(pred[j]->left->left)>height(pred[j]->left->right))	// right rotation needed
				new_root=rotateR(pred[j]);	//perform a right rotation
			else
				new_root=rotateLR(pred[j]);	//perform a left-right rotation
		}
		else if(height(pred[j]->left)-height(pred[j]->right)==-2) {			// right subtree taller
			if(height(pred[j]->right->right)>height(pred[j]->right->left))	// left rotation needed
				new_root=rotateL(pred[j]);	//perform a left rotation
			else
				new_root=rotateRL(pred[j]);	//perform a right-left rotation
		}
		else
			continue;	// no imbalances in this node

		if(j==0)				// we have reached the root
			root = new_root;	// store the new root
		else
			if(orient[i-2]==0)				// we reached the current node by traveling left
				pred[i-2]->left=new_root;	// store the new node
			else							// we reached the current node by traveling right
				pred[i-2]->right=new_root;	// store the new node
	}
	return true;
}

// accessory method; deletes a node from a standard BST
bool AVL::deleteBST(Node* &root, int key) {
	Node *current;	// index point the node on the path to finding the key node
	Node *parent;	// stores the parent of the current node
	int p; 			// stores the orientation from parent to next node; 1 for a left child, 2 for a right child of current node

	// search for the key node
	current=root;		// start from the root
	parent=nullptr;		// root has no parent
	while(current) {
		if(key == current->data)	// if key node found
			break;					// stop searching
		else if(key < current->data) {	// if key smaller that current node
			parent=current;				// store the parent node before going left
			p=1;						// store that we traveled left
			current=current->left;		// proceed to the left subtree
		}
		else { 							// if key greater that current node
			parent=current;				// store the parent node before going left
			p=2;						// store that we traveled right
			current=current->right;		// proceed to the right subtree
		}
	}
	if(!current)		// if key not found
		return false;	// completes unsuccessfully

	// key node found
	if(!current->left && !current->right) {	// case node has no children
		delete current;						// delete the node

		if(!parent)							// if it has no parent (it is the root node)
			root=nullptr;					// tree is empty
		else								// if it is not the root node
			if(p==1)						// the deleted node was a left child
				parent->left=nullptr;		// the node's parent now has no left child
			else							// the deleted node was a right child
				parent->right=nullptr;		// the node's parent now has no right child
		return true;						// completes successfully
	}
	else if(current->left && !current->right) {	// case node has only a left child
		if(!parent)								// if it has no parent (it is the root node)
			root=current->left;					// the node's left child becomes the root
		else									// if it is not the root node
			if(p==1)							// the deleted node was a left child
				parent->left=current->left;		// the deleted node's left child takes its place
			else								// the deleted node was a right child
				parent->right=current->left;	// the deleted node's left child takes its place
		delete current;							// deallocate the memory for the deleted node
		return true;							// completes successfully
	}
	else if(!current->left && current->right) {	// case node has only a right child
		if(!parent)								// if it has no parent (it is the root node)
			root=current->right;				// the node's right child becomes the root
		else									// if it is not the root node
			if(p==1)							// the deleted node was a left child
				parent->left=current->right;	// the deleted node's right child takes its place
			else								// the deleted node was a right child
				parent->right=current->right;	// the deleted node's right child takes its place
		delete current;							// deallocate the memory for the deleted node
		return true;							// completes successfully
	}
	else {										// case node has two children
		// find the next node in the inorder traversal (leftmost node of the right child)
		p=2;								// the node is a right child
		Node *nextOrdered=current->right;	// go right only once
		while(nextOrdered->left) {			// travel to the leftmost bottom
			parent=nextOrdered;				// store the parent
			nextOrdered=nextOrdered->left;	// go to the next left
			p=1;							// the node is a left child
		}

		// leftmost node of the right child found
		current->data=nextOrdered->data;	// trade values with the leftmost node of the right child (delete key node)
											// if it has right subtree, it won't carry it

		if(p==2) {	// inorder had no left subtree
			current->right=nextOrdered->right;	// subtree of the next node becomes right subtree of the node that took the place of the deleted node
			delete nextOrdered;					// deallocate the memory for the right child of the deleted node
		}
		else {		// inorder had left subtree
			parent->left=nextOrdered->right;	// subtree of the leftmost node of the right child becomes left subtree of its parent
			delete nextOrdered;					// deallocate the memory for the leftmost node of the right child
		}
	}
	return true;
}

// prints the AVL tree
void AVL::printAVL() {
	printSubTree(root);		// start printing from the root
	std::cout<<std::endl;
}

// accessory method; prints the subtree of a node
void AVL::printSubTree(Node *node)  {
	if(!node)				// if current node doesn't hold any data
		return;				// stop printing
	if(node->left) {		// if a left subtree exists
		std::cout << "(";
		printSubTree(node->left); // print the left subtree
		std::cout << ")";
	}
	std::cout << node->data;	// print the data of the current node
	if(node->right) {			// if a right subtree exists
		std::cout << "(";
		printSubTree(node->right);	// print the right subtree
		std::cout << ")";
	}
}

// searches the AVL tree for a key element
bool AVL::searchElement(int key) const {
	Node *current=root;					// an index points to root
	while(current) {					// while the node exists
		if(key == current->data)		// if it holds the key
			return true;				// key is found
		else if(key < current->data)	// if key is smaller than the data in the current node
			current=current->left;		// search starting from the left child
		else							// if key is greater than the data in the current node
			current=current->right;		// search starting from the right child
	}
	return false;						// key is not found
}

// accessory method; deletes all nodes of a subtree using postorder traversal
void AVL::clearBST(Node* parent) {
	if(parent->left)
		clearBST(parent->left);
	if(parent->right)
		clearBST(parent->right);
	delete parent;
}
