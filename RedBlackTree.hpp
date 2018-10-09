
#pragma once
#include "Node.hpp"
#include "BinaryTree.hpp"
namespace teyo {

	template <class T> class RedBlackTree : 
		public BinaryTree<T>
	{
		void insertFixup(const Node<T>& ins){
			while(ins->getRoot()->getColor() == RED){
				ins->getRoot();
			}
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
			if(this->root == NULL)
				ins->setColor(Color::BLACK);
			else
				ins->setColor(Color::RED);
			BinaryTree<T>::insert(ins);
			insertFixup(ins);
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
