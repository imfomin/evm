class error {
public:
	virtual void print() = 0;
};

class sizeerror : public error {
public:
	void print();
};