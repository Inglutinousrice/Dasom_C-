
#include <iostream>
#include <string>

using namespace std;

template <class T>
class CNode
{
private:
	T info;
	CNode* next = nullptr;
public:
	void AddData(T data)
	{
		if (next == nullptr)
		{

		}
	}

	void PrintData()
	{
		CNode* list = next;
		cout << "���縮��Ʈ :: ";
		while (list->next != nullptr) {
			cout << list->info;
			list = list->next;
			if (list != nullptr)
				cout << " -> ";
		}
	}

};


int main()
{
	int button;

	// int�������� CNode���� double�� �����Ϸ��� double�� �ٲ�
	CNode<int>* list = new CNode<int>;

	while (1) {

		// ��� ����
		CNode<int>* head = list;

		cout << endl;
		cout << "==============================================" << endl;
		cout << "1. �߰�" << endl;
		cout << "2. ����(�ε�����)" << endl;
		cout << "0. ����" << endl;
		cout << "==============================================" << endl;
		cout << "�Է� :: ";		cin >> button;



		if (button == 0)
			break;

		switch (button) {


			// ����
		case LIST_INSERT:
		{
			system("cls");

			int num;
			cout << "==============================================" << endl << endl;
			cout << "����Ʈ�� ���� �߰�!!" << endl << endl;
			cout << "����Ʈ�� �߰��� ���ڸ� �Է��� �ּ��� :: ";
			cin >> num;

			if (list == nullptr) {
				list->info = num;
				list->next = new Node;
				++lenList;
			}
			else {
				while (list->next != nullptr)
					list = list->next;

				list->info = num;
				list->next = new Node;

				list = head;
				++lenList;
			}
			break;
		}

		// �ε����� ����
		case LIST_DELETE_INDEX:
		{
			system("cls");
			int delIndex;

			if (list->next == nullptr) {
				cout << "����Ʈ�� ����ֽ��ϴ�." << endl;
				system("pause");
				break;
			}

			cout << "==============================================" << endl << endl;
			cout << "����Ʈ �� �ε��� ����!!" << endl << endl;
			cout << "����Ʈ���� ������ �ε����� �Է��� �ּ���(�ε����� 0���� �����մϴ�) :: "; cin >> delIndex;

			if (delIndex + 1 > lenList) {
				cout << "���� �ʰ��Դϴپƾƾ�" << endl << endl;
				system("pause");
				break;
			}

			if (delIndex == 0) {
				head = list->next;
				delete list;
				list = head;
				--lenList;
				break;
			}

			for (int i = 0; i < delIndex - 1; ++i) {
				list = list->next;
			}

			if (list->next->next == nullptr) {
				delete list->next;
				list->next = nullptr;
				list = head;
				--lenList;
				break;
			}
			else {
				Node* temp = list->next;
				list->next = list->next->next;
				delete temp;
				list = head;
				--lenList;
				break;
			}
			break;
		}

		// �� ��
		default:
		{
			cout << "�ٽ� �Է��� �ּ���" << endl;
			system("pause");
			break;
		}

		}
		system("cls");
	}
	return 0;
}