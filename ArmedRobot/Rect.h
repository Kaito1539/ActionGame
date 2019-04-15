#pragma once

#include "ConstantNum.h"
#include "DxLib.h"
typedef enum{
	eDirection_Right = 1,
	eDirection_Left = -1,
} eDirection;

//��`�N���X�B��`�̔�����s���I�u�W�F�N�g�͂��ׂĂ���Rectangle�N���X���p������B
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
	eDirection direction;//�E�Ȃ�1,���Ȃ�-1
	int atk, stun, blowX,blowY;//�U����, �t�b��΂���
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
	int* piID;//��x��������id�̍U���ɂ͓�����Ȃ��B

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