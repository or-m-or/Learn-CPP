#include <cassert>
#include <iostream>
using namespace std;

class MyString
{
	//private:
public: // ����� ���� �ӽ÷� public ������
	char* m_data = nullptr;
	int m_length = 0;
public:
	MyString(const char* source = "")
	{
		assert(source);

		// ���ڿ��� ���ڼ� �ľ�
		m_length = std::strlen(source) + 1; // +1 �� ���ڿ� �������� ǥ���ϴ� null ���ڿ��� ���� �߰�
		m_data = new char[m_length];

		// ���� �ϳ��� �߰�
		for (int i = 0; i < m_length; ++i)
			m_data[i] = source[i];

		// null ĳ���� �߰�
		m_data[m_length - 1] = '\0';
	}

	// ���� ������
	// source�� ���� ���� ���� 
	MyString(const MyString& source)
	{
		cout << "Copy Constructor " << endl;
		m_length = source.m_length;

		// �� �޸𸮸� ������ ���� ���..?
		if (source.m_data != nullptr)
		{
			// ���� �޸� ���� �Ҵ� �ް�
			m_data = new char[m_length];

			// source �� ������ �ִ� ���� ����޴´�.
			for (int i = 0; i < m_length; ++i)
				m_data[i] = source.m_data[i];
		}
		else
			m_data = nullptr;
	}

	MyString& operator = (const MyString& source)
	{
		// shallow copy(���� ����)
		// default copy contructor�� �̷��Ǿ� ����.
		// �����Ҵ�� �޸𸮿����� ū ������ ����
		//this->m_data = source.m_data;
		//this->m_length = source.m_length;

		cout << "Assignment operator(���� ������)" << endl;

		// ������ ������ �����Ϸ��ϸ� ���ƾ���. -> �� ���� �ʿ�
		if (this == &source) // prevent self-assignment
			return *this;
		
		// ������ �ִ� �޸� �����
		delete[] m_data;
		m_length = source.m_length; // ���� ����

		// source�� nullptr �ƴϸ� ���� �޸� �Ҵ� �޾Ƽ� ����
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
	
	//MyString str1 = hello; // assignment operator�� ������, copy constructor�� ȣ��� (����)
	//// MyString str1(hello); �̷��� ����ϸ� ��ɻ����� �����ϸ�, �� �򰥸��� �ִ�.
	//MyString str2; // ������ȣ��
	//str2 = hello; // ���Ը��ϰ� ����, assignment operator �� ȣ���

	cout << (int*)hello.m_data << endl; // new�� �Ҵ���� �޸��� �ּ�
	cout << hello.getString() << endl;

	{
		MyString copy = hello;			// �⺻ ���� ������ ȣ��
		//copy = hello; // �̰� ���� ������ ȣ��
		cout << (int*)copy.m_data << endl;
		cout << copy.getString() << endl;
	}

	cout << hello.getString() << endl;

	return 0;
}