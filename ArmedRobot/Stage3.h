#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "ConstantNum.h"

#include "Rect.h"

#include "DxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "Boss1.h"

class Stage3 : public BaseScene {
private:
	Rect* enemyRect[3];
	Player player;
	RectangularSlash playerSlash;
	RectangularBeamShoot playerBeamShoot[PLAYER_BULLET_MAX];
	Boss1 boss;
	RectangularSolidShoot enemySolidShoot;
	RectangularSlash enemySlash;

	int checkPointX[CHECK_X_MAX];
	int checkPointY[CHECK_Y_MAX];
	int checkPointPostX[CHECK_X_MAX];
	int checkPointPostY[CHECK_Y_MAX];
	int mapChipGraph[MAPCHIP_KIND];
	int startChipX;
	int startChipY;
	int startScreenX, startScreenY;
	int mapData[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];
	int mapH, mapW;

	char map[MAP_WIDTH_MAX];
	int a, b, c;//�ėp�ϐ�
	bool flg;
	int atkID;
	int bgm;
public:
	Stage3::Stage3(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void MakeMap();
	bool CheckCollisionRectToRect(Rect * setRectA, Rect * setRectB);
};