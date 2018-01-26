#pragma once
#define DEBUG

template <class Item>
class List
{
	struct Node {
		Node* next;
		Item value;

		Node(const Item& item);
	};

	Node* head = nullptr;
	Node* tail = nullptr;

	int _size = 0;

public:
	List() = default;
	~List();

	using size_t = unsigned int;

	int size();

	void add(const Item& item);
	void add(const Item& item, int index);
	void add(const Item* item, int index, int count);

	void remove();
	void remove(const Item& item);
	void remove(size_t index);
	void remove(int begin, int end);

	List<Item>* split(int index);

	Item* toArray();

	void clear();

#ifdef DEBUG
	void toString();
#endif

	Item* operator[](int index);

private:

	bool isIndexOfElement(int index);

	Node* getNodeByIndex(int index);
	Node* removeNode(Node* _node);
};

template<class Item>
inline List<Item>::Node::Node(const Item & item)
	: next (nullptr), value(item)
{}

template<class Item>
inline Item * List<Item>::operator[](int index)
{
	Node* _node = getNodeByIndex(index);
	return _node->item;
}

template<class Item>
inline bool List<Item>::isIndexOfElement(int index)
{
	return index >= 0 && index < _size;
}

template<class Item>
inline typename List<Item>::Node * List<Item>::getNodeByIndex(int index)
{
	if (!isIndexOfElement(index)) return nullptr;

	Node* _node = head;
	for (int i = 0; i < _size; ++i) {
		if (i == index) {
			return _node;
		}

		_node = _node->next;
	}
}

template<class Item>
inline typename List<Item>::Node * List<Item>::removeNode(Node * _node)
{
	Node* _temp = _node->next;
	delete _node;
	--_size;
	return _temp;
}


template<class Item>
List<Item>::~List()
{
	this->clear();
}

template<class Item>
int List<Item>::size()
{
	return _size;
}

template<class Item>
void List<Item>::add(const Item& item)
{
	++_size;

	if (head == nullptr) {
		head = tail = new Node(item);
		return;
	}

	Node* _node = new Node(item);

	tail->next = _node;
	tail = _node;
}

template<class Item>
void List<Item>::add(const Item& item, int index)
{
	if (index > _size || index < 0) throw "Out of range!";

	Node* _node = new Node(item);

	if (isIndexOfElement(index)) {
		_node->next = getNodeByIndex(index);
	}

	else {
		tail = _node;
	}

	if (isIndexOfElement(index - 1)) {
		Node* _prev = getNodeByIndex(index - 1);

		_prev->next = _node;
	}

	else {
		head = _node;
	}

	++_size;
}

template<class Item>
void List<Item>::add(const Item* item, int index, int count)
{
	if (index > _size || index < 0) throw "Out of range!";

	Node* begin = new Node(item[0]);
	Node* end = begin;

	for (int i = 1; i < count; ++i) {
		end->next = new Node(item[i]);
		end = end->next;
	}

	if (isIndexOfElement(index)) {
		end->next = getNodeByIndex(index);
	}

	else {
		tail = end;
	}

	if (isIndexOfElement(index - 1)) {
		Node* prev = getNodeByIndex(index - 1);

		prev->next = begin;
	}

	else {
		head = begin;
	}

	_size += count;
}

template<class Item>
void List<Item>::remove()
{
	if (head == nullptr) return;

	Node* _node = head;
	head = head->next;
	delete _node;
	--_size;
}

template<class Item>
void List<Item>::remove(const Item& item)
{
	Node* _node = head;
	Node* _prev = nullptr;

	while (_node != nullptr) {
		if (_node->value == item) {
			if (_prev != nullptr) {
				_prev->next = _node->next;

				delete _node;
				--_size;

				_node = _prev->next;
			}

			else {
				remove();
				_node = head;
			}
		}

		else {
			_prev = _node;
			_node = _node->next;
		}
	}
}

template<class Item>
void List<Item>::remove(size_t index)
{
	if (!isIndexOfElement(index)) throw "Out of bounds!";

	if (index == 0) {
		remove();
		return;
	}

	Node* _prev = getNodeByIndex(index - 1);
	Node* _node = _prev->next;

	_prev->next = _node->next;

	delete _node;
	--_size;
}

template<class Item>
void List<Item>::remove(int begin, int end)
{
	if (!isIndexOfElement(begin)) throw "Out of bounds!";
	if (!isIndexOfElement(end)) throw "Out of bounds!";

	Node* _node = getNodeByIndex(begin);
	for (int i = begin; i <= end; ++i) {
		_node = removeNode(_node);
	}

	if (_node == nullptr) {
		tail = _node;
	}

	if (isIndexOfElement(begin - 1)) {
		getNodeByIndex(begin - 1)->next = _node;
	}

	else {
		head = _node;
	}
}

template<class Item>
List<Item>* List<Item>::split(int index)
{
	if (!isIndexOfElement(index)) throw "Out of bounds!";

	if (isIndexOfElement(index - 1)) {
		Node* breach = getNodeByIndex(index - 1);
		List<Item>* output = new List<Item>();

		output->tail = this->tail;
		output->head = breach->next;
		output->_size = this->_size - index;

		this->tail = breach;
		this->tail->next = nullptr;
		this->_size = index;

		return output;
	}

	else {
		return this;
	}
}

template<class Item>
Item * List<Item>::toArray()
{
	if (_size == 0) return nullptr;

	Item* _array = new Item[_size];
	Node* _node = head;

	for (int i = 0; i < _size; ++i) {
		_array[i] = _node->value;
		_node = _node->next;
	}

	return _array;
}

template<class Item>
void List<Item>::clear()
{
	Node* _node = head;
	while (_node != nullptr) {
		_node = removeNode(_node);
	}

	head = nullptr;
	tail = nullptr;
}

template<class Item>
void List<Item>::toString()
{
	Node* _node = head;
	while (_node != nullptr) {
		std::cout << _node->value << " ";
		_node = _node->next;
	}

	std::cout << "Size: " << _size;
	std::cout << std::endl;
}
