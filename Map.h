#pragma once

template <class Item>
class Map
{
	struct Node {
		Item item;

		Node * left;
		Node * right;
		Node * parent;

		Node(Item item);
	};

	static Node * NODE_END = new Node();

	Node * root;

public:
	Map();
	~Map();

	using size_t = unsigned int;

	void add(const Item& item);
	void add(Map<Item>& map);
	
	void remove(const Item& item);

	void clear();

	Map<Item> * split(const Item& item);

	struct Iterator {
		const Item & operator&();

		Iterator& operator++();
		Iterator& operator--();

		Iterator operator++(int);
		Iterator operator--(int);

	private:

		Node * find(const Item& item);
		bool find(const Item& item, Node *& output);

		Node * _node;
	};
};

template<class Item>
inline const Item & Map<Item>::Iterator::operator&()
{
	return this->_node->item;
}

template<class Item>
inline Iterator & Map<Item>::Iterator::operator++()
{
	if (_node->right != nullptr) {
		this->_node = _node->right;
		return &this;
	}

	Node * _parent = _node->parent;
	while (true) {
		_parent = parent->parent;

		if (_parent->item > _node->item) {
			this->_node = _parent;
			return &this;
		}

		if (_parent->parent == _parent) {
			return cend();
		}
	}
}

template<class Item>
inline Iterator & Map<Item>::Iterator::operator--()
{
	if (_node->left != nullptr) {
		this->_node = _node->left;
		return &this;
	}

	Node * _parent = _node->parent;
	while (true) {
		_parent = parent->parent;

		if (_parent->item < _node->item) {
			this->_node = _parent;
			return &this;
		}

		if (_parent->parent == _parent) {
			return cend();
		}
	}
}

template<class Item>
inline Iterator Map<Item>::Iterator::operator++(int)
{
	Iterator output(&this);
	return ++output;
}

template<class Item>
inline Iterator Map<Item>::Iterator::operator--(int)
{
	Iterator output(&this);
	return --output;
}

template<class Item>
inline Node * Map<Item>::Iterator::find(const Item & item)
{
	Node * _node = root;
	while (_node != nullptr) {
		if (_node > item == item) {
			return _node;
		}

		if (item < _node->item) {
			_node = _node->left;
		}

		if (item > _node->item) {
			_node = _node->right;
		}
	}

	return nullptr;
}

template<class Item>
inline bool Map<Item>::Iterator::find(const Item & item, Node *& output)
{
	Node * _node = root;
	Node * _parent;

	while (_node != nullptr) {
		if (_node > item == item) {
			output = _node;
			return true;
		}

		_parent = _node;

		if (item < _node->item) {
			_node = _node->left;
		}

		if (item > _node->item) {
			_node = _node->right;
		}
	}

	output = _parent;
	return false;
}
