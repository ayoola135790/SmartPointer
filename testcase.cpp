#include <iostream>
#include <cassert>
#include <string>
#include "SmartPointer.cpp"
using namespace std;

//test case to ensure code passes
void test1()
{
	{
		int* p{ new int { 42 } };
		smart_ptr<int> sp1{ p };
		assert(sp1.ref_count() == 1);
		{
			smart_ptr<int> sp2{ sp1 };
			assert(sp1.ref_count() == 2);
			assert(sp2.ref_count() == 2);
		}
		assert(sp1.ref_count() == 1);
		smart_ptr<int> sp3;
		assert(sp3.ref_count() == 0);
		sp3 = sp1;
		assert(sp1.ref_count() == 2);
		assert(sp3.ref_count() == 2);
		smart_ptr<int> sp4 = std::move(sp1);
		assert(*sp4 == 42 && *sp3 == 42);
		bool exception = false;
		int t = 10;
		try
		{
			t = *sp1;
		}
		catch (null_ptrexcept e)
		{
			exception = true;
		}
		assert(t == 10);
		assert(exception == true);
	}
	{
		struct Point { int x = 2; int y = -5; };
		smart_ptr<Point> sp{ new Point };
		assert(sp->x == 2 && sp->y == -5);
	}
}
int main()
{
	test1();
	cout << "All tests passed! - Good to go!" << endl;
}
