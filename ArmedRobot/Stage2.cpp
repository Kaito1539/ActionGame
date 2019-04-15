#include "Stage2.h"

Stage2::Stage2(ISceneChanger* changer) : BaseScene(changer) {
}



//初期化
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

//更新
void Stage2::Update(){
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0 || Keyboard_Get(KEY_INPUT_ESCAPE) == 1){ //Escキーが押されていたら
		StopSoundMem(bgm);
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	if (player.GetAlive() != true){ //Escキーが押されていたら
		StopSoundMem(bgm);
		mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニューに変更
	}
	if (player.GetX() >= mapW*MAPCHIP_SIZE){
		StopSoundMem(bgm);
		saveData.clear[2] = true;
		Save();
		mSceneChanger->ChangeScene(eScene_Stage3);//シーンをメニューに変更
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
	//ヘリからの攻撃判定を
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

//描画
void Stage2::Draw(){
	BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
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
	//敵機,自機,敵攻撃,自機攻撃の順
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
	DrawFormatString(0, 30*i, GetColor(255, 255, 255), "変数 enSShoot の値は %d です\n", enemySolidShoot[i].GetX());
	}
	DrawFormatString(0, 30, GetColor(255, 255, 255), "変数 enSShoot の値は %d です\n", enemySolidShoot1.GetX());
	DrawFormatString(0, 60, GetColor(255, 255, 255), "変数 enSShoot の値は %d です\n", enemySolidShoot2.GetX());
	DrawFormatString(0, 90, GetColor(255, 255, 255), "変数 enSShoot の値は %d です\n", enemySolidShoot3.GetX());
	*/
	/*
	//以下確認用
	for (int i = 0; i < ENEMY_NUM; i++){
	DrawFormatString(0, 30, GetColor(255, 255, 255), "変数 enSShoot の値は %d です\n",enemySolidShoot[i].GetX());
	}
	for (int i = 0; i < MAP_HEIGHT_MAX; i++){
	for (int j = 0; j < MAP_WIDTH_MAX; j++){
	//DrawFormatString(240 + 30 * j, 30 * i, GetColor(255, 255, 255), "%d", mapData[i][j]);
	}
	}
	DrawString(0, 0, "ステージ1です。", GetColor(255, 255, 255));
	DrawFormatString(0, 30, GetColor(255, 255, 255), "変数 mapW の値は %d です\n", mapW);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "変数 mapH の値は %d です\n", mapH);
	DrawFormatString(0, 90, GetColor(255, 255, 255), "変数 a の値は %d です\n", a);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "変数 b の値は %d です\n", b);
	DrawFormatString(0, 150, GetColor(255, 255, 255), "player.GetX() の値は %d です\n", player.GetX());
	DrawFormatString(0, 180, GetColor(255, 255, 255), "接触 の値は %d です\n", CheckCollisionRectToRect(&player, enemyRect[0]));
	DrawFormatString(0, 210, GetColor(255, 255, 255), "Slashの値は %d です\n", playerSlash.GetAlive());
	DrawFormatString(0, 240, GetColor(255, 255, 255), "iIDの値は %d です\n", atkID);
	*/
}

void Stage2::MakeMap(){
	FILE *fp;
	char *fname = "maps/map2.csv";
	fopen_s(&fp, fname, "r");
	if (fp == NULL){
		DrawFormatString(0, 0, GetColor(255, 255, 255), "%sファイルが開けません。n", fname);
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
			if (mapData[mapH][mapW]>9){//マップチップの種類が100種以内である必要がある。
				a++;
			}
			a++;
		}
		mapH++;
		a = 0;
	}
	fclose(fp);
}

//矩形同士の接触判定
bool Stage2::CheckCollisionRectToRect(Rect * setRectA, Rect * setRectB){
	flg = false;
	if (setRectA->GetX() <= setRectB->GetX() + setRectB->GetWidth() && setRectB->GetX() <= setRectA->GetX() + setRectA->GetWidth()){
		if (setRectA->GetY() <= setRectB->GetY() + setRectB->GetHeight() && setRectB->GetY() <= setRectA->GetY() + setRectA->GetHeight()){
			flg = true;
		}
	}
	return flg;
}
