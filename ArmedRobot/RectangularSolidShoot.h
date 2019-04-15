#pragma once

#include "Rect.h"

class RectangularSolidShoot : public Rect{
private:
	bool streak;//˜A‘±ƒqƒbƒg”»’è
public:
	void Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int* setID);
	void Generate(int setAtk, int setStun, int setBlowX, int setBlowY, bool setStreak, int setHP,int setX, int setY, int setWidth, int setHeight, double setVX, double setVY, eDirection setDirection);
	void Finalize();     
	void Update();
	void Draw(int setStartScreenX, int setStartScreenY);
	int GetHP();
	void SetImage(int setImage);
};