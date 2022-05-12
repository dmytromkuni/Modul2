#pragma once

namespace task1
{

	struct Tree
	{
		struct Node
		{
			int num = 0;
			Node* l_child = nullptr;
			Node* r_child = nullptr;
			Node(int num);
		};

		Node* head = nullptr;

		void print(Node* iter);
		void self_ch(Node* iter);
	};

}