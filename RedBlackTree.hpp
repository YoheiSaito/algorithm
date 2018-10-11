
#pragma once
#include "Node.hpp"
#include "BinaryTree.hpp"
#include <iostream>
namespace teyo {

	template <class T> class RedBlackTree : 
		public BinaryTree<T>
	{
		public:
		void insertFixup(Node<T>* ins){
			while(ins->getParent()->getColor() == Color::RED){
				if(ins->getParent()->getParent()->getLeft() == ins->getParent()){
					auto y = ins->getParent()->getParent()->getRight();
					if(y->getColor() == Color::RED){
						//case 1 ancle is red
						ins->getParent()->setColor(Color::BLACK);
						y->setColor(Color::BLACK);
						ins = ins->getParent()->getParent();
						ins -> setColor(Color::RED);
					} else{
						//case 2,3 ancle is black
						if(ins ->getParent() -> getRight() == ins){
							//case2 z is right child
							ins = ins->getParent();
							this->rotateLeft(ins);
						}
							//case 3 z is left child
							ins->getParent()->setColor(Color::BLACK);
							ins->getParent()->getParent()->setColor(Color::RED);
							this->rotateRight(ins->getParent()->getParent());
					}
				}else{
					auto y = ins->getParent()->getParent()->getLeft();
					if(y->getColor() == Color::RED){
						//case 1 ancle is red
						ins->getParent()->setColor(Color::BLACK);
						y->setColor(Color::BLACK);
						ins = ins->getParent()->getParent();
						ins -> setColor(Color::RED);
					} else{
						//case 2,3 ancle is black
						if(ins ->getParent() -> getLeft() == ins){
							ins = ins->getParent();
							this->rotateLeft(ins);
						}
							//case 3 z is left child
							ins->getParent()->setColor(Color::BLACK);
							ins->getParent()->getParent()->setColor(Color::RED);
							this->rotateRight(ins->getParent()->getParent());

					}
				}
			}
			this->root->setColor(Color::BLACK);
		}

		RedBlackTree(void):
			BinaryTree<T>()
		{
		}
		RedBlackTree(T rootKey):
			BinaryTree<T>()
		{
			this->root = new Node<T>(rootKey);
		}

		~RedBlackTree(){
			this->deleteTree(this->root);
		}

		void insert(T key){
			Node<T>* ins = new Node<T>(key);
			BinaryTree<T>::insert(ins);
			if(ins->getParent() == NULL)
				ins->setColor(Color::BLACK);
			else{
				insertFixup(ins);
			}
		}

		void delNode(T key, bool discount = false){
		}
		void createGraphDot(const char* filename, 
				bool display_NIL = false, bool close = true)
		{
			BinaryTree<T>::createGraphDot(filename, display_NIL, false);
			std::ofstream dotFile(filename, std::ios::app);
			if(!dotFile)
				return;
			auto output = [&](Node<T>* node){
				if(node->getColor() == Color::RED){
					dotFile << +node->key << 
					"[\n"
					"color = RED\n"
					"fontcolor = BLACK\n"
					"];\n\n";
				}
			};

			std::function<void (Node<T>*)> print_color;
			print_color = [&](Node<T>* node){
				output(node);
				if(node->getLeft() != NULL){
					print_color(node->getLeft());
				}
				if(node->getRight() != NULL){
					print_color(node->getRight());
				}
			};
			print_color(dynamic_cast<Node<T>*>(this->root));
			if(close)
				dotFile << "}\n";
		}
	};
}
