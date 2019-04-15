#include "RectangularBeamShoot.h"

void RectangularBeamShoot::Initialize(int* setID){
	x = y = width = height = 0;
	atk = blowX = blowY = 0;
	alive = false;
	piID = setID;
}

void RectangularBeamShoot::Generate(int setAtk, int setStun, int setBlowX, int setBlowY, bool setStreak, int setHP, int setX, int setY, int setWidth, int setHeight, double setVX, double setVY, eDirection setDirection){
	atk = setAtk;
	stun = setStun;
	blowX = setBlowX;
	blowY = setBlowY;
	streak = setStreak;
	x = setX;
	y = setY;
	width = setWidth;
	height = setHeight;
	vx = setVX;
	vy = setVY;
	hp = setHP;
	(*piID)++;
	if (*piID >= 1023){
		*piID = 0;
	}
	iID = *piID;
	direction = setDirection;
	alive = true;
}

//èIóπ
void RectangularBeamShoot::Finalize(){
	alive = false;
}

//çXêV
void RectangularBeamShoot::Update(){
	hp--;
	if (hp <= 0){
		Finalize();
	}
	if (streak){
		iID++;
		if (iID >= 1023){
			iID = 0;
		}
	}
	x += (int)vx;
	y += (int)vy;
}

//ï`âÊ
void RectangularBeamShoot::Draw(int setStartScreenX, int setStartScreenY){
	if (alive){
		//DrawBox(x - setStartScreenX, y - setStartScreenY, x - setStartScreenX + width, y - setStartScreenY + height, GetColor(100, 200, 0), true);
	}
	if (alive){
		if (width >= height){
			if (direction == eDirection_Right){
				DrawGraph(x - setStartScreenX, y - setStartScreenY, showImage, TRUE);
			}
			else{
				DrawTurnGraph(x - setStartScreenX, y - setStartScreenY, showImage, TRUE);
			}
		}
		else{
			if (direction == eDirection_Right){
				DrawRotaGraph(x - setStartScreenX, y - setStartScreenY,1.0,-DX_PI/2,  showImage, TRUE);
			}
			else{
				DrawRotaGraph(x - setStartScreenX, y - setStartScreenY,1.0,-DX_PI/2, showImage, TRUE);
			}
		}
		
	}
}

void RectangularBeamShoot::SetImage(int setImage){
	showImage = setImage;
}