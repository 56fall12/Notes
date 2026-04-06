#include <iostream>
using namespace std;

struct IntPair
{
	int m_First {};
	int m_Second {};
	void print(){
		cout << m_First << " " << m_Second << endl;
	}
	bool isEqual(IntPair a)
	{
		return (m_First == a.m_First) && (m_Second == a.m_Second);
	}
};

int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();

	std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
	std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

	return 0;
}
