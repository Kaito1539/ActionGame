#pragma once

#include "BaseScene.h"
#include "ISceneChanger.h"
#include "ConstantNum.h"

#include "Rect.h"

#include "DxLib.h"
#include <stdio.h>
#include <stdlib.h>
#include "Player.h"
#include "Enemy.h"
#include "Signboard.h"

class Stage0 : public BaseScene {
private:
	static const int ENEMY_NUM = 3;
	Rect* enemyRect[2 * ENEMY_NUM];

	static const int SIGNBOARD_NUM = 16;
	Rect* signRect[SIGNBOARD_NUM];
	Signboard signboard[SIGNBOARD_NUM];

	Player player;
	RectangularSlash playerSlash;
	RectangularBeamShoot playerBeamShoot[PLAYER_BULLET_MAX];
	Enemy1 enemy[ENEMY_NUM];
	RectangularSolidShoot enemySolidShoot[ENEMY_NUM];
	//RectangularSolidShoot enemySolidShoot1, enemySolidShoot2, enemySolidShoot3;


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
	Stage0::Stage0(ISceneChanger* changer);
	void Initialize() override;    //�������������I�[�o�[���C�h�B
	//void Finalize() override;        //�I���������I�[�o�[���C�h�B
	void Update() override;        //�X�V�������I�[�o�[���C�h�B
	void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
	void MakeMap();
	bool CheckCollisionRectToRect(Rect * setRectA, Rect * setRectB);
};
