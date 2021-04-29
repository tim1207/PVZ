#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"



namespace game_framework {
	bool YouWin = false;
	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	//讀取音效檔
	void CGameStateInit::LoadAudio() {

	}

	// is finished 
	void CGameStateInit::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(0); // 一開始的loading進度為0%
		//
		// 開始載入資料
		//
		logo.LoadBitmap(Background);
		adventure_block.LoadBitmap(Adventure, RGB(255, 255, 255));
		//Sleep(300);    // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 此OnInit動作會接到CGameStaterRun::OnInit()，所以進度還沒到100%
		//
	}

	void CGameStateInit::OnBeginState()
	{
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
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);  // 切換至GAME_STATE_RUN
	}

	// is finish
	void CGameStateInit::OnShow()
	{
		logo.ShowBitmap();
		adventure_block.SetTopLeft(480, 100);
		adventure_block.ShowBitmap();

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

	// Init is over 




	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
	}
	//讀取結果的圖檔
	void CGameStateOver::LoadBitmap() {
		ZombiesWon.LoadBitmap(".\\BMP_RES\\image\\interface\\ZombiesWon.bmp");
		//TODO:	need to be set 
		ZombiesWon.SetTopLeft(0, 0);
		ZombieNote.LoadBitmap(".\\BMP_RES\\image\\interface\\trophy.bmp");
		//TODO:	need to be set 
		ZombieNote.SetTopLeft(0, 0);
	}

	// is finished
	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_INIT);
	}

	void CGameStateOver::OnBeginState()
	{
		counter = 30 * 5; // 5 seconds
	}
	// is finished 
	void CGameStateOver::OnInit()
	{
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(66); // 接個前一個狀態的進度，此處進度視為66%
		//
		// 開始載入資料
		//
		Sleep(300);    // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		// 最終進度為100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{
		if (YouWin == false) {
			ZombiesWon.ShowBitmap();
		}
		else {
			ZombieNote.ShowBitmap();
		}

		//teacher's code
		// 	CDC *pDC = CDDraw::GetBackCDC();   // 取得 Back Plain 的 CDC 
		// 	CFont f, *fp;
		// 	f.CreatePointFont(160, "Times New Roman"); // 產生 font f; 160表示16 point的字
		// 	fp = pDC->SelectObject(&f);     // 選用 font f
		// 	pDC->SetBkColor(RGB(0, 0, 0));
		// 	pDC->SetTextColor(RGB(255, 255, 0));
		// 	char str[80];        // Demo 數字對字串的轉換
		// 	sprintf(str, "Game Over ! (%d)", counter / 30);
		// 	pDC->TextOut(240, 210, str);
		// 	pDC->SelectObject(fp);      // 放掉 font f (千萬不要漏了放掉)
		// 	CDDraw::ReleaseBackCDC();     // 放掉 Back Plain 的 CDC
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
		background.SetTopLeft(-500, 0);    				// 設定背景的起始座標
		//help.SetTopLeft(0, SIZE_Y - help.Height());   // 設定說明圖的起始座標
		
		sunback.SetTopLeft(-400, 10);
		zombiesone[0].SetTopLeft(640, 150);
		zombiesone[1].SetTopLeft(660, 200);
		zombiesone[2].SetTopLeft(640, 250);
		zombiesone[3].SetTopLeft(660, 300);
		zombiesone[4].SetTopLeft(640, 350);

		//設定和滑鼠相關的變數
		SunCounter = 0;                                   //從空中掉落太陽的計時器
		selected = false;
		ChoosedCard = -1;
		ChoosedPlant = -1;
		//重設場上的植物
		// plants init
		 for (int i = 0; i < 5; i++) {
		 	for (int j = 0; j < 9; j++) {
		 		PlantManager[i][j] = 0;
				testp[i][j] = Plants(0, j, i);
		 	}
		 }
		 flow = 0;
		//確保所有的vector清空

		monster.clear();
		// plants.clear();
		peas.clear();
		suns.clear();
		seed.Reset();

		//重設除草機
		// for (int i = 0; i < 5; i++) {
		// 	LawnMower[i].Reset();
		// }
		// wave = 0;

		//CAudio::Instance()->Play(AUDIO_LAKE, true);   // 撥放 WAVE
		//CAudio::Instance()->Play(AUDIO_DING, false);  // 撥放 WAVE
		//CAudio::Instance()->Play(AUDIO_NTUT, true);   // 撥放 MIDI
	}

	void CGameStateRun::OnInit()          // 遊戲的初值及圖形設定
	{	
		int temp[] = { 1,2,3 };
		seed.Load(3, temp);//可能錯
		//
		// 當圖很多時，OnInit載入所有的圖要花很多時間。為避免玩遊戲的人
		//     等的不耐煩，遊戲會出現「Loading ...」，顯示Loading的進度。
		//
		ShowInitProgress(33); // 接個前一個狀態的進度，此處進度視為33%
		background.LoadBitmap(Background1row);     // 載入背景的圖形
		//
		// 完成部分Loading動作，提高進度
		//
		ShowInitProgress(50);
		Sleep(300); // 放慢，以便看清楚進度，實際遊戲請刪除此Sleep
		//
		for (int i = 0; i < 5; i++)						//載入殭屍
			zombiesone[i].LoadBitmap(".\\BMP_RES\\image\\zombies\\cutscene1_11.bmp", RGB(0, 0, 0));

		
		//plants.push_back(Plants(1, 3, 2));
		//testp[0]= Plants(1, 3, 1);
		cursor.LoadBitmap();
		sunback.LoadBitmap("BMP_RES/image/interface/SunBack.bmp", RGB(0, 0, 0));
		shovel.LoadBitmap();
		
		// 繼續載入其他資料

		//CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav"); // 載入編號0的聲音ding.wav
		//CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3"); // 載入編號1的聲音lake.mp3
		//CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid"); // 載入編號2的聲音ntut.mid
		//
		// 此OnInit動作會接到CGameStaterOver::OnInit()，所以進度還沒到100%
		//

	}

	void CGameStateRun::OnMove()       // 移動遊戲元素
	{
		//  開始的移動畫面
		if (background.Left() < -80)
			background.SetTopLeft(background.Left() + 10, 0);
		if (sunback.Left() < 100)
			sunback.SetTopLeft(sunback.Left() + 10, 10);
		// TODO: 放置殭屍 (right)


		//

		for (int i = 0; i < 5; i++) {
			if (zombiesone[i].Left() < 1040)
				zombiesone[i].SetTopLeft(zombiesone[i].Left() + 10, 150 + i * 50);
		}

		//每隔7秒從空中產生一個太陽
		SunCounter++;
		if (SunCounter == 210) {
			SunCounter = 0;
			suns.push_back(Sun(rand() % 400 + 100, rand() % 300 + 100, false));
		}
		/*
		for (int i = 0; i <= (5 - 1) / 3; i++) {
			int id = i + 1;
			int r = (rand() % 5);
			monster.push_back(Zombies(1,3,400));
		}
		*/
		//處理所有植物的動作
		vector<Plants>::iterator itpp;
		bool ErasePlant = false;

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				if (testp[i][j].isAlive() == false) {                               //如果植物的生命為零，設定植物的死亡
					ErasePlant = true;
					PlantManager[i][j] = 0;
					continue;
				}
				testp[i][j].OnMove();
				//處理向日葵的動作
				if (testp[i][j].GetID() == 1) {
					testp[i][j].SetCounterOn(true);
					if (testp[i][j].isAction() == true) {                             //時間到了就產生一個太陽
						suns.push_back(Sun(testp[i][j].GetX(), testp[i][j].GetY(), true));
					}
					continue;
				}
				//處理一般豌豆的動作
				if (testp[i][j].GetID() == 2) {
					bool FoundZombie = false;
					for (vector<Zombies>::iterator itz = monster.begin(); itz != monster.end(); itz++) {
						if (testp[i][j].GetRow() == testp[i][j].GetRow() && testp[i][j].GetX() + 50 >= testp[i][j].GetX()) {
							FoundZombie = true;
							if (testp[i][j].GetX() + 50 > testp[i][j].GetX()) {
								testp[i][j].SetCounterOn(true);                             //如果找到可攻擊的殭屍就進入攻擊狀態
							}
							else {
								testp[i][j].SetCounterOn(false);
							}
						}
						//}
						if (testp[i][j].isAction() == true) {
							//CAudio::Instance()->Play(AUDIO_SHOOT, false);
							peas.push_back(Pea(testp[i][j].GetX() + 50, testp[i][j].GetRow(), 0)); //如果攻擊冷卻時間到了就射出一顆豆子
						}
						if (FoundZombie == false) {
							testp[i][j].SetCounterOn(false);
						}
					}
				}

			}
			for (vector<Pea>::iterator itpea = peas.begin(); itpea != peas.end(); itpea++)
				itpea->OnMove();
			// maybe now don't need it  
			vector<Sun>::iterator itss;
			bool EraseSun = false;

			//處理所有太陽的動作
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



	//進入GameStateOver，並將vector清空，否則第二次完會產生錯誤
	void CGameStateRun::GameOver()
	{	//monster.swap(vector<Zombies>());
		//plants.swap(vector<Plants>());
		suns.swap(vector<Sun>());
		peas.swap(vector<Pea>());
		// CAudio::Instance()->Stop(AUDIO_MAIN_MUSIC);
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
			/*
			for (vector<Zombies>::iterator itz = zombies.begin(); itz != zombies.end(); itz++) {
				itz->GoToDie();
			}
			*/
		}
		else if (nChar == KEY_DOWN) {
			for (int i = 0; i < 40; i++) {
				seed.GotSun();
			}
		}
		else if (nChar == KEY_LEFT) {
			seed.ResetCD();
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

	// TODO:
	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{
		if (!selected) {
			//處理點擊太陽的動作
			bool GotSun = false;
			for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
				if (point.x >= its->GetX() && point.x <= its->GetX() + its->GetWidth() && point.y >= its->GetY() && point.y <= its->GetY() + its->GetHeight()) {
					its->PickUp();
					//CAudio::Instance()->Play(AUDIO_COLLECT_SUN, false);
					seed.GotSun();
					GotSun = true;
					break;
				}
			}
			//處理選擇卡片的動作
			if (point.x >= 0 && point.x <= 95 && point.y >= 50 && point.y <= 230 && GotSun == false) {
				ChoosedCard = (point.y - 50) / 60;
				ChoosedPlant = seed.GetCardID(ChoosedCard);
				if (seed.isCardAvailible(ChoosedCard)) {
					//CAudio::Instance()->Play(AUDIO_CHOOSE_CARD, false);
					selected = true;
					cursor.SetXY(point.x, point.y);
					cursor.SetWhich(ChoosedPlant); //讓游標的樣子變成準備種植的植物
					
				}
			}
			//處理點擊產子的動作
			if (point.x >= 135 && point.x <= 211 && point.y >= 10 && point.y <= 44 && GotSun == false) {
				if (shovel.isChoosed() == false) {
					//CAudio::Instance()->Play(AUDIO_SHOVEL, false);
					shovel.SetChoosed(true);
					selected = true;
					cursor.SetXY(point.x, point.y);
					cursor.SetWhich(8); //讓游標的樣子變成鏟子
				}
			}

		}
		else if (selected) {
			if (point.x >= 172 && point.x <= 900 && point.y >= 80 && point.y <= 580) {
				//實現用鏟子移除植物的功能
				
				if (shovel.isChoosed() == true) {
					PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] = 0;
					bool ErasePlant = false;
					//testp[(point.y - 80) / 98][(point.x - 172) / 80].SetID(0);
					
					testp[(point.y - 80) / 98][(point.x - 172) / 80]=Plants(0, (point.x - 172) / 80, (point.y - 80) / 98);
					/*
					vector<Plants>::iterator itpp;
					for (vector<Plants>::iterator itp = plants.begin(); itp != plants.end(); itp++) {
						if (itp->GetRow() == (point.y - 75) / 75 && itp->GetColumn() == (point.x - 46) / 66) {
							itpp = itp;
							ErasePlant = true;
						}
					}
					*/

				}
				
				else if (shovel.isChoosed() == false) {
					//植物功能
					if (PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] == 0) {
						PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] = ChoosedPlant;
						testp[(point.y - 80) / 98][(point.x - 172) / 80] = Plants(ChoosedPlant, (point.x - 172) / 80, (point.y - 80) / 98);
						
						//plants.push_back(Plants(ChoosedPlant, (point.x - 172) / 80, (point.y - 80) / 98));
						//CAudio::Instance()->Play(AUDIO_PLANT, false);
						//seed.ResetCardCounter(ChoosedCard);//冷卻
						seed.Buy(ChoosedCard);

					}
				}	
			}
			cursor.SetWhich(0);
			selected = false;
			ChoosedCard = -1;
			shovel.SetChoosed(false);
		}
		
	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // 處理滑鼠的動作
	{
		 if (selected) {
		 	cursor.SetXY(point.x, point.y);
		 }
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // 處理滑鼠的動作
	{
		for (int i = 0; i < 5; i++) {
			monster.push_back(Zombies(1, i, 590));
			for (int j = 0; j < 10; j++) {
				monster.back().Faster();
			}
		}
	}


void CGameStateRun::OnShow()
{
	//
	//  注意：Show裡面千萬不要移動任何物件的座標，移動座標的工作應由Move做才對，
	//        否則當視窗重新繪圖時(OnDraw)，物件就會移動，看起來會很怪。換個術語
	//        說，Move負責MVC中的Model，Show負責View，而View不應更動Model。
	//
	//
	//
	
	background.ShowBitmap();   // 貼上背景圖
	seed.OnShow();
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
		// Show plants
		for (int j = 0; j < 9; j++) {
			testp[i][j].OnShow();
		}
		vector<Zombies>::iterator itz;
		bool EraseZombie = false;
		for (vector<Zombies>::iterator it = monster.begin(); it != monster.end(); it++) {
			if (it->GetRow() == i)	it->OnShow();
			if (it->isFinished() == true) {             // 讓殭屍在死亡動畫顯示完畢後才會被解構
				itz = it;
				EraseZombie = true;
				continue;
			}
		}

	}
	
	
	/*
	for (int row = 0; row < 5; row++) {
		vector<Plants>::iterator itp;
		bool ErasePlant = false;
		for (vector<Plants>::iterator it = plants.begin(); it != plants.end(); it++) {
			if (it->GetRow() == row)	
				it->OnShow();

			if (it->isFinished() == true) {             //讓植物在死亡後或是動作結束後(葫蘆和櫻桃)被解構
				itp = it;
				ErasePlant = true;
				PlantManager[itp->GetRow()][itp->GetColumn()] = 0;
				continue;
			}
			if (ErasePlant == true) {
				plants.erase(itp);
				ErasePlant = false;
			}
		}
	}
	*/
	///
	for (int i = 0; i < 5; i++)
		zombiesone[i].ShowBitmap();
	// map.OnShow();
	shovel.OnShow();
	/*
	CDC *pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f, *fp;
	f.CreatePointFont(100, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
	pDC->SetBkColor(RGB(238, 230, 170));
	pDC->SetTextColor(RGB(0, 0, 0));

	pDC->TextOut(165, 18, "50");
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
	*/
	///sun drop
	
	for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
		its->OnShow();
	}
	if (selected) {

		cursor.OnShow();
	}
}

}