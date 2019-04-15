#include "Stage2.h"

Stage2::Stage2(ISceneChanger* changer) : BaseScene(changer) {
}



//������
void Stage2::Initialize(){
	LoadDivGraph("images/back.bmp", MAPCHIP_KIND, MAPCHIP_KIND / 2, MAPCHIP_KIND / 2, MAPCHIP_SIZE, MAPCHIP_SIZE, mapChipGraph);
	MakeMap();
	player.Initialize(mapData, mapH, mapW, 768, 1024, &atkID);
	player.SlashInitialize(&playerSlash);
	playerSlash.Initialize(&atkID);
	for (int i = 0; i < PLAYER_BULLET_MAX; i++){
		player.BeamShootInitialize(&(playerBeamShoot[i]),i);
		playerBeamShoot[i].Initialize(&atkID);
	}

	

	heli.Initialize(mapData, mapH, mapW, 128, 512, &atkID, &player);
	for (int i = 0; i < 9; i++){
		heli.SolidShootInitialize(&(enemySolidShoot[i]),i);
		enemySolidShoot[i].Initialize(mapData, mapH, mapW, &atkID);
		heli.BeamShootInitialize(&(enemyBeamShoot[i]), i);
		enemyBeamShoot[i].Initialize(&atkID);
	}
	
	atkID = 0;

	bgm = LoadSoundMem("musics/stage2BGM.wav");
	ChangeVolumeSoundMem(saveData.volume * 256 / 100 - 1, bgm);
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
}

//�X�V
void Stage2::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0 || Keyboard_Get(KEY_INPUT_ESCAPE) == 1){ //Esc�L�[��������Ă�����
		StopSoundMem(bgm);
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	if (player.GetAlive() != true){ //Esc�L�[��������Ă�����
		StopSoundMem(bgm);
		mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[�ɕύX
	}
	if (player.GetX() >= mapW*MAPCHIP_SIZE){
		StopSoundMem(bgm);
		saveData.clear[2] = true;
		Save();
		mSceneChanger->ChangeScene(eScene_Stage3);//�V�[�������j���[�ɕύX
	}

	player.Update();
	for (int i = 0; i < PLAYER_BULLET_MAX; i++){
		if (playerBeamShoot[i].GetAlive()){
			playerBeamShoot[i].Update();
		}
	}

	if (heli.GetAlive()){
		heli.Update();
	}

	for (int i = 0; i < 9; i++){
		if (enemySolidShoot[i].GetAlive()){
			enemySolidShoot[i].Update();
		}
		if (enemyBeamShoot[i].GetAlive()){
			enemyBeamShoot[i].Update();
		}
	}
	

	if (playerSlash.GetAlive()){
		if (heli.GetAlive()){
			if (CheckCollisionRectToRect(&playerSlash, &heli)){
				heli.SetDamage(playerSlash.GetAtk(), playerSlash.GetStun(), playerSlash.GetBlowX(), playerSlash.GetBlowY(), playerSlash.GetID());
			}
		}
		for (int i = 0; i < 9; i++){
			if (enemySolidShoot[i].GetAlive()){
				if (CheckCollisionRectToRect(&playerSlash, &enemySolidShoot[i])){
					enemySolidShoot[i].SetDamage(playerSlash.GetAtk(), playerSlash.GetStun(), playerSlash.GetBlowX(), playerSlash.GetBlowY(), playerSlash.GetID());
				}
			}
		}
	}

	for (int j = 0; j < PLAYER_BULLET_MAX; j++){
		if (playerBeamShoot[j].GetAlive()){

			if (heli.GetAlive()){
				if (CheckCollisionRectToRect(&(playerBeamShoot[j]), &heli)){
					heli.SetDamage(playerBeamShoot[j].GetAtk(), playerBeamShoot[j].GetStun(), playerBeamShoot[j].GetBlowX(), playerBeamShoot[j].GetBlowY(), playerBeamShoot[j].GetID());
				}
			}
			for (int i = 0; i < 9; i++){
				if (enemySolidShoot[i].GetAlive()){
					if (CheckCollisionRectToRect(&playerSlash, &enemySolidShoot[i])){
						enemySolidShoot[i].SetDamage(playerBeamShoot[j].GetAtk(), playerBeamShoot[j].GetStun(), playerBeamShoot[j].GetBlowX(), playerBeamShoot[j].GetBlowY(), playerBeamShoot[j].GetID());
					}
				}
			}
		}
	}
	
	if (heli.GetAlive()){
		if (CheckCollisionRectToRect(&player, &heli)){
			player.SetDamage(heli.GetAtk(), heli.GetStun(), heli.GetBlowX(), heli.GetBlowY(), heli.GetID());
			heli.SetDamage(player.GetAtk(), player.GetStun(), player.GetBlowX(), player.GetBlowY(), player.GetID());
		}
	}
	//�w������̍U�������
	for (int i = 0; i < 9; i++){
		if (enemySolidShoot[i].GetAlive()){
			if (CheckCollisionRectToRect(&player, &enemySolidShoot[i])){
				player.SetDamage(enemySolidShoot[i].GetAtk(), enemySolidShoot[i].GetStun(), enemySolidShoot[i].GetBlowX(), enemySolidShoot[i].GetBlowY(), enemySolidShoot[i].GetID());
				enemySolidShoot[i].SetDamage(player.GetAtk(), player.GetStun(), player.GetBlowX(), player.GetBlowY(), player.GetID());
			}
		}
		if (enemyBeamShoot[i].GetAlive()){
			if (CheckCollisionRectToRect(&player, &enemyBeamShoot[i])){
				player.SetDamage(enemyBeamShoot[i].GetAtk(), enemyBeamShoot[i].GetStun(), enemyBeamShoot[i].GetBlowX(), enemyBeamShoot[i].GetBlowY(), enemyBeamShoot[i].GetID());
			}
		}
	}
	
}

//�`��
void Stage2::Draw(){
	BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
	startScreenX = player.GetX() - SHOW_PLAYER_X;
	startScreenY = player.GetY() - SHOW_PLAYER_Y;
	if (startScreenX < 0){
		startScreenX = 0;
	}
	else if (startScreenX>MAPCHIP_SIZE*mapW - SCREEN_SIZE_X){
		startScreenX = MAPCHIP_SIZE*mapW - SCREEN_SIZE_X;
	}
	if (startScreenY < 0){
		startScreenY = 0;
	}
	else if (startScreenY>MAPCHIP_SIZE*mapH - SCREEN_SIZE_Y){
		startScreenY = MAPCHIP_SIZE*mapH - SCREEN_SIZE_Y;
	}
	for (int i = 0; i < mapH; i++){
		for (int j = 0; j < mapW; j++){
			DrawGraph(MAPCHIP_SIZE*j - startScreenX, MAPCHIP_SIZE*i - startScreenY, mapChipGraph[mapData[i][j]], FALSE);
		}
	}
	//�G�@,���@,�G�U��,���@�U���̏�
	if (heli.GetAlive()){
		heli.Draw(startScreenX, startScreenY);
	}

	player.Draw(startScreenX, startScreenY);

	for (int i = 0; i < 9; i++){
		if (enemySolidShoot[i].GetAlive()){
			enemySolidShoot[i].Draw(startScreenX, startScreenY);
		}
		if (enemyBeamShoot[i].GetAlive()){
			enemyBeamShoot[i].Draw(startScreenX, startScreenY);
		}
	}
	

	playerSlash.Draw(startScreenX, startScreenY);
	for (int i = 0; i < PLAYER_BULLET_MAX; i++){
		if (playerBeamShoot[i].GetAlive()){
			playerBeamShoot[i].Draw(startScreenX, startScreenY);
		}
	}
	
	/*
	for (int i = 0; i < ENEMY_NUM; i++){
	DrawFormatString(0, 30*i, GetColor(255, 255, 255), "�ϐ� enSShoot �̒l�� %d �ł�\n", enemySolidShoot[i].GetX());
	}
	DrawFormatString(0, 30, GetColor(255, 255, 255), "�ϐ� enSShoot �̒l�� %d �ł�\n", enemySolidShoot1.GetX());
	DrawFormatString(0, 60, GetColor(255, 255, 255), "�ϐ� enSShoot �̒l�� %d �ł�\n", enemySolidShoot2.GetX());
	DrawFormatString(0, 90, GetColor(255, 255, 255), "�ϐ� enSShoot �̒l�� %d �ł�\n", enemySolidShoot3.GetX());
	*/
	/*
	//�ȉ��m�F�p
	for (int i = 0; i < ENEMY_NUM; i++){
	DrawFormatString(0, 30, GetColor(255, 255, 255), "�ϐ� enSShoot �̒l�� %d �ł�\n",enemySolidShoot[i].GetX());
	}
	for (int i = 0; i < MAP_HEIGHT_MAX; i++){
	for (int j = 0; j < MAP_WIDTH_MAX; j++){
	//DrawFormatString(240 + 30 * j, 30 * i, GetColor(255, 255, 255), "%d", mapData[i][j]);
	}
	}
	DrawString(0, 0, "�X�e�[�W1�ł��B", GetColor(255, 255, 255));
	DrawFormatString(0, 30, GetColor(255, 255, 255), "�ϐ� mapW �̒l�� %d �ł�\n", mapW);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "�ϐ� mapH �̒l�� %d �ł�\n", mapH);
	DrawFormatString(0, 90, GetColor(255, 255, 255), "�ϐ� a �̒l�� %d �ł�\n", a);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "�ϐ� b �̒l�� %d �ł�\n", b);
	DrawFormatString(0, 150, GetColor(255, 255, 255), "player.GetX() �̒l�� %d �ł�\n", player.GetX());
	DrawFormatString(0, 180, GetColor(255, 255, 255), "�ڐG �̒l�� %d �ł�\n", CheckCollisionRectToRect(&player, enemyRect[0]));
	DrawFormatString(0, 210, GetColor(255, 255, 255), "Slash�̒l�� %d �ł�\n", playerSlash.GetAlive());
	DrawFormatString(0, 240, GetColor(255, 255, 255), "iID�̒l�� %d �ł�\n", atkID);
	*/
}

void Stage2::MakeMap(){
	FILE *fp;
	char *fname = "maps/map2.csv";
	fopen_s(&fp, fname, "r");
	if (fp == NULL){
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%s�t�@�C�����J���܂���Bn", fname);
		exit(-1);
	}
	mapH = mapW = a = 0;
	while ((fscanf_s(fp, "%[^\n]%*c", map, MAP_WIDTH_MAX)) != EOF){
		for (mapW = 0; mapW < MAP_WIDTH_MAX; mapW++){
			if (map[a] == ','){
				a++;
			}
			if (map[a] == '\0'){
				break;
			}
			mapData[mapH][mapW] = atoi(&map[a]);
			if (mapData[mapH][mapW]>9){//�}�b�v�`�b�v�̎�ނ�100��ȓ��ł���K�v������B
				a++;
			}
			a++;
		}
		mapH++;
		a = 0;
	}
	fclose(fp);
}

//��`���m�̐ڐG����
bool Stage2::CheckCollisionRectToRect(Rect * setRectA, Rect * setRectB){
	flg = false;
	if (setRectA->GetX() <= setRectB->GetX() + setRectB->GetWidth() && setRectB->GetX() <= setRectA->GetX() + setRectA->GetWidth()){
		if (setRectA->GetY() <= setRectB->GetY() + setRectB->GetHeight() && setRectB->GetY() <= setRectA->GetY() + setRectA->GetHeight()){
			flg = true;
		}
	}
	return flg;
}
