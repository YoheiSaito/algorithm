#include "BinaryTree.hpp"
#include <iostream>
#include <random>
using namespace teyo;
int main(){
	std::random_device rnd;
	BinaryTree<uint8_t> bt;
	int keys[] = {
		8,3,10,14,1,6,7,4,13
	};
	for(int i = 0; i < 8; i++){
		bt.insert((uint8_t)rnd()%20);
	}
	bt.createGraphDot("test.dot", true);
}
