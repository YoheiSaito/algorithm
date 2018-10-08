#pragma once
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>
namespace teyo {
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
		void deleteTree(Node <T> * pivot){
			if(pivot->getLeft() != NULL)
				deleteTree(pivot->getLeft());
			if(pivot->getRight() != NULL)
				deleteTree(pivot->getRight());
			delete pivot;
		}

		public:
		BinaryTree(void)
		{
			root = ((Node<T>*) NULL);
		}
		BinaryTree(T rootKey)
		{
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
					if(tmp->getLeft()!= NULL)
						tmp = tmp->getLeft();
					else{
						ins->setRoot(tmp);
						tmp->setLeft(ins);
					}
				}
				else if(tmp->key < key){
					if(tmp->getRight()!= NULL) 
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

		void delNode(T key, bool discount = false){
			Node<T>* tmp = root;
			auto del_routine = [&](){
				auto rt = tmp->getRoot();
				if(tmp->getLeft() == NULL && tmp->getRight() == NULL){
					if(rt->key < key)
						rt->setRight(NULL);
					else
						rt->setLeft(NULL);
				}else if(tmp->getLeft() == NULL){
					if(rt->key < key)
						rt->setRight(tmp->getRight());
					else
						rt->setLeft(tmp->getRight());
				}else if(tmp->getRight() == NULL){
					if(rt->key < key)
						rt->setRight(tmp->getLeft());
					else
						rt->setLeft(tmp->getLeft());
				}else{
					auto t = tmp->getRoot();
					if(rt->key < key){
						auto rgt = tmp->getRight();
						rt->setRight(tmp->getLeft());
						while(t->getRight() != NULL){
							t = t->getRight();
						}
						t->setRight(rgt);

					}else{
						auto lft = tmp->getLeft();
						rt->setLeft(tmp->getRight());
						while(t->getLeft() != NULL){
							t = t->getLeft();
						}
						t->setLeft(lft);
					}
				}
			};
			while(tmp != NULL){
				if(key < tmp->key){
					tmp = tmp->getLeft();
				}else if(key > tmp->key){
					tmp = tmp->getRight();
				}else{
					if(discount){
						tmp->countdown();
						if(tmp->getCount() == 0){
							del_routine();
							delete tmp;
						}
					}else{
						del_routine();
						delete tmp;
					}
					break;
				}
			}

		}

		Node<T>* getRoot(){
			return root;
		}
		void createGraphDot(const char* filename, bool display_NIL = false){
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
			std::function<void (Node<T>*)> print_all;
			print_all = [&](Node<T>* pivot){
				if(pivot->getLeft() != NULL){
					dotFile << +pivot->key << "->" << +pivot->getLeft()->key<<";\n";
					print_all(pivot->getLeft());
				}else if(display_NIL){
					dotFile << +pivot->key << "->\"" << +pivot->key << "NIL\";\n";
				}
				if(pivot->getRight() != NULL){
					dotFile << +pivot->key << "->" << +pivot->getRight()->key<<";\n";
					print_all(pivot->getRight());
				}else if(display_NIL){
					dotFile << +pivot->key << "->\""<< +pivot->key << "NIL\";\n";
				}
			};
			dotFile << +root->key <<";\n";
			print_all(this->getRoot());
			dotFile << "}\n";
		}
		Node<T>* search(T key){
			while(1){
				if(pivot->key > key){
					if(pivot->getLeft()!= NULL)
						pivot = pivot->getLeft();
					else{
						throw "unregistered key";
						return NULL;
					}
				}
				else if(tmp->key < key){
					if(tmp->getRight()!= NULL) 
						pivot = pivot->getRight();
					else{
						throw "unregistered key";
						return NULL;
					}
				}else{
					return  pivot;
				}
			}
		
		}
		void rotateLeft(T key){
			
		}

		void rotateRight(T key){
		}

	};
}
