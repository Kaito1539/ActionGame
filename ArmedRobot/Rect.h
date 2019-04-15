#pragma once

#include "ConstantNum.h"
#include "DxLib.h"
typedef enum{
	eDirection_Right = 1,
	eDirection_Left = -1,
} eDirection;

//矩形クラス。矩形の判定を行うオブジェクトはすべてこのRectangleクラスを継承する。
class Rect {
protected:

	typedef enum{
		eConnect_Up,
		eConnect_Down,
		eConnect_Right,
		eConnect_Left,
		eConnect_Free,
	} eConnect;

	int x, y;
	int postX, postY;
	double ax, ay, vx, vy;
	int width;
	int height;
	eDirection direction;//右なら1,左なら-1
	int atk, stun, blowX,blowY;//攻撃力, フッ飛ばし力
	int def,balance;
	bool alive;

	int showImage;
	int image[128];
	int imageFrame;

	int hp;
	eConnect onX, onY;
	eState nowState, nextState;
	int duration;
	int mapData[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];

	int invalidID[10];
	int iID;
	int* piID;//一度当たったidの攻撃には当たらない。

	int checkXNum, checkYNum;
	int checkPointX[CHECK_X_MAX];
	int checkPointY[CHECK_Y_MAX];
	int checkPointPostX[CHECK_X_MAX];
	int checkPointPostY[CHECK_Y_MAX];

	int transmittance;
public:
	int GetX();
	int GetY();
	int GetPostX();
	int GetPostY();
	double GetVX();
	double GetVY();
	int GetWidth();
	int GetHeight();
	eDirection GetDirection();
	int GetAtk();
	int GetBlowX();
	int GetBlowY();
	int GetStun();
	bool GetAlive();
	int GetID();

	virtual void SetDamage(int setDamage, int setStun,int setVX, int setVY,int setID);

	void SetPostX(int setPostX);
	void SetPostY(int setPostY);
	void SetOnX();
	void SetOnY();
	void MakeChecker();
	void CheckMap();
};