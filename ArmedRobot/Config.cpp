#include "Config.h"


Config::Config(ISceneChanger* changer) : BaseScene(changer) {
}


typedef enum{
	eConfig_Control,
	eConfig_BGM,
	eConfig_Num,        //本項目の数
} eConfig;

typedef enum{
	eConfigY_Control=300,
	eConfigY_BGM=330,
} eConfigY;

typedef enum{
	eControl_Keyboard,
	eControl_Joypad,
	eControl_Num,        //本項目の数
} eControl;

static int NowSelect = eConfig_Control;

//初期化
void Config::Initialize(){
	mImageHandle = LoadGraph("images/Scene_Config.png");    //画像のロード
}

//更新
void Config::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0||Keyboard_Get(KEY_INPUT_ESCAPE) == 1){ //Escキーが押されていたら
		Save();
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	if (Keyboard_Get(KEY_INPUT_DOWN) == 1){//下キーが押されていたら
		NowSelect = (NowSelect + 1) % eConfig_Num;//選択状態を一つ下げる
	}
	if (Keyboard_Get(KEY_INPUT_UP) == 1){//上キーが押されていたら
		NowSelect = (NowSelect + (eConfig_Num - 1)) % eConfig_Num;//選択状態を一つ上げる
	}
	
	switch (NowSelect){//現在選択中の状態によって処理を分岐
	case eConfig_Control:
		if (Keyboard_Get(KEY_INPUT_RETURN) == 1 || Keyboard_Get(KEY_INPUT_Z) == 1){//エンターキーが押されたら
			ChangeInputSystem();
		}
		break;
	case eConfig_BGM:
		if (Keyboard_Get(KEY_INPUT_LEFT) != 0){
			saveData.volume -= 5;
			if (saveData.volume < 0)saveData.volume = 0;
		}
		if (Keyboard_Get(KEY_INPUT_RIGHT) != 0){
			saveData.volume += 5;
			if (saveData.volume > 100)saveData.volume = 100;
		}
		break;
	}
}

//描画
void Config::Draw(){
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
	DrawString(0, 0, "設定画面です。Backボタン(Escキー)で戻ります。", GetColor(255, 255, 255));
	if (GetInputSystem()){
		DrawString(280, eConfigY_Control,  "入力装置切替: ジョイパッド",GetColor(255, 255, 255));
	}
	else{
		DrawString(280, eConfigY_Control, "入力装置切替: キーボード", GetColor(255, 255, 255));
	}
	
	DrawFormatString(280, eConfigY_BGM, GetColor(255, 255, 255), "BGM音量: %d %",saveData.volume );
	int y = 0;
	switch (NowSelect){//現在の選択状態に従って処理を分岐
	case eConfig_Control:
		y = eConfigY_Control;
		break;
	case eConfig_BGM:
		y = eConfigY_BGM;
		break;
	}
	DrawString(250, y, "■", GetColor(255, 255, 255));
}