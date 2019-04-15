#include "Keyboard.h"

static int m_Key[256][INPUT_ACCEPT_TIME];  // �L�[�̓��͏�Ԋi�[�p�ϐ�
static int pad;//�p�b�h�̓���
static bool joypadMode = false;

// �L�[�̓��͏�ԍX�V
void Keyboard_Update(){
	char tmpKey[256];             // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll(tmpKey);  // �S�ẴL�[�̓��͏�Ԃ𓾂�
	for (int i = 0; i<256; i++){
		for (int j = INPUT_ACCEPT_TIME - 1; j > 0; j--){
			m_Key[i][j] = m_Key[i][j-1];
		}
		if (tmpKey[i] != 0){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
			m_Key[i][0] = m_Key[i][1]+1;   // ���Z
		}
		else {              // ������Ă��Ȃ����
			m_Key[i][0] = 0; // 0�ɂ���
		}
	}
}

// KeyCode�̃L�[�̍ŐV�̓��͏�Ԃ��擾����,���̊ȈՔ�
int Keyboard_Get(int KeyCode){
	return m_Key[KeyCode][0]; // KeyCode�̍ŐV�̓��͏�Ԃ�Ԃ�
}

// KeyCode�̃L�[�̓��͏�Ԃ̋L�^���擾����
int Keyboard_Get(int KeyCode,int time){
	return m_Key[KeyCode][time]; // KeyCode��time�t���[���O�̓��͏�Ԃ�Ԃ�,time==0�Ȃ��Ɠ���
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

		pad = GetJoypadInputState(DX_INPUT_PAD1);        //���͏�Ԃ�Pad�Ɋi�[
		for (int i = 0; i<28; i++){      //�{�^��28�����[�v
			if (pad & (1 << i)){             //�{�^��i�̓��̓t���O�������Ă�����
				//DrawFormatString(0, i * 15, GetColor(255, 255, 255), "%d�̃L�[��������Ă��܂�", i);
				
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
			else{//���͂��Ȃ�
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
	for (int i = 0; i<256; i++){//���͕��@��؂�ւ����ۂɏ���������   
		if (i == KEY_INPUT_RETURN || i == KEY_INPUT_Z){
			m_Key[i][0] = 2;// 0��1�ɂ���ƌ���L�[�ɑ�����������̂�
		}
		else{
			m_Key[i][0] = 0; 
		}
	}
}

void ChangeInputSystem(){
	joypadMode = !joypadMode;
	for (int i = 0; i<256; i++){//���͕��@��؂�ւ����ۂɏ���������   
		if (i == KEY_INPUT_RETURN || i == KEY_INPUT_Z){
			m_Key[i][0] = 2;// 0��1�ɂ���ƌ���L�[�ɑ�����������̂�
		}
		else{
			m_Key[i][0] = 0;
		}
	}
}

int GetInputSystem(){
	return joypadMode;
}