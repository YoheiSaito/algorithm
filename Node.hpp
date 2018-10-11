#pragma once
#include <cstddef>
namespace teyo{
	enum Color {
		BLACK = 0,
		RED
	};
	template <class T> class Node{
		protected:
		Color color;
		Node<T> *parent;
		Node<T> *left, *right;
		unsigned int count;
		public:
		const T key;
		Node(T key_, Color color_ = Color::RED):
			key(key_)
		{
			color = color_;
			parent = NULL;
			left = NULL;
			right = NULL;
			count = 1;
		}
		Node(T key_, Node<T> *parent, Color color_ = Color::RED):
			key(key_)
		{
			color = color_;
			this->parent = parent;
			this->left = NULL;
			this->right = NULL;
			count = 1;
		}
		Node(T key_, Node<T> *left, Node<T> *right, Color color_ = Color::RED):
			key(key_)
		{
			color = color_;
			this->parent = NULL;
			this->left = left;
			this->right = right;
			count = 1;
		}

		Node(T key_, Node<T> *parent, Node<T> *left, Node<T> *right, Color color_ = Color::RED):
			key(key_)
		{
			color = color_;
			this->parent = parent;
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
		void setParent(Node<T> *parent){
			this->parent = parent;
		}

		virtual Node<T>* getLeft(void){
			return (this == NULL)?(NULL):(left);
		}
		virtual Node<T>* getRight(void){
			return (this == NULL)?(NULL):(right);
		}
		virtual Node<T>* getParent(void){
			return (this == NULL)?(NULL):(parent);
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
		Color getColor(){
			return (this == NULL)?(Color::BLACK):(color);
		}
		void setColor(Color c){
			color = c;
		}

	};


}
