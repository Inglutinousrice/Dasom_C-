
#include <iostream>

using namespace std;

// enum��
enum MENU
{
	EXIT,
	M_ADD,
	M_SUB,
	M_MUL
};

// ��� Ŭ����
class CMatrix
{
// ���������
private:
	int m_col;
	int m_row;
	int* pMatrixArr;

public:
	// ������
	CMatrix(int row, int col) 
	{
		//cout << "CMatrix ������" << m_row << endl;
		m_row = row;
		m_col = col;
		pMatrixArr = new int[row * col];
	}

	// �����Ҵ� �����Լ�,,,,,,(���ŵǴ����� �� ��)
	void DeleteDyList()
	{
		delete[] pMatrixArr;
		pMatrixArr = nullptr;
	}

	// ��� ���
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

	// ��� �� �ֱ�
	void SetMatrix()
	{
		cout << "����� �Է����ּ���!! ��� ��� �״�� �Է��ض�;;" << endl;
		for (int i = 0; i < m_row; ++i)
		{
			for (int j = 0; j < m_col; ++j)
			{
				cin >> pMatrixArr[i*m_col + j];
			}
		}
		cout << "��� �Է� �Ϸ�" << endl;
	}

	// ���ϱ�� ��� 0���� �ʱ�ȭ
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

	// �� ũ�� ����
	int GetRow() { return m_row; }

	// �� ũ�� ����
	int GetCol() { return m_col; }

	// ��� ���ϱ�
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
			cout << endl << "�� ����� ���ϱⰡ �Ұ����մϴ�!" << endl;
			return;
		}
	}

	// ��� ����
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
			cout << endl << "�� ����� ���Ⱑ �Ұ����մϴ�!" << endl;
			return;
		}
	}

	//��� ���ϱ�
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
			cout << endl << "�� ����� ���ϱⰡ �Ұ����մϴ�!" << endl;
			return;
		}
	}
};


// ���θ޴� �Լ� ����
void MainMenu();



// ���� �Լ�
int main()
{
	int col;
	int row;
	cout << "����� ũ�⸦ �Է��� �ּ���(��, �� ����) : ";
	cin >> row;
	cin >> col;

	CMatrix matrix1(row, col);
	//matrix1.SetDynamicMatrixArr(matrix1);
	matrix1.SetMatrix();

	cout << "����� ũ�⸦ �Է��� �ּ���(��, �� ����) : ";
	cin >> row;
	cin >> col;
	CMatrix matrix2(row, col);
	matrix2.SetMatrix();
	int menu;
	
	while (1)
	{
		system("cls");
		cout << "1�� ���" << endl;
		matrix1.PrintMatrix();
		cout << endl;
		cout << "2�� ���" << endl;
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
			cout << "����� ���� �����?!" << endl;
			matrix1.AddMatrix(matrix2);
			system("pause");
			break;
		case M_SUB:
			cout << "����� ���� �����?!" << endl;
			matrix1.SubMatrix(matrix2);
			system("pause");
			break;
		case M_MUL:
			cout << "����� ������ �����?!" << endl;
			matrix1.MulMatrix(matrix2);
			system("pause");
			break;
		default:
			cout << "�߸� �Է��ϼ̽��ϴ�." << endl;
			system("pause");
			break;
		}
	}
	return 0;
}


// ���θ޴� �Լ�
void MainMenu() {
	cout << "=====================================================" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "0. ����" << endl;
	cout << "=====================================================" << endl;
	cout << "�Է� :: ";
}