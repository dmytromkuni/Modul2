#include "task2.h"

int task2::TreeSearch::height(Node* iter)
{
	if (iter == nullptr) return 0;
	int l_height = height(iter->l_child);
	int r_height = height(iter->l_child);
	int result = (l_height > r_height) ? l_height : r_height;
	return result + 1;
}

void task2::TreeSearch::del(Node* iter)
{
	if (iter == nullptr) return;

	del(iter->l_child);
	del(iter->r_child);

	delete iter;
}

void task2::TreeSearch::height_del(Node* iter, int h)
{
	if (iter == nullptr) return;
	if (height(iter) > (h / 2 + 1))
	{
		height_del(iter->l_child, h);
		height_del(iter->r_child, h);
	}
	else if (height(iter) == (h / 2))
		if (height(iter->l_child) == height(iter->r_child)) del(iter);

		else return;

	else return;
}

