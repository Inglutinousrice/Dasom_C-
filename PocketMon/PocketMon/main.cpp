
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <string>

#define POSSESS_MAX		999 // 아이템 소지 최대 용량
#define SECOND_EVOLUTION	17	// 두번째 진화 레벨
#define LAST_EVOLUTION		37 // 마지막 진화 레벨

using namespace std;

/*
질문사항 : *****************동적 할당 해제하는 시점(방법)*****************
				    어플리케이션 클래스에 몽땅 옮겨서 실행하는 방법

구현하지 못한 부분
	-	타입에 따른 데미지 증감
	-	벨런스 조정
	-	각각의 포켓몬들의 스킬
	-	진화
	-	풀 회복약 회복양
*/

// 포켓몬 종료 enum문
enum POCKETMON_KIND
{
	PK_NONE,
	PK_TORCHIC, // 아차모
	PK_COMBUSKEN, // 영치코
	PK_BLAZIKEN, // 번치고
	PK_MUDKIP, // 물짱이
	PK_MARSHTOMP, // 늪짱이
	PK_SWAMPERT, // 대짱이
	PK_TREECKO, // 나무지기
	PK_GROVYLE, // 나무돌이
	PK_SCEPTILE, // 나무킹
	PK_LAST
};

// 포켓몬 타입 enum문
enum POCKETMON_TYPE
{
	PT_NONE,
	PT_FIRE, // 1 불
	PT_WATER, // 2 물
	PT_GRASS, // 3 물
	PT_LAST
};

// 시작 포켓몬 enum문
enum START_POCKETMON
{
	SP_NONE,
	SP_TORCHIC, // 아차모
	SP_MUDKIP, // 물짱이
	SP_TREECKO, // 나무지기
	SP_LAST
};

// 메인 메뉴 enum문
enum MAIN_MENU
{
	MM_NONE,
	MM_ADVENTURE, // 모험 떠나기
	MM_CHECK_PHOCKETMON, // 포켓몬 확인하기
	MM_BACKPACK, // 가방 확인하기
	MM_STORE, // 상점 가기
	MM_HOSPITAL, // 병원 가기
	MM_EXIT, // 종료
	MM_LAST
};

// 상점 enum문
enum MAIN_STORE
{
	MS_NONE,
	MS_NORMAL_RECOVERY_DRUG, // 회복약
	MS_HIGH_RECOVERY_DRUG, // 고급 회복약
	MS_MONSTER_BALL, // 몬스터볼
	MS_HYPER_BALL, // 하이퍼볼
	MS_MASTER_BALL, // 마스터볼
	MS_EXIT, // 종료
	MS_LAST
};


/*
상점에서는 회복약하고 몬스터볼을 팔 것이다.
회복약의 종류에는 치료약, 고급 치료약, 풀 회복약 총 세 종류이며
몬스터볼의 종류에는 몬스터볼, 하이퍼볼, 마스터볼 총 세 종류가 있다.
치료약은 체력을 100 회복해주고, 고급 치료약은 체력을 500 회복해주며, 풀 회복약은 최대체력까지 회복시켜 준다.
가격은 각각 200G, 700G, 2000G이다.
몬스터볼은 각각의 볼 마다 잡을 확률이 다른데,
몬스터볼은 30%의 확률로 성공하고, 하이퍼볼은 40%확률도 성공하며, 마스터볼은 100%의 확률로 성공하게 된다.
가격은 각각 200G, 700G, 8000G이다.
*/

// ============================================회복약 클래스============================================
class CRecoveryDrug
{
protected:
	int m_HealAmount; // 회복 양
	int m_PossessNum; // 현재 소지 개수
	int m_Price; // 가격
public:
	// 힐 양 리턴 함수
	int GetHealAmount() { return m_HealAmount; }

	// 개수 관리
	int GetPossessNum() { return m_PossessNum; }
	void PlusPossessNum() { ++m_PossessNum; }
	void MinusPossessNum() { --m_PossessNum; }

	// 가격 리턴
	int GetPrice() { return m_Price; }

};


// 일반 치료약 클래스
class CNormalRecoveryDrug
	: public CRecoveryDrug
{
public:
	CNormalRecoveryDrug() { m_HealAmount = 100; m_PossessNum = 2; m_Price = 200; }

};


// 고급 치료약 클래스
class CHighRecoveryDrug
	:public CRecoveryDrug
{
public:
	CHighRecoveryDrug() { m_HealAmount = 500; m_PossessNum = 0; m_Price = 700; }

};


// ============================================몬스터볼 클래스============================================
class CMonsterBall
{
protected:
	int m_CatchProbability; // 잡을 확률
	int m_PossessNum; // 현재 소지 개수
	int m_Price; // 가격

public:
	// 확률 가져오는 함수
	int GetCatchProbability() { return m_CatchProbability; }

	// 개수 관리
	int GetPossessNum() { return m_PossessNum; }
	void PlusPossessNum() { ++m_PossessNum; }
	void MinusPossessNum() { --m_PossessNum; }

	// 가격 리턴
	int GetPrice() { return m_Price; }

};


// 일반 몬스터볼 클래스
class CNormalMonsterBall
	: public CMonsterBall
{
public:
	CNormalMonsterBall() { m_CatchProbability = 30; m_PossessNum = 5; m_Price = 200; }
};


// 하이퍼볼 클래스
class CHyperBall
	: public CMonsterBall
{
public:
	CHyperBall() { m_CatchProbability = 40; m_PossessNum = 0; m_Price = 700; }
};


// 마스터볼 클래스
class CMasterBall
	: public CMonsterBall
{
public:
	CMasterBall() { m_CatchProbability = 100; m_PossessNum = 0; m_Price = 8000; }
};


// ============================================몬스터 클래스============================================
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
	// 스펙업 함수
	void PocketMonSpecUp(CMonster* monster)
	{
		monster->SetHP(monster->GetLevel() * 100);
		monster->SetAttack(monster->GetLevel() * 5);
		monster->SetEXP(0);
		monster->SetMaxHP(monster->GetLevel() * 100);
		monster->SetGold(monster->GetLevel() * 10);
		monster->SetMaxEXP(monster->GetLevel() * 10);
	}

	// HP 함수
	int GetHP(){ return m_HP; }
	void SetHP(int HP) { m_HP = HP; }

	// Attack 함수
	int GetAttack(){ return m_Attack; }
	void SetAttack(int attack) { m_Attack = attack; }

	// Type 함수
	int GetType() { return m_Type; }
	void SetType(int type) { m_Type = type; }

	// Level 함수
	int GetLevel() { return m_Level; }
	void SetLevel(int level) { m_Level = level; }

	// maxHP 함수
	int GetMaxHP() { return m_MaxHP; }
	void SetMaxHP(int maxHP) { m_MaxHP = maxHP; }

	// EXP 함수
	int GetEXP() { return m_EXP; }
	void SetEXP(int EXP) { m_EXP = EXP; }

	// MaxEXP 함수
	int GetMaxEXP() { return m_MaxEXP; }
	void SetMaxEXP(int maxEXP) { m_MaxEXP = maxEXP; }

	// Gold 함수
	int GetGold() { return m_Gold; }
	void SetGold(int gold) { m_Gold = gold; }

	// Name함수
	string GetName() { return m_Name; }

	// 동적할당 해제 함수
	void DeletePocketMon(CMonster* monster)
	{
		delete[] monster;
		monster = nullptr;
	}
};


// ============================================아차모 클래스 1-16============================================
class CTorchic
	: public CMonster
{
private:

public:
	CTorchic(int level)
	{
		m_Name = "아차모";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};
 
// ============================================영치코 클래스 17-36============================================
class CCombusken
	: public CMonster
{
private:

public:
	CCombusken(int level)
	{
		m_Name = "영치코";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================번치코 클래스 37-50============================================
class CBlaziken
	: public CMonster
{
private:

public:
	CBlaziken(int level)
	{
		m_Name = "번치코";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================물짱이 클래스 1-16============================================
class CMudkip
	: public CMonster
{
private:

public:
	CMudkip(int level)
	{
		m_Name = "물짱이";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================늪짱이 클래스 17-36============================================
class CMarshtomp
	: public CMonster
{
private:

public:
	CMarshtomp( int level )
	{
		m_Name = "늪짱이";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================대짱이 클래스 37-50============================================
class CSwampert
	: public CMonster
{
private:

public:
	CSwampert( int level )
	{
		m_Name = "대짱이";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};
 
// ============================================나무지기 클래스 1-16============================================
class CTreecko
	: public CMonster
{
private:

public:
	CTreecko(int level )
	{
		m_Name = "나무지기";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================나무돌이 클래스 17-36============================================
class CGrovyle
	: public CMonster
{
private:

public:
	CGrovyle(int level)
	{
		m_Name = "나무돌이";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================나무킹 클래스 37-50============================================
class CSceptile
	: public CMonster
{
private:

public:
	CSceptile(int level)
	{
		m_Name = "나무킹";
		m_HP = level * 100;
		m_Attack = level * 5;
		m_Level = level;
		m_EXP = 0;
		m_Gold = level * 10;
		m_MaxHP = level * 100;
		m_MaxEXP = level * 10;
	}
};

// ============================================플레이어 클래스============================================
class CPlayer
{
private:
	CMonster* monsterArr[6] = {};
	string m_Name = "김지완";
	int m_Gold = 500;
	int m_pocketMonNum = 0;
	CRecoveryDrug* norRecDrug = new CNormalRecoveryDrug;
	CRecoveryDrug* highRecDrug = new CHighRecoveryDrug;
	CMonsterBall* norBall = new CNormalMonsterBall;
	CMonsterBall* hyperBall = new CHyperBall;
	CMonsterBall* masterBall = new CMasterBall;

public:
	// 레벨업 함수
	void RepPocketMonLevelUp()
	{
		monsterArr[0]->SetLevel(monsterArr[0]->GetLevel() + 1);
		monsterArr[0]->PocketMonSpecUp(monsterArr[0]);
	}

	// 경험치 얻는 함수
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

	// 골드 얻는 함수
	void GoldPlus(CMonster* monster)
	{
		m_Gold = m_Gold + monster->GetGold();
	}

	// 입력받은 인덱스의 포켓몬이 살아 있는지 알아보기
	bool IsPocketMonLive(int idx)
	{
		if (monsterArr[idx - 1]->GetHP() != 0)
			return true;
		
		return false;
	}

	// 교체 가능한 포켓몬 누구 있는지 살펴보기
	void PocketMonWhoCanChange()
	{
		system("cls");
		cout << "=========================현재 포켓몬 상태=========================" << endl;
		for (int i = 0; i < m_pocketMonNum; ++i)
			cout << i + 1 << ". " << monsterArr[i]->GetName() << "  LEVEL : " << monsterArr[i]->GetLevel() << "  HP : " << monsterArr[i]->GetHP() << " / " << monsterArr[i]->GetMaxHP() << endl;
		cout << "==================================================================" << endl;
		cout << "교체할 포켓몬 번호를 입력해 주세요" << endl;
		cout << "==================================================================" << endl;
		cout << "=> ";
	}

	// 교체 가능한 포켓몬이 있는지 알아보기
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

	// 일반 회복약 가져오기
	CRecoveryDrug* GetNorRecDrug() { return norRecDrug; }

	// 고급 회복약 가져오기
	CRecoveryDrug* GetHighRecDrug() { return highRecDrug; }

	// 몬스터볼 가져오기
	CMonsterBall* GetNorMonsterBall() { return norBall; }

	// 하이퍼볼 가져오기
	CMonsterBall* GetHyperBall() { return hyperBall; }

	// 마스터볼 가져오기
	CMonsterBall* GetMasterBall() { return masterBall; }

	// 포켓몬센터 함수(몽땅 회복)
	void PocketMonCenter()
	{
		for (int i = 0; i < m_pocketMonNum; ++i)
			monsterArr[i]->SetHP(monsterArr[i]->GetMaxHP());
	}

	// 대표 포켓몬 바꿔주는 함수
	void ChangeRepPocketMon(int changeNum)
	{
		CMonster* temp = monsterArr[0];
		monsterArr[0] = monsterArr[changeNum-1];
		monsterArr[changeNum-1] = temp;
	}

	// 포켓몬 판매하는 함수
	void sellPocketMon(int sellNum)
	{
		m_Gold += monsterArr[sellNum - 1]->GetGold();
		monsterArr[sellNum - 1] = monsterArr[m_pocketMonNum - 1];
		monsterArr[m_pocketMonNum - 1] = nullptr;
		SubPocketMonNum();
	}

	// 대표 포켓몬 반환 함수
	CMonster* GetRepPocketMon() { return monsterArr[0]; }

	// Gold 함수
	int GetGold() { return m_Gold; }
	void SetGold(int gold) { m_Gold = gold; }

	// 포켓몬 추가 함수
	void AddPocketMon(CMonster* newMonster) { monsterArr[m_pocketMonNum - 1] = newMonster; }

	// 포켓몬숫자 증가 함수
	void AddPocketMonNum() { ++m_pocketMonNum; }

	// 포켓몬숫자 감소 함수
	void SubPocketMonNum() { --m_pocketMonNum; }

	// m_PocketMonNum  반환 함수
	int GetPocketMonNum() { return m_pocketMonNum; }

	
	// 2번 메뉴에서 보유 포켓몬 보여주는 함수
	void ShowPlayerPocketMon()
	{
		system("cls");
		cout << "============================================현재 보유 포켓몬============================================" << endl;
		cout << "                             1번에 오는 포켓몬이 대표 포켓몬이 됩니다." << endl;
		cout << "                  포켓몬 순서 교체는 1번 포켓몬과 1번이 아닌 포켓몬끼리만 가능합니다." << endl << endl;
		cout << "보유 포켓몬 수 :: " << m_pocketMonNum << endl;
		cout << "=======================================================================================================" << endl;
		for (int i = 0; i < m_pocketMonNum; ++i)
			cout << i + 1 << ". " << monsterArr[i]->GetName() << "  LEVEL : " << monsterArr[i]->GetLevel() << "  HP : " << monsterArr[i]->GetHP() << " / " << monsterArr[i]->GetMaxHP() << "  EXP : " << monsterArr[i]->GetEXP() << " / " << monsterArr[i]->GetMaxEXP() << endl;
		cout << "=======================================================================================================" << endl;
	}

	// 전투 중 보유 포켓몬 보여주는 함수
	void ShowPlayerPocketMonInBattle()
	{
		cout << "=========================현재 보유 포켓몬=========================" << endl;
		for (int i = 0; i < m_pocketMonNum; ++i)
			cout << i + 1 << ". " << monsterArr[i]->GetName() << "  LEVEL : " << monsterArr[i]->GetLevel() << "  HP : " << monsterArr[i]->GetHP() << " / " << monsterArr[i]->GetMaxHP() << endl;
		cout << "==================================================================" << endl;
	}
};



// 함수 선언
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


	// ============================================시작 포켓몬 고르기============================================
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
			cout << "잘못 고른 것 같군요,,,," << endl;
			system("pause");
			break;
		}
		}
	}

	// ============================================!!! 시작 !!!============================================





	// 테스트용
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

		// ============================================1. 모험 떠나기============================================
		// 항상 플레이어가 선공
		case MM_ADVENTURE: {
			int inBattleMenu;
			
			int meetWho = MeetPocketMonProbability();
			switch (meetWho)
			{
			// 아차모 만남 
			case PK_TORCHIC: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* torchic = new CTorchic(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, torchic);		cin >> inBattleMenu;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (torchic->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								torchic->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								torchic->SetHP(torchic->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << torchic->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(torchic);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(torchic);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(torchic);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, torchic);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - torchic->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - torchic->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << torchic->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && torchic->GetHP() != 0)
						{
							InBattleMenu(player, torchic);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && torchic->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && torchic->GetHP() == 0)
						{
							cout << "야생의 " << torchic->GetName() << "을 물리쳤습니다!!!" << endl;
							player.GoldPlus(torchic);
							player.EXPPlus(player, torchic);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// 영치코 만남
			case PK_COMBUSKEN: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* combusken = new CCombusken(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, combusken);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (combusken->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								combusken->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								combusken->SetHP(combusken->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << combusken->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(combusken);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(combusken);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(combusken);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, combusken);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - combusken->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - combusken->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << combusken->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && combusken->GetHP() != 0)
						{
							InBattleMenu(player, combusken);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && combusken->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && combusken->GetHP() == 0)
						{
							cout << "야생의 " << combusken->GetName() << "을 물리쳤습니다!!!" << endl;
							player.GoldPlus(combusken);
							player.EXPPlus(player, combusken);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// 번치코 만남
			case PK_BLAZIKEN: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* blaziken = new CBlaziken(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, blaziken);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (blaziken->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								blaziken->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								blaziken->SetHP(blaziken->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << blaziken->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(blaziken);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(blaziken);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(blaziken);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, blaziken);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - blaziken->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - blaziken->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << blaziken->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && blaziken->GetHP() != 0)
						{
							InBattleMenu(player, blaziken);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && blaziken->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && blaziken->GetHP() == 0)
						{
							cout << "야생의 " << blaziken->GetName() << "을 물리쳤습니다!!!" << endl;
							player.GoldPlus(blaziken);
							player.EXPPlus(player, blaziken);
							system("pause");
							break;
						}
					}
				}
				break;
			}

			// 물짱이 만남
			case PK_MUDKIP: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* mudkip = new CMudkip(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, mudkip);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (mudkip->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								mudkip->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								mudkip->SetHP(mudkip->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << mudkip->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(mudkip);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(mudkip);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(mudkip);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, mudkip);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - mudkip->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - mudkip->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << mudkip->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && mudkip->GetHP() != 0)
						{
							InBattleMenu(player, mudkip);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && mudkip->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && mudkip->GetHP() == 0)
						{
							cout << "야생의 " << mudkip->GetName() << "을 물리쳤습니다!!!" << endl;
							player.GoldPlus(mudkip);
							player.EXPPlus(player, mudkip);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// 늪짱이 만남
			case PK_MARSHTOMP: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* marshtomop = new CMarshtomp(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, marshtomop);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (marshtomop->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								marshtomop->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								marshtomop->SetHP(marshtomop->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << marshtomop->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(marshtomop);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(marshtomop);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(marshtomop);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, marshtomop);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - marshtomop->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - marshtomop->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << marshtomop->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && marshtomop->GetHP() != 0)
						{
							InBattleMenu(player, marshtomop);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && marshtomop->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && marshtomop->GetHP() == 0)
						{
							cout << "야생의 " << marshtomop->GetName() << "을 물리쳤습니다!!!" << endl;
							player.GoldPlus(marshtomop);
							player.EXPPlus(player, marshtomop);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// 대짱이 만남
			case PK_SWAMPERT: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* swampert = new CSwampert(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, swampert);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (swampert->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								swampert->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								swampert->SetHP(swampert->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << swampert->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(swampert);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(swampert);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(swampert);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, swampert);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - swampert->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - swampert->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << swampert->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && swampert->GetHP() != 0)
						{
							InBattleMenu(player, swampert);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && swampert->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && swampert->GetHP() == 0)
						{
							cout << "야생의 " << swampert->GetName() << "을 물리쳤습니다!!!" << endl;
							player.GoldPlus(swampert);
							player.EXPPlus(player, swampert);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// 나무지기 만남
			case PK_TREECKO: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* treecko = new CTreecko(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, treecko);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (treecko->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								treecko->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								treecko->SetHP(treecko->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << treecko->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(treecko);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(treecko);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(treecko);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, treecko);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - treecko->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - treecko->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << treecko->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && treecko->GetHP() != 0)
						{
							InBattleMenu(player, treecko);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && treecko->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && treecko->GetHP() == 0)
						{
							cout << "야생의 " << treecko->GetName() << "을 물리쳤습니다!!!" << endl;
							player.GoldPlus(treecko);
							player.EXPPlus(player, treecko);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// 나무돌이 만남
			case PK_GROVYLE: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* grovyle = new CGrovyle(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, grovyle);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (grovyle->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								grovyle->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								grovyle->SetHP(grovyle->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << grovyle->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(grovyle);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(grovyle);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(grovyle);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, grovyle);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - grovyle->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - grovyle->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << grovyle->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && grovyle->GetHP() != 0)
						{
							InBattleMenu(player, grovyle);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && grovyle->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && grovyle->GetHP() == 0)
						{
							cout << "야생의 " << grovyle->GetName() << "을 물리쳤습니다!!!" << endl;
							player.GoldPlus(grovyle);
							player.EXPPlus(player, grovyle);
							system("pause");
							break;
						}
					}
				}

				break;
			}

			// 나무킹 만남
			case PK_SCEPTILE: {
				bool playerTurn = true;
				bool enemyTurn = false;

				bool bInBattleMenu = true;
				int level = LevelPlusMinusFive(player);
				CMonster* sceptile = new CSceptile(level);

				// 아차모와의 하나의 배틀이 진행되는 동안
				while (bInBattleMenu)
				{
					InBattleMenu(player, sceptile);		cin >> inBattleMenu;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					// 플레이어 턴
					while (playerTurn)
					{
						// 공격
						if (inBattleMenu == 1)
						{

							// 공격했는데 상대방의 HP가 0보다 작아지면 -> 0으로 만들고 이김
							if (sceptile->GetHP() - player.GetRepPocketMon()->GetAttack() <= 0)
							{
								sceptile->SetHP(0);
								playerTurn = false;
								enemyTurn = false;
							}

							// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
							else
							{
								sceptile->SetHP(sceptile->GetHP() - player.GetRepPocketMon()->GetAttack());
								playerTurn = false;
								enemyTurn = true;
								cout << player.GetRepPocketMon()->GetName() << "의 공격!!!!!!" << endl;
								cout << sceptile->GetName() << "의 체력이 " << player.GetRepPocketMon()->GetAttack() << "만큼 달았다!!!" << endl;
								system("pause");
							}
						}

						// 가방
						// 구현 완료
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

							// 회복약 사용
							if (inBattleBackPackMenu == 1)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetNorRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetNorRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetNorRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 고급 회복약 사용
							if (inBattleBackPackMenu == 2)
							{
								// 회복약이 빵개다?! or 대표포켓몬이 최대체력이다?! -> 사용불가 다시 자기턴
								if (player.GetHighRecDrug()->GetPossessNum() == 0 || player.GetRepPocketMon()->GetHP() == player.GetRepPocketMon()->GetMaxHP())
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 회복했는데 최대체력을 넘어간다?!
								else if (player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount() > player.GetRepPocketMon()->GetMaxHP())
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetMaxHP());
									playerTurn = false;
									enemyTurn = true;
								}

								// 그 외 일반적으로 사용
								else
								{
									player.GetHighRecDrug()->MinusPossessNum();
									player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() + player.GetHighRecDrug()->GetHealAmount());
									playerTurn = false;
									enemyTurn = true;
								}
							}

							// 몬스터볼 사용
							if (inBattleBackPackMenu == 3)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetNorMonsterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetNorMonsterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetNorMonsterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(sceptile);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 하이퍼볼 사용
							if (inBattleBackPackMenu == 4)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetHyperBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetHyperBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetHyperBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(sceptile);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}

							// 마스터볼 사용
							if (inBattleBackPackMenu == 5)
							{

								// 확률 잡아놓기
								int catchProbability = ProbabilityOneToHundred();

								// 몬스터볼이 0개다?! or 이미 6마리가 꽉 차버렸다?! -> 다시 처음화면으로
								if (player.GetMasterBall()->GetPossessNum() == 0 || player.GetPocketMonNum() == 6)
								{
									cout << "아이템을 사용할 수 없습니다." << endl;
									system("pause");
								}

								// 실패하면 턴 종료
								else if (catchProbability > player.GetMasterBall()->GetCatchProbability())
								{
									cout << "잡는데에 실패했다!!!" << endl;
									playerTurn = false;
									enemyTurn = true;
									system("pause");
								}

								// 성공하면 포켓몬 배열에 추가하고 전투 종료
								else if (catchProbability <= player.GetMasterBall()->GetCatchProbability())
								{
									player.AddPocketMonNum();
									player.AddPocketMon(sceptile);
									cout << "포켓몬을 잡았다!!!!" << endl;
									playerTurn = false;
									enemyTurn = false;
									system("pause");
								}
							}
						}

						// 도망
						if (inBattleMenu == 3)
						{
							if (RunProbability() <= 80)
							{
								cout << "도망에 성공했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = false;
								system("pause");
								break;
							}
							else
							{
								cout << "도망에 실패했다!!!!" << endl;
								playerTurn = false;
								enemyTurn = true;
								system("pause");
							}
						}
					}

					// 몬스터 턴
					while (enemyTurn)
					{
						InBattleMenu(player, sceptile);
						// 공격했는데 나의 HP가 0보다 작아지면 -> 0으로 만들고 교체하게 해줌 
						// 교체할 친구들이 없으면 패배된 후 게임 꺼짐
						if (player.GetRepPocketMon()->GetHP() - sceptile->GetAttack() <= 0)
						{

							// 교체가 불가능한 상태이면(교체할 포켓몬이 더이상 없으면) 져버린다.
							player.GetRepPocketMon()->SetHP(0);
							if (!player.IsLivePocketMonThere())
							{
								playerTurn = false;
								enemyTurn = false;
							}

							// 교체가 가능하다면 교체 가능한 포켓몬들을 보여준 후  
							// 교체할 포켓몬을 대표 포켓몬으로 옮겨서 교체시켜준다. 턴은 적의 턴으로 시작한다.
							else if (player.IsLivePocketMonThere())
							{
								int pocketMonWhoCanChange;
								player.PocketMonWhoCanChange();		cin >> pocketMonWhoCanChange;
								if (cin.fail()) {
									cin.clear();
									cin.ignore(1024, '\n');
									continue;
								}
								// 입력 받은 포켓몬이 살아 있다면 대표 포켓몬으로 바꾸어준다.
								if (player.IsPocketMonLive(pocketMonWhoCanChange))
								{
									player.ChangeRepPocketMon(pocketMonWhoCanChange);
									playerTurn = true;
									enemyTurn = false;
								}
								else
								{
									cout << "그 포켓몬은 이미 죽어있습니다. " << endl;
									system("pause");
								}

							}
						}

						// 그게 아니라면 걍 피를 깎고 턴 넘긴다.
						else
						{
							player.GetRepPocketMon()->SetHP(player.GetRepPocketMon()->GetHP() - sceptile->GetAttack());
							playerTurn = true;
							enemyTurn = false;
							cout << "상대방의 공격!!!!!!" << endl;
							cout << player.GetRepPocketMon()->GetName() << "의 체력이 " << sceptile->GetAttack() << "만큼 달았다!!!" << endl;
							system("pause");
						}

					}

					// playerTurn, enemyTurn 모두 false인 경우(둘 중 하나가 죽어서 전투가 끝나면)
					// 플레이어의 대표포켓몬 체력이 0이면 플레이어의 패배 -> 게임 꺼진다
					// 적의 체력이 0이면 플레이어의 승리 -> 경험치와 골드를 얻고 메인화면으로
					// 둘다 0이 아니면 도망 or 잡는데 성공 -> 걍 메인화면으로

					if (!playerTurn && !enemyTurn)
					{
						// 플레이어의 패배
						if (player.GetRepPocketMon()->GetHP() == 0 && sceptile->GetHP() != 0)
						{
							InBattleMenu(player, sceptile);
							cout << "다음에 다시 만나요!!!!" << endl;
							exit(0);
						}
						// 둘다 0이 아니면
						else if (player.GetRepPocketMon()->GetHP() != 0 && sceptile->GetHP() != 0)
						{
							bInBattleMenu = false;
							break;
						}

						// 플레이어의 승리
						// 경험치와 골드를 얻는다.
						// 레벨업을 할 경우 레벨업 함수를 실행시켜준다.
						else if (player.GetRepPocketMon() != 0 && sceptile->GetHP() == 0)
						{
							cout << "야생의 " << sceptile->GetName() << "을 물리쳤습니다!!!" << endl;
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

		// ============================================2. 포켓몬 확인하기============================================
		// ============================================구현 완료============================================
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

				// 대표 포켓몬 교체
				if (inPlayerPocketMon == 1)
				{
					if (player.GetPocketMonNum() == 1) {
						cout << "교체할 수 있는 포켓몬이 없습니다." << endl;
						system("pause");
						break;
					}
					cout << "교체할 포켓몬의 번호를 입력해주세요." << endl;
					int changePocketMonNum;
					cout << "=> ";		cin >> changePocketMonNum;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					if (changePocketMonNum <= 0 || player.GetPocketMonNum() < changePocketMonNum)
					{
						cout << "잘못 고른 것 같군요,,,," << endl;
						system("pause");
						break;
					}

					player.ChangeRepPocketMon(changePocketMonNum);
					player.ShowPlayerPocketMon();
					bSelectInCheck = false;
				}

				// 포켓몬 팔기
				else if (inPlayerPocketMon == 2)
				{
					if (player.GetPocketMonNum() == 1) {
						cout << "판매할 수 있는 포켓몬이 없습니다." << endl;
						system("pause");
						break;
					}
					cout << "판매할 포켓몬의 번호를 입력해주세요." << endl;
					int sellPocketMonNum;
					cout << "=> ";		cin >> sellPocketMonNum;
					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}

					if (sellPocketMonNum <= 0 || player.GetPocketMonNum() < sellPocketMonNum)
					{
						cout << "잘못 고른 것 같군요,,,," << endl;
						system("pause");
						break;
					}

					player.sellPocketMon(sellPocketMonNum);
					player.ShowPlayerPocketMon();
					bSelectInCheck = false;
				}
				else
				{
					cout << "잘못 고른 것 같군요,,,," << endl;
					system("pause");
					break;
				}
			}
			break;
		}

		//============================================3. 가방 가기============================================
		// ============================================구현 완료============================================
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
					cout << "잘못 고른 것 같군요,,,," << endl;
					system("pause");
				}
			}
			break;
		}

		// ============================================4. 상점 가기============================================
		// ============================================구현 완료============================================
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
				// 일반 회복약
				case MS_NORMAL_RECOVERY_DRUG: {
					if (player.GetGold() < player.GetNorRecDrug()->GetPrice())
					{
						cout << "돈이 부족합니다." << endl;
						system("pause");
						break;
					}

					if (player.GetNorRecDrug()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "더 이상 소지할 수 없습니다." << endl;
						system("pause");
						break;
					}

					player.GetNorRecDrug()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetNorRecDrug()->GetPrice());
					cout << "구매가 완료되었습니다." << endl;
					selectShop = false;
					system("pause");
					break;
				}

				// 고급 회복약
				case MS_HIGH_RECOVERY_DRUG: {
					if (player.GetGold() < player.GetHighRecDrug()->GetPrice())
					{
						cout << "돈이 부족합니다." << endl;
						system("pause");
						break;
					}

					if (player.GetHighRecDrug()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "더 이상 소지할 수 없습니다." << endl;
						system("pause");
						break;
					}

					player.GetHighRecDrug()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetHighRecDrug()->GetPrice());
					cout << "구매가 완료되었습니다." << endl;
					selectShop = false;
					system("pause");
					break;
				}

				// 일반 몬스터볼
				case MS_MONSTER_BALL: {
					if (player.GetGold() < player.GetNorMonsterBall()->GetPrice())
					{
						cout << "돈이 부족합니다." << endl;
						system("pause");
						break;
					}

					if (player.GetNorMonsterBall()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "더 이상 소지할 수 없습니다." << endl;
						system("pause");
						break;
					}

					player.GetNorMonsterBall()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetNorMonsterBall()->GetPrice());
					cout << "구매가 완료되었습니다." << endl;
					selectShop = false;
					system("pause");
					break;
				}

				// 하이퍼볼
				case MS_HYPER_BALL: {
					if (player.GetGold() < player.GetHyperBall()->GetPrice())
					{
						cout << "돈이 부족합니다." << endl;
						system("pause");
						break;
					}

					if (player.GetHyperBall()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "더 이상 소지할 수 없습니다." << endl;
						system("pause");
						break;
					}

					player.GetHyperBall()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetHyperBall()->GetPrice());
					cout << "구매가 완료되었습니다." << endl;
					selectShop = false;
					system("pause");
					break;
				}

				// 마스터볼
				case MS_MASTER_BALL: {
					if (player.GetGold() < player.GetMasterBall()->GetPrice())
					{
						cout << "돈이 부족합니다." << endl;
						system("pause");
						break;
					}

					if (player.GetMasterBall()->GetPossessNum() == POSSESS_MAX)
					{
						cout << "더 이상 소지할 수 없습니다." << endl;
						system("pause");
						break;
					}

					player.GetMasterBall()->PlusPossessNum();
					player.SetGold(player.GetGold() - player.GetMasterBall()->GetPrice());
					cout << "구매가 완료되었습니다." << endl;
					selectShop = false;
					system("pause");
					break;
				}
				default:
					cout << "잘못 고른 것 같군요,,,," << endl;
					system("pause");
					break;
				}
			}
			break;
		}

		// ============================================5. 병원 가기============================================
		// ============================================구현 완료============================================
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


// 맨 처음 시작 화면
void StartMenu()
{
	system("cls");
	cout << "==================================================================" << endl << endl;
	cout << "                          포켓몬스터어" << endl << endl;
	cout << "==================================================================" << endl;
	cout << "                         *** 주의 ***" << endl;
	cout << "                      절대 죽지 마십시오." << endl;
	cout << "       한번 죽으면 게임이 종료된 후 처음부터 다시시작합니다." << endl << endl;
	cout << "1. 게임 시작" << endl;
	cout << "1이 아닌 무언가 : 종료" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

// 메인 화면
void MainMenu(CPlayer player)
{
	system("cls");
	cout << "==================================================================" << endl;
	cout << "플레이어 이름 :: 김지완" << endl;
	cout << "보유 골드 :: " << player.GetGold() << "G"<< endl;
	cout << "대표 포켓몬 :: " << player.GetRepPocketMon()->GetName() << endl;
	cout << "LEVLE :: " << player.GetRepPocketMon()->GetLevel() << endl;
	cout << "EXP :: " << player.GetRepPocketMon() ->GetEXP() << " / " << player.GetRepPocketMon()->GetMaxEXP() << endl;
	cout << "==================================================================" << endl;
	cout << "1. 야생으로 떠나기" << endl;
	cout << "2. 나의 포켓몬 확인" << endl;
	cout << "3. 가방 확인" << endl;
	cout << "4. 상점가기" << endl;
	cout << "5. 병원가기" << endl;
	cout << "6. 종료" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

// 스타트 포켓몬 고르는 창
void SelectStartPocketMon()
{
	system("cls");
	cout << "==================================================================" << endl;
	cout << "                 스타트 포켓몬을 골라 봅시다!!!" << endl;
	cout << "            풀타입은 미래에 고통받을 확률이 높습니다." << endl;
	cout << "==================================================================" << endl;
	cout << "1. 아차모 (타입 : 불)" << endl;
	cout << "2. 물짱이 (타입 : 물)" << endl;
	cout << "3. 나무지기 (타입 : 풀)" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

// 1부터 100까지 뽑아주는 함수
int ProbabilityOneToHundred()
{
	int num;
	srand((unsigned int)time(0));
	num = rand() % 100 + 1;
	return num;
}

// 포켓몬 관리 창
void InPlayerPocketMon()
{
	cout << "1. 대표 포켓몬 바꾸기" << endl;
	cout << "2. 포켓몬 팔기" << endl;
	cout << "3. 뒤로가기" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}

// 상점 창
void InShopMenu(CPlayer player)
{
	system("cls");
	cout << "============================================!!상점!!============================================" << endl;
	cout << "                      상점에서는 회복약과 몬스터볼을 판매하고 있습니다." << endl;
	cout << "                  회복약과 몬스터볼은 각각 999개 까지만 소지할 수 있습니다." << endl;
	cout << "================================================================================================" << endl;
	cout << "현재 보유 골드 :: " << player.GetGold() << "G" << endl << endl;
	cout << "1. 회복약(체력을 100 회복합니다.)  200G" << endl;
	cout << "2. 고급 회복약(체력을 500 회복합니다.)  700G" << endl;
	cout << "3. 몬스터 볼  200G" << endl;
	cout << "4. 하이퍼 볼  700G" << endl;
	cout << "5. 마스터 볼  8000G" << endl;
	cout << "6. 뒤로 가기" << endl;
	cout << "==================================================================" << endl;
	cout << "구매하실 물건의 번호를 입력해 주세요." << endl;
	cout << "=> ";
}

// 포켓몬 센터 창
void InHospital() {
	system("cls");
	cout << "==============================================================================================" << endl;
	cout << "                                     포켓몬 센터" << endl;
	cout << "==============================================================================================" << endl;
	cout << endl << "                            포켓몬이 모두 회복되었습니다." << endl << endl;
}

void InBackPack(CPlayer player)
{
	system("cls");
	cout << "============================================!!가방!!============================================" << endl;
	cout << "                가방에서는 현재 소지한 물건들의 개수를 알 수 있습니다." << endl;
	cout << "================================================================================================" << endl;
	cout << "회복약 :: " << player.GetNorRecDrug()->GetPossessNum() << "개" << endl;
	cout << "고급 회복약 :: " << player.GetHighRecDrug()->GetPossessNum() << "개" << endl;
	cout << "몬스터볼 :: " << player.GetNorMonsterBall()->GetPossessNum() << "개" << endl;
	cout << "하이퍼볼 :: " << player.GetHyperBall()->GetPossessNum() << "개" << endl;
	cout << "마스터볼 :: " << player.GetMasterBall()->GetPossessNum() << "개" << endl;
	cout << "==================================================================" << endl;
	cout << "1. 뒤로 가기" << endl;
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
	// 레벨이 5 미만이면 1 ~ 6 레벨의 몬스터가 등장한다.
	if (player.GetRepPocketMon()->GetLevel() <= 5)
		num = rand() % (player.GetRepPocketMon()->GetLevel() + 5) + 1;
	// 레벨이 45 이상이면 45 ~ 50 레벨의 몬스터가 등장한다.
	else if (player.GetRepPocketMon()->GetLevel() >= 45)
		num = rand() % 5 + 45;
	// 그 외에는 (레벨 - 5) ~ (레벨 + 5) 사이의 몬스터가 등장한다.
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
	cout << "야생의 " << monster->GetName() << "가 나타났다!!!!!" << endl;
	cout << "포켓몬 이름 : " << monster->GetName() << "   LEVEL : " << monster->GetLevel() << endl;
	cout << "HP : (" << monster->GetHP() << " / " << monster->GetMaxHP() << ")" << endl;
	cout << "==================================================================" << endl;
	cout << "나의 포켓몬" << endl;
	cout << "포켓몬 이름 : " << player.GetRepPocketMon()->GetName() << "   LEVEL : " << player.GetRepPocketMon()->GetLevel() << endl;
	cout << "HP : (" << player.GetRepPocketMon()->GetHP() << " / " << player.GetRepPocketMon()->GetMaxHP() << ")" << endl;
	cout << "==================================================================" << endl;
	cout << "1. 공격" << endl;
	cout << "2. 가방" << endl;
	cout << "3. 도망" << endl;
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
	cout << "                             가방" << endl;
	cout << "==================================================================" << endl;
	cout << "현재 아이템 목록" << endl;
	cout << "1. 회복약 : " << player.GetNorRecDrug()->GetPossessNum() << "개" << endl;
	cout << "2. 고급 회복약 : " << player.GetHighRecDrug()->GetPossessNum() << "개" << endl;
	cout << "3. 몬스터볼 : " << player.GetNorMonsterBall()->GetPossessNum() << "개" << endl;
	cout << "4. 하이퍼볼 : " << player.GetHyperBall()->GetPossessNum() << "개" << endl;
	cout << "5. 마스터볼 : " << player.GetMasterBall()->GetPossessNum() << "개" << endl;
	cout << "==================================================================" << endl;
	player.ShowPlayerPocketMonInBattle();
	cout << "         회복약은 대표 포켓몬에게만 사용이 가능합니다." << endl;
	cout << "1. 회복약 사용" << endl;
	cout << "2. 고급 회복약 사용" << endl;
	cout << "3. 몬스터볼 사용" << endl;
	cout << "4. 하이퍼볼 사용" << endl;
	cout << "5. 마스터볼 사용" << endl;
	cout << "6. 뒤로가기" << endl;
	cout << "==================================================================" << endl;
	cout << "=> ";
}