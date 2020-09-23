#pragma once

template <typename T> class Tree;

#include "node.h"

#include <iostream>
#include <stack>
#include <queue>

template <typename T>
class Tree {

	typedef Node<T>* node_ptr;

private:
	node_ptr root;

public:

	Tree() { root = nullptr; }

	node_ptr get_root() const { return root; }

	const node_ptr get_max(const node_ptr root) const {
		node_ptr head = root;

		while (head->right)
			head = head->right;
		return head;
	}

	const node_ptr get_min(const node_ptr root) const {
		node_ptr head = root;

		while (head->left)
			head = head->left;
		return head;

	}

	// return false if element is already in the tree
	bool insert(const T& element) {

		node_ptr node = new Node<T>(element); // node to insert
		node_ptr ptr  = nullptr; // will point on position to insert
		node_ptr ptr1 = nullptr; // will be parent of ptr

		node->parent 
			= node->left 
			= node->right = nullptr;

		ptr = root;


		// find pos to insert (left.value < parent.value < right.value)
		while (ptr) {

			if (ptr->data == element) return false;

			ptr1 = ptr;

			if (element < ptr->data)
				ptr = ptr->left;
			else
				ptr = ptr->right;

		}

		node->parent = ptr1;

		// insert node
		if (!ptr1) // tree was empty ?
			root = node;
		else {
			
			if (element < ptr1->data)
				ptr1->left = node;
			else
				ptr1->right = node;

		}
		return true;
	}

	// return false if any of elements cannot be inserted
	bool insert(const std::vector<T>& elements) {
		bool is_all = true;
		for (const auto& e : elements) {
			if (exist(e))
				insert(e);
			else
				is_all = false;
		}
		return is_all;
	}

	bool exist(const T& element) const {
		node_ptr node = bfs(element);

		if (!node)
			return false;
		else
			return true;
	}

	void erase(const T& element) {

		node_ptr ntd = dfs(element); // node to delete

		if (!ntd) return;

		// if ntd has no childs
		if (!ntd->left and !ntd->right) 
			if (ntd->parent->left == ntd)
				ntd->parent->left = nullptr;
			else
				ntd->parent->right = nullptr;
		

		//if ntd has one child
		else if (!ntd->left or !ntd->right) {
			if (ntd->parent->left == ntd) {
				ntd->parent->left = ntd->left == nullptr ? ntd->right : ntd->left;
				ntd->parent->left->parent = ntd->parent;
			}
			else {
				ntd->parent->right = ntd->left == nullptr ? ntd->right : ntd->left;
				ntd->parent->right->parent = ntd->parent;
			}
		}

		// if ntd has two childs
		else if (ntd->left and ntd->right) {
		
			node_ptr temp = get_max(ntd->left);
			//          = get_min(ntd->right);
			ntd->data = temp->data;

			if (temp->left or temp->right) {
				if (temp->parent->left == temp)
					temp->parent->left = temp->left == nullptr ? temp->right : temp->left;
				else
					temp->parent->right = temp->left == nullptr ? temp->right : temp->left;
			}
			else {
				if (temp->parent->left == temp)
					temp->parent->left = nullptr;
				else
					temp->parent->right = nullptr;
			}
		}

	}
	
	void erase(const std::vector<T>& elements) {
		for (const auto& e : elements)
			if (exist(e)) erase(e);
	}
	
	static void print_prefix(const node_ptr root) {
		
		if (!root) return;

		std::cout << root->data << "  ";

		print_prefix(root->left);
		print_prefix(root->right);
	}

	static void print_postfix(const node_ptr root) {

		if (!root) return;

		print_postfix(root->left);
		print_postfix(root->right);

		std::cout << root->data << "  ";
	}

	static void print_infix(const node_ptr root) {

		if (!root) return;
		
		print_infix(root->left);

		std::cout << root->data << "  ";

		print_infix(root->right);
	}

	const node_ptr dfs(const T& element) const {
		
		std::stack<node_ptr> items;

		items.push(this->root);

		while (!items.empty()) {

			node_ptr node = items.top();
			items.pop();

			//std::cout << node->data << "  ";

			if (node->data == element) return node;

			if (node->left)  items.push(node->left);
			if (node->right) items.push(node->right);

		}
		return nullptr;
	}

	const node_ptr bfs(const T& element) const {
		
		 std::queue<node_ptr> items;

		 items.push(this->root);

		 while (!items.empty()) {

			 node_ptr node = items.back();
			 items.pop();

			// std::cout << node->data << "  ";

			 if (node->data == element) return node;

			 if (node->left)  items.push(node->left);
			 if (node->right) items.push(node->right);
		 }
		 return nullptr;
	}

};

