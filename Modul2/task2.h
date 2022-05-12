#pragma once

namespace task2
{

	struct TreeSearch
	{
		struct Node
		{
			int num = 0;
			Node* l_child = nullptr;
			Node* r_child = nullptr;
			Node(int num);
		};

		Node* head = nullptr;

		int height(Node* iter);
		void del(Node* iter);
		void height_del(Node* iter, int h);
	};

}
