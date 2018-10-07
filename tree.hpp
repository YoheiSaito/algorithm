#pragma once
#include <cstddef>
namespace teyo{
	template <class T> class Node{
		Node<T> *root;
		Node<T> *left, *right;
		
		public:
		const T key;
		Node(T key_):
			key(key_)
		{
			root = NULL;
			left = NULL;
			right = NULL;
		}
		Node(T key_, Node<T> *root):
			key(key_)
		{
			this->root = root;
			this->left = NULL;
			this->right = NULL;
		}
		Node(T key_, Node<T> *left, Node<T> *right):
			key(key_)
		{
			this->root = NULL;
			this->left = left;
			this->right = right;
		}

		Node(T key_, Node<T> *root, Node<T> *left, Node<T> *right):
			key(key_)
		{
			this->root = root;
			this->left = left;
			this->right = right;
		}

		
		void setLeft(Node<T> *left){
			this->left = left;
		}
		void setRight(){
			this->right = right;
		}
		void setRoot(){
			this->root = root;
		}

		Node<T>* getLeft(void){
			return this->left;
		}
		Node<T>* getRight(void){
			return this->right;
		}
		Node<T>* getRoot(void){
			return this->root;
		}
		T getKey(){
			return this->key;
		}
	};

#if 0 
	template <class T> class BinaryTree{
	};
#endif
}
