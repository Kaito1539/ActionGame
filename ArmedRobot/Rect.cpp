#include "Rect.h"

int Rect::GetX(){
	return x;
}

int Rect::GetY(){
	return y;
}

int Rect::GetPostX(){
	return postX;
}

int Rect::GetPostY(){
	return postY;
}

double Rect::GetVX(){
	return vx;
}

double Rect::GetVY(){
	return vy;
}

int Rect::GetWidth(){
	return width;
}

int Rect::GetHeight(){
	return height;
}

eDirection Rect::GetDirection(){
	return direction;
}

int Rect::GetAtk(){
	return atk;
}

int Rect::GetStun(){
	return stun;
}

int Rect::GetBlowX(){
	return blowX*direction;
}

int Rect::GetBlowY(){
	return blowY;
}

bool Rect::GetAlive(){
	return alive;
}

int Rect::GetID(){
	return iID;
}

void Rect::SetDamage(int setDamage, int setStun, int setVX, int setVY, int setID){
	for (int i = 0; i < 10; i++){
		if (invalidID[i] == setID){
			return;
		}
	}
	
	if (balance <= 0){
		hp -= setDamage;
	}
	else if (setDamage - def>1){
		hp -= setDamage - def;
	}
	else{
		hp--;
	}
	balance -= setStun;
	vx = setVX;
	vy = setVY;
	for (int i = 9; i > 0; i--){
		invalidID[i] = invalidID[i - 1];
	}
	invalidID[0] = setID;
	//nextState = eState_Bend;
	//duration = 10;
	if (vx > 0){
		direction = eDirection_Left;
	}
	else{
		direction = eDirection_Right;
	}
	nextState = eState_Bend;
	duration = 20;
}

void Rect::SetPostX(int setPostX){
	postX = setPostX;
}

void Rect::SetPostY(int setPostY){
	postY = setPostY;
}

void Rect::SetOnX(){
	if (vx > 0){
		onX = eConnect_Right;
	}
	else{
		onX = eConnect_Left;
	}
}

void Rect::SetOnY(){
	if (vy > 0){
		onY = eConnect_Down;
	}
	else{
		onY = eConnect_Up;
	}
}

void Rect::MakeChecker(){
	onX = onY = eConnect_Free;
	//èáî‘ÇçHïvÇ∑ÇÍÇŒçHíˆÇå∏ÇÁÇπÇÈÇÕÇ∏,äÑÇËéZÇÃó]ÇËÇÃàµÇ¢Ç™ìÒèd
	checkXNum = (width + MAPCHIP_SIZE - 1) / MAPCHIP_SIZE + 1;
	checkYNum = (height + MAPCHIP_SIZE - 1) / MAPCHIP_SIZE + 1;
	for (int i = 0; i < checkXNum; i++){
		if (width % MAPCHIP_SIZE == 0){
			if (i == 0){
				checkPointX[i] = x;
				checkPointPostX[i] = postX;
			}
			else{
				checkPointX[i] = checkPointX[0] + MAPCHIP_SIZE*i - 1;
				checkPointPostX[i] = checkPointPostX[0] + MAPCHIP_SIZE*i - 1;
			}
		}
		else{
			if (i == 0){
				checkPointX[i] = x;
				checkPointPostX[i] = postX;
			}
			else if (i < checkXNum - 1){
				checkPointX[i] = checkPointX[0] + MAPCHIP_SIZE*i - 1;
				checkPointPostX[i] = checkPointPostX[0] + MAPCHIP_SIZE*i - 1;
			}
			else{
				checkPointX[i] = checkPointX[0] + MAPCHIP_SIZE*(i - 1) - 1 + width % MAPCHIP_SIZE;
				checkPointPostX[i] = checkPointPostX[0] + MAPCHIP_SIZE*(i - 1) - 1 + width % MAPCHIP_SIZE;
			}
		}
	}
	for (int i = 0; i < checkYNum; i++){
		if (height % MAPCHIP_SIZE == 0){
			if (i == 0){
				checkPointY[i] = y;
				checkPointPostY[i] = postY;
			}
			else{
				checkPointY[i] = checkPointY[0] + MAPCHIP_SIZE*i - 1;
				checkPointPostY[i] = checkPointPostY[0] + MAPCHIP_SIZE*i - 1;
			}
		}
		else{
			if (i == 0){
				checkPointY[i] = y;
				checkPointPostY[i] = postY;
			}
			else if (i < checkYNum - 1){
				checkPointY[i] = checkPointY[0] + MAPCHIP_SIZE*i - 1;
				checkPointPostY[i] = checkPointPostY[0] + MAPCHIP_SIZE*i - 1;
			}
			else{
				checkPointY[i] = checkPointY[0] + MAPCHIP_SIZE*(i - 1) - 1 + height % MAPCHIP_SIZE;
				checkPointPostY[i] = checkPointPostY[0] + MAPCHIP_SIZE*(i - 1) - 1 + height % MAPCHIP_SIZE;
			}
		}
	}
}

void Rect::CheckMap(){
	//xï˚å¸
	if (vx > 0){
		for (int i = 0; i < checkYNum; i++){
			if (mapData[checkPointY[i] / MAPCHIP_SIZE][checkPointPostX[checkXNum - 1] / MAPCHIP_SIZE]>MAPCHIP_PASSABLE){
				SetPostX((checkPointPostX[checkXNum - 1] / MAPCHIP_SIZE)*MAPCHIP_SIZE - width);
				SetOnX();
				break;
			}
		}
	}
	else if (vx < 0){
		for (int i = 0; i < checkYNum; i++){
			if (mapData[checkPointY[i] / MAPCHIP_SIZE][checkPointPostX[0] / MAPCHIP_SIZE]>MAPCHIP_PASSABLE){
				SetPostX((checkPointPostX[0] / MAPCHIP_SIZE + 1)*MAPCHIP_SIZE);
				SetOnX();
				break;
			}
		}
	}
	//yï˚å¸
	if (vy > 0){
		for (int i = 0; i < checkXNum; i++){
			if (mapData[checkPointPostY[checkYNum - 1] / MAPCHIP_SIZE][checkPointX[i] / MAPCHIP_SIZE]>MAPCHIP_PASSABLE){
				SetPostY((checkPointPostY[checkYNum - 1] / MAPCHIP_SIZE)*MAPCHIP_SIZE - height);
				SetOnY();
				break;
			}
		}
	}
	else if (vy < 0){
		for (int i = 0; i < checkXNum; i++){
			if (mapData[checkPointPostY[0] / MAPCHIP_SIZE][checkPointX[i] / MAPCHIP_SIZE]>MAPCHIP_PASSABLE){
				SetPostY((checkPointPostY[0] / MAPCHIP_SIZE + 1)*MAPCHIP_SIZE);
				SetOnY();
				break;
			}
		}
	}
}

