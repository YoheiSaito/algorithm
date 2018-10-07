#include "tree.hpp"
#include <iostream>
using namespace teyo;
int main(void){
	BinaryTree<int> bt(41);
	bt.insert(38);
	bt.insert(31);
	bt.insert(12);
	bt.insert(19);
	bt.insert(8);
	bt.createGraphDot("test.dot");
}
