#include <string>
#include <stdexcept>

class ThrowingNoexcept
{
public:
	ThrowingNoexcept() noexcept 
	{
		throw std::runtime_error("this is not allowed");
	}
};

class TechnicallyThrowingNoexcept
{
private:
	std::string _value;
public:
	TechnicallyThrowingNoexcept() noexcept : _value("abcdefgh")
	{
	}
};

class IndirectThrowingNoexcept : private ThrowingNoexcept
{
public:
	IndirectThrowingNoexcept() noexcept {}
};

class SomeClass
{
private:
	// event though this can technically throw, we want to mark it as noexcept
	std::string _result;

public:
	// not OK, this should be noexcept
	SomeClass() 
	{

	}

	// this as well
	SomeClass(const SomeClass &other) = default;

	// and this should also be noexcept
	SomeClass(SomeClass &&other) = default;
};

int main()
{
	IndirectThrowingNoexcept a;
	static_assert(std::is_nothrow_move_constructible_v<SomeClass>, "not nothrow move construction");
}
