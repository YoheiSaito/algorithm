#include "tree.hpp"
#include <iostream>
using namespace teyo;
int main(void){
	Node<int> i(10);
	Node<int> j(20, &i);

	std::cout << i.key << std::endl;
	std::cout << j.key << std::endl;
	std::cout << j.getRoot()->key << std::endl;
}
