#ifndef _NODE
#define _NODE
#include <vector>

template <class T>
struct Node {
	T value;
	std::vector<Node<T>> childrens;


};

#endif // !_NODE
