#include "Boss1.h"
//初期化
void Boss1::Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID, Player* setPlayer){
	LoadDivGraph("images/boss1-5.bmp", 8, 2, 4, 256, 96, image);
	LoadDivGraph("images/bossShoot.bmp", 4, 2, 2, 22, 10, &image[8]);
	showImage = image[0];
	x = setX;
	y = setY;
	width = eWidth_Normal;
	height = eHeight_Normal;
	ax = ay = vx = vy = 0;
	direction = eDirection_Left;
	hp = 500;
	atk = 10;
	blowX = 10;
	blowY = -10;
	def = 20;
	balance = 200;
	alive = true;
	piID = setID;
	player = setPlayer;
	atkTime = 120;
	nowState = eState_Flight;
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
void Boss1::Update(){
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
	atkTime--;
	imageFrame--;
	transmittance = 256;
	Move();
}

//描画
void Boss1::Draw(int setStartScreenX, int setStartScreenY){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, transmittance);
	if (direction == eDirection_Right){
		DrawGraph(x - setStartScreenX + width / 2 - 128, y - setStartScreenY, showImage, TRUE);
	}
	else{
		DrawTurnGraph(x - setStartScreenX + width / 2-128, y - setStartScreenY, showImage, TRUE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 256);
}

void Boss1::Move(){
	duration--;

	ay++;//重力
	if (onY == eConnect_Down&&vy>0){
		vy = 0;
	}

	if (balance <= 0 && nowState != eState_Stun){
		nextState = eState_Stun;
		duration = 40;
	}
	nowState = nextState;

	switch (nowState) {
	case  eState_Stand:
		ProcessStand();
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

	case  eState_Slash_Stanby:
		ProcessSlashStanby();
		break;
	case  eState_Rush_Slash:
		ProcessRushSlash();
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

void Boss1::ProcessStand(){
	
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
				//前フレームがスタンドでなかった場合
				showImage = image[0];
			}
		}
		imageFrame = IMAGE_CHANGE_FRAME;
	}

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
	if (atkTime < 0){
		
		if (player->GetY()<(y + height / 2) && player->GetY() + player->GetHeight()>(y + height / 2)){
			nextState = eState_Slash_Stanby;
			duration = 12;
		}
		

		if (hp <= 300){
			if (GetRand(3) == 3){
				nextState = eState_Shoot_Stanby;
				duration = 12;
			}
		}
	}
}



void Boss1::ProcessJumpStanby(){

}

void Boss1::ProcessJump(){

}

void Boss1::ProcessFlight(){
	showImage = image[0];

	if (onY == eConnect_Down){
		nextState = eState_Stand;
	}
	else{

	}
}

void Boss1::ProcessBend(){
	showImage = image[0];
	slash->Finalize();
	if (height == eHeight_Dash){
		height = eHeight_Normal;
		y -= eHeight_Normal - eHeight_Dash;
	}
	if (duration<0){
		nextState = eState_Flight; 
		if (y < MAPCHIP_SIZE * 4){
			vy = -10;
		}
	}
	if (duration % 3)transmittance = 164;
}

void Boss1::ProcessStun(){
	showImage = image[0];
	slash->Finalize();
	if (height == eHeight_Dash){
		height = eHeight_Normal;
		y -= eHeight_Normal - eHeight_Dash;
	}
	if (duration <= 0){
		nextState = eState_Flight;
		def = 20;
		balance = 150;
	}
	if (duration % 2)transmittance = 164;
}

void Boss1::ProcessShootStanby(){
	showImage = image[6];

	if (duration <= 0){
		if (direction == eDirection_Right){
			solidShoot->Generate(60, 10, 10, -5, false, 1, x + width, y + 21, 22, 10, 16 * direction, 0, direction);
		}
		else{
			solidShoot->Generate(60, 10, 10, -5, false, 1, x - 22, y + 21, 22, 10, 16 * direction, 0, direction);
		}
		solidShoot->SetImage(image[8]);
		nextState = eState_Shoot;
		duration = 12;
		atkTime = 36;
	}
}

void Boss1::ProcessShoot(){
	showImage = image[6];

	if (duration <= 0){
		nextState = eState_Stand;
	}
}


void Boss1::ProcessSlashStanby(){
	height = eHeight_Dash;
	showImage = image[5];
	if (duration <= 0){
		slash->Generate(80, 10, -5, -22, false);
		nextState = eState_Rush_Slash;
		duration = 128;
	}
}

void Boss1::ProcessRushSlash(){
	showImage = image[5];
	vx = 10 * direction;

	if (direction == eDirection_Right){
		slash->Update(x + width / 2, y+24, 116, height-24, direction);
	}
	else{
		slash->Update(x - 116 + width / 2, y+24, 116, height-24, direction);
	}
	if (onX != eConnect_Free){
		duration--;
	}
	if (duration <= 0){
		nextState = eState_Stand;
		slash->Finalize();
		atkTime = 36;
		height = eHeight_Normal;
		y -= eHeight_Normal - eHeight_Dash;
	}
}

void Boss1::SolidShootInitialize(RectangularSolidShoot* setSolidShoot){
	solidShoot = setSolidShoot;
}

void Boss1::SlashInitialize(RectangularSlash* setSlash){
	slash = setSlash;
}


void Boss1::SetDamage(int setDamage, int setStun, int setVX, int setVY, int setID){
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
	if (balance <= 40){
		vx = setVX;
		vy = setVY;
	}
	else{
		vx = setVX;
		vy = setVY/2;
	}
	
	
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