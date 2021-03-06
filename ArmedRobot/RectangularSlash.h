#pragma once

#include "DxLib.h"
#include "Rect.h"

class RectangularSlash : public Rect{
private:
	bool streak;//連続ヒット判定
public:
	void Initialize(int* setID);
	void Generate(int setAtk, int setStun, int setBlowX, int setBlowY, bool setStreak);
	void Finalize();
	void Update(int setX, int setY, int setWidth, int setHeight,eDirection setDirection);
	void Draw(int setScreenX, int setScreenY);
	void SetImage(int setImage);//Updateにまとめるべきだった
};