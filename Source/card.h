#pragma once
namespace game_framework {
	class Card {
	public:
		Card();
		Card(int);
		void OnMove();            //處理卡片的動作
		void OnShow();            //顯示卡片
		void LoadBitmap();        //讀取所需的圖檔
		void LoadPlant();         //讀取植物的圖片
		void LoadPrice();         //讀取價錢的圖片
		void SetXY(int);          //設定卡片的位置
		int GetPrice();
		int GetWidth();
		int GetHeight();
		int GetX();
		int GetY();
		int GetID();
		void SetAvailible(bool);  //設定卡片是否可被選取
		bool isAvailible();       //回傳卡片是否可被選取
		void DelayCounter(); 
		void ResetCounter();
		bool CounterFinished();
		bool counting;
		void Reset();             //重設卡片的初始狀態
	private:
		int x, y;
		double y2;                //卡片等待時間黑幕的位置
		int ID;                   //卡片代表的植物種類
		int price;                //價錢
		int delay;                //等待所需時間
		int counter;              //計時器
		bool availible;
		CMovingBitmap	bmp;
		CMovingBitmap	bmp2;
		CMovingBitmap	plant;
		CMovingBitmap	number[3][10]; // price picture
	};
}