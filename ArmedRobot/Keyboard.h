#pragma once

#include "DxLib.h"
#include "ConstantNum.h"

// �L�[�̓��͏�Ԃ��X�V����
void Keyboard_Update();

// �����̃L�[�R�[�h�̃L�[�̓��͏�Ԃ�Ԃ�
int Keyboard_Get(int KeyCode);

// �����̃L�[�R�[�h�̃L�[�̓��͏�Ԃ̋L�^��Ԃ�
int Keyboard_Get(int KeyCode,int time);

//�W���C�p�b�h�̓��͂��L�[�{�[�h���͂ɕϊ����ď�������B
//�ŏ�����l���č쐬���ׂ�������.
//�Ƃ��������͏���������������
void Joypad_Update();

void SetInputSystem(int);
void ChangeInputSystem();
int GetInputSystem();