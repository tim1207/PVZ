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
	int gamelevel=1;
	bool isGameOver;
	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C���}�Y�e������
	/////////////////////////////////////////////////////////////////////////////

	CGameStateInit::CGameStateInit(CGame *g)
		: CGameState(g)
	{
	}

	//Ū��������
	void CGameStateInit::LoadAudio() {

	}

	// is finished 
	void CGameStateInit::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(0); // �@�}�l��loading�i�׬�0%
		//
		// �}�l���J���
		//
		logo.LoadBitmap(Background);
		adventure_block.LoadBitmap(Adventure, RGB(255, 255, 255));
		//Sleep(300);    // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// ��OnInit�ʧ@�|����CGameStaterRun::OnInit()�A�ҥH�i���٨S��100%
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
			GotoGameState(GAME_STATE_RUN);      // ������GAME_STATE_RUN
		else if (nChar == KEY_ESC)        // Demo �����C������k
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0); // �����C��
	}


	void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)	// �B�z�ƹ����ʧ@
	{
		// �B�z�ƹ��M��檺����
	}

	void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
	{
		GotoGameState(GAME_STATE_RUN);  // ������GAME_STATE_RUN
	}

	// is finish
	void CGameStateInit::OnShow()
	{
		logo.ShowBitmap();
		adventure_block.SetTopLeft(480, 100);
		adventure_block.ShowBitmap();

		//   //
		//   // Demo�ù��r�����ϥΡA���L�}�o�ɽкɶq�קK�����ϥΦr���A���CMovingBitmap����n
		//   //
		//   CDC *pDC = CDDraw::GetBackCDC();   // ���o Back Plain �� CDC 
		//   CFont f, *fp;
		//   f.CreatePointFont(160, "Times New Roman"); // ���� font f; 160���16 point���r
		//   fp = pDC->SelectObject(&f);     // ��� font f
		//   pDC->SetBkColor(RGB(0, 0, 0));
		//   pDC->SetTextColor(RGB(255, 255, 0));
		//   pDC->TextOut(120, 220, "Please click mouse or press SPACE to begin.");
		//   pDC->TextOut(5, 395, "Press Ctrl-F to switch in between window mode and full screen mode.");
		//   if (ENABLE_GAME_PAUSE)
		//    pDC->TextOut(5, 425, "Press Ctrl-Q to pause the Game.");
		//   pDC->TextOut(5, 455, "Press Alt-F4 or ESC to Quit.");
		//   pDC->SelectObject(fp);      // �� font f (�d�U���n�|�F��)
		//   CDDraw::ReleaseBackCDC();     // �� Back Plain �� CDC
	}





	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����������A(Game Over)
	/////////////////////////////////////////////////////////////////////////////

	CGameStateOver::CGameStateOver(CGame *g)
		: CGameState(g)
	{
		
	}
	//Ū�����G������
	void CGameStateOver::LoadBitmap() {
		ZombiesWon.LoadBitmap(".\\BMP_RES\\image\\interface\\ZombiesWon.bmp");

		ZombiesWon.SetTopLeft(0, 0);
		ZombieNote.LoadBitmap(".\\BMP_RES\\image\\interface\\trophy.bmp");

		ZombieNote.SetTopLeft(0, 0);
	}

	void CGameStateOver::OnMove()
	{
		counter--;
		if (counter < 0)
			GotoGameState(GAME_STATE_RUN);
	}

	void CGameStateOver::OnBeginState()
	{	
		if(gamelevel==1){
			LoadBitmap();
		}
			
		counter = 30 * 5; // 5 seconds
		if(YouWin==true)
			gamelevel++;
	}
	// is finished 
	void CGameStateOver::OnInit()
	{
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(66); // ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
		//
		// �}�l���J���
		//
		Sleep(300);    // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		//
		// �̲׶i�׬�100%
		//
		ShowInitProgress(100);
	}

	void CGameStateOver::OnShow()
	{	
		if(isGameOver)
			if (YouWin == false) {
				ZombiesWon.ShowBitmap();
			}
			else {
				ZombieNote.ShowBitmap();
			}
	}

	/////////////////////////////////////////////////////////////////////////////
	// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
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
		background.SetTopLeft(-500, 0);    				// �]�w�I�����_�l�y��
		//help.SetTopLeft(0, SIZE_Y - help.Height());   // �]�w�����Ϫ��_�l�y��

		sunback.SetTopLeft(-400, 10);
		zombiesone[0].SetTopLeft(640, 150);
		zombiesone[1].SetTopLeft(660, 200);
		zombiesone[2].SetTopLeft(640, 250);
		zombiesone[3].SetTopLeft(660, 300);
		zombiesone[4].SetTopLeft(640, 350);

		//�]�w�M�ƹ��������ܼ�
		SunCounter = 0;                                   //�q�Ť������Ӷ����p�ɾ�
		ZombieCounter = 0;
		selected = false;
		ChoosedCard = -1;
		ChoosedPlant = -1;
		isGameOver=false;
		YouWin=false;
		//�T�O�Ҧ���vector�M��

		monster.clear();
		// plants.clear();
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				PlantManager[i][j] = 0;
				PlantClass[i][j] = Plants(0, j, i);
			}
		}
		peas.clear();
		suns.clear();
		seed.Reset();

		//���]�����
		//for (int i = 0; i < 5; i++) {
		 //	LawnCleaner[i].Reset();
		//}
		wave = 0;

		//CAudio::Instance()->Play(AUDIO_LAKE, true);   // ���� WAVE
		//CAudio::Instance()->Play(AUDIO_DING, false);  // ���� WAVE
		//CAudio::Instance()->Play(AUDIO_NTUT, true);   // ���� MIDI
	}

	void CGameStateRun::OnInit()          // �C������Ȥιϧγ]�w
	{
		//TODO:
		

		//���]���W���Ӫ�
		
		//
		// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
		//     �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
		//
		ShowInitProgress(33); // ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
		
		//
		// ��������Loading�ʧ@�A�����i��
		//
		ShowInitProgress(50);
		Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
		if(gamelevel==1){
			background.LoadBitmap(Background1row);     // ���J�I�����ϧ�
			int temp[] = {1,2,3,4,5,6,7};
			seed.Load(7, temp);

			for (int i = 0; i < 5; i++) {					//���J�L��
				zombiesone[i].LoadBitmap(".\\BMP_RES\\image\\zombies\\cutscene1_11.bmp", RGB(0, 0, 0));
				LawnCleaner[i].LoadBitmap();
			}

			//plants.push_back(Plants(1, 3, 2));
			//PlantClass[0]= Plants(1, 3, 1);
			mouse.LoadBitmap();
			sunback.LoadBitmap("BMP_RES/image/interface/SunBack.bmp", RGB(0, 0, 0));
			shovel.LoadBitmap();
		}
		

		// �~����J��L���

		//CAudio::Instance()->Load(AUDIO_DING, "sounds\\ding.wav"); // ���J�s��0���n��ding.wav
		//CAudio::Instance()->Load(AUDIO_LAKE, "sounds\\lake.mp3"); // ���J�s��1���n��lake.mp3
		//CAudio::Instance()->Load(AUDIO_NTUT, "sounds\\ntut.mid"); // ���J�s��2���n��ntut.mid
		//
		// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
		//

	}

	void CGameStateRun::OnMove()       // ���ʹC������
	{
		//  �}�l�����ʵe��
		if (background.Left() < -80)
			background.SetTopLeft(background.Left() + 10, 0);
		// TODO:
		// if (background.Left() >= -80){
		// 	for (int i = 0; i < 5; i++) {
		// 		LawnCleaner[i].Reset();
		// 		LawnCleaner[i].SetY(i);
		// 	}
		// }
			

		if (sunback.Left() < 100)
			sunback.SetTopLeft(sunback.Left() + 10, 10);
		
		// ��m�L�� (right)
		for (int i = 0; i < 5; i++) {
			if (zombiesone[i].Left() < 1040)
				zombiesone[i].SetTopLeft(zombiesone[i].Left() + 10, 150 + i * 50);
		}

		//�C�j7��q�Ť����ͤ@�ӤӶ�
		SunCounter++;
		if (SunCounter == 300) {
			SunCounter = 0;
			suns.push_back(Sun(rand() % 400 + 100, rand() % 300 + 100, false));
		}


		ZombieCounter++;
		if (wave < 1 && wave >= 0) {
			///�C�j10����1~3���H���������L��
			if (ZombieCounter == 200) {
				wave++;
				if (awooga == false) {
					//CAudio::Instance()->Play(AUDIO_AWOOGA, false);
					awooga = true;
				}
				ZombieCounter = 0;
				//int groan = rand() % 6;
				//CAudio::Instance()->Play(AUDIO_GROAN_1 + groan, false);
				for (int i = 0; i < 1; i++) {
					//int r = (rand() % 5);
					monster.push_back(make_shared<Zombies>(1, 3, 800));
				}
			}
		}
		else if (wave == 1 && ZombieCounter >= 200) {
			if (ZombieCounter == 450) {
				//CAudio::Instance()->Play(AUDIO_FINALWAVE, false);
			}
			if (ZombieCounter >= 450 && ZombieCounter <= 500) {
				if ((ZombieCounter - 450) % 10 == 0) {
					for (int i = 0; i < 5; i++) {
						//int id = (rand() % 3) + 1;
						monster.push_back(make_shared<Zombies>(1, 3, 800));
					}
				}
			}
		}
		// TODO:
		if (monster.size() >=1 && ZombieCounter > 200) {
			YouWin = true;
			isGameOver = true;
		}

		

		for (auto &itz : monster) {
			//�B�z�Ҧ��L�ͪ��ʧ@			
			itz->OnMove();
			if (itz->GetX() < 100) {
				YouWin = false;
				isGameOver = true;                                         //�p�G�L�Ͷ]�i�a�̡A�C������
			}
			//�M���L�ͥi�������Ĥ@���Ӫ�
			int closest = 10;
			for (int i = (itz->GetX() + 80) / 75; i >= 0; i--) {
				if (PlantManager[itz->GetRow()][i] > 0) {
					closest = i;
					break;
				}
			}
			if (itz->isAlive() == true) {
				//�p�G�L�ͳQ���������N���W���`
				
				// if (LawnCleaner[itz->GetRow()].GetX() > itz->GetX() + 30 && LawnCleaner[itz->GetRow()].GetX() < itz->GetX() + 100) {
				// 	LawnCleaner[itz->GetRow()].StartMove();
				// 	//CAudio::Instance()->Play(AUDIO_LAWN_MOWER, false);
				// 	itz->GoToDie();
				// }
				
				bool found = false;
				for (int i = 0; i < 5; i++) {
					for (int j = 0; j < 9; j++) {
						if (PlantClass[i][j].GetRow() == itz->GetRow() && PlantClass[i][j].GetColumn() == closest) {
							if (PlantClass[i][j].GetX() <= itz->GetX()+80 && PlantClass[i][j].GetX() >= itz->GetX() + 30) {
								itz->SetStatus(2);                                   //�p�G���L�ͳ̪񪺴Ӫ��i�J�����d��N�i�J�������A
								found = true;
							}
							else {
								itz->SetStatus(1);
							}
							//�p�G�L�ͥ��b�������A�B�����N�o�ɶ������A�Ӫ��N�������
							if (itz->GetStatus() == 2 && itz->Attack() == true) {
								int chomp = rand() % 3;
								//CAudio::Instance()->Play(AUDIO_CHOMP_1 + chomp, false);
								PlantClass[i][j].BeingAttacked();
								if (PlantClass[i][j].isAlive() == false) {
									PlantClass[i][j] = Plants(0, i,j);
									PlantManager[i][j] = 0;
									itz->SetStatus(1);                                 //�p�G�Ӫ��Q�L�ͦY���F�A�L�Ͱ��W��_���q���A
								}
							}

						}
					}
				}

				if (found == false) {
					itz->SetStatus(1);
				}
			}

			//�L�ͦ��`
			// TODO::
			if (itz->isFinished() == true) {
				itz->Die();
			}


		}
		//�B�z�Ҧ��Ӫ����ʧ@
		bool ErasePlant = false;
		if(isGameOver==true)
			GameOver();

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 9; j++) {
				if (PlantClass[i][j].isAlive() == false) {                               //�p�G�Ӫ����ͩR���s�A�]�w�Ӫ������`
					ErasePlant = true;
					PlantManager[i][j] = 0;
					continue;
				}
				PlantClass[i][j].OnMove();
				//�B�z�V�鸪���ʧ@
				if (PlantClass[i][j].GetID() == 1) {
					PlantClass[i][j].SetCounterOn(true);
					if (PlantClass[i][j].isAction() == true) {                             //�ɶ���F�N���ͤ@�ӤӶ�
						suns.push_back(Sun(PlantClass[i][j].GetX(), PlantClass[i][j].GetY(), true));
					}
					continue;
				}
				//�B�z�@��ܨ����ʧ@
				if (PlantClass[i][j].GetID() == 2) {
					bool FoundZombie = false;
					for (auto &itz : monster) {
						if (PlantClass[i][j].GetRow() == PlantClass[i][j].GetRow() && PlantClass[i][j].GetX() + 50 >= PlantClass[i][j].GetX()) {
							FoundZombie = true;
							if (PlantClass[i][j].GetX() + 50 > PlantClass[i][j].GetX()) {
								PlantClass[i][j].SetCounterOn(true);                             //�p�G���i�������L�ʹN�i�J�������A
							}
							else {
								PlantClass[i][j].SetCounterOn(false);
							}
						}

						if (PlantClass[i][j].isAction() == true) {
							//CAudio::Instance()->Play(AUDIO_SHOOT, false);
							peas.push_back(Pea(PlantClass[i][j].GetX() + 50, PlantClass[i][j].GetRow(), 0)); //�p�G�����N�o�ɶ���F�N�g�X�@�����l
						}
						if (FoundZombie == false) {
							PlantClass[i][j].SetCounterOn(false);
						}
					}
				}

			}
			for (vector<Pea>::iterator itpea = peas.begin(); itpea != peas.end(); itpea++) {
				itpea->OnMove();
				//vector<Zombies>::auto itzz;
				//vector< shared_ptr<Zombies> >::iterator itzz;
				bool HitZombie = false;
				int mi = 1000;
				for (auto &itz : monster) {

					if (itpea->GetRow() == itz->GetRow() && itpea->GetX() > itz->GetX() + 75 && itpea->GetX() < itz->GetX() + 110) {
						if (mi > itz->GetX()) {
							mi = itz->GetX();
							//itzz = itz;
							HitZombie = true;
							itpea->SetHitZombie(true);
							//�B�z�����L�᪺ͫ�ʧ@
							if (itz->GetID() == 3 && itz->GetLife() > 10) {
								int sound = rand() % 2;
								//CAudio::Instance()->Play(AUDIO_HIT_BUCKET_1 + sound, false);
							}
							else {
								int sound = rand() % 3;
								//CAudio::Instance()->Play(AUDIO_SPLAT_1 + sound, false);
							}
							itz->Hitted(itpea->MyType());
						}
					}
					if (itpea->GetX() > 880) {
						itpea->SetHitZombie(true);
					}
				}
			}
			vector<Sun>::iterator itss;
			bool EraseSun = false;

			//�B�z�Ҧ��Ӷ����ʧ@
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



	//�i�JGameStateOver�A�ñNvector�M�šA�_�h�ĤG�����|���Ϳ��~
	void CGameStateRun::GameOver()
	{
		monster.clear();
		suns.swap(vector<Sun>());
		peas.swap(vector<Pea>());
		// CAudio::Instance()->Stop(AUDIO_MAIN_MUSIC);
		GotoGameState(GAME_STATE_OVER);
	}


	//�K��
	void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
	{
		const char KEY_LEFT = 0x25; // keyboard���b�Y
		const char KEY_UP = 0x26; // keyboard�W�b�Y
		const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		const char KEY_DOWN = 0x28; // keyboard�U�b�Y

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
		// const char KEY_LEFT = 0x25; // keyboard���b�Y
		// const char KEY_UP = 0x26; // keyboard�W�b�Y
		// const char KEY_RIGHT = 0x27; // keyboard�k�b�Y
		// const char KEY_DOWN = 0x28; // keyboard�U�b�Y

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

	void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{
		if (!selected) {
			//�B�z�I���Ӷ����ʧ@
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
			//�B�z��ܥd�����ʧ@
			if (point.x >= 0 && point.x <= 95 && point.y >= 50 && point.y <= 230 && GotSun == false) {
				ChoosedCard = (point.y - 50) / 60;
				if(ChoosedCard<=gamelevel+1){
					ChoosedPlant = seed.GetCardID(ChoosedCard);
					if (seed.isCardAvailible(ChoosedCard)) {
						//CAudio::Instance()->Play(AUDIO_CHOOSE_CARD, false);
						selected = true;
						mouse.SetXY(point.x, point.y);
						mouse.SetWhich(ChoosedPlant); //����Ъ��ˤl�ܦ��ǳƺشӪ��Ӫ�

					}
				}
				
			}
			//�B�z�I�����l���ʧ@
			if (point.x >= 135 && point.x <= 211 && point.y >= 10 && point.y <= 44 && GotSun == false) {
				if (shovel.isChoosed() == false) {
					//CAudio::Instance()->Play(AUDIO_SHOVEL, false);
					shovel.SetChoosed(true);
					selected = true;
					mouse.SetXY(point.x, point.y);
					mouse.SetWhich(8); //����Ъ��ˤl�ܦ���l
				}
			}

		}
		else if (selected) {
			if (point.x >= 172 && point.x <= 900 && point.y >= 80 && point.y <= 580) {
				//��{����l�����Ӫ����\��

				if (shovel.isChoosed() == true) {
					PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] = 0;
					bool ErasePlant = false;
					PlantClass[(point.y - 80) / 98][(point.x - 172) / 80] = Plants(0, (point.x - 172) / 80, (point.y - 80) / 98);

				}

				else if (shovel.isChoosed() == false) {
					//�Ӫ��\��
					if (PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] == 0) {
						PlantManager[(point.y - 80) / 98][(point.x - 172) / 80] = ChoosedPlant;
						PlantClass[(point.y - 80) / 98][(point.x - 172) / 80] = Plants(ChoosedPlant, (point.x - 172) / 80, (point.y - 80) / 98);
						//CAudio::Instance()->Play(AUDIO_PLANT, false);
						// TODO:
						//seed.ResetCardCounter(ChoosedCard);//�N�o
						seed.Buy(ChoosedCard);

					}
				}
			}
			mouse.SetWhich(0);
			selected = false;
			ChoosedCard = -1;
			shovel.SetChoosed(false);
		}

	}

	void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
	{
		if (selected) {
			mouse.SetXY(point.x, point.y);
		}
	}

	void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // �B�z�ƹ����ʧ@
	{

	}

	void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point) // �B�z�ƹ����ʧ@
	{

		for (auto &itz : monster) {
			itz->Faster();
		}
	}


	void CGameStateRun::OnShow()
	{
		//
		//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
		//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
		//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
		//
		//
		//

		background.ShowBitmap();   // �K�W�I����

		seed.OnShow(gamelevel+1);
		
		for (int  i = 0; i < 5; i++)
		{
			LawnCleaner[i].OnShow();
		}
		for (int i = 0; i < 5; i++) {
			vector<Pea>::iterator itpea;
			bool ErasePea = false;
			for (vector<Pea>::iterator it = peas.begin(); it != peas.end(); it++) {
				if (it->isFinished() == true) {             //�����l�b�����L�ͪ��ʵe������~�|�Q�Ѻc
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
			if(isGameOver==false){
				for (int j = 0; j < 9; j++) {
					bool ErasePlant = false;
					if (PlantClass[i][j].GetRow() == i){
						PlantClass[i][j].OnShow();
						if (PlantClass[i][j].isFinished() == true) {             //���Ӫ��b���`��άO�ʧ@������(��Ī�M���)�Q�Ѻc
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
		for (int i = 0; i < 5; i++)
			zombiesone[i].ShowBitmap();
		// map.OnShow();
		shovel.OnShow();
		/*
		CDC *pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC
		CFont f, *fp;
		f.CreatePointFont(100, "Times New Roman");	// ���� font f; 160���16 point���r
		fp = pDC->SelectObject(&f);					// ��� font f
		pDC->SetBkColor(RGB(238, 230, 170));
		pDC->SetTextColor(RGB(0, 0, 0));

		pDC->TextOut(165, 18, "50");
		pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
		CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
		*/
		///sun drop

		for (vector<Sun>::iterator its = suns.begin(); its != suns.end(); its++) {
			its->OnShow();
		}
		if (selected) {

			mouse.OnShow();
		}
	}

}