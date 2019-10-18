#include <random>
#include <iostream>

using namespace std;

uint64_t generateBoundary()
{
	random_device rd;
	mt19937 mt(rd());

	return mt();
}

int main(void)
{
	cout << generateBoundary() << endl;
}
