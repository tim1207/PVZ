#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Seed.h"
#include "card.h"
namespace game_framework {
	Seed::Seed() {
		//money = 50;
		money =1000;
	}
	void Seed::Reset() {		                        // 重設初始狀態
		//money = 50;
		money = 1000;
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->Reset();
		}
	}
	void Seed::ResetCD() {		                      // 強制冷卻時間歸零(密技用)
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->Reset();
		}
	}
	int Seed::GetMoney() {		                      // 回傳目前太陽數量
		return money;
	}
	void Seed::Buy(int a) {		                      // 購買植物
		money -= cards[a].GetPrice();
	}
	void Seed::GotSun() {		                        // 增加太陽
		money += 25;
		if (money > 9999) {		                        // 上限9999
			money = 9999;
		}
	}
	void Seed::Load(int sum, int CardIDs[]) {	      //讀取所需的資源(包含卡片)
		LoadBitmap();
		for (int i = 0; i < sum; i++) {
			//cards.push_back(Card(CardIDs[i]));
			cards.push_back(Card(i+1));
		}
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->LoadBitmap();
		}
	}
	void Seed::LoadBitmap() {					              //讀取所需的圖檔
		// sum money
		bmp.LoadBitmap("./BMP_RES/image/interface/SunBack.bmp", RGB(0, 0, 0));	
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 10; j++) {
				char FILENAME[100];
				sprintf(FILENAME,  ".\\BMP_RES\\image\\interface\\%d.bmp", j);
				sun[i][j].LoadBitmap(FILENAME, RGB(255, 255, 255));
			}
		}
	}
	int Seed::GetCardID(int a) {				            // 回傳特定卡片所代表的植物種類
		return cards[a].GetID();
	}
	void Seed::ResetCardCounter(int a) {		        // 重設特定卡片的冷卻時間
		cards[a].ResetCounter();
	}
	bool Seed::isCardAvailible(int a) {			        // 回傳特定卡片是否可被選取
		return cards[a].isAvailible();
	}
	void Seed::OnMove()							                // 控制商店的動作
	{
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->OnMove();
			if (it->GetPrice() > GetMoney()) {
				it->SetAvailible(false);
			}
			else
				it->SetAvailible(true);
		}
	}
	void Seed::OnShow()							                // 顯示商店
	{
		bmp.SetTopLeft(0, 0);
		bmp.ShowBitmap();
		for (vector<Card>::iterator it = cards.begin(); it != cards.end(); it++) {
			it->SetXY(it-cards.begin());
			it->OnShow();
		}
		// 顯示太陽數量
		if (GetMoney() == 0) {
			sun[0][0].SetTopLeft(100, 10);
			sun[0][0].ShowBitmap();
		}
		else if (GetMoney() > 0 && GetMoney() < 100) {
			for (int i = 0, num = GetMoney(); i < 2; i++, num /= 10) {
				sun[i][num % 10].SetTopLeft(100 - 13 * i,8);
				sun[i][num % 10].ShowBitmap();
			}
		}
		else if (GetMoney() >= 100 && GetMoney() < 1000) {
			for (int i = 0, num = GetMoney(); i < 3; i++, num /= 10) {
				sun[i][num % 10].SetTopLeft(100 - 13 * i,8);
				sun[i][num % 10].ShowBitmap();
			}
		}
		else {
			for (int i = 0, num = GetMoney(); i < 4; i++, num /= 10) {
				sun[i][num % 10].SetTopLeft(100 - 13 * i,8);
				sun[i][num % 10].ShowBitmap();
			}
		}
	}
}