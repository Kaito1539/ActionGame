#include "Heli.h"
//初期化
void Heli::Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID, Player* setPlayer){
	LoadDivGraph("images/Heli2.bmp", 4, 2, 2, 128, 128, image);
	LoadDivGraph("images/HeliMissile.bmp", 4, 2, 2, 48, 12, &image[4]);
	LoadDivGraph("images/HeliBomb.bmp", 4, 2, 2, 144, 36, &image[8]);
	showImage = image[0];
	x = setX;
	y = setY;
	width = eWidth_Normal;
	height = eHeight_Normal;
	ax = ay = vx = vy = 0;
	direction = eDirection_Right;
	hp = 10;
	atk = 10;
	blowX = 10;
	blowY = -10;
	def = 0;
	balance = 100;
	alive = true;
	piID = setID;
	player = setPlayer;
	shootTime = 120;
	nowState =nextState= eState_Flight;
	for (int i = 0; i < setMapH; i++){
		for (int j = 0; j < setMapW; j++){
			mapData[i][j] = setMap[i][j];
		}
	}

	for (int i = 0; i < 10; i++){
		invalidID[i] = -1;
	}
}

//更新
void Heli::Update(){
	ax = ay = 0;
	if (hp <= 0){
		alive = false;
	}
	if (nowState != eState_Bend){
		(*piID)++;
		if (*piID >= 1023){
			*piID = 0;
		}
		iID = *piID;
	}
	shootTime--;
	Move();

	imageFrame--;
	if (imageFrame <= 0){
		for (int i = 0; i < 4; i++){
			if (showImage == image[i]){
				if (i == 3){
					showImage = image[0];
				}
				else{
					showImage = image[i + 1];
				}
				break;
			}
			if (i == 3){
				showImage = image[0];
			}
		}
		imageFrame = IMAGE_CHANGE_FRAME;
	}

	if (solidShoot->GetAlive()&&(solidShoot->GetHP()==0)){
		bomb[0]->Generate(40, 20, 16, 8, false,  3,solidShoot->GetX() - solidShoot->GetWidth(), solidShoot->GetY() - solidShoot->GetHeight(), 3 * solidShoot->GetWidth(), 3 * solidShoot->GetHeight(), 0, 0,eDirection_Right);
	}
	for (int i = 0; i < 8; i++){
		if (missile[i]->GetAlive() && (missile[i]->GetHP() <= 0)){
			bomb[i]->Generate(50, 20, 16, 16, false, 6, missile[i]->GetX() - missile[i]->GetWidth(), missile[i]->GetY() - missile[i]->GetHeight(), 3 * missile[i]->GetWidth(), 3 * missile[i]->GetHeight(), 0, 0, eDirection_Right);
			bomb[i]->SetImage(image[10]);
		}
	}

}

//描画
void Heli::Draw(int setStartScreenX, int setStartScreenY){
	/*
	DrawBox(x - setStartScreenX, y - setStartScreenY, x - setStartScreenX + width, y - setStartScreenY + height, GetColor(0, 0, 0), true);
	if (direction == eDirection_Right){
	DrawBox(x - setStartScreenX + width / 2, y - setStartScreenY + 5, x - setStartScreenX + width, y - setStartScreenY + height / 2, GetColor(255, 255, 255), true);
	}
	else{
	DrawBox(x - setStartScreenX, y - setStartScreenY + 5, x - setStartScreenX + width / 2, y - setStartScreenY + height / 2, GetColor(255, 255, 255), true);
	}
	*/

	if (direction == eDirection_Right){
		DrawGraph(x - setStartScreenX , y - setStartScreenY, showImage, TRUE);
	}
	else{
		DrawTurnGraph(x - setStartScreenX , y - setStartScreenY, showImage, TRUE);
	}
}

void Heli::Move(){
	duration--;
	/*
	ay++;//重力
	if (onY == eConnect_Down&&vy>0){
		vy = 0;
	}
	*/
	if (balance <= 0 && nowState != eState_Stun){
		nextState = eState_Stun;
		duration = 60;
	}
	nowState = nextState;

	switch (nowState) {
	case  eState_Flight:
		ProcessFlight();
		break;
	case  eState_Bend:
		ProcessBend();
		break;
	case  eState_Stun:
		ProcessStun();
		break;

	case  eState_Shoot_Stanby:
		ProcessShootStanby();
		break;
	case  eState_Shoot:
		ProcessShoot();
		break;
	}

	vx += ax;
	vy += ay;

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

	x = postX;
	y = postY;
}

void Heli::ProcessFlight(){
	if (x + width / 2 +512< player->GetX()){
		vx = 3;
	}
	else if (x+width/2 < player->GetX()){
		vx = 2;
	}
	else if(x<=player->GetX()+SCREEN_SIZE_X/2){
		vx = 4;
	}
	else{
		x = player->GetX() - SCREEN_SIZE_X / 2-256;
	}
	
	if (y <= 256){
		vy = 1;
	}
	else if(y >= 512){
		vy = -1;
	}

	if (shootTime < 0){
		nextState = eState_Shoot_Stanby;
		duration = 12;
	}
}

void Heli::ProcessBend(){
	if (duration<0){
		nextState = eState_Flight;
	}
}

void Heli::ProcessStun(){
	if (duration <= 0){
		nextState = eState_Flight;
		def = 20;
		balance = 100;
	}
}

void Heli::ProcessShootStanby(){

	if (duration <= 0){
		if (direction == eDirection_Right){
			missile[missileNum]->Generate(40, 10, 10, -5, false,1, x + 18, y + 64, 48, 12, vx/2 * direction, 8, direction);
		}
		else{
			missile[missileNum]->Generate(40, 10, 10, -5, false, 1, x + 18, y + 64, 48, 12, vx / 2 * direction, 8, direction);
		}
		missile[missileNum]->SetImage(image[4]);

		if (missileNum >= 7){
			missileNum = 0;
		}
		else{
			missileNum++;
		}
		nextState = eState_Shoot;
		duration = 4;
		shootTime = 16;
	}
}

void Heli::ProcessShoot(){

	if (duration <= 0){
		nextState = eState_Flight;
	}
}

void Heli::SolidShootInitialize(RectangularSolidShoot* setSolidShoot,int setNum){
	if (setNum == 0){
		solidShoot = setSolidShoot;
	}
	else{
		missile[setNum-1] = setSolidShoot;
	}
	
}

void Heli::BeamShootInitialize(RectangularBeamShoot* setBeamShoot, int setNum){
	bomb[setNum] = setBeamShoot;
}
