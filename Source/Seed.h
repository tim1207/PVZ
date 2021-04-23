#pragma once
#include "card.h"
namespace game_framework {
	class Seed {
	public:
		Seed();							          // 初始化
		int GetMoney();							  // 回傳目前擁有的太陽
		void OnMove();							  // 處理動作
		void OnShow();							  // 顯示
		void Load(int, int[]);	  				  // 讀取所需的資源(包含卡片)
		void LoadBitmap();		    			  // 讀取所需的圖檔
		void Buy(int);			      			  // 購買植物
		void GotSun();			      			  // 增加太陽
		int GetCardID(int);		    			  // 回傳特定卡片代表的植物種類
		void ResetCardCounter(int);				  // 重設特定卡片的冷卻時間
		bool isCardAvailible(int);				  // 回傳特定卡片是否可被選取
		void Reset();					  		  // 重設為初始狀態
		void ResetCD();			      			  // 重設所有卡片的冷卻時間(密技用)
	private:
		unsigned int money;			    		  // 目前擁有的太陽
		vector<Card> cards;			    		  // 儲存擁有的卡片
		CMovingBitmap bmp;			
		CMovingBitmap	sun[4][10];
	};
}