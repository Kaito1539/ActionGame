#include "Player.h"


//初期化
void Player::Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID){
	LoadDivGraph("images/player2-7.bmp", 100,10, 10, 96, 96, image);
	LoadDivGraph("images/player3.bmp", 4, 2, 2, 96, 64, &image[100]);
	LoadDivGraph("images/playerFrontSlash.bmp", 4, 2, 2, 144, 96, &image[104]);
	LoadDivGraph("images/playerUpperSlash.bmp", 4, 2, 2, 144, 96, &image[108]);
	LoadDivGraph("images/playerSweepSlash.bmp", 4, 2, 2, 144, 96, &image[112]);
	LoadDivGraph("images/playerBeamShoot.bmp", 4, 2, 2, 32, 16, &image[116]);
	LoadDivGraph("images/playerFrontSlash2.bmp", 4, 2, 2, 192, 96, &image[120]);
	LoadDivGraph("images/playerAirDownSlash.bmp", 4, 2, 2, 144, 96, &image[124]);
	LoadDivGraph("images/meter2.bmp", 4, 2, 2, 128, 128, meterImage);
	LoadDivGraph("images/marker2.bmp", 2, 2, 1, 192, 256, markerImage);
	LoadDivGraph("images/number.bmp", 4, 4, 1, 32, 64, numberImage);
	showImage = image[0];
	x = setX;
	y = setY;
	width = eWidth_Normal;
	height = eHeight_Normal;
	ax = ay = vx = vy = 0;
	direction = eDirection_Right;
	hp = MAX_HP;
	atk = 10;
	blowX = 10;
	blowY = -10;
	def = 50;
	balance = 100;
	alive = true;
	piID = setID;
	slashBind = 16;
	nextBulletNum = 0;
	remainBullet = 3;
	reloadCounter = 0;
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
void Player::Update(){
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
	transmittance = 256;
	//操作受付
	Move();
	HpMeterUpdate();
	for (int i = 0; i < PLAYER_BULLET_MAX; i++){
		if (beamShoot[i]->GetAlive()){
			if (shootBind % 6 == 0){
				shootImageNumber++;
				if (shootImageNumber >= 120)shootImageNumber = 116;
				beamShoot[i]->SetImage(image[shootImageNumber]);
			}
		}
	}
	
}

//描画
void Player::Draw(int setStartScreenX, int setStartScreenY){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,  transmittance);
	if (direction == eDirection_Right){
		//DrawBox(x - setStartScreenX, y - setStartScreenY, x - setStartScreenX + width, y - setStartScreenY + height, GetColor(200, 0, 0), true);
		//DrawBox(x - setStartScreenX + width / 2, y - setStartScreenY + 5, x - setStartScreenX + width, y - setStartScreenY + height / 2, GetColor(255, 255, 255), true);

		if (width == eWidth_Normal){
			DrawGraph(x - setStartScreenX - 16, y - setStartScreenY, showImage, TRUE);
		}
		else if (width == eWidth_Dash){
			DrawGraph(x - setStartScreenX - 8, y - setStartScreenY, showImage, TRUE);
		}
	}
	else{
		//DrawBox(x - setStartScreenX, y - setStartScreenY, x - setStartScreenX + width, y - setStartScreenY + height, GetColor(200, 0, 0), true);
		//DrawBox(x - setStartScreenX, y - setStartScreenY + 5, x - setStartScreenX + width / 2, y - setStartScreenY + height / 2, GetColor(255, 255, 255), true);
		if (width == eWidth_Normal){
			DrawTurnGraph(x - setStartScreenX - 16, y - setStartScreenY, showImage, TRUE);
		}
		else if (width == eWidth_Dash){
			DrawTurnGraph(x - setStartScreenX - 8, y - setStartScreenY, showImage, TRUE);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 256);
	HpMeterDraw();
}
/*
void Player::SetPostX(int setPostX){
postX = setPostX;
}

void Player::SetPostY(int setPostY){
postY = setPostY;
}

void Player::SetOnX(){
if (vx > 0){
onX = eConnect_Right;
}
else{
onX = eConnect_Left;
}
}

void Player::SetOnY(){
if (vy > 0){
onY = eConnect_Down;
}
else{
onY = eConnect_Up;
}
}
*/
void Player::Move(){
	duration--;
	imageFrame--;
	slashBind--;
	shootBind--;
	reloadCounter++;
	if (reloadCounter > RELOAD_FRAME){
		remainBullet++;
		if (remainBullet > 3){
			remainBullet = 3;
		}
		reloadCounter = 0;
	}
	ay++;//重力
	if (onY == eConnect_Down){
		avoidBind = 0;
		if (vy>0){
			vy = 0;
		}
	}
	

	if (balance <= 0 && nowState != eState_Stun){
		nextState = eState_Stun;
		duration = 32;
	}

	if (Keyboard_Get(KEY_INPUT_V) != 0&&avoidBind<=0){
		nextState = eState_Avoidance;
		avoidBind = 1;
		duration = AVOIDANCE_FRAME;
		width = eWidth_Crouch;
		height = eHeight_Crouch;
		if (Keyboard_Get(KEY_INPUT_LEFT)!=0/*&&direction==eDirection_Right*/){
			vy = -12;
			vx = -12;
			direction = eDirection_Right;
		}
		else if (Keyboard_Get(KEY_INPUT_RIGHT) != 0 /*&& direction == eDirection_Left*/){
			vy = -12;
			vx = 12;
			direction = eDirection_Left;
		}
		else {
			vy = -18;
			vx = -6*direction;
		}
	}

	if (nextState == eState_Bend || nextState == eState_Stun||nextState==eState_Avoidance){
		slash->Finalize();
		/*
		if (nowState == eState_Crouch) {
			checkXNum = (width + MAPCHIP_SIZE - 1) / MAPCHIP_SIZE + 1;
			//checkYNum = 1;
			for (int i = 0; i < checkXNum; i++) {
				if (width % MAPCHIP_SIZE == 0) {
					if (i == 0) {
						checkPointX[i] = x;
						checkPointPostX[i] = postX;
					}
					else {
						checkPointX[i] = checkPointX[0] + MAPCHIP_SIZE * i - 1;
						checkPointPostX[i] = checkPointPostX[0] + MAPCHIP_SIZE * i - 1;
					}
				}
				else {
					if (i == 0) {
						checkPointX[i] = x;
						checkPointPostX[i] = postX;
					}
					else if (i < checkXNum - 1) {
						checkPointX[i] = checkPointX[0] + MAPCHIP_SIZE * i - 1;
						checkPointPostX[i] = checkPointPostX[0] + MAPCHIP_SIZE * i - 1;
					}
					else {
						checkPointX[i] = checkPointX[0] + MAPCHIP_SIZE * (i - 1) - 1 + width % MAPCHIP_SIZE;
						checkPointPostX[i] = checkPointPostX[0] + MAPCHIP_SIZE * (i - 1) - 1 + width % MAPCHIP_SIZE;
					}
				}
			}
			checkPointY[0] = y;
			checkPointPostY[0] = checkPointY[0] - MAPCHIP_SIZE;

			for (int i = 0; i < checkXNum; i++) {
				if (mapData[checkPointPostY[0] / MAPCHIP_SIZE][checkPointX[i] / MAPCHIP_SIZE] > MAPCHIP_PASSABLE) {
					nextState = eState_Crouch;
					break;
				}
			}
		}
		*/
	}

	if (nowState != nextState){
		nowState = nextState;
		imageFrame = 0;
		SlashGenerate();
	}
	//関数を返す関数でまとめるのもありか？
	switch (nowState) {
	case  eState_Stand:
		ProcessStand();
		break;
	case  eState_Run:
		ProcessRun();
		break;
	case  eState_Dash:
		ProcessDash();
		break;
	case  eState_Crouch:
		ProcessCrouch();
		break;

	case  eState_Jump_Stanby:
		ProcessJumpStanby();
		break;
		/*
		case  eState_Jump:
		ProcessJump();
		break;
		*/
	case  eState_Flight:
		ProcessFlight();
		break;
	case  eState_Bend:
		ProcessBend();
		break;
	case  eState_Stun:
		ProcessStun();
		break;
	case  eState_Avoidance:
		ProcessAvoidance();
		break;
	case  eState_Slash_Stanby:
		ProcessSlashStanby();
		break;
	case  eState_Front_Slash1:
		ProcessFrontSlash1();
		break;
	case  eState_Front_Slash2:
		ProcessFrontSlash2();
		break;
	case  eState_Front_Slash3:
		ProcessFrontSlash3();
		break;
	case  eState_Upper_Slash:
		ProcessUpperSlash();
		break;
	case  eState_Sweep_Slash:
		ProcessSweepSlash();
		break;

	case  eState_Air_Front_Slash:
		ProcessAirFrontSlash();
		break;
	case  eState_Air_Down_Slash:
		ProcessAirDownSlash();
		break;
	case  eState_Shoot_Stanby:
		ProcessShootStanby();
		break;
	case  eState_Shoot:
		ProcessShoot();
		break;

	case eState_WallKick:
		ProcessWallKick();
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
	if (nextState != eState_Jump_Stanby){//正直これはひどい
		postX = x + (int)vx;
	}
	postY = y + (int)vy;

	MakeChecker();
	CheckMap();

	x = postX;
	y = postY;
}

void Player::ProcessStand(){
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
				showImage = image[1];
			}
		}
		imageFrame = IMAGE_CHANGE_FRAME;
	}

	vx = 0;//外に出して角バグ修正した

	if (onY == eConnect_Down){
		dashChecker = 0;

		if (Keyboard_Get(KEY_INPUT_DOWN) != 0){
			nextState = eState_Crouch;
		}
		else if (Keyboard_Get(KEY_INPUT_RIGHT) != 0){
			for (int i = 0; i < DASH_ACCEPT_FRAME; i++){
				if (Keyboard_Get(KEY_INPUT_RIGHT, i) == 1){
					dashChecker++;
				}
			}
			nextState = eState_Run;
			direction = eDirection_Right;
			duration = 2;
		}
		else if (Keyboard_Get(KEY_INPUT_LEFT) != 0){
			for (int i = 0; i < DASH_ACCEPT_FRAME; i++){
				if (Keyboard_Get(KEY_INPUT_LEFT, i) == 1){
					dashChecker++;
				}
			}
			nextState = eState_Run;
			direction = eDirection_Left;
			duration = 2;
		}

		if (dashChecker >= 2){
			nextState = eState_Dash;
			duration = 20;
		}

		if (Keyboard_Get(KEY_INPUT_C) == 1){//要修正
			nextState = eState_Jump_Stanby;
			duration = JUMP_STANDBY_FRAME;
		}
		else if (Keyboard_Get(KEY_INPUT_Z) == 1 && slashBind <= 0){
			nextState = eState_Slash_Stanby;
			duration = SLASH_STANDBY_FRAME;
		}
		else if (Keyboard_Get(KEY_INPUT_X) ==1 && remainBullet > 0){
			nextState = eState_Shoot_Stanby;
			duration = SHOOT_STANDBY_FRAME;
		}

		if (nextState == eState_Dash){
			width = eWidth_Dash;
			height = eHeight_Dash;
			y += eHeight_Normal - eHeight_Dash;
			if (direction == eDirection_Right){
				x -= eWidth_Dash - eWidth_Normal;
			}
		}
		else if (nextState == eState_Crouch){
			width = eWidth_Crouch;
			height = eHeight_Crouch;
			y += eHeight_Normal - eHeight_Crouch;
		}
	}
	else{
		nextState = eState_Flight;
	}
}

void Player::ProcessRun(){
	if (imageFrame <= 0){
		for (int i = 10; i < 20; i++){
			if (showImage == image[i]){
				if (i == 19){
					showImage = image[10];
				}
				else{
					showImage = image[i + 1];
				}
				break;
			}
			if (i == 19){
				//前フレームがランでなかった場合
				showImage = image[12];
			}
		}
		imageFrame = IMAGE_CHANGE_FRAME;
	}
	if (onY == eConnect_Down){
		if (vx<eVelocity_Run_Limit&&vx>-eVelocity_Run_Limit){
			ax += eAccel_Run*direction;
		}

		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0 && direction == eDirection_Right){
			duration++;
		}
		else if (Keyboard_Get(KEY_INPUT_LEFT) != 0 && direction == eDirection_Left){
			duration++;
		}

		if (duration<0){
			nextState = eState_Stand;
		}

		if (Keyboard_Get(KEY_INPUT_C) == 1){//要修正
			nextState = eState_Jump_Stanby;
			duration = JUMP_STANDBY_FRAME;
		}
		else if (Keyboard_Get(KEY_INPUT_Z) == 1 && slashBind <= 0){
			nextState = eState_Slash_Stanby;
			duration = SLASH_STANDBY_FRAME;
		}
		else if (Keyboard_Get(KEY_INPUT_X) ==1 && remainBullet> 0){
			nextState = eState_Shoot_Stanby;
			duration = SHOOT_STANDBY_FRAME;
		}
	}
	else{
		nextState = eState_Flight;
	}
}

void Player::ProcessDash(){
	showImage = image[102];

	vx = eVelocity_Dash*direction;

	if (duration<0){
		nextState = eState_Crouch;
		width = eWidth_Crouch;
		height = eHeight_Crouch;
		if (direction == eDirection_Left){
			x += eWidth_Dash - eWidth_Crouch;
		}
	}
	else if (Keyboard_Get(KEY_INPUT_C) != 0 && onY == eConnect_Down){//要修正
		checkXNum = (width + MAPCHIP_SIZE - 1) / MAPCHIP_SIZE + 1;
		//checkYNum = 1;
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
		checkPointY[0] = y;
		checkPointPostY[0] = checkPointY[0] - MAPCHIP_SIZE;

		for (int i = 0; i < checkXNum; i++){
			if (mapData[checkPointPostY[0] / MAPCHIP_SIZE][checkPointX[i] / MAPCHIP_SIZE]>MAPCHIP_PASSABLE){
				break;
			}
			if (i == checkXNum - 1){
				vy = -eVelocity_Jump_Min;
				nextState = eState_Flight;
				y -= eHeight_Normal - eHeight_Crouch;
				width = eWidth_Normal;
				height = eHeight_Normal;
				if (direction == eDirection_Left){
					x += eWidth_Dash - eWidth_Crouch;
				}
			}
		}
	}
}

void Player::ProcessCrouch(){
	if (vx != 0){
		if (imageFrame <= 0){
			for (int i = 100; i < 102; i++){
				if (showImage == image[i]){
					if (i == 101){
						showImage = image[100];
					}
					else{
						showImage = image[i + 1];
					}
					break;
				}
				if (i == 101){
					//前フレームがクロークでなかった場合
					showImage = image[100];
				}
			}
			imageFrame = IMAGE_CHANGE_FRAME;
		}
	}
	else{
		showImage = image[100];
	}

	comboNum = 0;

	if (onY == eConnect_Down){
		vx = 0;
		if (Keyboard_Get(KEY_INPUT_DOWN) == 0){
			checkXNum = (width + MAPCHIP_SIZE - 1) / MAPCHIP_SIZE + 1;
			//checkYNum = 1;
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
			checkPointY[0] = y;
			checkPointPostY[0] = checkPointY[0] - MAPCHIP_SIZE;

			for (int i = 0; i < checkXNum; i++){
				if (mapData[checkPointPostY[0] / MAPCHIP_SIZE][checkPointX[i] / MAPCHIP_SIZE]>MAPCHIP_PASSABLE){
					break;
				}
				if (i == checkXNum - 1){
					nextState = eState_Stand;
					y -= eHeight_Normal - eHeight_Crouch;
					width = eWidth_Normal;
					height = eHeight_Normal;
				}
			}
		}

		if (Keyboard_Get(KEY_INPUT_Z) == 1 && slashBind <= 0){
			nextState = eState_Sweep_Slash;
			duration = SLASH_FRAME * 2 / 3;
			slash->Generate(Sweep_Slash_ATK, Sweep_Slash_STUN, Sweep_Slash_BLOW_X, Sweep_Slash_BLOW_Y, false);
			slashImageNumber = 113 + 1;
		}

		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0){
			direction = eDirection_Right;
			ax += eAccel_Crouch;
		}
		else if (Keyboard_Get(KEY_INPUT_LEFT) != 0){
			direction = eDirection_Left;
			ax -= eAccel_Crouch;
		}
	}
	else{
		nextState = eState_Flight;
		width = eWidth_Normal;
		height = eHeight_Normal;
	}
}

void Player::ProcessJumpStanby(){
	showImage = image[5];
	if (Keyboard_Get(KEY_INPUT_RIGHT)>0){
		if (vx<eVelocity_Run_Limit){
			ax += eAccel_Run;
		}
	}
	if (Keyboard_Get(KEY_INPUT_LEFT)>0){
		if (vx>-eVelocity_Run_Limit){
			ax -= eAccel_Run;
		}
	}
	if (duration<0){
		nextState = eState_Flight;
		vy = -eVelocity_Jump_Min;
	}
	else if (onY != eConnect_Down){
		nextState = eState_Flight;
		vy = -eVelocity_Jump_Min;
	}
}
/*
void Player::ProcessJump(){
showImage = image[6];

if (vx>eVelocity_Dash){
vx = eVelocity_Dash;
}
else if (vx<-eVelocity_Dash){
vx = -eVelocity_Dash;
}
vy = -eVelocity_Jump_Min;
duration = 0;
nextState = eState_Flight;
}
*/
void Player::ProcessFlight(){
	showImage = image[6];

	if (onY == eConnect_Down){
		nextState = eState_Stand;
	}
	else{
		if (Keyboard_Get(KEY_INPUT_C) != 0){
			if (vy <= 0){
				ay -= 0.35;
			}
		}
		else{
			//
		}
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0){
			if (vx<eVelocity_Run_Limit){
				if (direction == eDirection_Right){
					ax += eAccel_Run;
				}
				else{
					ax += eAccel_Run / 2;
				}

			}
		}
		else{
			if (vx>0 && vx <= eVelocity_Run_Limit){
				ax -= 0.5;
				if (vy < 0){
					ay += 1;
				}
			}
		}
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0){
			if (vx>-eVelocity_Run_Limit){
				if (direction == eDirection_Left){
					ax -= eAccel_Run;
				}
				else{
					ax -= eAccel_Run / 2;
				}
			}
		}
		else{
			if (vx<0 && vx >= -eVelocity_Run_Limit){
				ax += 0.5;
				if (vy < 0){
					ay += 1;
				}
			}
		}

	}

	if (Keyboard_Get(KEY_INPUT_Z) != 0 && slashBind <= 0){
		nextState = eState_Slash_Stanby;
		duration = SLASH_STANDBY_FRAME;
	}
	else if (Keyboard_Get(KEY_INPUT_X) != 0 && remainBullet>0){
		nextState = eState_Shoot_Stanby;
		duration = SHOOT_STANDBY_FRAME;
	}

	//壁蹴り
	if (((Keyboard_Get(KEY_INPUT_C) <= 4 && Keyboard_Get(KEY_INPUT_C) != 0)/* || (Keyboard_Get(KEY_INPUT_LEFT) <= 4 && Keyboard_Get(KEY_INPUT_LEFT) != 0)*/) && onX == eConnect_Right&&direction == eDirection_Right){//要修正　壁蹴り
		vy = -15;
		vx = -15;
		direction = eDirection_Left;
		duration = 12;
		nextState = eState_WallKick;
	}
	else if (((Keyboard_Get(KEY_INPUT_C) <= 4 && Keyboard_Get(KEY_INPUT_C) != 0) /*|| (Keyboard_Get(KEY_INPUT_RIGHT) <= 4 && Keyboard_Get(KEY_INPUT_RIGHT) != 0)*/) && onX == eConnect_Left&&direction == eDirection_Left){//要修正　壁蹴り
		vy = -15;
		vx = 15;
		direction = eDirection_Right;
		duration = 12;
		nextState = eState_WallKick;
	}
	if (nextState == eState_Crouch) {
		width = eWidth_Crouch;
		height = eHeight_Crouch;
		y += eHeight_Normal - eHeight_Crouch;
	}
}

void Player::ProcessWallKick(){
	//壁蹴り中に十字キー入力があっても壁蹴りに支障がなくなった。
	showImage = image[7];
	if (onY == eConnect_Down){
		nextState = eState_Stand;
	}
	else{
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0 && direction == eDirection_Right){
			if (vx<eVelocity_Run_Limit){
				ax += eAccel_Run;
			}
		}
		else{
			if (vx>0 && vx <= eVelocity_Run_Limit){
				ax -= 0.5;
				if (vy < 0){
					ay += 1;
				}
			}
		}
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0 && direction == eDirection_Left){
			if (vx>-eVelocity_Run_Limit){
				ax -= eAccel_Run;
			}
		}
		else{
			if (vx<0 && vx >= -eVelocity_Run_Limit){
				ax += 0.5;
				if (vy < 0){
					ay += 1;
				}
			}
		}

	}

	if (Keyboard_Get(KEY_INPUT_Z) != 0 && slashBind <= 0){
		nextState = eState_Slash_Stanby;
		duration = SLASH_STANDBY_FRAME;
	}
	else if (Keyboard_Get(KEY_INPUT_X) != 0 && remainBullet>0){
		nextState = eState_Shoot_Stanby;
		duration = SHOOT_STANDBY_FRAME;
	}

	if (((Keyboard_Get(KEY_INPUT_C) <= 4 && Keyboard_Get(KEY_INPUT_C) != 0) /*|| (Keyboard_Get(KEY_INPUT_LEFT) <= 4 && Keyboard_Get(KEY_INPUT_LEFT) != 0)*/) && onX == eConnect_Right&&direction == eDirection_Right){//要修正　壁蹴り
		vy = -15;
		vx = -15;
		direction = eDirection_Left;
	}
	else if (((Keyboard_Get(KEY_INPUT_C) <= 4 && Keyboard_Get(KEY_INPUT_C) != 0)/* || (Keyboard_Get(KEY_INPUT_RIGHT) <= 4 && Keyboard_Get(KEY_INPUT_RIGHT) != 0)*/) && onX == eConnect_Left&&direction == eDirection_Left){//要修正　壁蹴り
		vy = -15;
		vx = 15;
		direction = eDirection_Right;
	}

	if (duration <= 0){
		nextState = eState_Flight;
	}
}

void Player::ProcessBend(){
	showImage = image[8];

	width = eWidth_Normal;
	height = eHeight_Normal;
	if (duration < 0) {
		nextState = eState_Flight;
	}
	if (duration % 4)transmittance = 164;
}

void Player::ProcessStun(){
	showImage = image[8];

	width = eWidth_Normal;
	height = eHeight_Normal;
	if (duration<0){
		balance = 100;
		nextState = eState_Flight;
	}
	if (duration % 3)transmittance = 164;
}

void Player::ProcessAvoidance(){
	if (imageFrame <= 0){
		for (int i = 41; i < 43; i++){
			if (showImage == image[i]){
				showImage = image[i + 1];
				break;
			}
			if (i == 42){
				//前フレームがavoidでなかった場合
				showImage = image[41];
			}
		}
		imageFrame = AVOIDANCE_FRAME/2;
	}

	if (Keyboard_Get(KEY_INPUT_RIGHT) != 0){
		if (vx<eVelocity_Run_Limit){
			if (direction == eDirection_Right){
				ax += eAccel_Run;
			}
			else{
				ax += eAccel_Run / 2;
			}

		}
	}
	else{
		if (vx>0 && vx <= eVelocity_Run_Limit){
			ax -= 0.5;
			if (vy < 0){
				ay += 1;
			}
		}
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) != 0){
		if (vx>-eVelocity_Run_Limit){
			if (direction == eDirection_Left){
				ax -= eAccel_Run;
			}
			else{
				ax -= eAccel_Run / 2;
			}
		}
	}
	else{
		if (vx<0 && vx >= -eVelocity_Run_Limit){
			ax += 0.5;
			if (vy < 0){
				ay += 1;
			}
		}
	}
	if (Keyboard_Get(KEY_INPUT_Z) == 1){
		nextState = eState_Slash_Stanby;
		duration = SLASH_STANDBY_FRAME;
		width = eWidth_Normal;
		height = eHeight_Normal;
	}
	else if (Keyboard_Get(KEY_INPUT_X) == 1&&remainBullet>0){
		nextState = eState_Shoot_Stanby;
		duration = SHOOT_STANDBY_FRAME;
		width = eWidth_Normal;
		height = eHeight_Normal;
	}
	else if (duration <= 0){
		nextState = eState_Crouch;
		//nextState = eState_Flight;
		//width = eWidth_Normal;
		//height = eHeight_Normal;
	}
}

void Player::ProcessSlashStanby(){
	showImage = image[20];
	comboNum = 0;
	if (onY == eConnect_Down){
		vx = 0;
		if (Keyboard_Get(KEY_INPUT_UP) == 1){
			nextState = eState_Upper_Slash;
			duration = SLASH_FRAME;
		}
		else if (Keyboard_Get(KEY_INPUT_DOWN) == 1){
			nextState = eState_Sweep_Slash;
			duration = SLASH_FRAME;
			/*
			width = eWidth_Crouch;
			height = eHeight_Crouch;
			y += eHeight_Normal - eHeight_Crouch;
			*/
		}
	}
	else {
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
			nextState = eState_Air_Down_Slash;
			duration = SLASH_FRAME;
		}
	}


	if (duration <= 0){
		if (onY == eConnect_Down){
			if (Keyboard_Get(KEY_INPUT_UP) != 0){
				nextState = eState_Upper_Slash;
			}
			else if (Keyboard_Get(KEY_INPUT_DOWN) != 0){
				nextState = eState_Sweep_Slash;
			}
			else{
				nextState = eState_Front_Slash1;
			}
		}
		else{
			if (Keyboard_Get(KEY_INPUT_DOWN) != 0) {
				nextState = eState_Air_Down_Slash;
			}
			else {
				nextState = eState_Air_Front_Slash;
			}
		}
	}
}

void Player::ProcessFrontSlash1(){
	showImage = image[21];

	if (direction == eDirection_Right){
		slash->Update(x + width / 2, y, 144, height, direction);
	}
	else{
		slash->Update(x - 144 + width / 2, y, 144, height, direction);
	}
	if (duration % (SLASH_FRAME / 3) == 0)slashImageNumber++;
	slash->SetImage(image[slashImageNumber]);
	//Combo();
	if (duration <= 0){
		//comboNum++;
		Combo2();
		nextState = reserveState;
		slash->Finalize();
		slashBind = Front_Slash_BIND;
	}
}

void Player::ProcessFrontSlash2(){
	showImage = image[22];

	if (direction == eDirection_Right){
		slash->Update(x , y, 192, height, direction);
	}
	else{
		slash->Update(x - 192 + width, y, 192, height, direction);
	}
	if (duration % (SLASH_FRAME / 3) == 0)slashImageNumber++;
	slash->SetImage(image[slashImageNumber]);
	//Combo();
	if (duration <= 0){
		//comboNum++;
		Combo2();
		nextState = reserveState;
		slash->Finalize();
		slashBind = Front_Slash_BIND;
	}
}
void Player::ProcessFrontSlash3(){
	showImage = image[23];

	if (direction == eDirection_Right){
		slash->Update(x + width / 2, y, 144, height, direction);
	}
	else{
		slash->Update(x - 144 + width / 2, y, 144, height, direction);
	}
	if (duration % (SLASH_FRAME / 3) == 0)slashImageNumber++;
	slash->SetImage(image[slashImageNumber]);
	//Combo();
	if (duration <= 0){
		//comboNum++;
		Combo2();
		nextState = reserveState;
		slash->Finalize();
		slashBind = Front_Slash_BIND;
	}
}

void Player::ProcessUpperSlash(){
	showImage = image[24];

	vx = 2 * direction;
	vy = -16;
	if (direction == eDirection_Right){
		slash->Update(x + width / 2, y - 16, 144, 32, direction);
	}
	else{
		slash->Update(x - 144 + width / 2, y - 16, 144, 32, direction);
	}
	if (duration % (SLASH_FRAME / 3) == 0)slashImageNumber++;
	slash->SetImage(image[slashImageNumber]);
	//Combo();
	if (duration <= 0){
		//comboNum++;
		Combo2();
		if (reserveState == eState_Stand)nextState = eState_Flight;
		else nextState = reserveState;
		slash->Finalize();
		slashBind = Front_Slash_BIND;
	}
}

void Player::ProcessSweepSlash(){
	showImage = image[103];

	vx = 0;
	if (height != eHeight_Crouch){
		width = eWidth_Crouch;
		height = eHeight_Crouch;
		y += eHeight_Normal - eHeight_Crouch;
	}

	if (direction == eDirection_Right){
		slash->Update(x - 16, y, 144, 96, direction);
	}
	else{
		slash->Update(x - 16 - 48, y, 144, 96, direction);
	}
	if (duration % (SLASH_FRAME / 3) == 0)slashImageNumber++;
	slash->SetImage(image[slashImageNumber]);
	//Combo();
	if (duration <= 0){

		if (onY == eConnect_Down){
			vx = 0;
			checkXNum = (width + MAPCHIP_SIZE - 1) / MAPCHIP_SIZE + 1;
			//checkYNum = 1;
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
			checkPointY[0] = y;
			checkPointPostY[0] = checkPointY[0] - MAPCHIP_SIZE;

			for (int i = 0; i < checkXNum; i++){
				if (mapData[checkPointPostY[0] / MAPCHIP_SIZE][checkPointX[i] / MAPCHIP_SIZE]>MAPCHIP_PASSABLE){
					reserveState = eState_Crouch;
					break;
				}
				if (i == checkXNum - 1){
					nextState = eState_Stand;
					y -= eHeight_Normal - eHeight_Crouch;
					width = eWidth_Normal;
					height = eHeight_Normal;
				}

			}
		}
		else{
			nextState = eState_Flight;
			y -= eHeight_Normal - eHeight_Crouch;
			width = eWidth_Normal;
			height = eHeight_Normal;
		}
		//comboNum++;
		if (height == eHeight_Normal){
			Combo2();
			nextState = reserveState;
		}
		else{
			nextState = eState_Crouch;
		}


		slash->Finalize();
		slashBind = Front_Slash_BIND;
	}
}

void Player::ProcessAirFrontSlash(){
	showImage = image[21];
	if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
		if (vx < eVelocity_Run_Limit) {
			if (direction == eDirection_Right) {
				ax += eAccel_Run / 2;
			}
			else {
				ax += eAccel_Run / 4;
			}

		}
	}
	else {
		if (vx > 0 && vx <= eVelocity_Run_Limit) {
			ax -= 0.5;
			if (vy < 0) {
				ay += 1;
			}
		}
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
		if (vx > -eVelocity_Run_Limit) {
			if (direction == eDirection_Left) {
				ax -= eAccel_Run / 2;
			}
			else {
				ax -= eAccel_Run / 4;
			}
		}
	}
	else {
		if (vx < 0 && vx >= -eVelocity_Run_Limit) {
			ax += 0.5;
			if (vy < 0) {
				ay += 1;
			}
		}
	}

	if (onY == eConnect_Down){
		vx = 0;
	}
	if (direction == eDirection_Right){
		slash->Update(x + width / 2, y, 144, height, direction);
	}
	else{
		slash->Update(x - 144 + width / 2, y, 144, height, direction);
	}
	if (duration % (SLASH_FRAME / 3) == 0)slashImageNumber++;
	slash->SetImage(image[slashImageNumber]);
	//Combo();
	if (duration <= 0){
		//comboNum++;
		Combo2();
		if (reserveState == eState_Stand)nextState = eState_Flight;
		else nextState = reserveState;
		slash->Finalize();
		slashBind = Front_Slash_BIND;
	}
}

void Player::ProcessAirDownSlash() {
	showImage = image[23];
	if (Keyboard_Get(KEY_INPUT_RIGHT) != 0) {
		if (vx < eVelocity_Run_Limit) {
			if (direction == eDirection_Right) {
				ax += eAccel_Run/2;
			}
			else {
				ax += eAccel_Run / 4;
			}

		}
	}
	else {
		if (vx > 0 && vx <= eVelocity_Run_Limit) {
			ax -= 0.5;
			if (vy < 0) {
				ay += 1;
			}
		}
	}
	if (Keyboard_Get(KEY_INPUT_LEFT) != 0) {
		if (vx > -eVelocity_Run_Limit) {
			if (direction == eDirection_Left) {
				ax -= eAccel_Run/2;
			}
			else {
				ax -= eAccel_Run / 4;
			}
		}
	}
	else {
		if (vx < 0 && vx >= -eVelocity_Run_Limit) {
			ax += 0.5;
			if (vy < 0) {
				ay += 1;
			}
		}
	}

	if (direction == eDirection_Right) {
		slash->Update(x + width / 2, y+16 , 144, 32, direction);
	}
	else {
		slash->Update(x - 144 + width / 2, y+16 , 144, 32, direction);
	}
	
	if (slashImageNumber<=126) {
		if (duration % (SLASH_FRAME / 4) == 0)slashImageNumber++;
	}
	else {
		if (duration % (SLASH_FRAME / 4) == 0)slashImageNumber--;
	}
	slash->SetImage(image[slashImageNumber]);
	
	if (duration <= 0) {
		nextState = eState_Flight;
		slash->Finalize();
		slashBind = Front_Slash_BIND;
	}

	if (onY == eConnect_Down) {
		vx = 0;
		//vy = 0;
		nextState = eState_Flight;
		slash->Finalize();
		slashBind = Front_Slash_BIND;
	}
}


void Player::ProcessShootStanby(){
	if (Keyboard_Get(KEY_INPUT_UP) != 0){
		showImage = image[26];
	}
	else{
		showImage = image[25];
	}
	
	if (onY == eConnect_Down){
		vx = 0;
	}
	if (duration <= 0){
		if (Keyboard_Get(KEY_INPUT_UP) != 0){
			if (direction == eDirection_Right){
				beamShoot[nextBulletNum]->Generate(40, 4, 3, -5, false, 32, x + width, y , 16, 32, 0, -24, direction);
			}
			else{
				beamShoot[nextBulletNum]->Generate(40, 4, 3, -5, false, 32, x, y, 16, 32, 0, -24, direction);
			}
		}
		else{
			if (direction == eDirection_Right){
				beamShoot[nextBulletNum]->Generate(40, 4, 3, -5, false, 32, x + width, y + 48, 32, 16, 24 * direction, 0, direction);
			}
			else{
				beamShoot[nextBulletNum]->Generate(40, 4, 3, -5, false, 32, x - 64, y + 48, 32, 16, 24 * direction, 0, direction);
			}
		}
		remainBullet--;
		shootImageNumber = 116;
		beamShoot[nextBulletNum]->SetImage(image[shootImageNumber]);
		shootBind = Shoot_BIND;
		nextState = eState_Shoot;
		duration = 12;
		if (nextBulletNum < PLAYER_BULLET_MAX-1){
			nextBulletNum++;
		}
		else{
			nextBulletNum = 0;
		}
	}
}

void Player::ProcessShoot(){
	if (Keyboard_Get(KEY_INPUT_UP) != 0){
		showImage = image[26];
	}
	else{
		showImage = image[25];
	}

	if (onY == eConnect_Down){
		vx = 0;
	}
	if (Keyboard_Get(KEY_INPUT_X) == 1&&remainBullet>0){
		nextState = eState_Shoot_Stanby;
		duration = SHOOT_STANDBY_FRAME;
	}
	if (duration <= 0){

		if (onY == eConnect_Down){
			nextState = eState_Stand;
		}
		else{
			nextState = eState_Flight;
		}
	}
}

void Player::SlashInitialize(RectangularSlash* setSlash){
	slash = setSlash;
}

void Player::BeamShootInitialize(RectangularBeamShoot* setBeamShoot,int setNum){
	beamShoot[setNum] = setBeamShoot;
}

void Player::HpMeterUpdate(){
	HpAngle = MIN_HP_ANGLE + ((MAX_HP_ANGLE - MIN_HP_ANGLE)*hp / MAX_HP);
}

void Player::HpMeterDraw(){
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, 160, 160, GetColor(255, 255, 255), TRUE);
	double ang = MIN_HP_ANGLE;
	for (int i = 0; i <= HP_METER_DIVIDE_NUM; i++){
		if (i < HP_METER_DIVIDE_NUM / 4){
			DrawLine(80 + (int)(60 * cos(ang)), 80 + (int)(60 * sin(ang)), 80 + (int)(30 * cos(ang)), 80 + (int)(30 * sin(ang)), GetColor(255, 0, 0));
		}
		else if (i < HP_METER_DIVIDE_NUM / 2){
			DrawLine(80 + (int)(60 * cos(ang)), 80 + (int)(60 * sin(ang)), 80 + (int)(30 * cos(ang)), 80 + (int)(30 * sin(ang)), GetColor(220, 220, 0));
		}
		else{
			DrawLine(80 + (int)(60 * cos(ang)), 80 + (int)(60 * sin(ang)), 80 + (int)(30 * cos(ang)), 80 + (int)(30 * sin(ang)), GetColor(0, 0, 255));
		}
		ang += (MAX_HP_ANGLE - MIN_HP_ANGLE) / HP_METER_DIVIDE_NUM;
	}
	DrawLine(80, 80, 80 + (int)(60 * cos(HpAngle)), 80 + (int)(60 * sin(HpAngle)), GetColor(0, 0, 0));
	DrawFormatString(75, 120, GetColor(0, 0, 0), "HP");

	
	DrawGraph(SCREEN_SIZE_X - 192, 0, markerImage[GetInputSystem()], true);
	DrawGraph(SCREEN_SIZE_X - 32, 64, numberImage[remainBullet], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 256);
	/*
	SelectObject(hDC, GetStockObject(DC_PEN));
	SelectObject(hDC, GetStockObject(DC_BRUSH));
	SetDCPenColor(hDC, RGB(0x00, 0x66, 0x99));
	SetDCBrushColor(hDC, RGB(0x00, 0xCC, 0xFF));
	Pie(hDC,0,0,128,128,128,128,0,128);
	DrawGraph(0,0,meterImage[3],true);
	*/
}

void Player::SlashGenerate(){
	if (nextState == eState_Front_Slash1){
		slash->Generate(Front_Slash1_ATK, Front_Slash1_STUN, Front_Slash1_BLOW_X, Front_Slash1_BLOW_Y, false);
		slashImageNumber = 104 - 1;
		duration = SLASH_FRAME;
	}
	else if (nextState == eState_Front_Slash2){
		slash->Generate(Front_Slash2_ATK, Front_Slash2_STUN, Front_Slash2_BLOW_X, Front_Slash2_BLOW_Y, false);
		slashImageNumber = 120 - 1;
		duration = SLASH_FRAME;
	}
	else if (nextState == eState_Front_Slash3) {
		slash->Generate(Front_Slash3_ATK, Front_Slash3_STUN, Front_Slash3_BLOW_X, Front_Slash3_BLOW_Y, false);
		slashImageNumber = 104 - 1;
		duration = SLASH_FRAME;
	}
	else if (nextState == eState_Upper_Slash){
		slash->Generate(Upper_Slash_ATK, Upper_Slash_STUN, Upper_Slash_BLOW_X, Upper_Slash_BLOW_Y, true);
		slashImageNumber = 108 - 1;
		duration = SLASH_FRAME;
	}
	else if (nextState == eState_Sweep_Slash){
		slash->Generate(Sweep_Slash_ATK, Sweep_Slash_STUN, Sweep_Slash_BLOW_X, Sweep_Slash_BLOW_Y, false);
		slashImageNumber = 112 - 1;
		duration = SLASH_FRAME;
	}
	else if (nextState == eState_Air_Front_Slash){
		slash->Generate(Air_Front_Slash_ATK, Air_Front_Slash_STUN, Air_Front_Slash_BLOW_X, Air_Front_Slash_BLOW_Y, false);
		slashImageNumber = 104 - 1;
		duration = SLASH_FRAME;
	}
	else if (nextState == eState_Air_Down_Slash) {
		slash->Generate(Air_Down_Slash_ATK, Air_Down_Slash_STUN, Air_Down_Slash_BLOW_X, Air_Down_Slash_BLOW_Y, true);
		slashImageNumber = 124 - 1;
		duration = AIR_DOWN_SLASH_FRAME;
	}
}

void Player::Combo(){
	if (comboNum < COMBO_MAX){
		if (duration <= SLASH_FRAME && Keyboard_Get(KEY_INPUT_Z) != 0 && Keyboard_Get(KEY_INPUT_Z) <= SLASH_FRAME * 10000){//コンボ
			if (onY == eConnect_Down){
				if (Keyboard_Get(KEY_INPUT_UP) != 0){
					reserveState = eState_Upper_Slash;
				}
				else if (Keyboard_Get(KEY_INPUT_DOWN) != 0){
					reserveState = eState_Sweep_Slash;

				}
				else{
					reserveState = eState_Front_Slash1;
				}
			}
			else{
				reserveState = eState_Air_Front_Slash;
			}
		}
		if (nowState == reserveState){
			reserveState = eState_Stand;
		}
	}
	else{
		reserveState = eState_Stand;
	}
}

void Player::Combo2(){
	comboNum++;
	comboApplication = false;
	reserveState = eState_Stand;
	if (comboNum < COMBO_MAX){
		for (int i = 0; i < COMBO_ACCEPT_FRAME; i++){
			if (Keyboard_Get(KEY_INPUT_Z, i) == 1){
				comboApplication = true;
			}
		}
		if (comboApplication){
			if (onY == eConnect_Down){
				for (int i = COMBO_ACCEPT_FRAME - 1; i >= 0; i--){
					if (i == 0 && nowState != eState_Front_Slash1/*&&reserveState==eState_Stand*/){
						reserveState = eState_Front_Slash1;
					}
					if (Keyboard_Get(KEY_INPUT_UP, i) == 1 && nowState != eState_Upper_Slash){
						reserveState = eState_Upper_Slash;
						break;
					}
					else if (Keyboard_Get(KEY_INPUT_DOWN, i) == 1 && nowState != eState_Sweep_Slash){
						reserveState = eState_Sweep_Slash;
						break;
					}
					else if(nowState==eState_Front_Slash2){
						reserveState = eState_Front_Slash3;
					}
					else{
						reserveState = eState_Front_Slash2;
					}
				}
			}
			else{
				for (int i = COMBO_ACCEPT_FRAME - 1; i >= 0; i--) {
					if (Keyboard_Get(KEY_INPUT_DOWN, i) == 1 && nowState != eState_Air_Down_Slash) {
						reserveState = eState_Air_Down_Slash;
						break;
					}
					else {
						reserveState = eState_Air_Front_Slash;
					}
				}
			}
		}
		else{
			reserveState = eState_Stand;
		}
	}
	else{
		reserveState = eState_Stand;
	}
}

