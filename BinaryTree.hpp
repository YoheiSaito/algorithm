#pragma once
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
#include <functional>

#include "Node.hpp"

namespace teyo {
	template <class T> class BinaryTree{
		protected:
		Node <T> *root;
		virtual void deleteTree(Node <T> * pivot){
			if(pivot != NULL)
				return;
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
		virtual void insert(Node<T>* ins){
			Node<T>* tmp = root;
			if( root == NULL){
				root = ins;
				return;
			}
			while(ins->getParent() == NULL){
				if(tmp->key > ins->key){
					if(tmp->getLeft()!= NULL)
						tmp = tmp->getLeft();
					else{
						ins->setParent(tmp);
						tmp->setLeft(ins);
					}
				}
				else if(tmp->key < ins->key){
					if(tmp->getRight()!= NULL) 
						tmp = tmp->getRight();
					else{
						ins->setParent(tmp);
						tmp->setRight(ins);
					}
				}else{
					tmp->countup();
					break;
				}
			}
		}

		virtual void insert(T key){
			Node<T>* ins = new Node<T> (key);
			insert(ins);
		}
		
		virtual void delNode(T key, bool discount = false){
			Node<T>* tmp = root;
			auto del_routine = [&](){
				auto rt = tmp->getParent();
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
					auto t = tmp->getParent();
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

		Node<T>* getParent(){
			return root;
		}
		virtual void createGraphDot(const char* filename, 
				bool display_NIL = false, bool close = true){
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
				"];\n"
				"node[\n"
				"color=black\n"
				"fontcolor=white\n"
				"color=black\n"
				"style = \"solid,filled\",\n"
				"];\n"
			;
			std::function<void (Node<T>*)> print_all;
			print_all = [&](Node<T>* pivot){
				if(pivot->getLeft() != NULL){
					dotFile << +pivot->key << "->" <<
						+pivot->getLeft()->key<<";\n";
					print_all(pivot->getLeft());
				}else if(display_NIL){
					dotFile << +pivot->key << "->\"" <<
						+pivot->key << "NIL\";\n";
				}
				if(pivot->getRight() != NULL){
					dotFile << +pivot->key << "->" <<
						+pivot->getRight()->key<<";\n";
					print_all(pivot->getRight());
				}else if(display_NIL){
					dotFile << +pivot->key << "->\""<<
						+pivot->key << "NIL\";\n";
				}
			};
			dotFile << +root->key <<";\n";
			print_all(this->getParent());
			if(close)
				dotFile << "}\n";
		}
		Node<T>* search(T key){
			Node<T>* pivot = root;
			while(1){
				if(pivot->key > key){
					if(pivot->getLeft()!= NULL)
						pivot = pivot->getLeft();
					else{
						throw "unregistered key";
						return NULL;
					}
				}
				else if(pivot->key < key){
					if(pivot->getRight()!= NULL) 
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
		bool rotateLeft(Node<T>* pivot){
			auto rt = pivot->getParent();
			auto next = pivot->getRight();
			if(next==NULL){
				return false;
			}
			pivot->setRight(next->getLeft());
			pivot->setParent(next);
			next->setLeft(pivot);
			next->setParent(rt);
			if(rt == NULL)
				root = next;
			else if(rt->key < pivot->key){
				rt->setRight(next);
			}else{
				rt->setLeft(next);
			}
			return true;
		}
		bool rotateRight(Node<T>* pivot){
			auto rt = pivot->getParent();
			auto next = pivot->getLeft();
			if(next==NULL){
				return false;
			}
			pivot->setLeft(next->getRight());
			pivot->setParent(next);
			next->setRight(pivot);
			next->setParent(rt);
			if(rt == NULL)
				root = next;
			else if(rt->key < pivot->key){
				rt->setRight(next);
			}else{
				rt->setLeft(next);
			}
			return true;
		}

		bool rotateLeft(T key){
			auto pivot = search(key);
			rotateLeft(pivot);
		}
		bool rotateRight(T key){
			auto pivot = search(key);
			rotateRight(pivot);
		}


	};
}
