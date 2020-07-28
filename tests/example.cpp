#include <string>

class ABC
{
private:
    int _a;
    int b;
    int c;
    float d;

protected:
    int _fine;
    int notfine;

public:
    int thisisfine;

public:
	ABC() {
		// fine
		throw 100;
	}

	int value() const
	{
		throw 5;
		return 0;
	}

	// no virtual destructor, not allowed
	~ABC() = default;
};

class ThrowMem
{
public:
	ThrowMem() { throw 10; }

	// no virtual destructor, not allowed
};

class NoThrowThrowMem
{
private:
	ThrowMem _mem;
public:
	NoThrowThrowMem() = default;

	// no virtual destructor, not allowed
};

class NonThrow
{
public:
	NonThrow()
	{
		// does not throw 
	}

	// virtual destructor, so this is fine
	virtual ~NonThrow() {}
};

class BadInherit : std::string
{
public:
	BadInherit() = default;

	// no virtual destructor
};

class Handler
{
	// this is fine, no virtual destructors
	virtual void onSomething() = 0;
	virtual void onOther() = 0;
};

class HandlerImpl : public Handler
{
	std::string _member;

	virtual void onSomething() override {}
	virtual void onOther() override {}

	~HandlerImpl() {}
};

int main()
{
	try {
		// throwing constructor but it is caught
		ABC b;

		// fine
		throw 6;

	} catch(...) {}	

	// not fine, this is throwing constructor but is not caught
	ABC a;

	// not fine, class itself doesn't throw but member does
	NoThrowThrowMem nothrow;

	// this is fine, doesn't throw
	NonThrow fine;

	BadInherit abc;

	// lambda should be OK
	[&a]() {
		return;
	};
     
	// not fine
	throw 5;
}
