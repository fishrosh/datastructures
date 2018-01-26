#include "stdafx.h"
#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

template<class Item>
void Map<Item>::add(const Item & item)
{
	if (root == nullptr) {
		root = new Node();

		root->parent = root;
		root->item = item;

		return;
	}

	Node * _node = root;
	Node * _parent;

	while (_node != nullptr) {
		if (item = _node->item) {
			return;
		}

		_parent = _node;

		if (item < _node->item) {
			_node = _node->left;
		}

		if (item > _node->item) {
			_node = _node->right;
		}
	}

	if (item < _parent->item) {
		_parent->left = new Node(item);
	}

	if (item > _parent->item) {
		_parent->right = new Node(item);
	}
}

template<class Item>
void Map<Item>::add(Map<Item>& map)
{
}

template<class Item>
void Map<Item>::remove(const Item & item)
{
	Node * _node = find(item);
	if (_node != nullptr) {

	}
}
