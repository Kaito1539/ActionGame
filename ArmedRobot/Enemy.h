#pragma once

#include "ConstantNum.h"

#include "DxLib.h"
#include "Rect.h"
#include "Player.h"
#include "RectangularSolidShoot.h"


class Enemy1 : public Rect{
private:
	typedef enum{
		eWidth_Normal = 64,
	} eWidth;

	typedef enum{
		eHeight_Normal = 96,
	} eHeight;

	Player* player;
	RectangularSolidShoot* solidShoot;
	int dashChecker;
	int jumpPower;
	int shootTime;
	/*
	int mapData[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

	int checkXNum, checkYNum;
	int checkPointX[CHECK_X_MAX];
	int checkPointY[CHECK_Y_MAX];
	int checkPointPostX[CHECK_X_MAX];
	int checkPointPostY[CHECK_Y_MAX];
	*/
public:
	void Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID,Player* setPlayer);
	//void Finalize();     
	void Update();
	void Draw(int setStartScreenX, int setStartScreenY);
	/*
	void SetPostX(int setPostX);
	void SetPostY(int setPostY);
	void SetOnX();
	void SetOnY();
	*/
	void Move();
	/*
	void MakeChecker();
	void CheckMap();
	*/

	void ProcessStand();
	void ProcessRun();;
	void ProcessJumpStanby();
	void ProcessJump();
	void ProcessFlight();
	void ProcessBend();
	void ProcessStun();
	void ProcessShootStanby();
	void ProcessShoot();

	void SolidShootInitialize(RectangularSolidShoot* setSolidShoot);
};