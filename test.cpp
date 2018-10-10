#include "RedBlackTree.hpp"
#include <iostream>
#include <random>
#include <unistd.h>
using namespace teyo;
int main(){
	std::random_device rnd;
	RedBlackTree <uint8_t> bt;
	int keys[] = {
		4,2,6,1,3,5,7
	};
	
	Node<uint8_t>* t = (Node<uint8_t>*) NULL;
	for(int i = 0; i < 7; i++){
		std::cout << keys[i] << std::endl;
		 bt.insert(keys[i]); 
	}
	
	std::cout << "end insertion" << std::endl;
	bt.createGraphDot("r.dot");
	std::cout << "end dot output" << std::endl;
}
