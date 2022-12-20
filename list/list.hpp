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

enum AddMode { Inc, Dec };

class SortedList : public List {
private:
	static AddMode add_mode;

	std::istream& input(std::istream& stream) override;

	static bool less(int a, int b);
	static bool bigger(int a, int b);
public:
	static void set_add_mode(AddMode mode);

	void add(int _info) override;
	void remove(int _info) override;
};

#endif // LIST_HPP