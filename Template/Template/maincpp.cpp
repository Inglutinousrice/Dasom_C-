
#include <iostream>
#include <string>

using namespace std;

template <typename T>
class CArray
{
private:
	T* dataArr;
	int m_size = 0;

public:
	void SetArr(T data)
	{
		dataArr[m_size-1] = data;
	}

	int GetSize()
	{
		return m_size;
	}

	T* GetArr()
	{
		return dataArr;
	}

	CArray(int size)
	{
		cout << "������ ����" << endl;
		dataArr = new T[size];
	}

	~CArray()
	{
		cout << "�Ҹ��� ����" << endl;
		delete[] dataArr;
		cout << "�Ҹ��� ��!" << endl;
	}
	
	void PlusSize() { ++m_size; }

	void MinsSize() { --m_size; }
};


int main()
{
	int arrSize;
	cout << "�迭�� ũ�⸦ �Է��� �ּ���";		cin >> arrSize;
	
	CArray<int> arr1(arrSize);

	int menu;
	int g;
	while (1)
	{
		system("cls");
		cout << "================================================================" << endl;
		cout << "1. �� �Է��ϱ�" << endl;
		cout << "2. �� ����ϱ�" << endl;
		cout << "3. ����" << endl;
		cout << "================================================================" << endl;
		cout << "=> ";		cin >> menu;


		if (menu == 1)
		{
			if (arrSize <= arr1.GetSize() - 1)
			{
				cout << "�ϰ� ũ�� ���س��� �ϰ� ������� �ϰ� �߸��̴�" << endl;
				system("pause");
				break;
			}

			cout << "================================================================" << endl;
			cout << "���� �Է��� �ּ���!!!" << endl;
			cout << "================================================================" << endl;
			cout << "=> ";		cin >> g;
			cout << "�ԷµǾ����ϴ�!!!" << endl;
			arr1.PlusSize();
			arr1.SetArr(g);
			system("pause");
		}

		else if (menu == 2)
		{
			int* tempArr = arr1.GetArr();
			for (int i = 0; i < arr1.GetSize(); ++i)
			{
				cout << tempArr[i] << endl;;
			}
			cout << "��µǾ����ϴ�!!!" << endl;
			system("pause");
		}
		else
			break;
	}

	return 0;
}