
#include <iostream>

using namespace std;

int main() {
	int xCrd;
	int yCrd;
	bool player1Turn = true;
	bool player2Turn = false;
	char player1List[9] = " ";
	char player2List[9] = " ";
	bool turn = true;
	int cnt = 0;
	int sumTurn = 0;

	while (sumTurn < 9) {
		if (player1Turn == turn) {

			

			cout << "---|---|---" << endl;
			cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
			cout << "---|---|---" << endl;
			cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
			cout << "---|---|---" << endl;
			cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
			cout << "---|---|---" << endl;

			cout << "(x, y)��ǥ (���� : -1, -1) : ";
			cin >> xCrd;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				system("cls");
				continue;
			}

			cin >> yCrd;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1024, '\n');
				system("cls");
				continue;
			}

			if (xCrd > 2 || yCrd > 2) {
				system("cls");
				continue;
			}

			if (player1List[3 * xCrd + yCrd] == 'X' || player1List[3 * xCrd + yCrd] == 'O') {
				system("cls");
				continue;
			}

			if (xCrd == -1 && yCrd == -1)
				break;

			cout << endl;
			player1List[3 * xCrd + yCrd] = 'O';

			turn = false;
		}

		else if (player2Turn == turn) {

			

			cout << "---|---|---" << endl;
			cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
			cout << "---|---|---" << endl;
			cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
			cout << "---|---|---" << endl;
			cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
			cout << "---|---|---" << endl;

			cout << "(x, y)��ǥ (���� : -1, -1) : ";
			cin >> xCrd;
			cin >> yCrd;

			if (xCrd > 2 || yCrd > 2) {
				system("cls");
				continue;
			}

			if (player1List[3 * xCrd + yCrd] == 'X' || player1List[3 * xCrd + yCrd] == 'O') {
				system("cls");
				continue;
			}

			if (xCrd == -1 && yCrd == -1)
				break;

			cout << endl;
			player1List[3 * xCrd + yCrd] = 'X';

			turn = true;
		}
		system("cls");

		// ���� Ȯ���ϱ�
		// ������
		for (int i = 0; i <= 2; ++i) {
			for (int j = 0; j <= 2; ++j) {
				if (player1List[3 * i + j] == 'O')
					++cnt;
			}
			if (cnt == 3) {
				cout << "---|---|---" << endl;
				cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " O �� �̰���ϴ� �����մϴ�!!!" << endl;
				exit(1);
			}
			cnt = 0;
		}

		for (int i = 0; i <= 2; ++i) {
			for (int j = 0; j <= 2; ++j) {
				if (player1List[3 * i + j] == 'X')
					++cnt;
			}
			if (cnt == 3) {
				cout << "---|---|---" << endl;
				cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " X �� �̰���ϴ� �����մϴ�!!!" << endl;
				exit(1);
			}
			cnt = 0;
		}

		// ������ Ȯ���ϱ�!!!
		for (int i = 0; i <= 2; ++i) {
			for (int j = 0; j <= 2; ++j) {
				if (player1List[3 * j + i] == 'O')
					++cnt;
			}
			if (cnt == 3) {
				cout << "---|---|---" << endl;
				cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " O �� �̰���ϴ� �����մϴ�!!!" << endl;
				exit(1);
			}
			cnt = 0;
		}

		for (int i = 0; i <= 2; ++i) {
			for (int j = 0; j <= 2; ++j) {
				if (player1List[3 * j + i] == 'X')
					++cnt;
			}
			if (cnt == 3) {
				cout << "---|---|---" << endl;
				cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " X �� �̰���ϴ� �����մϴ�!!!" << endl;
				exit(1);
			}
			cnt = 0;
		}

		// ������ �Ʒ��� �밢�� Ȯ���ϱ�!!!!
		for (int i = 0; i <= 8; i += 4) {
				if (player1List[i] == 'O')
					++cnt;
			if (cnt == 3) {
				cout << "---|---|---" << endl;
				cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " O �� �̰���ϴ� �����մϴ�!!!" << endl;
				exit(1);
			}
		}
		cnt = 0;


		for (int i = 0; i <= 8; i += 4) {
			if (player1List[i] == 'X')
				++cnt;
			if (cnt == 3) {
				cout << "---|---|---" << endl;
				cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " X �� �̰���ϴ� �����մϴ�!!!" << endl;
				exit(1);
			}
		}
		cnt = 0;


		// �Ʒ����� �� �밢�� Ȯ���ϱ�!!!!
		for (int i = 2; i <= 6; i += 2) {
			if (player1List[i] == 'O')
				++cnt;
			if (cnt == 3) {
				cout << "---|---|---" << endl;
				cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " O �� �̰���ϴ� �����մϴ�!!!" << endl;
				exit(1);
			}
		}
		cnt = 0;

		for (int i = 2; i <= 6; i += 2) {
			if (player1List[i] == 'X')
				++cnt;
			if (cnt == 3) {
				cout << "---|---|---" << endl;
				cout << " " << player1List[0] << " | " << player1List[1] << " | " << player1List[2] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[3] << " | " << player1List[4] << " | " << player1List[5] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " " << player1List[6] << " | " << player1List[7] << " | " << player1List[8] << " " << endl;
				cout << "---|---|---" << endl;
				cout << " X �� �̰���ϴ� �����մϴ�!!!" << endl;
				exit(1);
			}
		}
		cnt = 0;
		++sumTurn;
	}
	cout << "������" << endl;

	return 0;
}