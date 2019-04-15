#pragma once

#include "DxLib.h"
#include "ConstantNum.h"

// キーの入力状態を更新する
void Keyboard_Update();

// 引数のキーコードのキーの入力状態を返す
int Keyboard_Get(int KeyCode);

// 引数のキーコードのキーの入力状態の記録を返す
int Keyboard_Get(int KeyCode,int time);

//ジョイパッドの入力をキーボード入力に変換して処理する。
//最初から考えて作成すべきだった.
//というか入力処理が頭おかしい
void Joypad_Update();

void SetInputSystem(int);
void ChangeInputSystem();
int GetInputSystem();