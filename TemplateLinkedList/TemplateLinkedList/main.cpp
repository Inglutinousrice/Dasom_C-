
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
		cout << "현재리스트 :: ";
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

	// int형식으로 CNode선언 double로 선언하려면 double로 바꿈
	CNode<int>* list = new CNode<int>;

	while (1) {

		// 헤드 지정
		CNode<int>* head = list;

		cout << endl;
		cout << "==============================================" << endl;
		cout << "1. 추가" << endl;
		cout << "2. 제거(인덱스로)" << endl;
		cout << "0. 종료" << endl;
		cout << "==============================================" << endl;
		cout << "입력 :: ";		cin >> button;



		if (button == 0)
			break;

		switch (button) {


			// 삽입
		case LIST_INSERT:
		{
			system("cls");

			int num;
			cout << "==============================================" << endl << endl;
			cout << "리스트에 숫자 추가!!" << endl << endl;
			cout << "리스트에 추가할 숫자를 입력해 주세요 :: ";
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

		// 인덱스로 제거
		case LIST_DELETE_INDEX:
		{
			system("cls");
			int delIndex;

			if (list->next == nullptr) {
				cout << "리스트가 비어있습니다." << endl;
				system("pause");
				break;
			}

			cout << "==============================================" << endl << endl;
			cout << "리스트 속 인덱스 제거!!" << endl << endl;
			cout << "리스트에서 제거할 인덱스를 입력해 주세요(인덱스는 0부터 시작합니다) :: "; cin >> delIndex;

			if (delIndex + 1 > lenList) {
				cout << "범위 초과입니다아아아" << endl << endl;
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

		// 그 외
		default:
		{
			cout << "다시 입력해 주세요" << endl;
			system("pause");
			break;
		}

		}
		system("cls");
	}
	return 0;
}