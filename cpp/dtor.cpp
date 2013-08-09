#include <iostream>

using namespace std;

class foo_t
{
public:
	foo_t() { cout << "ctor " << (void*)this << endl; };
	~foo_t() { cout << "dtor " << (void*)this << endl; };
private:
	int something;
	int others[3];
};

struct simple_t
{
	simple_t() { cout << "simple!" << endl; };
	int a;
	int b[3];
};

int main()
{
	char* p = new char[100];
	delete p;
	foo_t* pfoo = new foo_t();
	delete pfoo;

	cout << "delete struct" << endl;
	simple_t* psim = new simple_t[3];
	delete psim;
	cout << "delete struct end!" << endl;
	
	pfoo = new foo_t[4];
	delete pfoo;

	cout << "end of test!" << endl;
}


