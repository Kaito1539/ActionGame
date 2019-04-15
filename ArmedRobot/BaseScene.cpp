#include "BaseScene.h"


BaseScene::BaseScene(ISceneChanger* changer) :
mImageHandle(0) {
	mSceneChanger = changer;
}

void BaseScene::Finalize(){
	DeleteGraph(mImageHandle);
}

void BaseScene::Draw(){
	//DrawGraph(0, 0, mImageHandle, FALSE);
	DrawRotaGraph(SCREEN_SIZE_X / 2, SCREEN_SIZE_Y / 2, 4.0, 0, mImageHandle, false);
}