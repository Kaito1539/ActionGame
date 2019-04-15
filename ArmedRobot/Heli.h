#pragma once

#include "ConstantNum.h"

#include "DxLib.h"
#include "Rect.h"
#include "Player.h"
#include "RectangularSolidShoot.h"
#include "RectangularBeamShoot.h"


class Heli : public Rect{
private:
	typedef enum{
		eWidth_Normal = 128,
	} eWidth;

	typedef enum{
		eHeight_Normal = 128,
	} eHeight;

	Player* player;
	RectangularSolidShoot* solidShoot;
	RectangularSolidShoot* missile[8];
	RectangularBeamShoot* bomb[9];
	int shootTime;
	int missileNum;
public:
	void Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID, Player* setPlayer);
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

	void ProcessFlight();
	void ProcessBend();
	void ProcessStun();
	void ProcessShootStanby();
	void ProcessShoot();

	void SolidShootInitialize(RectangularSolidShoot* setSolidShoot,int setNum);
	void BeamShootInitialize(RectangularBeamShoot* setBeamShoot, int setNum);
};