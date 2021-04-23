#pragma once
namespace game_framework {
	class Shovel {
	public:
		Shovel();					        // 鏟子的初始化
		void OnShow();				    // 顯示在畫面上
		void LoadBitmap();			  // 讀取所需的圖檔
		bool isChoosed();			    // 檢查鏟子是否被選取
		void SetChoosed(bool);		// 設定鏟子是否已被選取
	private:
		int x, y;					        // 鏟子的座標
		int xb, yb;					      // 放置鏟子的框框的位置
		bool Choosed;				      // 儲存鏟子的狀態
		CMovingBitmap bmp;
		CMovingBitmap back;
	};
}