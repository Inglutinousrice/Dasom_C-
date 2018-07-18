
#include <iostream>

using namespace std;

// enum문
enum MENU
{
	EXIT,
	M_ADD,
	M_SUB,
	M_MUL
};

// 행렬 클래스
class CMatrix
{
// 멤버변수들
private:
	int m_col;
	int m_row;
	int* pMatrixArr;

public:
	// 생성자
	CMatrix(int row, int col) 
	{
		//cout << "CMatrix 생성자" << m_row << endl;
		m_row = row;
		m_col = col;
		pMatrixArr = new int[row * col];
	}

	// 동적할당 제거함수,,,,,,(제거되는지는 잘 모름)
	void DeleteDyList()
	{
		delete[] pMatrixArr;
		pMatrixArr = nullptr;
	}

	// 행렬 출력
	void PrintMatrix()
	{
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				cout << pMatrixArr[i*m_col + j] << "\t";
			}
			cout << endl;
		}
	}

	// 행렬 값 넣기
	void SetMatrix()
	{
		cout << "행렬을 입력해주세요!! 행렬 모양 그대로 입력해라;;" << endl;
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				cin >> pMatrixArr[i*m_col + j];
			}
		}
		cout << "행렬 입력 완료" << endl;
	}

	// 곱하기용 행렬 0으로 초기화
	void SetMatrixByZero()
	{
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				pMatrixArr[i*m_col + j] = 0;
			}
		}
	}

	// 행 크기 리턴
	int GetRow() { return m_row; }

	// 열 크기 리턴
	int GetCol() { return m_col; }

	// 행렬 더하기
	void AddMatrix(CMatrix otherMatrix)
	{
		CMatrix resultMatrix(m_row, m_col);
		//resultMatrix.SetDynamicMatrixArr(resultMatrix);

		if (m_row == otherMatrix.m_row && m_col == otherMatrix.m_col)
		{
			for (int i = 0; i < m_row*m_col; ++i)
			{
				resultMatrix.pMatrixArr[i] = pMatrixArr[i] + otherMatrix.pMatrixArr[i];
			}
			resultMatrix.PrintMatrix();
			resultMatrix.DeleteDyList();
			return;
		}
		else
		{
			cout << endl << "두 행렬은 더하기가 불가능합니다!" << endl;
			return;
		}
	}

	// 행렬 빼기
	void SubMatrix(CMatrix otherMatrix)
	{
		CMatrix resultMatrix(m_row, m_col);
		//resultMatrix.SetDynamicMatrixArr(resultMatrix);

		if (m_row == otherMatrix.m_row && m_col == otherMatrix.m_col)
		{
			for (int i = 0; i < m_row*m_col; ++i)
			{
				resultMatrix.pMatrixArr[i] = pMatrixArr[i] - otherMatrix.pMatrixArr[i];
			}
			resultMatrix.PrintMatrix();
			resultMatrix.DeleteDyList();
			return;
		}
		else
		{
			cout << endl << "두 행렬은 빼기가 불가능합니다!" << endl;
			return;
		}
	}

	//행렬 곱하기
	void MulMatrix(CMatrix otherMatrix)
	{
		CMatrix resultMatrix(m_row, otherMatrix.m_col);
		//resultMatrix.SetDynamicMatrixArr(resultMatrix);
		int cnt = 0;
		int arrCnt = 0;
		resultMatrix.SetMatrixByZero();
		if (m_col == otherMatrix.m_row)
		{
			do
			{
				for (int i = 0; i < otherMatrix.m_col; ++i)
				{
					for (int j = 0; j < m_col; ++j)
					{
						resultMatrix.pMatrixArr[arrCnt] += 0 + pMatrixArr[cnt * m_col + j] * otherMatrix.pMatrixArr[j * otherMatrix.m_col + i];
					}
					++arrCnt;
				}
				++cnt;
			} while (cnt < m_row);
			resultMatrix.PrintMatrix();
			resultMatrix.DeleteDyList();
			return;
		}
		else
		{
			cout << endl << "두 행렬은 곱하기가 불가능합니다!" << endl;
			return;
		}
	}
};


// 메인메뉴 함수 정의
void MainMenu();



// 메인 함수
int main()
{
	int col;
	int row;
	cout << "행렬의 크기를 입력해 주세요(행, 열 순서) : ";
	cin >> row;
	cin >> col;

	CMatrix matrix1(row, col);
	//matrix1.SetDynamicMatrixArr(matrix1);
	matrix1.SetMatrix();

	cout << "행렬의 크기를 입력해 주세요(행, 열 순서) : ";
	cin >> row;
	cin >> col;
	CMatrix matrix2(row, col);
	matrix2.SetMatrix();
	int menu;
	
	while (1)
	{
		system("cls");
		cout << "1번 행렬" << endl;
		matrix1.PrintMatrix();
		cout << endl;
		cout << "2번 행렬" << endl;
		matrix2.PrintMatrix();
		cout << endl;
		MainMenu();
		cin >> menu;


		if (menu == EXIT)
		{
			matrix1.DeleteDyList();
			matrix2.DeleteDyList();
			break;
		}


		switch (menu)
		{
		case M_ADD:
			cout << "행렬을 더한 결과는?!" << endl;
			matrix1.AddMatrix(matrix2);
			system("pause");
			break;
		case M_SUB:
			cout << "행렬을 빼준 결과는?!" << endl;
			matrix1.SubMatrix(matrix2);
			system("pause");
			break;
		case M_MUL:
			cout << "행렬을 곱해준 결과는?!" << endl;
			matrix1.MulMatrix(matrix2);
			system("pause");
			break;
		default:
			cout << "잘못 입력하셨습니다." << endl;
			system("pause");
			break;
		}
	}
	return 0;
}


// 메인메뉴 함수
void MainMenu() {
	cout << "=====================================================" << endl;
	cout << "1. 덧셈" << endl;
	cout << "2. 뺄셈" << endl;
	cout << "3. 곱셈" << endl;
	cout << "0. 종료" << endl;
	cout << "=====================================================" << endl;
	cout << "입력 :: ";
}