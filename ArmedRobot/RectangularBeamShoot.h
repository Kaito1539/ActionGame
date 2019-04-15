#pragma once

#include "DxLib.h"
#include "Rect.h"

class RectangularBeamShoot : public Rect{
private:
	/*
	int x, y;
	int width, height;
	*/
	int id;//一度当たったidの攻撃には当たらない。
	bool streak;//連続ヒット判定
public:
	void Initialize(int* setID);
	void Generate(int setAtk, int setStun, int setBlowX, int setBlowY, bool setStreak, int setHP, int setX, int setY, int setWidth, int setHeight, double setVX, double setVY, eDirection setDirection);
	void Finalize();
	void Update();
	void Draw(int setScreenX, int setScreenY);
	void SetImage(int setImage);
	/*
	int GetX();
	int GetY();
	int GetW();
	int GetH();
	*/
};