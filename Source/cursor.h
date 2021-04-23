#pragma once
//class CMovingBitmap;
namespace game_framework {
	class Cursor {
	public:
		Cursor();              //初始化
		void LoadBitmap();     //讀取圖片
		void OnMove();         //處理移動
		void SetWhich(int);    //設定顯示的圖片
		void OnShow();         //顯示
		void SetXY(int, int);  //設定圖片的位置
	private:
		int x, y;
		int which;             //目前要顯示哪個圖片
		CMovingBitmap	Sunflower;
		CMovingBitmap	peashooter;
		CMovingBitmap	Wallnut;
		//CMovingBitmap	squash;
		//CMovingBitmap	cherrybomb;
		//CMovingBitmap	snowpea;
		//CMovingBitmap	repeater;
		CMovingBitmap	shovel;
	};
}