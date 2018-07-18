
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
		cout << "생성자 등장" << endl;
		dataArr = new T[size];
	}

	~CArray()
	{
		cout << "소멸자 등장" << endl;
		delete[] dataArr;
		cout << "소멸자 끝!" << endl;
	}
	
	void PlusSize() { ++m_size; }

	void MinsSize() { --m_size; }
};


int main()
{
	int arrSize;
	cout << "배열의 크기를 입력해 주세요";		cin >> arrSize;
	
	CArray<int> arr1(arrSize);

	int menu;
	int g;
	while (1)
	{
		system("cls");
		cout << "================================================================" << endl;
		cout << "1. 값 입력하기" << endl;
		cout << "2. 값 출력하기" << endl;
		cout << "3. 종료" << endl;
		cout << "================================================================" << endl;
		cout << "=> ";		cin >> menu;


		if (menu == 1)
		{
			if (arrSize <= arr1.GetSize() - 1)
			{
				cout << "니가 크기 정해놓고서 니가 까먹으면 니가 잘못이다" << endl;
				system("pause");
				break;
			}

			cout << "================================================================" << endl;
			cout << "값을 입력해 주세요!!!" << endl;
			cout << "================================================================" << endl;
			cout << "=> ";		cin >> g;
			cout << "입력되었습니다!!!" << endl;
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
			cout << "출력되었습니다!!!" << endl;
			system("pause");
		}
		else
			break;
	}

	return 0;
}