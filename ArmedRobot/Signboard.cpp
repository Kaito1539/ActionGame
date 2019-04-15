#include "Signboard.h"
//èâä˙âª
void Signboard::Initialize(int setMap[MAP_HEIGHT_MAX][MAP_WIDTH_MAX], int setMapH, int setMapW, int setX, int setY, int* setID) {
	LoadDivGraph("images/signboard.bmp", 4, 2,2,64, 64, image);
	LoadDivGraph("images/signContents.bmp", 1, 1, 1, SCREEN_SIZE_X, CONTENTSAREA_HEIGHT, &image[4]);
	showImage = image[0];
	contentsImage = image[4];
	x = setX;
	y = setY;
	width = eWidth_Normal;
	height = eHeight_Normal;
	ax = ay = vx = vy = 0;
	direction = eDirection_Left;
	hp = 1;
	atk = 0;
	blowX = 0;
	blowY = 0;
	def = 1;
	balance = 100;
	alive = true;
	piID = setID;
	nowState = eState_Flight;
	for (int i = 0; i < setMapH; i++) {
		for (int j = 0; j < setMapW; j++) {
			mapData[i][j] = setMap[i][j];
		}
	}

	for (int i = 0; i < 10; i++) {
		invalidID[i] = -1;
	}
	duration = 0;

}

void Signboard::SetContents(char** setContents) {
	for (int i = 0; i < CONTENTS_ROW_NUM; i++) {
		contents[i] = setContents[i];
	}
}

//çXêV
void Signboard::Update() {
	ax = ay = vx=vy=0;
	if (hp <= 0) {
		alive = false;
	}
	showContents = false;
	duration++;
	if (duration % 8 == 0)imageFrame++;
	imageFrame  %= 2;
	
	showImage = image[imageFrame];
}

//ï`âÊ
void Signboard::Draw(int setStartScreenX, int setStartScreenY) {
	DrawGraph(x - setStartScreenX , y - setStartScreenY, showImage, TRUE);
}

void Signboard::Show() {
	showContents = true;
	imageFrame += 2;
	showImage = image[imageFrame];
}

bool Signboard::GetShowContents() {
	return showContents;
}

void Signboard::DrawContents(int setStartScreenX, int setStartScreenY) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawGraph(0, SCREEN_SIZE_Y - CONTENTSAREA_HEIGHT, contentsImage, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 256);
	for (int i = 0; i < CONTENTS_ROW_NUM; i++) {
		DrawString(16, SCREEN_SIZE_Y - CONTENTSAREA_HEIGHT + 8 + 32 * i, contents[i], GetColor(0, 0, 0));
	}
}