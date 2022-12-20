#include <iostream>
#include "list.hpp"

List::List() : head(nullptr), size(0) {}
List::List(const List& other) : head(nullptr), size(other.size) {
	if (other.head == nullptr) return;

	head = new Node;
	head->info = other.head->info;
	head->next = nullptr;
	size++;

	Node* t = head;
	Node* t_other = other.head->next;

	while (t_other) {
		t->next = new Node;
		t = t->next;
		t->info = t_other->info;
		t->next = nullptr;
		size++;

		t_other = t_other->next;
	}
}
List::List(List&& other) noexcept {
	head = other.head;
	size = other.size;

	other.head = nullptr;
	other.size = 0;
}
List::~List() {
	clear();
}

void List::clear() {
	Node* head_t = head;

	while (head) {
		head = head->next;
		delete head_t;
		head_t = head;
	}

	size = 0;
}

void List::copy_info(const List& other) {
	Node* t = head;
	Node* t_other = other.head;
	while (t) {
		t->info = other.head->info;
		t = t->next;
		t_other = t_other->next;
	}
}

List& List::operator =(const List& other) {
	if (this == &other) return *this;

	if (size == other.size) {
		copy_info(other);
		return *this;
	}

	clear();

	if (other.head == nullptr) return *this;

	head = new Node;
	head->info = other.head->info;
	head->next = nullptr;
	size++;

	Node* t = head;
	Node* t_other = other.head->next;

	while (t_other) {
		t->next = new Node;
		t = t->next;
		t->info = t_other->info;
		t->next = nullptr;
		size++;

		t_other = t_other->next;
	}

	return *this;
}

List& List::operator =(List&& other) noexcept {
	if (this == &other) return *this;

	head = other.head;
	size = other.size;

	other.head = nullptr;
	other.size = 0;

	return *this;
}

void List::add(int _info) {
	Node* new_node = new Node;
	new_node->info = _info;
	new_node->next = nullptr;

	if (head == nullptr) {
		head = new_node;
		return;
	}

	Node* head_t = head;
	while (head_t->next) {
		head_t = head_t->next;
	}

	head_t->next = new_node;
	size++;
}

void List::remove(int _info) {
	if (head == nullptr) return;

	Node* head_t, * head_prev;
	head_t = head_prev = head;

	while (head_t && head_t->info != _info) {
		head_prev = head_t;
		head_t = head_t->next;
	}

	if (head_t == nullptr) return;

	if (head_t == head) {
		head = head->next;
	}
	else {
		head_prev->next = head_t->next;
	}

	delete head_t;
}

std::ostream& operator <<(std::ostream& stream, const List& list) {
	stream << '(';

	List::Node* head_t = list.head;
	while (head_t) {
		stream << head_t->info;
		if (head_t->next) stream << ' ';

		head_t = head_t->next;
	}
	stream << ')';

	return stream;
}

std::istream& List::input(std::istream& stream) {
	clear();

	try {
		while (stream.peek() == ' ' || stream.peek() == '\n') stream.ignore();

		if (stream.peek() != '(') throw 1;
		stream.ignore();

		int _info;
		stream >> _info;
		if (stream.fail()) throw 1;

		head = new List::Node;
		head->info = _info;
		head->next = nullptr;
		size = 1;

		List::Node* t = head;
		while (true) {
			if (stream.peek() == ')') {
				stream.ignore();
				return stream;
			}

			int _info;
			stream >> _info;
			if (stream.fail()) throw 1;

			t->next = new List::Node;
			t = t->next;
			t->info = _info;
			t->next = nullptr;
			size++;
		}
	}
	catch (...) {
		stream.setstate(std::ios::failbit);
		return stream;
	}

	return stream;
}

std::istream& operator >>(std::istream& stream, List& list) {
	return list.input(stream);
}

// ------------------------------------------------------------------------

bool SortedList::less(int a, int b) {
	return a < b;
}
bool SortedList::bigger(int a, int b) {
	return a > b;
}

void SortedList::set_add_mode(AddMode mode) {
	add_mode = mode;
}

AddMode SortedList::add_mode = Inc;

void SortedList::add(int _info) {
	Node* new_node = new Node;
	new_node->info = _info;
	new_node->next = nullptr;

	if (head == nullptr) {
		head = new_node;
		return;
	}

	Node* head_t = head;
	Node* head_prev = nullptr;

	bool (*cmp_predicate)(int, int);
	switch (add_mode) {
	case Inc: cmp_predicate = less;		break;
	case Dec: cmp_predicate = bigger;	break;
	default: throw 1;
	}

	while (head_t && cmp_predicate(head_t->info, _info)) {
		head_prev = head_t;
		head_t = head_t->next;
	}

	if (head_prev) {
		head_prev->next = new_node;
		new_node->next = head_t;
	}
	else {
		new_node->next = head;
		head = new_node;
	}

	size++;
}

void SortedList::remove(int _info) {
	if (head == nullptr) return;

	Node* head_t, * head_prev;
	head_t = head_prev = head;

	while (head_t && head_t->info != _info) {
		if (head_t->info > _info) return;

		head_prev = head_t;
		head_t = head_t->next;
	}

	if (head_t == nullptr) return;

	if (head_t == head) {
		head = head->next;
	}
	else {
		head_prev->next = head_t->next;
	}

	delete head_t;
}

std::istream& SortedList::input(std::istream& stream) {
	clear();

	try {
		while (stream.peek() == ' ' || stream.peek() == '\n') stream.ignore();

		if (stream.peek() != '(') throw 1;
		stream.ignore();

		while (true) {
			if (stream.peek() == ')') {
				stream.ignore();
				return stream;
			}

			int _info;
			stream >> _info;
			if (stream.fail()) throw 1;

			add(_info);
		}
	}
	catch (...) {
		stream.setstate(std::ios::failbit);
		return stream;
	}

	return stream;
}