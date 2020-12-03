#include "stdafx.h"
#include "Tile.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "GameManager.h"

Tile::Tile() :
	GameObject(L"resources/image/tile_1.png"), alpha(0)
{
	isIn = isOut = false;
	renderer->alpha = 0;
}

Tile::~Tile()
{
}

void Tile::Update()
{
	if (isIn)
	{
		// FadeIn �� �ڸ�
		if (alpha < 1) {
			alpha += TimeManager::GetDeltaTime();
			renderer->alpha = alpha;
		}
		else {
			alpha = 1;
			renderer->alpha = 1;
			isIn = false;
		}
	}
	else if (isOut)
	{
		// FadeOut �� �ڸ�
		if (alpha > 0) {
			alpha -= TimeManager::GetDeltaTime() * 2;
			renderer->alpha = alpha;
		}
		else {
			alpha = 0;
			renderer->alpha = 0;
			isOut = false;
		}
	}
}

void Tile::FadeIn(int pos)
{
	currentPos = pos;

	float posX = (pos % 3 - 1) * 75;
	float posY = -(pos / 3 - 1) * 75;
	transform->SetPosition(posX, posY);

	renderer->alpha = alpha = 0;
	isIn = true;
}

void Tile::FadeOut()
{
	alpha = renderer->alpha;
	isOut = true;
	// FadeOut �ϸ鼭 ������ ���� ������
	GameManager::GetInstance()->coins[currentPos]->FlipWithDelay(0.3f);
}