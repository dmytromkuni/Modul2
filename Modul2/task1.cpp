#include "task1.h"
#include <iostream>

task1::Tree::Node::Node(int num)
{
	this->num = num;
}


void task1::Tree::print(Node* iter)
{
	if (iter == nullptr) return;
	else
	{
		std::cout << iter->num << " ";
		print(iter->l_child);
		print(iter->r_child);
	}
}

void task1::Tree::self_ch(Node* iter)
{
	if (iter == nullptr) return;
	
	self_ch(iter->l_child);
	self_ch(iter->r_child);

	Node* temp = iter->l_child;
	iter->l_child = iter->r_child;
	iter->r_child = temp;
}



