

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "card.h"
#include "Seed.h"
namespace game_framework
{
	Card::Card() {
	}
	// 卡片的初始化
	Card::Card(int a) {
		ID = a;
		availible = true;							// 設定卡片的等待時間和價錢
		switch (ID) {
		case 1:delay = 33 * 5;	price = 50;	 break; // SunFlower
		case 2:delay = 33 * 5;	price = 100; break; // PeaShoot
		case 3:delay = 33 * 10;	price = 50;	 break; // WallNut
		case 4:delay = 33 * 30;	price = 50;	 break; // Squash
		case 5:delay = 33 * 30;	price = 150; break; //	Cherry boom
		case 6:delay = 33 * 5;	price = 175; break; // Snow
		case 7:delay = 33 * 5;	price = 200; break; // Repeater
		}
		counting = false;
		counter = delay;
	}
	//每次重新開始遊戲的重設卡片初始狀態
	void Card::Reset() {
		availible = true;
		counter = delay;
		counting = false;
	}
	// 讀取卡片所需的所有圖片
	void Card::LoadBitmap() {
		LoadPlant();
		LoadPrice();
	}
	void Card::LoadPrice() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 10; j++) {
				char FILENAME[100];
				sprintf(FILENAME, ".\\BMP_RES\\image\\interface\\%d.bmp", j);
				number[i][j].LoadBitmap(FILENAME, RGB(255, 255, 255));
			}
		}

	}
	void Card::LoadPlant() {
		switch (ID) {
		case 1:	plant.LoadBitmap(".\\BMP_RES\\image\\interface\\menu\\handbook\\Card\\plants\\SunFlower.bmp", RGB(0, 0, 0));   break;
		case 2: plant.LoadBitmap(".\\BMP_RES\\image\\interface\\menu\\handbook\\Card\\plants\\Peashooter.bmp", RGB(0, 0, 0));  break;
		case 3: plant.LoadBitmap(".\\BMP_RES\\image\\interface\\menu\\handbook\\Card\\plants\\WallNut.bmp", RGB(0, 0, 0));	   break;
		case 4: plant.LoadBitmap(".\\BMP_RES\\image\\interface\\menu\\handbook\\Card\\plants\\Squash.bmp", RGB(0, 0, 0));	   break;
		case 5: plant.LoadBitmap(".\\BMP_RES\\image\\interface\\menu\\handbook\\Card\\plants\\CherryBomb.bmp", RGB(0, 0, 0));  break;
		case 6: plant.LoadBitmap(".\\BMP_RES\\image\\interface\\menu\\handbook\\Card\\plants\\SnowPea.bmp", RGB(0, 0, 0));	   break;
		case 7: plant.LoadBitmap(".\\BMP_RES\\image\\interface\\menu\\handbook\\Card\\plants\\Repeater.bmp", RGB(0, 0, 0));    break;
		}
	}
	int Card::GetPrice() {
		return price;
	}
	// int Card::GetWidth() {
	// 	return bmp.Width();
	// }
	// int Card::GetHeight() {
	// 	return bmp.Height();
	// }
	int Card::GetX() {
		return x;
	}
	int Card::GetY() {
		return y;
	}
	int Card::GetID() {
		return ID;
	}
	void Card::SetXY(int num) {
		x = 0;
		y = 50 + num * 60;
	}
	// 設定卡片是可被選取
	void Card::SetAvailible(bool a) {
		availible = a;
	}
	// 回傳卡片是否可被選取
	bool Card::isAvailible() {
		return availible && CounterFinished();
	}
	// 計時卡片的冷卻時間
	void Card::DelayCounter() {
		if (!CounterFinished()) {
			counting = true;
			counter++;
		}
		else if (CounterFinished()) {
			counting = false;
		}
	}
	void Card::ResetCounter() {
		counter = 0;
	}
	bool Card::CounterFinished() {
		return counter == delay;
	}
	void Card::OnMove() {
		DelayCounter();
		y2 = double(y) - 70 * counter / delay;
	}
	void Card::OnShow() {
		int modx = 0, mody = 0;

		if (!CounterFinished()) {
			//bmp.SetTopLeft(x, y);
			//bmp.ShowBitmap(0.5);
			plant.SetTopLeft(x + 8 + modx, y + 12 + mody);
			plant.ShowBitmap(1);
			int y3 = int(y2);
			//bmp2.SetTopLeft(x, y3);
			//bmp2.ShowBitmap();
		}
		else if (!availible) {
			//bmp.SetTopLeft(x, y);
			//bmp.ShowBitmap(0.5);
			plant.SetTopLeft(x + 8 + modx, y + 12 + mody);
			plant.ShowBitmap(1);
			//bmp2.SetTopLeft(x, y);
			//bmp2.ShowBitmap();
		}
		else if (availible) {
			//bmp.SetTopLeft(x, y);
			//bmp.ShowBitmap(0.5);
			plant.SetTopLeft(x + 8 + modx, y + 12 + mody);
			plant.ShowBitmap(1);
		}
		if (GetPrice() > 0 && GetPrice() < 100) {
			for (int i = 0, num = GetPrice(); i < 2; i++, num /= 10) {
				number[i][num % 10].SetTopLeft(x + 90 - i * 10, y + 47);
				number[i][num % 10].ShowBitmap();
			}
		}
		else if (GetPrice() >= 100 && GetPrice() < 1000) {
			for (int i = 0, num = GetPrice(); i < 3; i++, num /= 10) {
				number[i][num % 10].SetTopLeft(x + 95 - i * 11, y + 47);
				number[i][num % 10].ShowBitmap();
			}
		}
	}
}
