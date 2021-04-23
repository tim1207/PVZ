#pragma once
namespace game_framework {
	class Pea {
	public:
		Pea();
		Pea(int,int,int);					  // 豆子的初始化
		void LoadBitmap();					// 讀取豆子的相關圖片
		void OnShow();
		void OnMove();
		int GetRow();						    // 回傳豆子所在的排數
		int GetX();						    	// 回傳豆子目前的X位置
		void SetHitZombie(bool);		// 設定豆子目前是否擊中殭屍
		bool isHitZombie();					// 回傳豆子的狀態
		bool isFinished();					// 回傳豆子的動畫是否已經結束
		int MyType();					    	// 回傳豆子的型態
	private:
		int x, y;
		int row;
		int type;						      	// 豆子的型態(0是普通豆子，1是冷凍豆子)
		bool finished;				  		// 豆子的動畫是否已經顯示結束
		bool HitZombie;				  		// 豆子是否有擊中殭屍
	};
}