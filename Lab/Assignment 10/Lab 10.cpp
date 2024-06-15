#include <iostream>
#include <string>

using namespace std;

template <class T, class U>
T GetMin(T one, U two) {

	return ((one > two) ? two : one);

}

template <class T, class U>
T GetMax(T one, U two)
{
	return ((one > two) ? one : two);
}

template <class T>
class Pair 
{
	T values[2];
	public:

		Pair() : values{} {}

		Pair(T one, T two) : values{ one, two } {}

		T GetMax() {
			return ((values[0] > values[1]) ? values[0] : values[1]);
		}

		T GetMin();

		template <class T> friend ostream& operator<< (ostream& out, const Pair<T>& p);

};

template <class T>
T Pair<T>::GetMin() {
	return ((values[0] > values[1]) ? values[1] : values[0]);
}

template <class T>
ostream& operator<< (ostream& out, const Pair<T>& p) {

	out << "Value1: " << p.values[0] << endl;
	out << "Value2: " << p.values[1];

	return out;

}

template <class T>
class Container {

	T data;

	public:

		Container(T d) : data(d) {}

		T increase();

};

template <class T>
T Container<T>::increase() {
	return (++data);
}

template <>
class Container<char> {

	char data;

	public:

		Container(char d) : data(d) {}

		char uppercase();
	
};

char Container<char>::uppercase() {
	return data - 32;
}

template <class T, int N>
class Sequence {

	T memblock[N];

	public:

		Sequence() {}

		void setmember(int x, T value);

		T getmember(int x);

};

template <class T, int N>
void Sequence<T, N>::setmember(int x, T value) {
	memblock[x] = value;
}

template <class T, int N>
T Sequence<T, N>::getmember(int x) {
	return memblock[x];
}

int main() {

	/*int i = 5, j = 6, k;
	long l = 10, m = 5, n;

	k = GetMax<int>(i, j);
	n = GetMin<long>(l, m);

	cout << k << endl;
	cout << n << endl;*/


	/*char i = 'Z';
	int j = 6, k;
	long l = 10, m = 5, n;

	k = GetMax(i, m);
	n = GetMin(j, l);

	cout << k << endl;
	cout << n << endl;*/


	/*Pair <double> myobject(1.012, 1.01234);
	cout << myobject.GetMax();*/

	/*Container<int> myint(7);
	Container<char> mychar('j');
	cout << myint.increase() << endl;
	cout << mychar.uppercase() << endl;*/

	/*Sequence <int, 5> myints;
	Sequence <double, 5> myfloats;
	myints.setmember(0, 100);
	myfloats.setmember(3, 3.1416);
	cout << myints.getmember(0) << '\n';
	cout << myfloats.getmember(3) << '\n';*/

	Pair <double> y(2.23, 3.45);
	Sequence <Pair<double>, 5> myPairs;
	myPairs.setmember(0, y);
	cout << myPairs.getmember(0) << '\n';

	return 0;

}