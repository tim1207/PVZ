#pragma once
//class CMovingBitmap;
namespace game_framework {
	class Mouse {
	public:
		Mouse();              
		void LoadBitmap();     
		void OnMove();         
		void SetWhich(int);    
		void OnShow();         
		void SetXY(int, int); 
	private:
		int x, y;
		int which;            
		CMovingBitmap	Sunflower;
		CMovingBitmap	peashooter;
		CMovingBitmap	Wallnut;
		CMovingBitmap	squash;
		CMovingBitmap	cherrybomb;
		CMovingBitmap	snowpea;
		CMovingBitmap	repeater;
		CMovingBitmap	shovel;
	};
}