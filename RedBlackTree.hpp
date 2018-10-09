
#pragma once
#include "Node.hpp"
#include "BinaryTree.hpp"
namespace teyo {

	template <class T> class RedBlackTree : 
		public BinaryTree<T>
	{
		void insertFixup(const Node<T>& ins){
			while(ins->getRoot()->getColor() == Color::RED){
				if(ins->getRoot()->getRoot()->getLeft() == ins->getRoot()){
					auto y = ins->getRoot()->getRoot()->getRight();
					if(y->getColor() == Color::RED){
						// case 1 
						// uncle and parparent is red 
						// before odd generation will be black (ins is 0)
						// until uncle is not be red
						ins->getRoot()->setColor(BLACK);
						y->setColor(Color::BLACK());
						y->getRoot()->setColor(Color::RED);
						ins = y->getRoot();
					} else if (ins == ins->getRoot()->getRight()){
						//case 2
						// self is right side node and uncle is Black
						ins = ins->getRoot();
						this->rotateLeft(ins);
					}
					ins->getRoot()->setColor(Color::BLACK);
					ins->getRoot()->getRoot()->setColor(Color::RED);
					this->rotateRight(ins->getRoot()->getRoot());
				}else{
					auto y = ins->getRoot()->getRoot()->getLeft();
					if(y->getColor() == Color::RED){
						// case 1 
						// uncle and parparent is red 
						// before odd generation will be black (ins is 0)
						// until uncle is not be red
						ins->getRoot()->setColor(BLACK);
						y->setColor(Color::BLACK());
						y->getRoot()->setColor(Color::RED);
						ins = y->getRoot();
					} else if (ins == ins->getRoot()->getLeft()){
						//case 2
						// self is right side node and uncle is Black
						ins = ins->getRoot();
						this->rotateRight(ins);
					}
					//case3
					//self is left side node.
					ins->getRoot()->setColor(Color::BLACK);
					ins->getRoot()->getRoot()->setColor(Color::RED);
					this->rotateLeft(ins->getRoot()->getRoot());
				}
			}
			this->getRoot()->setColor(Color::BLACK);
		}

		public:
		RedBlackTree(void):
			BinaryTree<T>()
		{
		}
		RedBlackTree(T rootKey):
			BinaryTree<T>()
		{
			this->root = new Node<T>(rootKey);
			this->root->setColor(Color::BLACK);
		}

		~RedBlackTree(){
			this->deleteTree(this->root);
		}
		void insert(T key){
			auto ins = new Node<T>(key);
			if(this->root == NULL){
				ins->setColor(Color::BLACK);
				BinaryTree<T>::insert(ins);
				insertFixup(ins);
			}
			else {
				ins->setColor(Color::RED);
				BinaryTree<T>::insert(ins);
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
					dotFile << node->key << 
					"[\n"
					"color = RED\n"
					"];\n\n";
				}
			};

			std::function<void (Node<T>*)> print_color;
			print_color = [&](Node<T>* node){
				if(node->getLeft() != NULL){
					output(node);
					print_color(node->getLeft());
				}
				if(node->getRight() != NULL){
					output(node);
					print_color(node->getRight());
				}
			};
			print_color(dynamic_cast<Node<T>*>(this->root));
			if(close)
				dotFile << "}\n";
		}
	};
}
