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
};

class ThrowMem
{
public:
	ThrowMem() { throw 10; }
};

class NoThrowThrowMem
{
private:
	ThrowMem _mem;
public:
	NoThrowThrowMem() = default;
};

class NonThrow
{
public:
	NonThrow()
	{
		// does not throw 
	}
	
	// virtual destructor
	virtual ~NonThrow() = default;
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
     
	// not fine
	throw 5;
}
