#pragma once
#ifndef TREE_H
#define TREE_H
#include <iostream>
#ifndef nullptr
#define nullptr NULL
#endif
enum OpenType {
	in,
	out
};
enum Status {
	none,
	read,
	write,
	open,
	close
};

enum Location {
	begin,
	current,
	end
};




using namespace std;
//-----------------------------------
//  class Tree (Binary Trees)
// process nodes in Pre/In/Post  order
//-----------------------------------
template <class T>
class Tree
{
protected:
	//--------------------------------------------------------
	//  inner class Node
	//      a single Node from a binary tree
	//--------------------------------------------------------
	class Node
	{
	public:
		Node* left;
		Node* right;
		T value;
		Node(T val)
			: value(val), left(nullptr), right(nullptr) {}
		Node(T val, Node* l, Node* r)
			: value(val), left(l), right(r) {}
	};		//end of Node class

	Node* root;

public:
	Tree() { root = nullptr; }	 // initialize tree
	virtual ~Tree();
	bool isEmpty() const;
	void clear()
	{
		clear(root);
		root = nullptr;
	}
	void preOrder() { preOrder(root); }
	void inOrder() { inOrder(root); }
	void postOrder() { postOrder(root); }
	int height() { return height(root); }
	void reflect() { reflect(root); }
	virtual void process(T val) { /*cout << val << " ";*/ }
	virtual void add(T val) = 0;
	virtual Node* search(T val) = 0;
	virtual void remove(T val) = 0;
	void breadthScan() {
		if (Tree<T>::root) {
			int height = this->height();
			for (int i = 0; i <= height; i++)
			{
				breadthScan(Tree<T>::root, i);
			}

		}
	}


private:
	void  clear(Node* current);
	void  preOrder(Node* current);
	void  inOrder(Node* current);
	void  postOrder(Node* current);
	int height(Node* current);
	void reflect(Node* current);
	void breadthScan(Node* current, int level);
};


//----------------------------------------------------------
//  class Tree implementation
//----------------------------------------------------------
template <class T>
Tree<T>::~Tree() // deallocate tree
{
	if (root != nullptr)
		clear(root);
}

template <class T>
void Tree<T>::clear(Node* current)
{
	if (current)
	{    // Release memory associated with children
		if (current->left)
			clear(current->left);
		if (current->right)
			clear(current->right);
		delete current;

	}


}

template <class T>
bool Tree<T>::isEmpty() const
{
	return  root == nullptr;
}

// preOrder processing of tree rooted at current
template <class T>
void Tree<T>::preOrder(Node* current)
{    // visit Node, left child, right child
	if (current)
	{   // process current Node
		process(current->value);
		// then visit children
		preOrder(current->left);
		preOrder(current->right);
	}
}

// inOrder processing of tree rooted at current
template <class T>
void Tree<T>::inOrder(Node* current)
{    // visit left child, Node, right child
	if (current)
	{
		inOrder(current->left);
		process(current->value);
		inOrder(current->right);
	}
}

// postOrder processing of tree rooted at current
template <class T>
void Tree<T>::postOrder(Node* current)
{    // visit left child, right child, node
	if (current)
	{
		postOrder(current->left);
		postOrder(current->right);
		process(current->value);
	}
}

template<class T>
int Tree<T>::height(Node* current)
{
	if (current == nullptr)
	{
		return -1;
	}
	int left = height(current->left), right = height(current->right);
	return left > right ? left + 1 : right + 1;
}

template<class T>
void Tree<T>::reflect(Node* current)
{
	if (current != nullptr)
	{
		Node* tmp = current->right;
		current->right = current->left;
		current->left = tmp;
		reflect(current->left);
		reflect(current->right);
	}



}

template<class T>
inline void Tree<T>::breadthScan(Node* current, int level)
{
	if (!current) {
		return;
	}
	if (level == 0)
	{
		if (current && (current->value || current->value == 0))
		{
			cout << current->value << " ";
		}
	}
	else
	{
		breadthScan(current->left, level - 1);
		breadthScan(current->right, level - 1);
	}
}

#endif