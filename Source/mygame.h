#include "maps.h"
#include "Plants.h"
#include "Sun.h"
#include "zombies.h"
#include "Seed.h"
#include "Pea.h"
#include "cursor.h"
#include "Shovel.h"
// #include "LawnMower.h"
// #include <vector>
// #include "Selector.h"

namespace game_framework {
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_DING,				// 0
		AUDIO_LAKE,				// 1
		AUDIO_NTUT				// 2
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								                // 遊戲的初值及圖形設定
		void OnBeginState();							             	 // 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				        		// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  				// 處理滑鼠的動作
		//TODO:
		void OnMouseMove(UINT nFlags, CPoint point);	  				// 處理滑鼠的動作
		void LoadAudio();								                // 讀取所需的音效檔
		//

	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap logo;								// 冒險模式畫面
		CMovingBitmap	adventure_block;				// 冒險模式 
		// TODO:
		// Selector menu;
		// bool conditionA;								// 檢查游標是否有碰到開始遊戲的按鈕
		// bool conditionB;								// 檢查游標是否有碰到開始遊戲的按鈕
		// bool play_Audio;								// 儲存是否已經開始撥放背景音樂的flag
		// bool load_Audio;								// 儲存是否已經讀取音效檔的flag
		// CMovingBitmap	help;							// help的圖檔
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////




	class CGameStateRun : public CGameState {
	public:
		CGameStateRun(CGame *g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作 
		void OnRButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnRButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void GameOver();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		// finish
		CMovingBitmap	background;	// 背景圖
		CMovingBitmap zombiesone[5];	// 殭屍
		CMovingBitmap peacard;	// PEA
		CMovingBitmap sunflowercard;	// sunflower
		CMovingBitmap wallnutcard;	// wallnut
		CMovingBitmap sunback;
		// TODO:
		// Maps			        map;					            	  	// 背景圖
		Seed		      	    seed;					             	  	// 視窗上方管理卡片的物件
		Cursor		    	cursor;						            	// 用來顯示目前選取的東西
		Shovel		    	shovel;						            	// 鏟子
		// LawnMower	     	LawnMower[5];			         	  		// 除草機
		vector<Zombies>		monster;			    	      			// 儲存所有殭屍的vector
		//vector<Plants>		plants;					          	  		// 儲存所有植物的vector
		
		Plants testp[5][9] ;
		vector<Pea>		  	peas;						              	// 儲存所有豆子的vector
		vector<Sun>	  		suns;						              	// 儲存所有太陽的vector
		bool		      		selected;						            // 判斷目前是否有選取東西
		int			      	ChoosedCard;					          	// 目前選取的卡片
		int			      	ChoosedPlant;					          	// 目前選取的植物
		int			      	SunCounter;						          	// 從空中掉落太陽的計時器
		 int			      	PlantManager[5][9] = { 0 };	  				// 儲存場上植物的位置
		 int flow;//
		// int			      	ZombieCounter;				        		// 產生殭屍的計時器
		// int			      	wave;						                // 目前的波數
		// void		      		GameOver();			        	      		// 讓遊戲進入CGameStateOver
		// bool		      		isGameOver;				              		// 檢查遊戲使否結束
		// bool		      		awooga;					                	// 第一批殭屍出現時撥放音樂的flag
		// CMovingBitmap	  	FinalWave;			    		    	  	// 最後一波殭屍的預告圖
		// CMovingBitmap	  	Wave;					        	    	// 顯示wave
		// CMovingBitmap	  	numbers[10];	    			    	 	// 顯示數字
		// CMovingBitmap	  	slash;					      	    	  	// 顯示斜線
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);

		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();
		// TODO:
		void LoadBitmap();
		void LoadAudio();							  	// 讀取所需的音效檔
	protected:
		void OnMove();								  	// 移動遊戲元素
		void OnShow();								  	// 顯示這個狀態的遊戲畫面
	private:
		int counter;	                    // 倒數之計數器
		CMovingBitmap ZombiesWon;					// 遊戲失敗的畫面
		CMovingBitmap ZombieNote;					// 遊戲勝利的畫面
	};
}