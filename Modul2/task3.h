#pragma once

#include <string>

namespace task3
{
	template <class T>
	struct Stack
	{
		struct Node
		{
			T value;
			Node* next = nullptr;
			Node* prev = nullptr;
			Node(T value);
		};
		Node* head = nullptr;
		Node* tail = nullptr;
		void printStack();
		T top();
		void pop();
		bool empty();
		void push(T value);
	};

	struct ExpressionTree
	{
		struct Node
		{
			char val;
			Node* l_child = nullptr;
			Node* r_child = nullptr;
			Node(char val);
		};

		Node* head = nullptr;

		void change_val(Node* iter);

		void print(Node* iter);
		void printGraph(const std::string& prefix, const task3::ExpressionTree::Node* node, bool isLeft);

		void del(Node* iter);
		void add(char val);

		void print_var(Node* iter);

		void build(char* input);

		int simplify(Node* iter);
	};
	int precedence(char input);
	void infix_to_postfix(char* input, char* result);
	bool is_num_var(char input);
}
