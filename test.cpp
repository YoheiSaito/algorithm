#include "BinaryTree.hpp"
#include <iostream>
#include <random>
using namespace teyo;
int main(){
	std::random_device rnd;
	BinaryTree<uint8_t> bt;
	int keys[] = {
		4,2,6,1,3,5,7
	};
	for(int i = 0; i < 7; i++){
		bt.insert(keys[i]);
	}
	try{
		bt.createGraphDot("rot_original.dot", true);
		bt.rotateLeft(4);
		bt.createGraphDot("rot_left.dot", true);
		bt.rotateRight(4);
		bt.createGraphDot("rot_right.dot", true);
	}catch (const char * errormsg){
		std::cerr << errormsg << std::endl;
	}
}
