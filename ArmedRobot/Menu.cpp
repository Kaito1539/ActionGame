#include "Menu.h"

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
}
const static int STAGE0_Y = 270;
const static int STAGE1_Y = 300;    //「ステージ1」文字のy位置
const static int STAGE2_Y = 330;    
const static int STAGE3_Y = 360;    
const static int CONFIG_Y = 390;    
const static int SPACE = 30;

typedef enum{
	eMenu_Stage0,
	eMenu_Stage1,        //ゲーム
	eMenu_Stage2,        //ゲーム
	eMenu_Stage3,        //ゲーム
	eMenu_Config,    //設定

	eMenu_Num,        //本項目の数
} eMenu;

static int NowSelect = eMenu_Stage0;    

//初期化
void Menu::Initialize(){
	mImageHandle = LoadGraph("images/TitleBack.bmp");    //画像のロード
}

//更新
void Menu::Update(){
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1){//下キーが押されていたら
		NowSelect = (NowSelect + 1) % eMenu_Num;//選択状態を一つ下げる
	}
	if (Keyboard_Get(KEY_INPUT_UP) == 1){//上キーが押されていたら
		NowSelect = (NowSelect + (eMenu_Num - 1)) % eMenu_Num;//選択状態を一つ上げる
	}
	if (Keyboard_Get(KEY_INPUT_RETURN) == 1){//エンターキーが押されたら
		switch (NowSelect){//現在選択中の状態によって処理を分岐
		case eMenu_Stage0://ステージ1選択中なら
			mSceneChanger->ChangeScene(eScene_Stage0);
			break;
		case eMenu_Stage1://ステージ1選択中なら
			mSceneChanger->ChangeScene(eScene_Stage1);
			break;
		case eMenu_Stage2://ステージ1選択中なら
			mSceneChanger->ChangeScene(eScene_Stage2);
			break;
		case eMenu_Stage3://ステージ1選択中なら
			mSceneChanger->ChangeScene(eScene_Stage3);
			break;
		case eMenu_Config://設定選択中なら
			mSceneChanger->ChangeScene(eScene_Config);//シーンを設定画面に変更
			break;
		}
	}

}

//描画
void Menu::Draw(){
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ

	DrawString(280, STAGE0_Y, "チュートリアル", GetColor(255, 255, 255));
	for (int i = 1; i <= eMenu_Stage3; i++) {
		DrawFormatString(280, STAGE0_Y+SPACE*i , GetColor(255, 255, 255), "ステージ%d", i);
	}
	DrawString(280, CONFIG_Y, "設定", GetColor(255, 255, 255));
	for (int i = 0; i <= eMenu_Stage3; i++) {
		if(saveData.clear[i])DrawFormatString(480, STAGE0_Y + SPACE * i, GetColor(255, 255, 255), "CLEAR");
	}
	int y = 0;
	y = STAGE0_Y + NowSelect * SPACE;
	DrawString(250, y, "■", GetColor(255, 255, 255));
	DrawString(64, 480, "基本的にXboxコントローラーでの操作を想定しています。キーボードでもプレイは可能です。", GetColor(255, 255, 255));
	DrawString(96, 510, "Xboxコントローラーのアナログパッド(もしくはキーボードの十字キー)で選択し、", GetColor(255, 255, 255));
	DrawString(256, 540, "startボタン(Enterキー)で開始してください。", GetColor(255, 255, 255));
}
