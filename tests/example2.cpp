#include <string>

class BadInherit : std::string
{
public:
	BadInherit() {}
};

struct NonVirtual
{
public:
	NonVirtual() {}
};

int main()
{
	int a;
	[&a] () {
		// empty lambda
	};
}
