#include "tree.hpp"
#include <iostream>
using namespace teyo;
int main(void){
	BinaryTree<int> bt;
	int keys[] = {
		8,3,10,14,1,6,7,4,13
	};
	for(int i = 0; i < 9; i++){
		bt.insert(keys[i]);
	}
	bt.createGraphDot("test.dot");
}
