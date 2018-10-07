#pragma once
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>

namespace teyo{
	template <class T> class Node{
		Node<T> *root;
		Node<T> *left, *right;
		unsigned int count;
		public:
		const T key;
		Node(T key_):
			key(key_)
		{
			root = NULL;
			left = NULL;
			right = NULL;
			count = 1;
		}
		Node(T key_, Node<T> *root):
			key(key_)
		{
			this->root = root;
			this->left = NULL;
			this->right = NULL;
			count = 1;
		}
		Node(T key_, Node<T> *left, Node<T> *right):
			key(key_)
		{
			this->root = NULL;
			this->left = left;
			this->right = right;
			count = 1;
		}

		Node(T key_, Node<T> *root, Node<T> *left, Node<T> *right):
			key(key_)
		{
			this->root = root;
			this->left = left;
			this->right = right;
			count = 1;
		}

		
		void setLeft(Node<T> *left){
			this->left = left;
		}
		void setRight(Node<T> *right){
			this->right = right;
		}
		void setRoot(Node<T> *root){
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
		void countup(void){
			count++;
		}
		void countdown(void){
			count--;
		}
		unsigned int getCount(void){
			return count;
		}
	};

	template <class T> class BinaryTree{
		Node <T> *root;
		const Node<T>* NIL;
		void deleteTree(Node <T> * pivot){
			if(pivot->getLeft() != NIL)
				deleteTree(pivot->getLeft());
			if(pivot->getRight() != NIL)
				deleteTree(pivot->getRight());
			delete pivot;
		}

		public:
		BinaryTree(void)
		{
			NIL = ((Node<T>*) NULL);
			root = ((Node<T>*) NULL);
		}
		BinaryTree(T rootKey)
		{
			NIL = ((Node<T>*) NULL);
			root = new Node<T>(rootKey);
		}

		~BinaryTree(){
			deleteTree(root);
		}

		void insert(std::vector<T> keys){
			for(auto key : keys){
				this->insert(key);
			}
		}
		void insert(T key){
			Node<T>* tmp = root;
			Node<T>* ins = new Node<T> (key);
			if( root == NULL){
				root = ins;
				return;
			}
			while(ins->getRoot() == NULL){
				if(tmp->key > key){
					if(tmp->getLeft()!= NIL)
						tmp = tmp->getLeft();
					else{
						ins->setRoot(tmp);
						tmp->setLeft(ins);
					}
				}
				else if(tmp->key < key){
					if(tmp->getRight()!= NIL) 
						tmp = tmp->getRight();
					else{
						ins->setRoot(tmp);
						tmp->setRight(ins);
					}
				}else{
					tmp->countup();
					break;
				}
			}
		}

		Node<T>* getRoot(){
			return root;
		}
		void createGraphDot(const char* filename){
			std::ofstream dotFile(filename);
			dotFile << 
				"digraph binary_graph{\n"
				"graph[\n"
				"charset = \"utf-8\",\n"
				"labelloc = \"t\",\n"
				"labeljust = \"c\",\n"
				"bgcolor = \"white\",\n"
				"fontcolor = \"black\",\n"
				"fontsize = 8,\n"
				"style = \"filled\",\n"
				"layout = dot\n"
				"];\n"
				"edge[\n"
				"color = black \n"
				"];\n";
			std::function<void (Node<T>*)> all_print;
			all_print = [&](Node<T>* pivot){
				if(pivot->getLeft() != this->NIL){
					dotFile << pivot->key << "->" << pivot->getLeft()->key<<";\n";
					all_print(pivot->getLeft());
				}
				if(pivot->getRight() != this->NIL){
					dotFile << pivot->key << "->" << pivot->getRight()->key<<";\n";
					all_print(pivot->getRight());
				}
			};
			dotFile << root->key <<";\n";
			all_print(this->getRoot());
			dotFile << "}\n";
		}
	};

}
