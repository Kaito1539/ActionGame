#include "DxLib.h"
#include "SceneMgr.h"
#include "Keyboard.h"
#include "ConstantNum.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int){
	int Time;

	// 画面モードの設定
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更と初期化と裏画面設定

	SceneMgr sceneMgr;
	sceneMgr.Initialize();

	if (GetJoypadNum() == 0){
		SetInputSystem(KEYBOARD_INPUT);
	}
	else{
		SetInputSystem(JOYPAD_INPUT);
	}
	saveData=Load();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){//画面更新 & メッセージ処理 & 画面消去
		Time = GetNowCount();

		if (GetInputSystem() == KEYBOARD_INPUT){
			Keyboard_Update();    //キーボードの更新
		}
		else{
			Joypad_Update();
		}
		
		sceneMgr.Update();  //更新
		sceneMgr.Draw();    //描画
		
		//リフレッシュレートを無視して一フレームを17ms(1s=60frame)に合わせる。画像がぶれる。
		//あと、操作に対する反応が悪くなる。そんなこともなかった
		while (GetNowCount() - Time < 17){}
	}

	sceneMgr.Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}