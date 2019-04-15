#include "Enemy.h"
//初期化
void Enemy1::Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID,Player* setPlayer){
	LoadDivGraph("images/zako1-2.bmp", 4, 4, 1, 96, 96, image);
	LoadDivGraph("images/EnemySolidBullet.bmp",4,2,2,32,16,&image[4]);
	showImage = image[0];
	x = setX;
	y = setY;
	width = eWidth_Normal;
	height = eHeight_Normal;
	ax = ay = vx = vy = 0;
	direction = eDirection_Left;
	hp = 100;
	atk = 10;
	blowX = 10;
	blowY = -10;
	def = 20;
	balance = 100;
	alive = true;
	piID = setID;
	player = setPlayer;
	shootTime = 120;
	nowState = eState_Flight;
	//GetGraphSize(graphic, &size[XA], &size[YA]);
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
void Enemy1::Update(){
	ax = ay = 0;
	if (hp <= 0){
		alive = false;
	}
	transmittance = 256;
	if (nowState != eState_Bend){
		(*piID)++;
		if (*piID >= 1023){
			*piID = 0;
		}
		iID = *piID;
	}
	shootTime--;
	Move();
	/*
	if (solidShoot->GetAlive()){
		solidShoot->Update();
	}
	*/
}

//描画
void Enemy1::Draw(int setStartScreenX, int setStartScreenY){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transmittance);
	if (direction == eDirection_Right) {
		DrawGraph(x - setStartScreenX - 16, y - setStartScreenY, showImage, TRUE);
	}
	else {
		DrawTurnGraph(x - setStartScreenX - 16, y - setStartScreenY, showImage, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 256);
	
}

void Enemy1::Move(){
	duration--;

	ay++;//重力
	if (onY == eConnect_Down&&vy>0){
		vy = 0;
	}

	if (balance <= 0&&nowState!=eState_Stun){
		nextState = eState_Stun;
		duration = 60;
	}
	nowState = nextState;

	switch (nowState) {
	case  eState_Stand:
		ProcessStand();
		break;
	case  eState_Run:
		ProcessRun();
		break;
	case  eState_Jump_Stanby:
		ProcessJumpStanby();
		break;
	case  eState_Jump:
		ProcessJump();
		break;
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

void Enemy1::ProcessStand(){
	showImage = image[0];

	if (onY == eConnect_Down){
		vx = 0;
	}
	if (balance < 100){
		balance++;
	}
	if (player->GetX() + player->GetWidth() / 2>x + width / 2){
		direction = eDirection_Right;
	}
	else{
		direction = eDirection_Left;
	}
	if (shootTime < 0){
		if (player->GetY()<(y + height / 2) && player->GetY() + player->GetHeight()>(y + height / 2)){
			nextState = eState_Shoot_Stanby;
			duration = 12;
		}
	}
}

void Enemy1::ProcessRun(){
	
}

void Enemy1::ProcessJumpStanby(){
	
}

void Enemy1::ProcessJump(){
	
}

void Enemy1::ProcessFlight(){
	showImage = image[0];

	if (onY == eConnect_Down){
		nextState = eState_Stand;
	}
	else{
		
	}
}

void Enemy1::ProcessBend(){
	showImage = image[3];

	if (duration<0){
		nextState = eState_Flight;
	}
	if(duration%3)transmittance = 128;
}

void Enemy1::ProcessStun(){
	showImage = image[3];

	if (duration <= 0){
		nextState = eState_Flight;
		def = 20;
		balance = 100;
	}
	if (duration % 3)transmittance = 128;
}

void Enemy1::ProcessShootStanby(){
	showImage = image[1];

	if (duration <= 0){
		if (direction == eDirection_Right){
			solidShoot->Generate(40, 10, 10, -5, false,1,x + width, y + 48, 32, 16,8*direction,0,direction);
			solidShoot->SetImage(image[4]);
		}
		else{
			solidShoot->Generate(40, 10, 10, -5, false,1, x -64, y + 48, 32, 16, 8*direction, 0,direction);
			solidShoot->SetImage(image[4]);
		}
		nextState = eState_Shoot;
		duration = 12;
		shootTime = 240;
	}
}

void Enemy1::ProcessShoot(){
	showImage = image[2];

	if (duration <= 0){
		nextState = eState_Stand;
	}
}

void Enemy1::SolidShootInitialize(RectangularSolidShoot* setSolidShoot){
	solidShoot = setSolidShoot;
}
