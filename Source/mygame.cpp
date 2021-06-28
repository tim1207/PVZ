#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include <memory>



namespace game_framework {
	bool YouWin = false;
	//TODO:
	int gamelevel=1;
	bool isGameOver;
	//bool myrunning＝true;
	bool frist_load = true;
	
	
	

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
		
	}

	//讀取音效檔
	void CGameStateInit::LoadAudio() {
		CAudio::Instance()->Load(AUDIO_MENU, ".\\Sounds\\ZombiesOnYourLawn.wav");
		CAudio::Instance()->Load(AUDIO_EVIL_LAUGH, ".\\Sounds\\evillaugh.wav");
	}

	// is finished 
	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0); // 一開始的loading進度為0%
		//loading_picture.ShowBitmap();
		//
		// 開始載入資料
		//
		
		conditionA = false;
		conditionB = false;
		LoadAudio();
		logo.LoadBitmap(Background);
		adventure_block.LoadBitmap(Adventure, RGB(255, 255, 255));
		adventure_block2.LoadBitmap(".\\BMP_RES\\image\\interface\\adventure2.bmp", RGB(255, 255, 255));
		//Sleep(300);    // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
		play_Audio = false;
		
	}

	// is finsihed
	void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_ESC = 27;
		const char KEY_SPACE = ' ';
		if (nChar == KEY_SPACE)
			GotoGameState(GAME_STATE_RUN);      // 切換至GAME_STATE_RUN
		else if (nChar == KEY_ESC)        // Demo 關閉遊戲的方法
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0); // 關閉遊戲
	}


	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
	{
		// 處理滑鼠和選單的互動
		bool conditionA1 = (point.y - 125 <= 35 * (point.x - 350) / 250);
		bool conditionA2 = (point.y - 68 >= -57 * (point.x - 351));
		bool conditionA3 = (point.y - 68 >= 17 * (point.x - 351) / 261);
		bool conditionA4 = (point.y - 160 <= -75 * (point.x - 600) / 12);
		bool conditionB1 = (point.y - 70 >= -20 * (point.x - 400) / 25);
		bool conditionB2 = (point.y >= 50);
		bool conditionB3 = (point.y - 50 >= 31 * (point.x - 520) / 26);
		bool conditionB4 = (point.y - 70 <= 11 * (point.x - 400) / 146);
		
		if (point.y < 240 && point.y > 100 && point.x < 680 && point.x > 390) {

			CAudio::Instance()->Stop(AUDIO_MENU);
			CAudio::Instance()->Play(AUDIO_EVIL_LAUGH, false);
		}
		
		conditionA = (point.y < 245 && point.y > 100 && point.x <680 && point.x > 390);
		conditionB = (conditionB1 && conditionB2 && conditionB3 && conditionB4);
		//menu.SetHighLight(conditionA || conditionB);
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{	
		if (conditionA || conditionB) {
			//menu.Shine();
			CAudio::Instance()->Stop(AUDIO_MENU);
			CAudio::Instance()->Play(AUDIO_EVIL_LAUGH, false);
			GotoGameState(GAME_STATE_RUN);  // 切換至GAME_STATE_RUN
		}
		
		
	}

	// is finish
	void CGameStateInit::OnShow()
	{
		
		Sleep(300);    // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		logo.SetTopLeft(-100, 0);
		logo.ShowBitmap();
		if (conditionA) {
			adventure_block2.SetTopLeft(380, 100);
			adventure_block2.ShowBitmap();
		}else {
			adventure_block.SetTopLeft(380, 100);
			adventure_block.ShowBitmap();
		}
		

		if (play_Audio == false) {
			play_Audio = true;
			CAudio::Instance()->Play(AUDIO_MENU, true);
		}
		//   //
		//   // Demo螢幕字型的使用，不過開發時請盡量避免直接使用字型，改用CMovingBitmap比較好
		//   //
		//   CDC *pDC = CDDraw::GetBackCDC();   // 取得 Back Plain 的 CDC 
		//   CFont f, *fp;
		//   f.CreatePointFont(160, "Times New Roman"); // 產生 font f; 160表示16 point的字
		//   fp = pDC->SelectObject(&f);     // 選用 font f
		//   pDC->SetBkColor(RGB(0, 0, 0));
		//   pDC->SetTextColor(RGB(255, 255, 0));
		//   pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
		//   pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		//   if (ENABLE_GAME_PAUSE)
		//    pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		//   pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
		//   pDC->SelectObject(fp);      // 放掉 font f (千萬不要漏了放掉)
		//   CDDraw::ReleaseBackCDC();     // 放掉 Back Plain 的 CDC
	}





	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
		
	}
	//讀取結果的圖檔
	void CGameStateOver::LoadBitmap() {
		ZombiesWon.LoadBitmap(".\\BMP_RES\\image\\interface\\ZombiesWon0.bmp");

		ZombiesWon.SetTopLeft(0, 0);
		ZombieLose.LoadBitmap(".\\BMP_RES\\image\\interface\\win0.bmp");
		ZombieLose.SetTopLeft(0, 0);
		FinalWin.LoadBitmap(".\\BMP_RES\\image\\interface\\finalwin.bmp");
		FinalWin.SetTopLeft(0, 0);
	}

	void CGameStateOver::OnMove()
	{
	}

	void CGameStateOver:: OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭
		
		if (nChar == KEY_LEFT) {
			GotoGameState(GAME_STATE_INIT);
		}
		if (nChar == KEY_RIGHT) {
			GotoGameState(GAME_STATE_RUN);
		}
		
		
	}

	void CGameStateOver::OnBeginState()
	{	
			
		counter = 30 * 5; // 5 seconds
		if(YouWin==true){
			gamelevel++;
			CAudio::Instance()->Play(AUDIO_WIN_MUSIC, false);
		}
		else
			CAudio::Instance()->Play(AUDIO_LOSE_MUSIC, false);
	}
	// is finished 
	void CGameStateOver::LoadAudio() 
	{
		CAudio::Instance()->Load(AUDIO_LOSE_MUSIC, ".\\Sounds\\losemusic.wav");
		CAudio::Instance()->Load(AUDIO_WIN_MUSIC, ".\\Sounds\\winmusic.wav");
	}
	void CGameStateOver::OnInit()
	{	
		LoadAudio();
		ShowInitProgress(66); 
		//Sleep(300);    
		ShowInitProgress(100);
		LoadBitmap();
	}

	void CGameStateOver::OnShow()
	{	
		if(isGameOver)
			if (YouWin == false) {
				ZombiesWon.ShowBitmap();
			}
			else {
				if (gamelevel == 11) {
					FinalWin.ShowBitmap();		
					
					//GotoGameState(GAME_STATE_INIT);
					//gamelevel = 1;
				}
				else {
					ZombieLose.ShowBitmap();
				}
				
			}
	}

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	/////////////////////////////////////////////////////////////////////////////

	CGameStateRun::CGameStateRun(CGame *g)
		: CGameState(g)
	{
		srand((unsigned)time(NULL));
	}

	CGameStateRun::~CGameStateRun()
	{
	}

	void CGameStateRun::OnBeginState()
	{
		if (gamelevel == 11) {
			//Sleep(3000);
			gamelevel = 1;
			//GotoGameState(GAME_STATE_INIT);
		}
		
		show_menu = false;
		background[gamelevel-1].SetTopLeft(-500, 0);    				// 設定背景的起始座標
		//help.SetTopLeft(0, SIZE_Y - help.Height());   // 設定說明圖的起始座標
		CAudio::Instance()->Play(AUDIO_MAIN_MUSIC, true); //撥放遊戲背景音樂
		sunback.SetTopLeft(-400, 10);
		zombiesone[0].SetTopLeft(640, 150);
		zombiesone[1].SetTopLeft(660, 200);
		zombiesone[2].SetTopLeft(640, 250);
		zombiesone[3].SetTopLeft(660, 300);
		zombiesone[4].SetTopLeft(640, 350);

		run_menu.SetTopLeft(230, 50);
		run_con[0].SetTopLeft(315, 180);
		run_con[1].SetTopLeft(315, 180);
		run_return[0].SetTopLeft(315, 250);
		run_return[1].SetTopLeft(315, 250);
		//設定和滑鼠相關的變數
		SunCounter = 0;                                   //從空中掉落太陽的計時器
		ZombieCounter = 0;
		selected = false;
		ChoosedCard = -1;
		ChoosedPlant = -1;
		isGameOver=false;
		YouWin=false;
		show_back = 0;
		show_con = 0;
		//確保所有的vector清空

		monster.clear();
		// plants.clear();
		
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				PlantManager[i][j] = 0;
				PlantClass[i][j] = zero[i][j];
			}
		}
		peas.clear();
		suns.clear();
		seed.Reset();

		//重設除草機
		if(gamelevel>=3){
			for(int i=0;i<5;i++)
			LawnCleaner[i].Reset();
		}

		wave = 0;

		// CAudio::Instance()->Play(AUDIO_LAKE, true);   // 撥放 WAVE
		// CAudio::Instance()->Play(AUDIO_DING, false);  // 撥放 WAVE
		// CAudio::Instance()->Play(AUDIO_NTUT, true);   // 撥放 MIDI
	}

	void CGameStateRun::OnInit()          // 遊戲的初值及圖形設定
	{
		//TODO:
		LoadAudio();
		 ShowInitProgress(33);
		 Sleep(500); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		 ShowInitProgress(50);
		
		
		myrunning = true;
		if( frist_load == true){
			background[0].LoadBitmap(Background1row);     // 載入背景的圖形
			background[1].LoadBitmap("BMP_RES\\image\\interface\\background1unsodded2.bmp");
			background[2].LoadBitmap("BMP_RES\\image\\interface\\background1.bmp");
			background[3].LoadBitmap("BMP_RES\\image\\interface\\background1.bmp");
			background[4].LoadBitmap("BMP_RES\\image\\interface\\background1.bmp");
			background[5].LoadBitmap("BMP_RES\\image\\interface\\background1.bmp");
			background[6].LoadBitmap("BMP_RES\\image\\interface\\background1.bmp");
			background[7].LoadBitmap("BMP_RES\\image\\interface\\background1.bmp");
			background[8].LoadBitmap("BMP_RES\\image\\interface\\background1.bmp");
			background[9].LoadBitmap("BMP_RES\\image\\interface\\background1.bmp");
			background[10].LoadBitmap("BMP_RES\\image\\interface\\night1.bmp");

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 9; j++) {
					zero[i][j] = Plants(0, i, j);
				}
			}
			menu.LoadBitmap("BMP_RES\\image\\interface\\menu\\mainmenu\\menu0.bmp", RGB(0, 0, 0));
			run_menu.LoadBitmap("BMP_RES\\image\\interface\\choicemenu\\OptionsMenuback8.bmp", RGB(0, 0, 0));
			for (int i = 0; i < 2; i++) {
				char FILENAME[100];
				sprintf(FILENAME, "BMP_RES\\image\\interface\\menu\\mainmenu\\back%d.bmp", i);
				run_con[i].LoadBitmap(FILENAME, RGB(0, 0, 0));		//繼續
				sprintf(FILENAME, "BMP_RES\\image\\interface\\menu\\mainmenu\\menu%d.bmp", i);
				run_return[i].LoadBitmap(FILENAME, RGB(0, 0, 0)); // 回選單
			}
			
			

			int temp[] = {1,2,3,4,5,6,7};
			seed.Load(7, temp);

			for (int i = 0; i < 5; i++) {					//載入殭屍
				zombiesone[i].LoadBitmap(".\\BMP_RES\\image\\zombies\\Normal Zombie\\Zombie_0.bmp", RGB(0, 0, 0));
				LawnCleaner[i].LoadBitmap();
			}

			mouse.LoadBitmap();
			sunback.LoadBitmap("BMP_RES/image/interface/SunBack.bmp", RGB(0, 0, 0));
			shovel.LoadBitmap();
			frist_load = false;
		}
	}

	void CGameStateRun::OnMove()       // 移動遊戲元素
	{	

		if(myrunning)
		{
			//  開始的移動畫面
			if (background[gamelevel-1].Left() < -80){
				background[gamelevel-1].SetTopLeft(background[gamelevel-1].Left() + 10, 0);
				// TODO:
				//for
				
			}
			if(gamelevel>=3){
				for(int i=0;i<5;i++){
					LawnCleaner[i].SetY(i);
					LawnCleaner[i].OnMove();
				}
			}	
			
			
		
				

			if (sunback.Left() < 100)
				sunback.SetTopLeft(sunback.Left() + 10, 10);
			
			// 放置殭屍 (right)
			for (int i = 0; i < 5; i++) {
				if (zombiesone[i].Left() < 1040)
					zombiesone[i].SetTopLeft(zombiesone[i].Left() + 10, 150 + i * 50);
			}

			//每隔7秒從空中產生一個太陽
			SunCounter++;
			if (SunCounter == 300) {
				SunCounter = 0;
				suns.push_back(Sun(rand() % 400 + 100, rand() % 300 + 100, false));
			}


			ZombieCounter++;
			if (wave < gamelevel*1 && wave >= 0) {
				///每隔10秒產生1~3隻隨機種類的殭屍
				if (ZombieCounter == 200-gamelevel*5) {
					wave++;
					if (awooga == false) {
						CAudio::Instance()->Play(AUDIO_AWOOGA, false);
						awooga = true;
					}
					ZombieCounter = 0;
					int groan = rand() % 6;
					CAudio::Instance()->Play(AUDIO_GROAN_1 + groan, false);

					if(gamelevel==1){
							monster.push_back(make_shared<Zombies>(1, 3, 800));	
					}
					if(gamelevel==2){ // 3row
						for (int i = 0; i < 2; i++) {
							monster.push_back(make_shared<Zombies>(rand()%3+1,rand()%3+2, 800));// for demo
						}
					}
					if(gamelevel>=3){ // 5 row
						for (int i = 0; i < 3; i++) {
							monster.push_back(make_shared<Zombies>(rand()%3+1,rand()%5+1, 800));// for demo
						}
					}
					
				}
			}
			// TODO:
			if(wave == gamelevel*1){
				int checkwin=1;
				for(auto &itz:monster){
					if(itz->GetX()!=1000){
						checkwin = 0;
						break;
					}
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 9; j++) {
							if (PlantClass[i][j].isFinished() == false && PlantClass[i][j].GetID()==4 && PlantClass[i][j].WhichAction() == 2) {
								checkwin = 0;
								break;
							}
						}
					}
				}
				if(checkwin==1){
					YouWin = true;
					isGameOver = true;
				}
			}

			

			for (auto &itz : monster) {
				//處理所有殭屍的動作	
				itz->OnMove();
				if (itz->GetX() < 50) {
					YouWin = false;
					isGameOver = true;                                         //如果殭屍跑進家裡，遊戲結束
				}
				//尋找殭屍可攻擊的第一隻植物
				int closest = 10;
				for (int i = (itz->GetX() - 80) / 75; i >= 0; i--) {
					if (PlantManager[itz->GetRow()][i] > 0) {
						closest = i;
						break;
					}
				}
				if (itz->isAlive() == true) {
					//如果殭屍被除草機撞到就馬上死亡
					if(gamelevel>=3)
						if (LawnCleaner[itz->GetRow()].GetX() > itz->GetX() + 30 && LawnCleaner[itz->GetRow()].GetX() < itz->GetX() + 100) {
							LawnCleaner[itz->GetRow()].StartMove();
							CAudio::Instance()->Play(AUDIO_LAWN_MOWER, false);
							itz->GoToDie();
						}
					
					bool found = false;
					for (int i = 0; i < 5; i++) {
						for (int j = 0; j < 9; j++) {
							if (PlantClass[i][j].GetRow() == itz->GetRow() && PlantClass[i][j].GetColumn() == closest) {
								if (PlantClass[i][j].GetX() <= itz->GetX()+80 && PlantClass[i][j].GetX() >= itz->GetX() + 30) {
									itz->SetStatus(2);                                   //如果離殭屍最近的植物進入攻擊範圍就進入攻擊狀態
									found = true;
								}
								else {
									itz->SetStatus(1);
								}
								//如果殭屍正在攻擊狀態且攻擊冷卻時間結束，植物就受到攻擊
								if (itz->GetStatus() == 2 && itz->Attack() == true) {
									int chomp = rand() % 3;
									CAudio::Instance()->Play(AUDIO_CHOMP_1 + chomp, false);
									PlantClass[i][j].BeingAttacked();
									if (PlantClass[i][j].isAlive() == false) {
										PlantClass[i][j] = zero[i][j];
										PlantManager[i][j] = 0;
										itz->SetStatus(1);                                 //如果植物被殭屍吃掉了，殭屍馬上恢復普通狀態
									}
								}

							}
						}
					}

					if (found == false) {
						itz->SetStatus(1);
					}
				}

				//殭屍死亡
				// TODO:
				if (itz->isFinished() == true) {
					itz->GoToDie();
				}


			}
			//處理所有植物的動作
			bool ErasePlant = false;
			if(isGameOver==true)
				GameOver();

			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 9; j++) {
					if (PlantClass[i][j].isAlive() == false) {                               //如果植物的生命為零，設定植物的死亡
						ErasePlant = true;
						PlantManager[i][j] = 0;
						continue;
					}
					PlantClass[i][j].OnMove();
					//處理向日葵的動作
					if (PlantClass[i][j].GetID() == 1) {
						PlantClass[i][j].SetCounterOn(true);
						if (PlantClass[i][j].isAction() == true) {                             //時間到了就產生一個太陽
							suns.push_back(Sun(PlantClass[i][j].GetX(), PlantClass[i][j].GetY(), true));
						}
						continue;
					}
					//處理一般豌豆的動作
					if (PlantClass[i][j].GetID() == 2) {
						bool FoundZombie = false;
						for (auto &itz : monster) {
							if (PlantClass[i][j].GetRow() == PlantClass[i][j].GetRow() && PlantClass[i][j].GetX() + 50 >= PlantClass[i][j].GetX()) {
								FoundZombie = true;
								if (PlantClass[i][j].GetX() + 50 > PlantClass[i][j].GetX()) {
									PlantClass[i][j].SetCounterOn(true);                             //如果找到可攻擊的殭屍就進入攻擊狀態
								}
								else {
									PlantClass[i][j].SetCounterOn(false);
								}
							}

							if (PlantClass[i][j].isAction() == true) {
								CAudio::Instance()->Play(AUDIO_SHOOT, false);
								peas.push_back(Pea(PlantClass[i][j].GetX() + 50, PlantClass[i][j].GetRow(), 0)); //如果攻擊冷卻時間到了就射出一顆豆子
							}
							if (FoundZombie == false) {
								PlantClass[i][j].SetCounterOn(false);
							}
						}
					}
					
					//處理ID 4 的動作	

					if (PlantClass[i][j].GetID() == 4) {
						for (auto &itz : monster) {
							if (itz->GetRow() == PlantClass[i][j].GetRow() && (itz->GetX()-80)/75 == j+1 || (itz->GetX()-80)/75 == j+2){
								PlantClass[i][j].SetTargetX(10);
								if ((itz->GetX() )  < PlantClass[i][j].GetX()+10) {
									itz->SetSnowCounter();
								}
								
								if (PlantClass[i][j].WhichAction() == 2) {
									itz->GoToDie();
								}
							}
						}
						if (PlantClass[i][j].WhichAction() == 3){
							PlantClass[i][j]= zero[i][j];
							PlantManager[i][j]= 0;
						}
							
					}	
					//處理櫻桃的動作
					if (PlantClass[i][j].GetID() == 5) {
						if (PlantClass[i][j].WhichAction() == 2) {
							CAudio::Instance()->Play(AUDIO_CHERRY_BOMB, false);
							for (auto &itz : monster) { 
								if (abs(itz->GetRow() - PlantClass[i][j].GetRow()) <= 1 && itz->GetX() + 50 < PlantClass[i][j].GetX() + 100 && itz->GetX() + 50 > PlantClass[i][j].GetX() - 100) {
									itz->BoomToDie();                                    //如果殭屍在櫻桃的爆炸範圍內就會瞬間被炸死
								}
							}
						}
						if (PlantClass[i][j].WhichAction() == 3){
							PlantClass[i][j]= zero[i][j];
							PlantManager[i][j]= 0;
						}
						
					}
					//處理冷凍豌豆的動作
					if (PlantClass[i][j].GetID() == 6) {
						bool FoundZombie = false;
						for (auto &itz : monster) {
							if (itz->GetRow() == PlantClass[i][j].GetRow() && itz->GetX() + 50 >= PlantClass[i][j].GetX()) {
								FoundZombie = true;
								if (itz->GetX() + 50 > PlantClass[i][j].GetX()) {
									PlantClass[i][j].SetCounterOn(true);                             //如果有殭屍在攻擊範圍內就進入攻擊模式
								}
								else {
									PlantClass[i][j].SetCounterOn(false);
								}
							}
						}
						if (PlantClass[i][j].isAction() == true) {
							CAudio::Instance()->Play(AUDIO_SHOOT, false);
							peas.push_back(Pea(PlantClass[i][j].GetX() + 50, PlantClass[i][j].GetRow(), 1)); //如果攻擊冷卻時間到了就射出一顆豆子
						}
						if (FoundZombie == false) {
							PlantClass[i][j].SetCounterOn(false);
						}
					}
					//處理連射豌豆的動作
					if (PlantClass[i][j].GetID() == 7) {
						bool FoundZombie = false;
						for (auto &itz :monster) {
							if (itz->GetRow() == PlantClass[i][j].GetRow() && itz->GetX() + 50 >= PlantClass[i][j].GetX()) {
								FoundZombie = true;
								if (itz->GetX() + 50 > PlantClass[i][j].GetX()) {
									PlantClass[i][j].SetCounterOn(true);                             //如果有殭屍在攻擊範圍內就進入攻擊模式
								}
								else {
									PlantClass[i][j].SetCounterOn(false);
								}
							}
						}
						if (PlantClass[i][j].isAction() == true) {
							CAudio::Instance()->Play(AUDIO_SHOOT, false);
							peas.push_back(Pea(PlantClass[i][j].GetX() + 50, PlantClass[i][j].GetRow(), 0)); //如果攻擊冷卻時間到了就射出一顆豆子
						}
						if (FoundZombie == false) {
							PlantClass[i][j].SetCounterOn(false);
						}
					}
				}
				// 處理所有豆子
				for (vector<Pea>::iterator itpea = peas.begin(); itpea != peas.end(); itpea++) {
					itpea->OnMove();
					bool HitZombie = false;
					int mi = 1000;
					for (auto &itz : monster) {

						if (itpea->GetRow() == itz->GetRow() && itpea->GetX() > itz->GetX() + 75 && itpea->GetX() < itz->GetX() + 110) {
							if (mi > itz->GetX()) {
								mi = itz->GetX();
								//itzz = itz;
								HitZombie = true;
								itpea->SetHitZombie(true);
								//處理擊中殭屍後的動作
								if (itz->GetID() == 3 && itz->GetLife() > 10) {
									int sound = rand() % 2;
									CAudio::Instance()->Play(AUDIO_HIT_BUCKET_1 + sound, false);
								}
								else {
									int sound = rand() % 3;
									CAudio::Instance()->Play(AUDIO_SPLAT_1 + sound, false);
								}
								itz->Hitted(itpea->MyType());
							}
						}
						if (itpea->GetX() > 780) {
							itpea->SetHitZombie(true);
						}
					}
				}
				
				//處理所有太陽的動作
				vector<Sun>::iterator itss;
				bool EraseSun = false;			
				for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
					if (its == suns.begin()) {
						its->MoveAnime();
					}
					its->OnMove();
					if (its->isFinished()) {
						itss = its;
						EraseSun = true;
					}
				}
				if (EraseSun == true) {
					suns.erase(itss);
					EraseSun = false;
				}
				seed.OnMove();
			}
		}
	}

	  //讀取所需的音效檔
	void CGameStateRun::LoadAudio() {
		CAudio::Instance()->Load(AUDIO_MAIN_MUSIC, ".\\Sounds\\mainmusic.wav");
		CAudio::Instance()->Load(AUDIO_AWOOGA, ".\\Sounds\\awooga.wav");
		for (int i = 1; i <= 6; i++) {
			char FILENAME[100];
			sprintf(FILENAME, ".\\Sounds\\groan%d.wav", i);
			CAudio::Instance()->Load(AUDIO_GROAN_1 + i - 1, FILENAME);
		}
		for (int i = 1; i <= 3; i++) {
			char FILENAME[100];
			sprintf(FILENAME, ".\\Sounds\\chomp%d.wav", i);
			CAudio::Instance()->Load(AUDIO_CHOMP_1 + i - 1, FILENAME);
		}
		CAudio::Instance()->Load(AUDIO_CHERRY_BOMB, ".\\Sounds\\cherrybomb.wav");
		CAudio::Instance()->Load(AUDIO_LAWN_MOWER, ".\\Sounds\\lawnmower.wav");
		CAudio::Instance()->Load(AUDIO_PLANT, ".\\Sounds\\plant.wav");
		CAudio::Instance()->Load(AUDIO_COLLECT_SUN, ".\\Sounds\\points.wav");
		CAudio::Instance()->Load(AUDIO_CHOOSE_CARD, ".\\Sounds\\seedlift.wav");
		CAudio::Instance()->Load(AUDIO_HIT_BUCKET_1, ".\\Sounds\\shieldhit1.wav");
		CAudio::Instance()->Load(AUDIO_HIT_BUCKET_2, ".\\Sounds\\shieldhit2.wav");
		CAudio::Instance()->Load(AUDIO_SHOVEL, ".\\Sounds\\shovel.wav");
		CAudio::Instance()->Load(AUDIO_SPLAT_1, ".\\Sounds\\splat.wav");
		CAudio::Instance()->Load(AUDIO_SPLAT_2, ".\\Sounds\\splat2.wav");
		CAudio::Instance()->Load(AUDIO_SPLAT_3, ".\\Sounds\\splat3.wav");
		CAudio::Instance()->Load(AUDIO_SHOOT, ".\\Sounds\\puff.wav");
		CAudio::Instance()->Load(AUDIO_FINALWAVE, ".\\Sounds\\finalwave.wav");
	}



	//進入GameStateOver，並將vector清空，否則第二次完會產生錯誤
	void CGameStateRun::GameOver()
	{
		monster.clear();
		suns.swap(vector<Sun>());
		peas.swap(vector<Pea>());

		// plants.clear();
		// for (int i = 0; i < 5; i++) {
		// 	for (int j = 0; j < 9; j++) {
		// 		PlantManager[i][j] = 0;
		// 		PlantClass[i][j] = Plants(0, j, i);
		// 	}
		// }

		CAudio::Instance()->Stop(AUDIO_MAIN_MUSIC);
		GotoGameState(GAME_STATE_OVER);
	}

	//密技
	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard左箭頭
		const char KEY_UP = 0x26; // keyboard上箭頭
		const char KEY_RIGHT = 0x27; // keyboard右箭頭
		const char KEY_DOWN = 0x28; // keyboard下箭頭

		if (nChar == KEY_UP) {
			// for(auto &it:monster)
			// 	it->GoToDie();
			YouWin = true;
			isGameOver = true;
			GameOver();
		}
		else if (nChar == KEY_DOWN) {
			for (int i = 0; i < 40; i++) {
				seed.GotSun();
			}
		}
		else if (nChar == KEY_LEFT) {
			seed.ResetCD();
		}
		else if (nChar == KEY_RIGHT) {
			for(auto &it:monster)
				it->Faster();
			//myrunning=!myrunning;
		}
	}

	void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		// const char KEY_LEFT = 0x25; // keyboard左箭頭
		// const char KEY_UP = 0x26; // keyboard上箭頭
		// const char KEY_RIGHT = 0x27; // keyboard右箭頭
		// const char KEY_DOWN = 0x28; // keyboard下箭頭

		// if (nChar == KEY_LEFT)
		// 	eraser.SetMovingLeft(false);
		// if (nChar == KEY_RIGHT)
		// 	eraser.SetMovingRight(false);
		// if (nChar == KEY_UP)
		// 	eraser.SetMovingUp(false);
		// if (nChar == KEY_DOWN)
		// 	eraser.SetMovingDown(false);

		// gamemap.OnKeyDown(nChar);
	}

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		if (!selected) {
			//處理menu的動作
			if (point.x >= 695 && point.x <= 800 && point.y >= 0 && point.y <= 40 ) {
				myrunning = false;
				show_menu = true;
				selected = true;
			}
			//處理點擊太陽的動作
			bool GotSun = false;
			for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
				if (point.x >= its->GetX() && point.x <= its->GetX() + its->GetWidth() && point.y >= its->GetY() && point.y <= its->GetY() + its->GetHeight()) {
					its->PickUp();
					CAudio::Instance()->Play(AUDIO_COLLECT_SUN, false);
					seed.GotSun();
					GotSun = true;
					break;
				}
			}
			//處理選擇卡片的動作
			if (point.x >= 0 && point.x <= 95 && point.y >= 50 && point.y <= 470 && GotSun == false) {
				ChoosedCard = (point.y - 50) / 60;
				if(ChoosedCard < gamelevel+1){
					ChoosedPlant = seed.GetCardID(ChoosedCard);
					if (seed.isCardAvailible(ChoosedCard)) {
						CAudio::Instance()->Play(AUDIO_CHOOSE_CARD, false);
						selected = true;
						mouse.SetXY(point.x, point.y);
						mouse.SetWhich(ChoosedPlant); //讓游標的樣子變成準備種植的植物

					}
				}
				
			}
			//處理點擊產子的動作
			if (point.x >= 135 && point.x <= 211 && point.y >= 10 && point.y <= 44 && GotSun == false) {
				if (shovel.isChoosed() == false) {
					CAudio::Instance()->Play(AUDIO_SHOVEL, false);
					shovel.SetChoosed(true);
					selected = true;
					mouse.SetXY(point.x, point.y);
					mouse.SetWhich(8); //讓游標的樣子變成鏟子
				}
			}


		}
		else if (selected == true &&  myrunning == false) {
			//實現back to game的功能
			if (point.x >= 315 && point.x <= 550 && point.y >= 180 && point.y <= 230 && show_menu == true && myrunning == false) {
				myrunning = true;
				selected = false;
				show_menu = false;
			}
			//實現back to menu的功能
			if (point.x >= 315 && point.x <= 550 && point.y >= 250 && point.y <= 300 && show_menu == true && myrunning == false) {
				monster.clear();
				suns.swap(vector<Sun>());
				peas.swap(vector<Pea>());
				CAudio::Instance()->Stop(AUDIO_MAIN_MUSIC);
				myrunning = !myrunning;
				selected = false;
				show_menu = false;
				GotoGameState(GAME_STATE_INIT);

			}

		}
		else if (selected) {
			if (point.x >= 172 && point.x <= 800 && point.y >= 80 && point.y <= 580) {
				//實現用鏟子移除植物的功能

				if (shovel.isChoosed() == true) {
					PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] = 0;
					bool ErasePlant = false;
					PlantClass[(point.y - 80) / 98][(point.x - 172) / 80] = zero[(point.x - 172) / 80][(point.y - 80) / 98];

				}

				else if (shovel.isChoosed() == false) {
					//植物功能
					if (PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] == 0) {
						PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] = ChoosedPlant;
						PlantClass[(point.y - 80) / 98][(point.x - 172) / 80] = Plants(ChoosedPlant, (point.x - 172) / 80, (point.y - 80) / 98);
						CAudio::Instance()->Play(AUDIO_PLANT, false);
						// TODO:
						seed.ResetCardCounter(ChoosedCard);//冷卻
						seed.Buy(ChoosedCard);

					}
				}
			}
			mouse.SetWhich(0);
			selected = false;
			ChoosedCard = -1;
			shovel.SetChoosed(false);
		}


		//  touch meau then myrunning ==false
		// 然後判斷點擊位置 回到主選單或繼續

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
	{
		if (selected) {
			mouse.SetXY(point.x, point.y);
		}
		if (show_menu) {
			if (point.x >= 315 && point.x <= 550 && point.y >= 180 && point.y <= 230) {
				show_con = 1;
			}
			else {
				show_con = 0;
			}
			//實現back to menu的功能
			if (point.x >= 315 && point.x <= 550 && point.y >= 250 && point.y <= 300) {
				show_back = 1;
			}
			else {
				show_back = 0;
			}
		}
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
	{

		for (auto &itz : monster) {
			itz->Faster();
		}
	}


	void CGameStateRun::OnShow()
	{
		if (wave >= gamelevel * 1 && gamelevel >= 3) {// 第三關後才有黑夜
			background[10].SetTopLeft(background[gamelevel - 1].Left(),0);
			background[10].ShowBitmap();
		}
		else {
			background[gamelevel - 1].ShowBitmap();   // 貼上背景圖
		}


		seed.OnShow(gamelevel+1);
		
		for (int  i = 0; i < 5; i++)
		{
			if(background[gamelevel-1].Left()>=-80 && gamelevel>=3)
				LawnCleaner[i].OnShow();
		}
		if (background[gamelevel - 1].Left() >= -80) {
			menu.SetTopLeft(695,0);
			menu.ShowBitmap(0.3);
		}
			

		
		for (int i = 0; i < 5; i++){
			// Show plants
			if(isGameOver==false){
				for (int j = 0; j < 9; j++) {
					bool ErasePlant = false;
					if (PlantClass[i][j].GetRow() == i /*&& PlantManager[i][j]!=0*/){
						PlantClass[i][j].OnShow();
						if (PlantClass[i][j].isFinished() == true) {             //讓植物在死亡後或是動作結束後(葫蘆和櫻桃)被解構
								ErasePlant = true;
								PlantManager[PlantClass[i][j].GetRow()][PlantClass[i][j].GetColumn()] = 0;
								continue;
						}
						if (ErasePlant == true) {
							ErasePlant = false;
							}
						}
				}
			}
		}


		// Show zombies
		for (auto &itz : monster) {
			itz->OnShow();
		}


		for (int i = 0; i < 5; i++) {
			vector<Pea>::iterator itpea;
			bool ErasePea = false;
			for (vector<Pea>::iterator it = peas.begin(); it != peas.end(); it++) {
				if (it->isFinished() == true) {             //讓豆子在擊中殭屍的動畫結束後才會被解構
					itpea = it;
					ErasePea = true;
					continue;
				}
				it->OnShow();
			}
			if (ErasePea == true) {
				peas.erase(itpea);
				ErasePea = false;
			}
		}

		for (int i = 0; i < 5; i++)
			zombiesone[i].ShowBitmap();
		shovel.OnShow();

		for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
			its->OnShow();
		}
		if (selected) {

			mouse.OnShow();
		}
		//show menu
		if (show_menu) {
			run_menu.ShowBitmap();
			run_con[show_con].ShowBitmap(0.7);
			run_return[show_back].ShowBitmap(0.7);

		}

	}

}