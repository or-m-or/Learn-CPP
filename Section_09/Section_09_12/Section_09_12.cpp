#include <iostream>
#include <cassert>
#include <initializer_list>

using namespace std;

class IntArray
{
private:
	unsigned m_length = 0;
	int* m_data = nullptr;
public:
	// 길이를 입력받고, 메모리를 잡아주는 생성자
	IntArray(unsigned length)
		: m_length(length)
	{
		m_data = new int[length];
	}

	// initializer을 입력으로 받는 생성자
	IntArray(const std::initializer_list<int>& list)
		:IntArray(list.size())
	{
		int count = 0;
		for (auto& element : list)
		{
			m_data[count] = element;
			++count;
		}

		// 오래된 스타일
		//for (unsigned count = 0; count < list.size(); ++count)
		//	m_data[count] = list[count]; // error 벡터나 array는 제공하지만 initialize list는 제공 X
	}

	~IntArray()
	{
		delete[] this->m_data;
	}

	// 대입연산자도 같이 해주는게 좋음
	//TODO: overload operator = 

	// 출력연산자 operator overloading
	friend ostream& operator << (ostream& out, IntArray& arr)
	{
		for (unsigned i = 0; i < arr.m_length; ++i)
			out << arr.m_data[i] << " ";
		out << endl;
		return out;
	}
};

int main()
{
	int my_arr1[5] = { 1, 2, 3, 4, 5 };
	int* my_arr2 = new int[5] { 1, 2, 3, 4, 5};

	auto il = { 10, 20, 30 }; // initializer list 라고 자료형 자동으로 잡아줌 include 주석하면 에러남

	IntArray int_array = { 1, 2, 3, 4, 5 };
	cout << int_array << endl;

	return 0;
}