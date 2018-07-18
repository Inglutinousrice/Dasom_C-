
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

#define POSSESS_MAX		999 // ������ ���� �ִ� �뷮
#define SECOND_EVOLUTION	17	// �ι�° ��ȭ ����
#define LAST_EVOLUTION		37 // ������ ��ȭ ����

using namespace std;

/*
�������� : *****************���� �Ҵ� �����ϴ� ����(���)*****************
				    ���ø����̼� Ŭ������ ���� �Űܼ� �����ϴ� ���

�������� ���� �κ�
	-	Ÿ�Կ� ���� ������ ����
	-	������ ����
	-	������ ���ϸ���� ��ų
	-	��ȭ
	-	Ǯ ȸ���� ȸ����
*/

// ���ϸ� ���� enum��
enum POCKETMON_KIND
{
	PK_NONE,
	PK_TORCHIC, // ������
	PK_COMBUSKEN, // ��ġ��
	PK_BLAZIKEN, // ��ġ��
	PK_MUDKIP, // ��¯��
	PK_MARSHTOMP, // ��¯��
	PK_SWAMPERT, // ��¯��
	PK_TREECKO, // ��������
	PK_GROVYLE, // ��������
	PK_SCEPTILE, // ����ŷ
	PK_LAST
};

// ���ϸ� Ÿ�� enum��
enum POCKETMON_TYPE
{
	PT_NONE,
	PT_FIRE, // 1 ��
	PT_WATER, // 2 ��
	PT_GRASS, // 3 ��
	PT_LAST
};

// ���� ���ϸ� enum��
enum START_POCKETMON
{
	SP_NONE,
	SP_TORCHIC, // ������
	SP_MUDKIP, // ��¯��
	SP_TREECKO, // ��������
	SP_LAST
};

// ���� �޴� enum��
enum MAIN_MENU
{
	MM_NONE,
	MM_ADVENTURE, // ���� ������
	MM_CHECK_PHOCKETMON, // ���ϸ� Ȯ���ϱ�
	MM_BACKPACK, // ���� Ȯ���ϱ�
	MM_STORE, // ���� ����
	MM_HOSPITAL, // ���� ����
	MM_EXIT, // ����
	MM_LAST
};

// ���� enum��
enum MAIN_STORE
{
	MS_NONE,
	MS_NORMAL_RECOVERY_DRUG, // ȸ����
	MS_HIGH_RECOVERY_DRUG, // ��� ȸ����
	MS_MONSTER_BALL, // ���ͺ�
	MS_HYPER_BALL, // �����ۺ�
	MS_MASTER_BALL, // �����ͺ�
	MS_EXIT, // ����
	MS_LAST
};


/*
���������� ȸ�����ϰ� ���ͺ��� �� ���̴�.
ȸ������ �������� ġ���, ��� ġ���, Ǯ ȸ���� �� �� �����̸�
���ͺ��� �������� ���ͺ�, �����ۺ�, �����ͺ� �� �� ������ �ִ�.
ġ����� ü���� 100 ȸ�����ְ�, ��� ġ����� ü���� 500 ȸ�����ָ�, Ǯ ȸ������ �ִ�ü�±��� ȸ������ �ش�.
������ ���� 200G, 700G, 2000G�̴�.
���ͺ��� ������ �� ���� ���� Ȯ���� �ٸ���,
���ͺ��� 30%�� Ȯ���� �����ϰ�, �����ۺ��� 40%Ȯ���� �����ϸ�, �����ͺ��� 100%�� Ȯ���� �����ϰ� �ȴ�.
������ ���� 200G, 700G, 8000G�̴�.
*/

// ============================================ȸ���� Ŭ����============================================
class CRecoveryDrug
{
protected:
	int m_HealAmount; // ȸ�� ��
	int m_PossessNum; // ���� ���� ����
	int m_Price; // ����
public:
	// �� �� ���� �Լ�
	int GetHealAmount() { return m_HealAmount; }

	// ���� ����
	int GetPossessNum() { return m_PossessNum; }
	void PlusPossessNum() { ++m_PossessNum; }
	void MinusPossessNum() { --m_PossessNum; }

	// ���� ����
	int GetPrice() { return m_Price; }

};


// �Ϲ� ġ��� Ŭ����
class CNormalRecoveryDrug
	: public CRecoveryDrug
{
public:
	CNormalRecoveryDrug() { m_HealAmount = 100; m_PossessNum = 2; m_Price = 200; }

};


// ��� ġ��� Ŭ����
class CHighRecoveryDrug
	:public CRecoveryDrug
{
public:
	CHighRecoveryDrug() { m_HealAmount = 500; m_PossessNum = 0; m_Price = 700; }

};


// ============================================���ͺ� Ŭ����============================================
class CMonsterBall
{
protected:
	int m_CatchProbability; // ���� Ȯ��
	int m_PossessNum; // ���� ���� ����
	int m_Price; // ����

public:
	// Ȯ�� �������� �Լ�
	int GetCatchProbability() { return m_CatchProbability; }

	// ���� ����
	int GetPossessNum() { return m_PossessNum; }
	void PlusPossessNum() { ++m_PossessNum; }
	void MinusPossessNum() { --m_PossessNum; }

	// ���� ����
	int GetPrice() { return m_Price; }

};


// �Ϲ� ���ͺ� Ŭ����
class CNormalMonsterBall
	: public CMonsterBall
{
public:
	CNormalMonsterBall() { m_CatchProbability = 30; m_PossessNum = 5; m_Price = 200; }
};


// �����ۺ� Ŭ����
class CHyperBall
	: public CMonsterBall
{
public:
	CHyperBall() { m_CatchProbability = 40; m_PossessNum = 0; m_Price = 700; }
};


// �����ͺ� Ŭ����
class CMasterBall
	: public CMonsterBall
{
public:
	CMasterBall() { m_CatchProbability = 100; m_PossessNum = 0; m_Price = 8000; }
};


// ============================================���� Ŭ����============================================
class CMonster
{
protected:
	int m_HP;
	int m_Attack;
	int m_Type;
	int m_Level;
	int m_MaxHP;
	int m_EXP;
	int m_Gold;
	int m_MaxEXP;
	string m_Name;

public:
	// ����� �Լ�
	void PocketMonSpecUp(CMonster* monster)
	{
		monster->SetHP(monster->GetLevel() * 100);
		monster->SetAttack(monster->GetLevel() * 5);
		monster->SetEXP(0);
		monster->SetMaxHP(monster->GetLevel() * 100);
		monster->SetGold(monster->GetLevel() * 10);
		monster->SetMaxEXP(monster->GetLevel() * 10);
	}

	// HP �Լ�
	int GetHP(){ return m_HP; }
	void SetHP(int HP) { m_HP = HP; }

	// Attack �Լ�
	int GetAttack(){ return m_Attack; }
	void SetAttack(int attack) { m_Attack = attack; }

	// Type �Լ�
	int GetType() { return m_Type; }
	void SetType(int type) { m_Type = type; }

	// Level �Լ�
	int GetLevel() { return m_Level; }
	void SetLevel(int level) { m_Level = level; }

	// maxHP �Լ�
	int GetMaxHP() { return m_MaxHP; }
	void SetMaxHP(int maxHP) { m_MaxHP = maxHP; }

	// EXP �Լ�
	int GetEXP() { return m_EXP; }
	void SetEXP(int EXP) { m_EXP = EXP; }

	// MaxEXP �Լ�
	int GetMaxEXP() { return m_MaxEXP; }
	void SetMaxEXP(int maxEXP) { m_MaxEXP = maxEXP; }

	// Gold �Լ�
	int GetGold() { return m_Gold; }
	void SetGold(int gold) { m_Gold = gold; }

	// Name�Լ�
	string GetName() { return m_Name; }

	// �����Ҵ� ���� �Լ�
	void DeletePocketMon(CMonster* monster)
	{
		delete[] monster;
		monster = nullptr;
	}
};


// ============================================������ Ŭ���� 1-16============================================
class CTorchic
	: public CMonster
{
private:

public:
	CTorchic(int level)
	{
		m_Name = "������";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};
 
// ============================================��ġ�� Ŭ���� 17-36============================================
class CCombusken
	: public CMonster
{
private:

public:
	CCombusken(int level)
	{
		m_Name = "��ġ��";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================��ġ�� Ŭ���� 37-50============================================
class CBlaziken
	: public CMonster
{
private:

public:
	CBlaziken(int level)
	{
		m_Name = "��ġ��";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================��¯�� Ŭ���� 1-16============================================
class CMudkip
	: public CMonster
{
private:

public:
	CMudkip(int level)
	{
		m_Name = "��¯��";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================��¯�� Ŭ���� 17-36============================================
class CMarshtomp
	: public CMonster
{
private:

public:
	CMarshtomp( int level )
	{
		m_Name = "��¯��";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================��¯�� Ŭ���� 37-50============================================
class CSwampert
	: public CMonster
{
private:

public:
	CSwampert( int level )
	{
		m_Name = "��¯��";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};
 
// ============================================�������� Ŭ���� 1-16============================================
class CTreecko
	: public CMonster
{
private:

public:
	CTreecko(int level )
	{
		m_Name = "��������";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================�������� Ŭ���� 17-36============================================
class CGrovyle
	: public CMonster
{
private:

public:
	CGrovyle(int level)
	{
		m_Name = "��������";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================����ŷ Ŭ���� 37-50============================================
class CSceptile
	: public CMonster
{
private:

public:
	CSceptile(int level)
	{
		m_Name = "����ŷ";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================�÷��̾� Ŭ����============================================
class CPlayer
{
private:
	CMonster* monsterArr[6] = {};
	string m_Name = "������";
	int m_Gold = 500;
	int m_pocketMonNum = 0;
	CRecoveryDrug* norRecDrug = new CNormalRecoveryDrug;
	CRecoveryDrug* highRecDrug = new CHighRecoveryDrug;
	CMonsterBall* norBall = new CNormalMonsterBall;
	CMonsterBall* hyperBall = new CHyperBall;
	CMonsterBall* masterBall = new CMasterBall;

public:
	// ������ �Լ�
	void RepPocketMonLevelUp()
	{
		monsterArr[0]->SetLevel(monsterArr[0]->GetLevel() + 1);
		monsterArr[0]->PocketMonSpecUp(monsterArr[0]);
	}

	// ����ġ ��� �Լ�
	void EXPPlus(CPlayer player, CMonster* monster)
	{
		if (player.GetRepPocketMon()->GetEXP() + monster->GetMaxEXP() >= player.GetRepPocketMon()->GetMaxEXP())
		{
			int temp = player.GetRepPocketMon()->GetEXP() + monster->GetMaxEXP() - player.GetRepPocketMon()->GetMaxEXP();
			RepPocketMonLevelUp();
			player.GetRepPocketMon()->SetEXP(player.GetRepPocketMon()->GetEXP() + temp);
		}
		else
			player.GetRepPocketMon()->SetEXP(player.GetRepPocketMon()->GetEXP() + monster->GetMaxEXP());
	}

	// ��� ��� �Լ�
	void GoldPlus(CMonster* monster)
	{
		m_Gold = m_Gold + monster->GetGold();
	}

	// �Է¹��� �ε����� ���ϸ��� ��� �ִ��� �˾ƺ���
	bool IsPocketMonLive(int idx)
	{
		if (monsterArr[idx - 1]->GetHP() != 0)
			return true;
		
		return false;
	}

	// ��ü ������ ���ϸ� ���� �ִ��� ���캸��
	void PocketMonWhoCanChange()
	{
		system("cls");
		cout << "=========================���� ���ϸ� ����=========================" << endl;
		for (int i = 0; i < m_pocketMonNum; ++i)
			cout << i + 1 << ". " << monsterArr[i]->GetName() << "  LEVEL : " << monsterArr[i]->GetLevel() << "  HP : " << monsterArr[i]->GetHP() << " / " << monsterArr[i]->GetMaxHP() << endl;
		cout << "==================================================================" << endl;
		cout << "��ü�� ���ϸ� ��ȣ�� �Է��� �ּ���" << endl;
		cout << "==================================================================" << endl;
		cout << "=> ";
	}

	// ��ü ������ ���ϸ��� �ִ��� �˾ƺ���
	bool IsLivePocketMonThere()
	{
		int cnt = 1;
		for (int i = 0; i < m_pocketMonNum; ++i)
		{
			if (monsterArr[i]->GetHP() != 0)
				++cnt;
		}
		if (cnt == 1)
			return false;

		return true;
	}

	// �Ϲ� ȸ���� ��������
	CRecoveryDrug* GetNorRecDrug() { return norRecDrug; }

	// ��� ȸ���� ��������
	CRecoveryDrug* GetHighRecDrug() { return highRecDrug; }

	// ���ͺ� ��������
	CMonsterBall* GetNorMonsterBall() { return norBall; }

	// �����ۺ� ��������
	CMonsterBall* GetHyperBall() { return hyperBall; }

	// �����ͺ� ��������
	CMonsterBall* GetMasterBall() { return masterBall; }

	// ���ϸ��� �Լ�(���� ȸ��)
	void PocketMonCenter()
	{
		for (int i = 0; i < m_pocketMonNum; ++i)
			monsterArr[i]->SetHP(monsterArr[i]->GetMaxHP());
	}

	// ��ǥ ���ϸ� �ٲ��ִ� �Լ�
	void ChangeRepPocketMon(int changeNum)
	{
		CMonster* temp = monsterArr[0];
		monsterArr[0] = monsterArr[changeNum-1];
		monsterArr[changeNum-1] = temp;
	}

	// ���ϸ� �Ǹ��ϴ� �Լ�
	void sellPocketMon(int sellNum)
	{
		m_Gold += monsterArr[sellNum - 1]->GetGold();
		monsterArr[sellNum - 1] = monsterArr[m_pocketMonNum - 1];
		monsterArr[m_pocketMonNum - 1] = nullptr;
		SubPocketMonNum();
	}

	// ��ǥ ���ϸ� ��ȯ �Լ�
	CMonster* GetRepPocketMon() { return monsterArr[0]; }

	// Gold �Լ�
	int GetGold() { return m_Gold; }
	void SetGold(int gold) { m_Gold = gold; }

	// ���ϸ� �߰� �Լ�
	void AddPocketMon(CMonster* newMonster) { monsterArr[m_pocketMonNum - 1] = newMonster; }

	// ���ϸ���� ���� �Լ�
	void AddPocketMonNum() { ++m_pocketMonNum; }

	// ���ϸ���� ���� �Լ�
	void SubPocketMonNum() { --m_pocketMonNum; }

	// m_PocketMonNum  ��ȯ �Լ�
	int GetPocketMonNum() { return m_pocketMonNum; }

	
	// 2�� �޴����� ���� ���ϸ� �����ִ� �Լ�
	void ShowPlayerPocketMon()
	{
		system("cls");
		cout << "============================================���� ���� ���ϸ�============================================" << endl;
		cout << "                             1���� ���� ���ϸ��� ��ǥ ���ϸ��� �˴ϴ�." << endl;
		cout << "                  ���ϸ� ���� ��ü�� 1�� ���ϸ�� 1���� �ƴ� ���ϸ󳢸��� �����մϴ�." << endl << endl;
		cout << "���� ���ϸ� �� :: " << m_pocketMonNum << endl;
		cout << "=======================================================================================================" << endl;
		for (int i = 0; i < m_pocketMonNum; ++i)
			cout << i + 1 << ". " << monsterArr[i]->GetName() << "  LEVEL : " << monsterArr[i]->GetLevel() << "  HP : " << monsterArr[i]->GetHP() << " / " << monsterArr[i]->GetMaxHP() << "  EXP : " << monsterArr[i]->GetEXP() << " / " << monsterArr[i]->GetMaxEXP() << endl;
		cout << "=======================================================================================================" << endl;
	}

	// ���� �� ���� ���ϸ� �����ִ� �Լ�
	void ShowPlayerPocketMonInBattle()
	{
		cout << "=========================���� ���� ���ϸ�=========================" << endl;
		for (int i = 0; i < m_pocketMonNum; ++i)
			cout << i + 1 << ". " << monsterArr[i]->GetName() << "  LEVEL : " << monsterArr[i]->GetLevel() << "  HP : " << monsterArr[i]->GetHP() << " / " << monsterArr[i]->GetMaxHP() << endl;
		cout << "==================================================================" << endl;
	}
};



// �Լ� ����
void StartMenu();
void SelectStartPocketMon();
void MainMenu(CPlayer player);
void InPlayerPocketMon();
void InShopMenu(CPlayer player);
void InHospital();
void InBackPack(CPlayer player);
void InBattleMenu(CPlayer player, CMonster* monster);
void InBattleBackPack(CPlayer player);
int LevelPlusMinusFive(CPlayer player);
int ProbabilityOneToHundred();
int MeetPocketMonProbability();
int RunProbability();

int main()
{
	int startmenu;
	StartMenu();	cin >> startmenu;

	if (startmenu != 1)
		exit(0);


	CPlayer player;


	// ============================================���� ���ϸ� ����============================================
	bool bselect = true;
	int startPocketMon;
	while (bselect)
	{
		SelectStartPocketMon();		cin >> startPocketMon;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		switch (startPocketMon)
		{
		case SP_TORCHIC:
		{
			// 	CTorchic(int HP, int attack, int level, int EXP, int gold, int maxHP, int maxEXP)
			CMonster* torchic = new CTorchic(1);
			player.AddPocketMonNum();
			player.AddPocketMon(torchic);
			bselect = false;
			break;
		}
		case SP_MUDKIP:
		{
			CMonster* mudkip = new CMudkip(1);
			player.AddPocketMonNum();
			player.AddPocketMon(mudkip);
			bselect = false;
			break;
		}
		case SP_TREECKO:
		{
			CMonster* treecko = new CTreecko(1);
			player.AddPocketMonNum();
			player.AddPocketMon(treecko);
			bselect = false;
			break;
		}
		default:
		{
			cout << "�߸� �� �� ������,,,," << endl;
			system("pause");
			break;
		}
		}
	}

	// ============================================!!! ���� !!!============================================





	// �׽�Ʈ��
	CMonster* treecko = new CTreecko(1);
	player.AddPocketMonNum();
	player.AddPocketMon(treecko);
	CMonster* mudkip = new CMudkip(50);
	player.AddPocketMonNum();
	player.AddPocketMon(mudkip);



	int mainMenu;
	while (1)
	{
		MainMenu(player);		cin >> mainMenu;
		
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		
		if (mainMenu == MM_EXIT)
			exit(0);


		switch (mainMenu) {

		// ============================================1. ���� ������============================================
		// �׻� �÷��̾ ����
		case MM_ADVENTURE: {
			int inBattleMenu;
			
			int meetWho = MeetPocketMonProbability();
			switch (meetWho)
			{
			// ������ ���� 
			case PK_TORCHIC: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* torchic = new CTorchic(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, torchic);		cin >> inBattleMenu;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (torchic->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								torchic->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								torchic->SetHP(torchic->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << torchic->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;

							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(torchic);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(torchic);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(torchic);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, torchic);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - torchic->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - torchic->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << torchic->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && torchic->GetHP() != 0)
						{
							InBattleMenu(player, torchic);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && torchic->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && torchic->GetHP() == 0)
						{
							cout << "�߻��� " << torchic->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(torchic);
							player.EXPPlus(player, torchic);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// ��ġ�� ����
			case PK_COMBUSKEN: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* combusken = new CCombusken(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, combusken);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (combusken->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								combusken->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								combusken->SetHP(combusken->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << combusken->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(combusken);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(combusken);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(combusken);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, combusken);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - combusken->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - combusken->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << combusken->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && combusken->GetHP() != 0)
						{
							InBattleMenu(player, combusken);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && combusken->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && combusken->GetHP() == 0)
						{
							cout << "�߻��� " << combusken->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(combusken);
							player.EXPPlus(player, combusken);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// ��ġ�� ����
			case PK_BLAZIKEN: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* blaziken = new CBlaziken(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, blaziken);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (blaziken->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								blaziken->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								blaziken->SetHP(blaziken->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << blaziken->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(blaziken);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(blaziken);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(blaziken);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, blaziken);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - blaziken->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - blaziken->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << blaziken->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && blaziken->GetHP() != 0)
						{
							InBattleMenu(player, blaziken);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && blaziken->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && blaziken->GetHP() == 0)
						{
							cout << "�߻��� " << blaziken->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(blaziken);
							player.EXPPlus(player, blaziken);
							system("pause");
							break;
						}
					}
				}
				break;
			}

			// ��¯�� ����
			case PK_MUDKIP: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* mudkip = new CMudkip(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, mudkip);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (mudkip->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								mudkip->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								mudkip->SetHP(mudkip->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << mudkip->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(mudkip);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(mudkip);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(mudkip);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, mudkip);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - mudkip->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - mudkip->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << mudkip->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && mudkip->GetHP() != 0)
						{
							InBattleMenu(player, mudkip);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && mudkip->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && mudkip->GetHP() == 0)
						{
							cout << "�߻��� " << mudkip->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(mudkip);
							player.EXPPlus(player, mudkip);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// ��¯�� ����
			case PK_MARSHTOMP: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* marshtomop = new CMarshtomp(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, marshtomop);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (marshtomop->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								marshtomop->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								marshtomop->SetHP(marshtomop->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << marshtomop->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(marshtomop);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(marshtomop);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(marshtomop);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, marshtomop);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - marshtomop->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - marshtomop->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << marshtomop->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && marshtomop->GetHP() != 0)
						{
							InBattleMenu(player, marshtomop);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && marshtomop->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && marshtomop->GetHP() == 0)
						{
							cout << "�߻��� " << marshtomop->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(marshtomop);
							player.EXPPlus(player, marshtomop);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// ��¯�� ����
			case PK_SWAMPERT: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* swampert = new CSwampert(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, swampert);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (swampert->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								swampert->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								swampert->SetHP(swampert->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << swampert->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(swampert);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(swampert);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(swampert);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, swampert);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - swampert->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - swampert->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << swampert->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && swampert->GetHP() != 0)
						{
							InBattleMenu(player, swampert);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && swampert->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && swampert->GetHP() == 0)
						{
							cout << "�߻��� " << swampert->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(swampert);
							player.EXPPlus(player, swampert);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// �������� ����
			case PK_TREECKO: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* treecko = new CTreecko(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, treecko);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (treecko->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								treecko->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								treecko->SetHP(treecko->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << treecko->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(treecko);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(treecko);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(treecko);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, treecko);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - treecko->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - treecko->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << treecko->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && treecko->GetHP() != 0)
						{
							InBattleMenu(player, treecko);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && treecko->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && treecko->GetHP() == 0)
						{
							cout << "�߻��� " << treecko->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(treecko);
							player.EXPPlus(player, treecko);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// �������� ����
			case PK_GROVYLE: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* grovyle = new CGrovyle(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, grovyle);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (grovyle->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								grovyle->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								grovyle->SetHP(grovyle->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << grovyle->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(grovyle);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(grovyle);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(grovyle);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, grovyle);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - grovyle->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - grovyle->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << grovyle->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && grovyle->GetHP() != 0)
						{
							InBattleMenu(player, grovyle);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && grovyle->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && grovyle->GetHP() == 0)
						{
							cout << "�߻��� " << grovyle->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(grovyle);
							player.EXPPlus(player, grovyle);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// ����ŷ ����
			case PK_SCEPTILE: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* sceptile = new CSceptile(level);

				// ��������� �ϳ��� ��Ʋ�� ����Ǵ� ����
				while (bInBattleMenu)
				{
					InBattleMenu(player, sceptile);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// �÷��̾� ��
					while (playerTurn)
					{
						// ����
						if (inBattleMenu == 1)
						{

							// �����ߴµ� ������ HP�� 0���� �۾����� -> 0���� ����� �̱�
							if (sceptile->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								sceptile->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
							else
							{
								sceptile->SetHP(sceptile->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "�� ����!!!!!!" << endl;
								cout << sceptile->GetName() << "�� ü���� " << player.GetRepPocketMon()->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
								system("pause");
							}
						}

						// ����
						// ���� �Ϸ�
						if (inBattleMenu == 2)
						{
							int inBattleBackPackMenu;
							InBattleBackPack(player);		cin >> inBattleBackPackMenu;
							if (cin.fail()) {
								cin.clear();
								cin.ignore(1024, '\n');
								continue;
							}

							if (inBattleBackPackMenu == 6)
								break;

							// ȸ���� ���
							if (inBattleBackPackMenu == 1)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ��� ȸ���� ���
							if (inBattleBackPackMenu == 2)
							{
								// ȸ������ ������?! or ��ǥ���ϸ��� �ִ�ü���̴�?! -> ���Ұ� �ٽ� �ڱ���
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// ȸ���ߴµ� �ִ�ü���� �Ѿ��?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// �� �� �Ϲ������� ���
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// ���ͺ� ���
							if (inBattleBackPackMenu == 3)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(sceptile);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ۺ� ���
							if (inBattleBackPackMenu == 4)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(sceptile);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// �����ͺ� ���
							if (inBattleBackPackMenu == 5)
							{

								// Ȯ�� ��Ƴ���
								int catchProbability = ProbabilityOneToHundred();

								// ���ͺ��� 0����?! or �̹� 6������ �� �����ȴ�?! -> �ٽ� ó��ȭ������
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "�������� ����� �� �����ϴ�." << endl;
									system("pause");
								}

								// �����ϸ� �� ����
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "��µ��� �����ߴ�!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// �����ϸ� ���ϸ� �迭�� �߰��ϰ� ���� ����
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(sceptile);
									cout << "���ϸ��� ��Ҵ�!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// ����
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "������ �����ߴ�!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// ���� ��
					while (enemyTurn)
					{
						InBattleMenu(player, sceptile);
						// �����ߴµ� ���� HP�� 0���� �۾����� -> 0���� ����� ��ü�ϰ� ���� 
						// ��ü�� ģ������ ������ �й�� �� ���� ����
						if (player.GetRepPocketMon()->GetHP() - sceptile->GetAttack() <= 0)
						{

							// ��ü�� �Ұ����� �����̸�(��ü�� ���ϸ��� ���̻� ������) ��������.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// ��ü�� �����ϴٸ� ��ü ������ ���ϸ���� ������ ��  
							// ��ü�� ���ϸ��� ��ǥ ���ϸ����� �Űܼ� ��ü�����ش�. ���� ���� ������ �����Ѵ�.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// �Է� ���� ���ϸ��� ��� �ִٸ� ��ǥ ���ϸ����� �ٲپ��ش�.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "�� ���ϸ��� �̹� �׾��ֽ��ϴ�. " << endl;
									system("pause");
								}

							}
						}

						// �װ� �ƴ϶�� �� �Ǹ� ��� �� �ѱ��.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - sceptile->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "������ ����!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "�� ü���� " << sceptile->GetAttack() << "��ŭ �޾Ҵ�!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn ��� false�� ���(�� �� �ϳ��� �׾ ������ ������)
					// �÷��̾��� ��ǥ���ϸ� ü���� 0�̸� �÷��̾��� �й� -> ���� ������
					// ���� ü���� 0�̸� �÷��̾��� �¸� -> ����ġ�� ��带 ��� ����ȭ������
					// �Ѵ� 0�� �ƴϸ� ���� or ��µ� ���� -> �� ����ȭ������

					if (!playerTurn && !enemyTurn)
					{
						// �÷��̾��� �й�
						if (player.GetRepPocketMon()->GetHP() == 0 && sceptile->GetHP() != 0)
						{
							InBattleMenu(player, sceptile);
							cout << "������ �ٽ� ������!!!!" << endl;
							exit(0);
						}
						// �Ѵ� 0�� �ƴϸ�
						else if (player.GetRepPocketMon()->GetHP() != 0 && sceptile->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// �÷��̾��� �¸�
						// ����ġ�� ��带 ��´�.
						// �������� �� ��� ������ �Լ��� ��������ش�.
						else if (player.GetRepPocketMon() != 0 && sceptile->GetHP() == 0)
						{
							cout << "�߻��� " << sceptile->GetName() << "�� �����ƽ��ϴ�!!!" << endl;
							player.GoldPlus(sceptile);
							player.EXPPlus(player, sceptile);
							system("pause");
							break;
						}
					}
				}

				break;
			}
			default:
				break;
			}
			
			break;
		}

		// ============================================2. ���ϸ� Ȯ���ϱ�============================================
		// ============================================���� �Ϸ�============================================
		case MM_CHECK_PHOCKETMON: {
			int inPlayerPocketMon;
			bool bSelectInCheck = true;
			player.ShowPlayerPocketMon();

			while (bSelectInCheck)
			{
				InPlayerPocketMon();		cin >> inPlayerPocketMon;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (inPlayerPocketMon == 3)
					break;

				// ��ǥ ���ϸ� ��ü
				if (inPlayerPocketMon == 1)
				{
					if (player.GetPocketMonNum() == 1) {
						cout << "��ü�� �� �ִ� ���ϸ��� �����ϴ�." << endl;
						system("pause");
						break;
					}
					cout << "��ü�� ���ϸ��� ��ȣ�� �Է����ּ���." << endl;
					int changePocketMonNum;
					cout << "=> ";		cin >> changePocketMonNum;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					if (changePocketMonNum <= 0 || player.GetPocketMonNum() < changePocketMonNum)
					{
						cout << "�߸� �� �� ������,,,," << endl;
						system("pause");
						break;
					}

					player.ChangeRepPocketMon(changePocketMonNum);
					player.ShowPlayerPocketMon();
					bSelectInCheck = false;
				}

				// ���ϸ� �ȱ�
				else if (inPlayerPocketMon == 2)
				{
					if (player.GetPocketMonNum() == 1) {
						cout << "�Ǹ��� �� �ִ� ���ϸ��� �����ϴ�." << endl;
						system("pause");
						break;
					}
					cout << "�Ǹ��� ���ϸ��� ��ȣ�� �Է����ּ���." << endl;
					int sellPocketMonNum;
					cout << "=> ";		cin >> sellPocketMonNum;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					if (sellPocketMonNum <= 0 || player.GetPocketMonNum() < sellPocketMonNum)
					{
						cout << "�߸� �� �� ������,,,," << endl;
						system("pause");
						break;
					}

					player.sellPocketMon(sellPocketMonNum);
					player.ShowPlayerPocketMon();
					bSelectInCheck = false;
				}
				else
				{
					cout << "�߸� �� �� ������,,,," << endl;
					system("pause");
					break;
				}
			}
			break;
		}

		//============================================3. ���� ����============================================
		// ============================================���� �Ϸ�============================================
		case MM_BACKPACK: {
			int inBackpack;
			bool bInBackPack = true;

			while (bInBackPack)
			{
				InBackPack(player);		cin >> inBackpack;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (inBackpack == 1)
					break;
				else
				{
					cout << "�߸� �� �� ������,,,," << endl;
					system("pause");
				}
			}
			break;
		}

		// ============================================4. ���� ����============================================
		// ============================================���� �Ϸ�============================================
		case MM_STORE: {

			int inShopMenu;
			bool selectShop = true;
			while (selectShop)
			{
				InShopMenu(player);		cin >> inShopMenu;
				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (inShopMenu == MS_EXIT)
					break;

				switch (inShopMenu)
				{
				// �Ϲ� ȸ����
				case MS_NORMAL_RECOVERY_DRUG: {
					if (player.GetGold() < player.GetNorRecDrug()->GetPrice())
					{
						cout << "���� �����մϴ�." << endl;
						system("pause");
						break;
					}

					if (player.GetNorRecDrug()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "�� �̻� ������ �� �����ϴ�." << endl;
						system("pause");
						break;
					}

					player.GetNorRecDrug()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetNorRecDrug()->GetPrice());
					cout << "���Ű� �Ϸ�Ǿ����ϴ�." << endl;
					selectShop = false;
					system("pause");
					break;
				}

				// ��� ȸ����
				case MS_HIGH_RECOVERY_DRUG: {
					if (player.GetGold() < player.GetHighRecDrug()->GetPrice())
					{
						cout << "���� �����մϴ�." << endl;
						system("pause");
						break;
					}

					if (player.GetHighRecDrug()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "�� �̻� ������ �� �����ϴ�." << endl;
						system("pause");
						break;
					}

					player.GetHighRecDrug()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetHighRecDrug()->GetPrice());
					cout << "���Ű� �Ϸ�Ǿ����ϴ�." << endl;
					selectShop = false;
					system("pause");
					break;
				}

				// �Ϲ� ���ͺ�
				case MS_MONSTER_BALL: {
					if (player.GetGold() < player.GetNorMonsterBall()->GetPrice())
					{
						cout << "���� �����մϴ�." << endl;
						system("pause");
						break;
					}

					if (player.GetNorMonsterBall()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "�� �̻� ������ �� �����ϴ�." << endl;
						system("pause");
						break;
					}

					player.GetNorMonsterBall()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetNorMonsterBall()->GetPrice());
					cout << "���Ű� �Ϸ�Ǿ����ϴ�." << endl;
					selectShop = false;
					system("pause");
					break;
				}

				// �����ۺ�
				case MS_HYPER_BALL: {
					if (player.GetGold() < player.GetHyperBall()->GetPrice())
					{
						cout << "���� �����մϴ�." << endl;
						system("pause");
						break;
					}

					if (player.GetHyperBall()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "�� �̻� ������ �� �����ϴ�." << endl;
						system("pause");
						break;
					}

					player.GetHyperBall()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetHyperBall()->GetPrice());
					cout << "���Ű� �Ϸ�Ǿ����ϴ�." << endl;
					selectShop = false;
					system("pause");
					break;
				}

				// �����ͺ�
				case MS_MASTER_BALL: {
					if (player.GetGold() < player.GetMasterBall()->GetPrice())
					{
						cout << "���� �����մϴ�." << endl;
						system("pause");
						break;
					}

					if (player.GetMasterBall()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "�� �̻� ������ �� �����ϴ�." << endl;
						system("pause");
						break;
					}

					player.GetMasterBall()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetMasterBall()->GetPrice());
					cout << "���Ű� �Ϸ�Ǿ����ϴ�." << endl;
					selectShop = false;
					system("pause");
					break;
				}
				default:
					cout << "�߸� �� �� ������,,,," << endl;
					system("pause");
					break;
				}
			}
			break;
		}

		// ============================================5. ���� ����============================================
		// ============================================���� �Ϸ�============================================
		case MM_HOSPITAL: {
			InHospital();
			player.PocketMonCenter();
			system("pause");
			break;
		}
		default:
			break;
		}
	}
	return 0;
}


// �� ó�� ���� ȭ��
void StartMenu()
{
	system("cls");
	cout << "==================================================================" << endl << endl;
	cout << "                          ���ϸ��;�" << endl << endl;
	cout << "==================================================================" << endl;
	cout << "                         *** ���� ***" << endl;
	cout << "                      ���� ���� ���ʽÿ�." << endl;
	cout << "       �ѹ� ������ ������ ����� �� ó������ �ٽý����մϴ�." << endl << endl;
	cout << "1. ���� ����" << endl;
	cout << "1�� �ƴ� ���� : ����" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

// ���� ȭ��
void MainMenu(CPlayer player)
{
	system("cls");
	cout << "==================================================================" << endl;
	cout << "�÷��̾� �̸� :: ������" << endl;
	cout << "���� ��� :: " << player.GetGold() << "G"<< endl;
	cout << "��ǥ ���ϸ� :: " << player.GetRepPocketMon()->GetName() << endl;
	cout << "LEVLE :: " << player.GetRepPocketMon()->GetLevel() << endl;
	cout << "EXP :: " << player.GetRepPocketMon() ->GetEXP() << " / " << player.GetRepPocketMon()->GetMaxEXP() << endl;
	cout << "==================================================================" << endl;
	cout << "1. �߻����� ������" << endl;
	cout << "2. ���� ���ϸ� Ȯ��" << endl;
	cout << "3. ���� Ȯ��" << endl;
	cout << "4. ��������" << endl;
	cout << "5. ��������" << endl;
	cout << "6. ����" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

// ��ŸƮ ���ϸ� ���� â
void SelectStartPocketMon()
{
	system("cls");
	cout << "==================================================================" << endl;
	cout << "                 ��ŸƮ ���ϸ��� ��� ���ô�!!!" << endl;
	cout << "            ǮŸ���� �̷��� ������� Ȯ���� �����ϴ�." << endl;
	cout << "==================================================================" << endl;
	cout << "1. ������ (Ÿ�� : ��)" << endl;
	cout << "2. ��¯�� (Ÿ�� : ��)" << endl;
	cout << "3. �������� (Ÿ�� : Ǯ)" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

// 1���� 100���� �̾��ִ� �Լ�
int ProbabilityOneToHundred()
{
	int num;
	srand((unsigned int)time(0));
	num = rand() % 100 + 1;
	return num;
}

// ���ϸ� ���� â
void InPlayerPocketMon()
{
	cout << "1. ��ǥ ���ϸ� �ٲٱ�" << endl;
	cout << "2. ���ϸ� �ȱ�" << endl;
	cout << "3. �ڷΰ���" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

// ���� â
void InShopMenu(CPlayer player)
{
	system("cls");
	cout << "============================================!!����!!============================================" << endl;
	cout << "                      ���������� ȸ����� ���ͺ��� �Ǹ��ϰ� �ֽ��ϴ�." << endl;
	cout << "                  ȸ����� ���ͺ��� ���� 999�� ������ ������ �� �ֽ��ϴ�." << endl;
	cout << "================================================================================================" << endl;
	cout << "���� ���� ��� :: " << player.GetGold() << "G" << endl << endl;
	cout << "1. ȸ����(ü���� 100 ȸ���մϴ�.)  200G" << endl;
	cout << "2. ��� ȸ����(ü���� 500 ȸ���մϴ�.)  700G" << endl;
	cout << "3. ���� ��  200G" << endl;
	cout << "4. ������ ��  700G" << endl;
	cout << "5. ������ ��  8000G" << endl;
	cout << "6. �ڷ� ����" << endl;
	cout << "==================================================================" << endl;
	cout << "�����Ͻ� ������ ��ȣ�� �Է��� �ּ���." << endl;
	cout << "=> ";
}

// ���ϸ� ���� â
void InHospital() {
	system("cls");
	cout << "==============================================================================================" << endl;
	cout << "                                     ���ϸ� ����" << endl;
	cout << "==============================================================================================" << endl;
	cout << endl << "                            ���ϸ��� ��� ȸ���Ǿ����ϴ�." << endl << endl;
}

void InBackPack(CPlayer player)
{
	system("cls");
	cout << "============================================!!����!!============================================" << endl;
	cout << "                ���濡���� ���� ������ ���ǵ��� ������ �� �� �ֽ��ϴ�." << endl;
	cout << "================================================================================================" << endl;
	cout << "ȸ���� :: " << player.GetNorRecDrug()->GetPossessNum() << "��" << endl;
	cout << "��� ȸ���� :: " << player.GetHighRecDrug()->GetPossessNum() << "��" << endl;
	cout << "���ͺ� :: " << player.GetNorMonsterBall()->GetPossessNum() << "��" << endl;
	cout << "�����ۺ� :: " << player.GetHyperBall()->GetPossessNum() << "��" << endl;
	cout << "�����ͺ� :: " << player.GetMasterBall()->GetPossessNum() << "��" << endl;
	cout << "==================================================================" << endl;
	cout << "1. �ڷ� ����" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

int MeetPocketMonProbability()
{
	int num;
	srand((unsigned int)time(0));
	num = rand() % 9 + 1;
	return num;
}

int LevelPlusMinusFive(CPlayer player)
{
	int num;
	srand((unsigned int)time(0));
	// ������ 5 �̸��̸� 1 ~ 6 ������ ���Ͱ� �����Ѵ�.
	if (player.GetRepPocketMon()->GetLevel() <= 5)
		num = rand() % (player.GetRepPocketMon()->GetLevel() + 5) + 1;
	// ������ 45 �̻��̸� 45 ~ 50 ������ ���Ͱ� �����Ѵ�.
	else if (player.GetRepPocketMon()->GetLevel() >= 45)
		num = rand() % 5 + 45;
	// �� �ܿ��� (���� - 5) ~ (���� + 5) ������ ���Ͱ� �����Ѵ�.
	else
	{
		int temp = player.GetRepPocketMon()->GetLevel() - 5;
		num = temp + rand() % 11;
	}
	return num;
}

void InBattleMenu(CPlayer player, CMonster* monster)
{
	system("cls");
	cout << "==================================================================" << endl;
	cout << "�߻��� " << monster->GetName() << "�� ��Ÿ����!!!!!" << endl;
	cout << "���ϸ� �̸� : " << monster->GetName() << "   LEVEL : " << monster->GetLevel() << endl;
	cout << "HP : (" << monster->GetHP() << " / " << monster->GetMaxHP() << ")" << endl;
	cout << "==================================================================" << endl;
	cout << "���� ���ϸ�" << endl;
	cout << "���ϸ� �̸� : " << player.GetRepPocketMon()->GetName() << "   LEVEL : " << player.GetRepPocketMon()->GetLevel() << endl;
	cout << "HP : (" << player.GetRepPocketMon()->GetHP() << " / " << player.GetRepPocketMon()->GetMaxHP() << ")" << endl;
	cout << "==================================================================" << endl;
	cout << "1. ����" << endl;
	cout << "2. ����" << endl;
	cout << "3. ����" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}


int RunProbability()
{
	int num;
	srand((unsigned int)time(0));
	num = rand() % 100 + 1;
	return num;
}

void InBattleBackPack(CPlayer player)
{
	system("cls");
	cout << "==================================================================" << endl;
	cout << "                             ����" << endl;
	cout << "==================================================================" << endl;
	cout << "���� ������ ���" << endl;
	cout << "1. ȸ���� : " << player.GetNorRecDrug()->GetPossessNum() << "��" << endl;
	cout << "2. ��� ȸ���� : " << player.GetHighRecDrug()->GetPossessNum() << "��" << endl;
	cout << "3. ���ͺ� : " << player.GetNorMonsterBall()->GetPossessNum() << "��" << endl;
	cout << "4. �����ۺ� : " << player.GetHyperBall()->GetPossessNum() << "��" << endl;
	cout << "5. �����ͺ� : " << player.GetMasterBall()->GetPossessNum() << "��" << endl;
	cout << "==================================================================" << endl;
	player.ShowPlayerPocketMonInBattle();
	cout << "         ȸ������ ��ǥ ���ϸ󿡰Ը� ����� �����մϴ�." << endl;
	cout << "1. ȸ���� ���" << endl;
	cout << "2. ��� ȸ���� ���" << endl;
	cout << "3. ���ͺ� ���" << endl;
	cout << "4. �����ۺ� ���" << endl;
	cout << "5. �����ͺ� ���" << endl;
	cout << "6. �ڷΰ���" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}