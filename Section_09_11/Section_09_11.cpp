#include <cassert>
#include <iostream>
using namespace std;

class MyString
{
	//private:
public: // 출력을 위해 임시로 public 설정함
	char* m_data = nullptr;
	int m_length = 0;
public:
	MyString(const char* source = "")
	{
		assert(source);

		// 문자열의 글자수 파악
		m_length = std::strlen(source) + 1; // +1 은 문자열 마지막을 표시하는 null 문자열을 위해 추가
		m_data = new char[m_length];

		// 글자 하나씩 추가
		for (int i = 0; i < m_length; ++i)
			m_data[i] = source[i];

		// null 캐릭터 추가
		m_data[m_length - 1] = '\0';
	}

	// 복사 생성자
	// source로 들어온 것을 복사 
	MyString(const MyString& source)
	{
		cout << "Copy Constructor " << endl;
		m_length = source.m_length;

		// 즉 메모리를 가지고 있을 경우..?
		if (source.m_data != nullptr)
		{
			// 나도 메모리 새로 할당 받고
			m_data = new char[m_length];

			// source 가 가지고 있는 값을 복사받는다.
			for (int i = 0; i < m_length; ++i)
				m_data[i] = source.m_data[i];
		}
		else
			m_data = nullptr;
	}

	MyString& operator = (const MyString& source)
	{
		// shallow copy(얕은 복사)
		// default copy contructor은 이래되어 있음.
		// 동적할당된 메모리에서는 큰 문제가 생김
		//this->m_data = source.m_data;
		//this->m_length = source.m_length;

		cout << "Assignment operator(대입 연산자)" << endl;

		// 본인이 본인을 대입하려하면 막아야함. -> 이 로직 필요
		if (this == &source) // prevent self-assignment
			return *this;
		
		// 가지고 있는 메모리 지우기
		delete[] m_data;
		m_length = source.m_length; // 길이 변경

		// source가 nullptr 아니면 새로 메모리 할당 받아서 복사
		if (source.m_data != nullptr)
		{
			m_data = new char[m_length];

			for (int i = 0; i < m_length; ++i)
				m_data[i] = source.m_data[i];
		}
		else
			m_data = nullptr;

		return *this;
	}

	~MyString()
	{
		delete[] m_data;
	}

	char* getString() { return m_data; }
	int getLength() { return m_length; }
};


int main()
{
	MyString hello("Hello");
	
	//MyString str1 = hello; // assignment operator가 있지만, copy constructor이 호출됨 (주의)
	//// MyString str1(hello); 이렇게 사용하면 기능상으로 동일하며, 덜 헷갈릴수 있다.
	//MyString str2; // 생성자호출
	//str2 = hello; // 대입만하고 있음, assignment operator 이 호출됨

	cout << (int*)hello.m_data << endl; // new로 할당받은 메모리의 주소
	cout << hello.getString() << endl;

	{
		MyString copy = hello;			// 기본 복사 생성자 호출
		//copy = hello; // 이건 대입 연산자 호출
		cout << (int*)copy.m_data << endl;
		cout << copy.getString() << endl;
	}

	cout << hello.getString() << endl;

	return 0;
}