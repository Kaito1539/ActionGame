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

class Stage1 : public BaseScene {
private:
	static const int ENEMY_NUM = 3;
	Rect* enemyRect[2 * ENEMY_NUM];
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
	int a,b,c;//汎用変数
	bool flg;
	int atkID;
	int bgm;
public:
	Stage1::Stage1(ISceneChanger* changer);
	void Initialize() override;    //初期化処理をオーバーライド。
	//void Finalize() override;        //終了処理をオーバーライド。
	void Update() override;        //更新処理をオーバーライド。
	void Draw() override;            //描画処理をオーバーライド。
	void MakeMap();
	bool CheckCollisionRectToRect(Rect * setRectA, Rect * setRectB);
};