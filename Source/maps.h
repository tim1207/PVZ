#pragma once

namespace game_framework {
	class Maps {
	public:
		Maps();
		void LoadBitmap();		// 載入圖形
		void LoadBitmap(std::string path);		// 載入圖形
		void OnShow(int, int);			  // 將圖形貼到畫面
	private:
		int x, y;				      // 圖形座標
		CMovingBitmap bmp;
	};
}
