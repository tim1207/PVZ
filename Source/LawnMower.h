#pragma once
#pragma once
namespace game_framework {
	class LawnMower {
	public:
		LawnMower();
		void SetY(int);       //設定除草機的位置
		int GetX();           //取得除草機的位置
		void OnMove();        //處理除草機的移動
		void OnShow();        //顯示除草機
		void LoadBitmap();    //讀取除草機的圖片
		void StartMove();     //讓除草機開始移動
		void Reset();         //讓除草機回復初始狀態
	private:
		int x, y;
		bool move;            //儲存除草機目前的狀態
		CMovingBitmap	bmp;
	};
}