#pragma once

#include "Keyboard.h"
#include "Rect.h"
#include "RectangularSlash.h"
#include "RectangularBeamShoot.h"
#include <math.h>

#include "DxLib.h"

const int SHOW_PLAYER_X = (SCREEN_SIZE_X - 64) / 2;
const int SHOW_PLAYER_Y = SCREEN_SIZE_Y * 1 / 2;

const double PI = 3.141592;
const double MIN_HP_ANGLE = (PI / 3 * 2);
const double MAX_HP_ANGLE = (PI / 3 * 7);
const int HP_METER_DIVIDE_NUM = 30;

const int MAX_HP = 100;

const int SIMULTANEOUS_FRAME = 12;
const int SLASH_FRAME = 12;
const int AIR_DOWN_SLASH_FRAME = 36;

const int Front_Slash1_ATK = 60;
const int Front_Slash1_STUN = 20;
const int Front_Slash1_BLOW_X = 6;
const int Front_Slash1_BLOW_Y = -5;
const int Front_Slash2_ATK = 60;
const int Front_Slash2_STUN = 10;
const int Front_Slash2_BLOW_X = 2;
const int Front_Slash2_BLOW_Y = -5;
const int Front_Slash3_ATK = 70;
const int Front_Slash3_STUN = 20;
const int Front_Slash3_BLOW_X = 6;
const int Front_Slash3_BLOW_Y = -5;
const int Front_Slash_BIND = 24;
const int Upper_Slash_ATK = 20;
const int Upper_Slash_STUN = 4;
const int Upper_Slash_BLOW_X = 4;
const int Upper_Slash_BLOW_Y = -20;
const int Sweep_Slash_ATK = 30;
const int Sweep_Slash_STUN = 50;
const int Sweep_Slash_BLOW_X = 1;
const int Sweep_Slash_BLOW_Y = -10;

const int Air_Front_Slash_ATK = 70;
const int Air_Front_Slash_STUN = 20;
const int Air_Front_Slash_BLOW_X = 10;
const int Air_Front_Slash_BLOW_Y = -5;
const int Air_Down_Slash_ATK = 25;
const int Air_Down_Slash_STUN = 5;
const int Air_Down_Slash_BLOW_X = 5;
const int Air_Down_Slash_BLOW_Y = 5;

const int Shoot_BIND = 48;

const int DASH_ACCEPT_FRAME = 14;
const int COMBO_ACCEPT_FRAME = SLASH_FRAME;

const int JUMP_STANDBY_FRAME = 2;
const int SHOOT_STANDBY_FRAME = 2;
const int SLASH_STANDBY_FRAME = 2;

const int MAX_LOAD_BULLET = 3;

const int AVOIDANCE_FRAME = 12;

const int PLAYER_BULLET_MAX = 3;
const int RELOAD_FRAME = 120;

class Player : public Rect{
private:
	typedef enum{
		eWidth_Normal = 64,
		eWidth_Dash = 79,
		eWidth_Crouch = eWidth_Normal,
	} eWidth;

	typedef enum{
		eHeight_Normal = 96,
		eHeight_Dash = 64,
		eHeight_Crouch = eHeight_Dash,
	} eHeight;

	//ここから
	typedef enum{
		eAccel_Run = 5,
		eAccel_Crouch = 2,
	} eAccel;

	typedef enum{
		eVelocity_Run_Limit = 10,
		eVelocity_Dash = 20,
		eVelocity_Jump_Min = 16,
	} eVelocity;
	//ここまでconst intの方がいいかも

	RectangularSlash* slash;
	RectangularBeamShoot* beamShoot[PLAYER_BULLET_MAX];

	int nextBulletNum;
	int remainBullet;
	int reloadCounter;

	int dashChecker;
	//int jumpPower;
	int slashImageNumber, shootImageNumber;
	int slashBind, avoidBind;
	int shootBind;//弾丸の絵を変えるためのカウンターとしてのみ使われている。

	double HpAngle;

	eState reserveState;

	int comboNum;
	const int COMBO_MAX = 3;
	bool comboApplication;
	int meterImage[4];
	int markerImage[2];
	int numberImage[4];

	//PAINTSTRUCT     ps;
	//HDC             hDC;
	/*
	int mapData[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

	int checkXNum, checkYNum;
	int checkPointX[CHECK_X_MAX];
	int checkPointY[CHECK_Y_MAX];
	int checkPointPostX[CHECK_X_MAX];
	int checkPointPostY[CHECK_Y_MAX];
	*/
public:
	//Player();//Initializeの方が復活,残機の処理が楽と思われ。やっぱ使いづらい
	void Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID);
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
	void ProcessRun();
	void ProcessDash();
	void ProcessCrouch();
	void ProcessJumpStanby();
	void ProcessJump();
	void ProcessFlight();
	void ProcessBend();
	void ProcessStun();
	void ProcessWallKick();
	void ProcessAvoidance();
	void ProcessSlashStanby();
	void ProcessFrontSlash1();
	void ProcessFrontSlash2();
	void ProcessFrontSlash3();
	void ProcessUpperSlash();
	void ProcessSweepSlash();
	void ProcessAirDownSlash();

	void ProcessShootStanby();
	void ProcessShoot();

	void ProcessAirFrontSlash();

	void SlashInitialize(RectangularSlash* setSlash);
	void BeamShootInitialize(RectangularBeamShoot* setBeamShoot,int setNum);

	void HpMeterUpdate();
	void HpMeterDraw();

	void SlashGenerate();
	void Combo();
	void Combo2();
};
