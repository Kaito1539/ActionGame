#include "RectangularSlash.h"

void RectangularSlash::Initialize(int* setID){
	piID = setID;
}

void RectangularSlash::Generate(int setAtk, int setStun, int setBlowX, int setBlowY, bool setStreak){
	(*piID)++;
	if (*piID >= 1023){
		*piID = 0;
	}
	iID = *piID;
	x = y = width = height = 0;
	atk = setAtk;
	stun = setStun;
	blowX = setBlowX;
	blowY = setBlowY;
	streak = setStreak;
	alive = true;
}

//終了
void RectangularSlash::Finalize(){
	alive = false;
}

//更新
void RectangularSlash::Update(int setX, int setY, int setWidth, int setHeight, eDirection setDirection){
	if (streak){
		(*piID)++;
		if (*piID >= 1023){
			*piID = 0;
		}
		iID = *piID;
	}
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	direction = setDirection;
}

//描画
void RectangularSlash::Draw(int setStartScreenX, int setStartScreenY){
	/*
	if (alive){
		DrawBox(x - setStartScreenX, y - setStartScreenY, x - setStartScreenX + width, y - setStartScreenY + height, GetColor(100, 200, 0), true);
	}
	*/
	if (alive){
		if (direction == eDirection_Right){
			DrawGraph(x - setStartScreenX, y - setStartScreenY, showImage, TRUE);
		}
		else{
			DrawTurnGraph(x - setStartScreenX, y - setStartScreenY, showImage, TRUE);
		}
	}
	/*
	DrawFormatString(0, 270, GetColor(255, 0, 255), "iIDの値は %d です\n", iID);
	DrawFormatString(0, 300, GetColor(255, 0, 255), "piIDの値は %d です\n", piID);
	DrawFormatString(0, 330, GetColor(255, 0, 255), "*piIDの値は %d です\n", *piID);
	*/
}

void RectangularSlash::SetImage(int setImage){
	showImage = setImage;
}