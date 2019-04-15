#include "RectangularSolidShoot.h"

void RectangularSolidShoot::Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int* setID){
	x = y = width=height=0;
	atk = blowX =blowY = 0;
	alive = false;
	//GetGraphSize(graphic, &size[XA], &size[YA]);
	for (int i = 0; i < setMapH; i++){
		for (int j = 0; j < setMapW; j++){
			mapData[i][j] = setMap[i][j];
		}
	}
	piID = setID;
}

void RectangularSolidShoot::Generate(int setAtk, int setStun, int setBlowX, int setBlowY, bool setStreak,int setHP, int setX, int setY, int setWidth, int setHeight, double setVX, double setVY, eDirection setDirection){
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

//終了
void RectangularSolidShoot::Finalize(){
	alive = false;
}

//更新
void RectangularSolidShoot::Update(){
	if (hp <= 0){
		Finalize();
		//return;
	}
	if (streak){
		(*piID)++;
		if (*piID >= 1023){
			*piID = 0;
		}
		iID = *piID;
	}

	//速度制限
	if (vx > MAPCHIP_SIZE){
		vx = MAPCHIP_SIZE;
	}
	else if (vx < -MAPCHIP_SIZE){
		vx = -MAPCHIP_SIZE;
	}
	if (vy > MAPCHIP_SIZE){
		vy = MAPCHIP_SIZE;
	}
	else if (vy < -MAPCHIP_SIZE){
		vy = -MAPCHIP_SIZE;
	}

	postX = x + (int)vx;
	postY = y + (int)vy;

	MakeChecker();
	CheckMap();

	if (onX != eConnect_Free || onY != eConnect_Free){
		hp = 0;
	}

	x = postX;
	y = postY;
}

//描画
void RectangularSolidShoot::Draw(int setStartScreenX, int setStartScreenY){
	if (alive){
		//DrawBox(x - setStartScreenX, y - setStartScreenY, x - setStartScreenX + width, y - setStartScreenY + height, GetColor(100, 200, 0), true);
	}
	if (alive){
		if (direction == eDirection_Right){
			DrawGraph(x - setStartScreenX, y - setStartScreenY, showImage, TRUE);
		}
		else{
			DrawTurnGraph(x - setStartScreenX, y - setStartScreenY, showImage, TRUE);
		}
	}
}

int RectangularSolidShoot::GetHP(){
	return hp;
}

void RectangularSolidShoot::SetImage(int setImage){
	showImage = setImage;
}