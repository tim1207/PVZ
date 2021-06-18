#include "maps.h"
#include "Plants.h"
#include "Sun.h"
#include "zombies.h"
#include "Seed.h"
#include "Pea.h"
#include "mouse.h"
#include "Shovel.h"
#include "LawnCleaner.h"
#include <vector>
#include <memory>
// #include "Selector.h"

namespace game_framework {
	
	/////////////////////////////////////////////////////////////////////////////
	// Constants
	/////////////////////////////////////////////////////////////////////////////

	enum AUDIO_ID {				// 定義各種音效的編號
		AUDIO_AWOOGA,
		AUDIO_CHERRY_BOMB,
		AUDIO_CHOMP_1,
		AUDIO_CHOMP_2,
		AUDIO_CHOMP_3,
		AUDIO_EVIL_LAUGH,
		AUDIO_FINALWAVE,
		AUDIO_GROAN_1,
		AUDIO_GROAN_2,
		AUDIO_GROAN_3,
		AUDIO_GROAN_4,
		AUDIO_GROAN_5,
		AUDIO_GROAN_6,
		AUDIO_LAWN_MOWER,
		AUDIO_LOSE_MUSIC,
		AUDIO_MAIN_MUSIC,
		AUDIO_MENU,
		AUDIO_PLANT,
		AUDIO_COLLECT_SUN,
		AUDIO_CHOOSE_CARD,
		AUDIO_HIT_BUCKET_1,
		AUDIO_HIT_BUCKET_2,
		AUDIO_SHOVEL,
		AUDIO_SPLAT_1,
		AUDIO_SPLAT_2,
		AUDIO_SPLAT_3,
		AUDIO_SHOOT,
		AUDIO_WIN_MUSIC
	};


	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲開頭畫面物件
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateInit : public CGameState {
	public:
		CGameStateInit(CGame *g);
		void OnInit();  								                // 遊戲的初值及圖形設定
		void OnBeginState();							             	// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				        		// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  				// 處理滑鼠的動作
		//TODO:
		void OnMouseMove(UINT nFlags, CPoint point);	  				// 處理滑鼠的動作
		void LoadAudio();								                // 讀取所需的音效檔
		

	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap   logo;								// 冒險模式畫面
		CMovingBitmap	adventure_block;				// 冒險模式
		CMovingBitmap	adventure_block2;
		//CMovingBitmap   loading_picture;				// 冒險模式
		
		// TODO:
		// Selector menu;
		 bool conditionA;								// 檢查游標是否有碰到開始遊戲的按鈕
		 bool conditionB;								// 檢查游標是否有碰到開始遊戲的按鈕
		 bool play_Audio;								// 儲存是否已經開始撥放背景音樂的flag
		 bool load_Audio;								// 儲存是否已經讀取音效檔的flag
		// CMovingBitmap	help;							// help的圖檔
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////


	typedef shared_ptr<Zombies> ZombiesPtr;

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
		void LoadAudio();							// 讀取所需的音效檔
		void GameOver();
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		// finish
		CMovingBitmap background[11];		// 背景圖
		CMovingBitmap zombiesone[5];	// 殭屍 右圖
		CMovingBitmap sunback;
		CMovingBitmap menu;
		CMovingBitmap run_menu;
		CMovingBitmap run_con[2];		//繼續
		CMovingBitmap run_return[2];  // 回選單
		//CMovingBitmap   loading_picture;
		// TODO:
		Seed		      	seed;					             	// 視窗上方管理卡片的物件
		Mouse		    	mouse;						            	// 用來顯示目前選取的東西
		Shovel		    	shovel;						            	// 鏟子
		LawnCleaner	     	LawnCleaner[5];			         	  		// 除草機
		std::vector< shared_ptr<Zombies> >	monster;			    	// 儲存所有殭屍的vector

		Plants PlantClass[5][9] ;
		vector<Pea>		  	peas;						              	// 儲存所有豆子的vector
		vector<Sun>	  		suns;						              	// 儲存所有太陽的vector
		bool		      	selected;						            // 判斷目前是否有選取東西
		int			      	ChoosedCard;					          	// 目前選取的卡片
		int			      	ChoosedPlant;					          	// 目前選取的植物
		int			      	SunCounter;						          	// 從空中掉落太陽的計時器
		int			      	PlantManager[5][9] = { 0 };	  				// 儲存場上植物的位置
		int flow;
		int			      	ZombieCounter;				        		// 產生殭屍的計時器
		int			      	wave;						                // 目前的波數
		bool		      	awooga;					                // 第一批殭屍出現時撥放音樂的flag
		bool 				myrunning;
		bool 				show_menu;
		int show_back;
		int show_con;
	};

	/////////////////////////////////////////////////////////////////////////////
	// 這個class為遊戲的結束狀態(Game Over)
	// 每個Member function的Implementation都要弄懂
	/////////////////////////////////////////////////////////////////////////////

	class CGameStateOver : public CGameState {
	public:
		CGameStateOver(CGame *g);

		void OnBeginState();						// 設定每次重玩所需的變數
		void OnInit();
		// TODO:
		void LoadBitmap();
		void LoadAudio();							// 讀取所需的音效檔
		void OnKeyDown(UINT, UINT, UINT);  // 處理滑鼠的動作
	protected:
		void OnMove();								// 移動遊戲元素
		void OnShow();								// 顯示這個狀態的遊戲畫面
	private:
		int counter;	                    		// 倒數之計數器
		CMovingBitmap ZombiesWon;					// 遊戲失敗的畫面
		CMovingBitmap ZombieLose;					// 遊戲勝利的畫面
		CMovingBitmap FinalWin;					// 最後遊戲勝利的畫面
	};
}