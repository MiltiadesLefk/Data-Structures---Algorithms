# 🗂️ Data Structures & Algorithms Implementation

**Author:** Miltiadis Lefkopoulos  

This repository contains implementations of several fundamental **data structures** and **graph algorithms** in C++, including:

- 🌳 **Binary Search Trees (BSTs)**
- 📊 **Weighted Undirected Graphs**
- 🧩 **Hash Tables**

Each implementation comes with associated operations and auxiliary classes for efficient management.

---

## 📑 Table of Contents

- [Binary Search Tree](#binary-search-tree-bst)
- [Weighted Undirected Graph](#weighted-undirected-graph)
- [Hash Table](#hash-table)

---

## 🌳 Binary Search Tree (BST)

Implemented as a dynamic tree with nodes storing integer elements.  

### ⚡ Features

- **Insert & Delete**
  - `insertRoot(Node*&, int)`: Insert a node at the root of a subtree.
  - `deleteRoot(int&)`: Delete the root node if it has no children.
  - `deleteLeft(Node*, int&)`: Delete the left child of a node.
  - `deleteRight(Node*, int&)`: Delete the right child of a node.
- **Tree Operations**
  - `height(Node*)`: Returns the height of a subtree.
  - `rotateR(Node*) / rotateL(Node*)`: Right/left rotation of a node.
  - `rotateLR(Node*) / rotateRL(Node*)`: Left-right / right-left rotations for balancing.
  - `clearBST(Node*)`: Recursively deletes a subtree (used in destructor).

---

## 📊 Weighted Undirected Graph

Graph is stored as **adjacency lists** with weighted edges.  

### ⚡ Features

- **Graph Construction**
  - `Graph()` / `~Graph()`: Constructor and destructor.
  - `buildGraph(int)`: Initializes graph with given number of vertices.
- **Edge Operations**
  - `addEdge(int, int, int)`: Adds an edge with weight.
  - `deleteEdge(int, int)`: Deletes an edge.
  - `destroyGraph()`: Frees all memory for vertices and edges.
- **Graph Algorithms**
  - `computeShortestPath(int, int, int*&, int&, int&)`: Shortest path via Dijkstra's algorithm.
  - `computeSpanningTree(Graph&, int&)`: Minimum Spanning Tree via Prim's algorithm.
  - `findConnectedComponents(int&)`: Counts connected components using DFS.

### 🛠️ Auxiliary Classes

- `Stack`: Used for depth-first search.
- `List`: Implements adjacency lists.

---

## 🧩 Hash Table

Implemented using **Separate Chaining** with singly linked lists to handle collisions.  

### ⚡ Features

- Hash function: `h(x) = (2x + 1) mod 193`  
- Class: `HashList` for storing integer elements in a list.
- Methods:
  - Insert, Delete, Search elements in the hash table.
- Table size: `193` (prime number to reduce collisions).

---
