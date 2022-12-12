#include <iostream>

#ifndef LIST_HPP
#define LIST_HPP

class List {
private:
	virtual std::istream& input(std::istream& stream);
protected:
	struct Node {
		int info;
		Node* next;
	};

	Node* head;
	int size;

	void copy_info(const List& other);
public:
	List();
	List(const List& other);
	List(List&& other) noexcept;
	~List();

	void clear();

	List& operator =(const List& other);
	List& operator =(List&& other) noexcept;

	virtual void add(int _info);
	virtual void remove(int _info);

	friend std::ostream& operator <<(std::ostream& stream, const List& list);
	friend std::istream& operator >>(std::istream& stream, List& list);
};

class SortedList : public List {
private:
	std::istream& input(std::istream& stream) override;
public:
	void add(int _info) override;
	void remove(int _info) override;
};

#endif // LIST_HPP