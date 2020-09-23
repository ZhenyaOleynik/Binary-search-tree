#pragma once

template <typename T>
class Node {

	friend class Tree<T>;
	
private:
		
	T     data;
	Node* left;
	Node* right;
	Node* parent;

public:

	Node(const T& data) {
		this->data = data;
		left = right 
			 = parent 
			 = nullptr;
	}
	
	T get_data() const { return data; }

	~Node() {

		if (left)  left->~Node();
		if (right) right->~Node();

		delete this;
	}

};