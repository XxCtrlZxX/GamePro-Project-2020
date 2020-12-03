#include "stdafx.h"
#include "GameManager.h"
#include "OverScene.h"
#include "Random.h"

GameManager::GameManager()
{
}

GameManager* GameManager::GetInstance()
{
	/* if (instance == nullptr) {
		static GameManager gmr;
		instance = &gmr;
	}
	return instance; */

	static GameManager gmr;
	return &gmr;
}

void GameManager::Init()
{
	GameManager* i = GetInstance();

	i->currentTurn = 0;
	i->maxTurn = MAX_TURN;
	i->score = MAX_TURN;
}

void GameManager::AddScore(int d)
{
	GameManager* i = GetInstance();

	i->score += d;
	i->scoreText->UpdateScore();

	if (i->score <= 0)
		Scene::ChangeScene(new OverScene());	// ���� ����
}

void GameManager::GameManagerUpdate()
{
	// ���� �� ������ �� ����
	GameManager* i = GetInstance();

	// ��� ���� ������ üũ
	bool flag = true;
	for (int k = 1; k < i->coins.size() - 1; k++) {
		// ���� �Ͱ� ���� ���� ������ -> �ٸ��� flag = false
		if (i->coins[k]->GetCurrentCur() != i->coins[k + 1]->GetCurrentCur()) {
			flag = false;
			break;
		}
	}

	if (flag)
		std::cout << "���� Ŭ����!" << std::endl;

	if (i->currentTurn % TURN_INTERVAL == TURN_INTERVAL - 1)	// �� �Ͽ� �� ���� Ÿ�� ����
		i->tile->FadeIn(Random::Range(0, 8));
	else if (i->currentTurn % TURN_INTERVAL == 0)	// �� �������� �� �����
		i->tile->FadeOut();
}

void GameManager::PutScoreText(ScoreText* st)
{
	GetInstance()->scoreText = st;
}

void GameManager::PutCoins(std::vector<Coin*> &c)
{
	GetInstance()->coins = c;
}

void GameManager::PutTile(Tile* t)
{
	GetInstance()->tile = t;
}