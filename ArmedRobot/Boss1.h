#pragma once

#include "ConstantNum.h"

#include "DxLib.h"
#include "Rect.h"
#include "Player.h"
#include "RectangularSolidShoot.h"


class Boss1 : public Rect{
private:
	typedef enum{
		eWidth_Normal = 64,
		eWidth_Dash = 79,
		eWidth_Crouch = eWidth_Normal,
	} eWidth;

	typedef enum{
		eHeight_Normal = 96,
		eHeight_Dash = 84,
		eHeight_Crouch = eHeight_Dash,
	} eHeight;

	Player* player;
	RectangularSolidShoot* solidShoot;
	RectangularSlash* slash;
	int dashChecker;
	int jumpPower;
	int atkTime;
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

	void ProcessStand();
	void ProcessJumpStanby();
	void ProcessJump();
	void ProcessFlight();
	void ProcessBend();
	void ProcessStun();
	void ProcessShootStanby();
	void ProcessShoot();
	void ProcessSlashStanby();
	void ProcessRushSlash();

	void SolidShootInitialize(RectangularSolidShoot* setSolidShoot);
	void SlashInitialize(RectangularSlash* setSlash);

	void SetDamage(int setDamage, int setStun, int setVX, int setVY, int setID) override;

};