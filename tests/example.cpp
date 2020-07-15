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
};

int main()
{
	try{
		// fine
		throw 6;
	} catch(...) {}	
     
	// not fine
	throw 5;
}
