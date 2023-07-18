#pragma once
#include "Tree.h"
#define nullptr NULL


template <class T>
class SearchTree : public Tree<T>
{
public:
	// protocol for search trees
	void add(T value);
	typename Tree<T>::Node* search(T value)
	{
		return search(Tree<T>::root, value);
	}
	void remove(T value) {
		if (search(value))
		{
			if (Tree<T>::root) {
				if (Tree<T>::root->value == value) {
					Tree<T>::root = removeAccordingToFather(Tree<T>::root);
				}
				else
				{
					remove(Tree<T>::root, value);
				}
			}
		}

	}
	typename T successor(T val) { if (Tree<T>::root) { return successor(Tree<T>::root, NULL, val); } }
	int level(T val);
	void deleteDuplicates() { if (Tree<T>::root) { deleteDuplicates(Tree<T>::root); } }
private:
	typename Tree<T>::Node* removeAccordingToFather(typename Tree<T>::Node* father);
	void add(typename Tree<T>::Node* current, T val);
	typename Tree<T>::Node* search(typename Tree<T>::Node* current, T val);
	void remove(typename Tree<T>::Node* current, T val);
	int level(typename Tree<T>::Node* current, T val);
	typename T successor(typename Tree<T>::Node* current, T father, T val);
	typename Tree<T>::Node* find(typename Tree<T>::Node* current);
	void deleteDuplicates(typename Tree<T>::Node* current);
	void deleteMe(typename Tree<T>::Node* current, T val);
};
template <class T>
void SearchTree<T>::add(T val)
{
	// add value to binary search tree 
	if (!Tree<T>::root)
	{
		Tree<T>::root = new typename Tree<T>::Node(val);
		return;
	}
	add(Tree<T>::root, val);
}
template <class T>
typename Tree<T>::Node* SearchTree<T>::search(typename Tree<T>::Node* current, T val)
{
	// see if argument value occurs in tree
	if (!current)  		return nullptr;	// not found
	if (current->value == val)
		return current;
	if (current->value < val)
		return search(current->right, val);
	else
		return search(current->left, val);
}
template<class T>
void SearchTree<T>::remove(typename Tree<T>::Node* father, T val)
{
	if (father && father->right && father->right->value == val)
	{
		father->right = removeAccordingToFather(father->right);
	}
	else if (father && father->left && father->left->value == val)
	{
		father->left = removeAccordingToFather(father->left);
	}
	else if (father)
	{
		if (val > father->value)
		{
			remove(father->right, val);
		}
		remove(father->left, val);
	}

}
template<class T>
typename Tree<T>::Node* SearchTree<T>::removeAccordingToFather(typename Tree<T>::Node* root) {
	typename Tree<T>::Node* tmp;
	if (root->left) {
		if (root->right)
		{
			if (root->right->left)
			{
				tmp = find(root->right);//ptr to the father of the node to the folowing item
				tmp->left->right = root->right;
				tmp->left->left = root->left;
				delete root;
				root = tmp->left;
				tmp->left = nullptr;
			}
			else
			{
				root->right->left = root->left;
				tmp = root->right;
				delete root;
				root = tmp;
			}
		}
		else
		{
			tmp = root->left;
			delete root;
			root = tmp;
		}
	}
	else
	{
		if (root->right)
		{
			tmp = root->right;
			delete root;
			root = tmp;
		}
		else
		{
			delete root;
			root = nullptr;
		}
	}
	return root;

}
template<class T>
inline typename T SearchTree<T>::successor(typename Tree<T>::Node* current, T father, T val)
{
	if (!current)
	{
		if (father < val)
		{
			throw "no successor\n";
		}
		return father;
	}
	if (val == current->value)
	{
		if (current->right)
		{
			if (current->right->left) {
				return find(current->right)->left->value;
			}

			else {
				return current->right->value;
			}
		}
		else
		{
			return father;
		}
	}
	if (val > current->value)
	{
		return successor(current->right, father, val);
	}
	else
	{
		return successor(current->left, current->value, val);
	}

}
template<class T>
inline typename Tree<T>::Node* SearchTree<T>::find(typename Tree<T>::Node* current)//returmn ptr to the smaller leaf
{
	if (!current->left->left)
	{
		return current;
	}
	return find(current->left);
}
template<class T>
void SearchTree<T>::deleteDuplicates(typename Tree<T>::Node* current)
{
	if (current)
	{

		if (current->value && search(current->right, current->value))
		{
			if (current->right->value == current->value)
			{
				delete current->right;
				current->right = nullptr;

			}
			else
			{
				deleteMe(current->right, current->value);
			}

		}
		deleteDuplicates(current->right);
		deleteDuplicates(current->left);
	}
}
template<class T>
inline void SearchTree<T>::deleteMe(typename Tree<T>::Node* current, T val)
{

	if (!current || !current->left)
	{
		return;
	}
	if (current->left->value == val)
	{
		delete current->left;
		current->left = nullptr;
		return;

	}

	deleteMe(current->left, val);

}
template <class T>
void SearchTree<T>::add(typename Tree<T>::Node* current, T val)
{
	if (current->value <= val)
		// add to right subtree
		if (!current->right)
		{
			current->right = new typename Tree<T>::Node(val);
			return;
		}
		else add(current->right, val);
	else
		// add to left subtree
		if (!current->left)
		{
			current->left = new typename Tree<T>::Node(val);
			return;
		}
		else add(current->left, val);
}



