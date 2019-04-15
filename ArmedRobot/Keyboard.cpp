#include "Keyboard.h"

static int m_Key[256][INPUT_ACCEPT_TIME];  // キーの入力状態格納用変数
static int pad;//パッドの入力
static bool joypadMode = false;

// キーの入力状態更新
void Keyboard_Update(){
	char tmpKey[256];             // 現在のキーの入力状態を格納する
	GetHitKeyStateAll(tmpKey);  // 全てのキーの入力状態を得る
	for (int i = 0; i<256; i++){
		for (int j = INPUT_ACCEPT_TIME - 1; j > 0; j--){
			m_Key[i][j] = m_Key[i][j-1];
		}
		if (tmpKey[i] != 0){ // i番のキーコードに対応するキーが押されていたら
			m_Key[i][0] = m_Key[i][1]+1;   // 加算
		}
		else {              // 押されていなければ
			m_Key[i][0] = 0; // 0にする
		}
	}
}

// KeyCodeのキーの最新の入力状態を取得する,下の簡易版
int Keyboard_Get(int KeyCode){
	return m_Key[KeyCode][0]; // KeyCodeの最新の入力状態を返す
}

// KeyCodeのキーの入力状態の記録を取得する
int Keyboard_Get(int KeyCode,int time){
	return m_Key[KeyCode][time]; // KeyCodeのtimeフレーム前の入力状態を返す,time==0なら上と同じ
}

void Joypad_Update(){
	int keyNum=KEY_INPUT_0;
	if (GetJoypadNum()==0){
		SetInputSystem(KEYBOARD_INPUT);
	}
	else{
		for (int i = 0; i<256; i++){
			for (int j = INPUT_ACCEPT_TIME - 1; j > 0; j--){
				m_Key[i][j] = m_Key[i][j - 1];
			}
		}

		pad = GetJoypadInputState(DX_INPUT_PAD1);        //入力状態をPadに格納
		for (int i = 0; i<28; i++){      //ボタン28個分ループ
			if (pad & (1 << i)){             //ボタンiの入力フラグが立っていたら
				//DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%dのキーが押されています", i);
				
				switch (1<<i){
				case PAD_INPUT_DOWN:
					keyNum = KEY_INPUT_DOWN;
					break;
				case PAD_INPUT_LEFT:
					keyNum = KEY_INPUT_LEFT;
					break;
				case PAD_INPUT_RIGHT:
					keyNum = KEY_INPUT_RIGHT;
					break;
				case PAD_INPUT_UP:
					keyNum = KEY_INPUT_UP;
					break;
				case PAD_INPUT_1:
					keyNum = KEY_INPUT_C;
					break;
				case PAD_INPUT_2:
					keyNum = KEY_INPUT_X;
					break;
				case PAD_INPUT_3:
					keyNum = KEY_INPUT_Z;
					break;
				case PAD_INPUT_4:
					keyNum = KEY_INPUT_V;
					break;
				case PAD_INPUT_7:
					keyNum = KEY_INPUT_ESCAPE;
					break;
				case PAD_INPUT_8:
					keyNum = KEY_INPUT_RETURN;
					break;
				default:
					keyNum = KEY_INPUT_0;
					break;
				}
				m_Key[keyNum][0] = m_Key[keyNum][1] + 1;
			}
			else{//入力がない
				switch (1<<i){
				case PAD_INPUT_DOWN:
					keyNum = KEY_INPUT_DOWN;
					break;
				case PAD_INPUT_LEFT:
					keyNum = KEY_INPUT_LEFT;
					break;
				case PAD_INPUT_RIGHT:
					keyNum = KEY_INPUT_RIGHT;
					break;
				case PAD_INPUT_UP:
					keyNum = KEY_INPUT_UP;
					break;
				case PAD_INPUT_1:
					keyNum = KEY_INPUT_C;
					break;
				case PAD_INPUT_2:
					keyNum = KEY_INPUT_X;
					break;
				case PAD_INPUT_3:
					keyNum = KEY_INPUT_Z;
					break;
				case PAD_INPUT_4:
					keyNum = KEY_INPUT_V;
					break;
				case PAD_INPUT_7:
					keyNum = KEY_INPUT_ESCAPE;
					break;
				case PAD_INPUT_8:
					keyNum = KEY_INPUT_RETURN;
					break;
				default:
					keyNum = KEY_INPUT_0;
					break;
				}
				m_Key[keyNum][0] = 0;
			}
		}
		/*
		for (int i = 0; i<256; i++){
			if (m_Key[i][0] == m_Key[i][1]){ 
				m_Key[i][0] = 0;
			}
		}
		*/
	}
}

void SetInputSystem(int setMode){
	joypadMode = setMode;
	for (int i = 0; i<256; i++){//入力方法を切り替えた際に初期化する   
		if (i == KEY_INPUT_RETURN || i == KEY_INPUT_Z){
			m_Key[i][0] = 2;// 0か1にすると決定キーに即時反応するので
		}
		else{
			m_Key[i][0] = 0; 
		}
	}
}

void ChangeInputSystem(){
	joypadMode = !joypadMode;
	for (int i = 0; i<256; i++){//入力方法を切り替えた際に初期化する   
		if (i == KEY_INPUT_RETURN || i == KEY_INPUT_Z){
			m_Key[i][0] = 2;// 0か1にすると決定キーに即時反応するので
		}
		else{
			m_Key[i][0] = 0;
		}
	}
}

int GetInputSystem(){
	return joypadMode;
}