#pragma once
#pragma once
namespace game_framework {
	class LawnCleaner {
	public:
		LawnCleaner();
		void SetY(int);       //�]�w���������m
		int GetX();           //���o���������m
		void OnMove();        //�B�z�����������
		void OnShow();        //��ܰ����
		void LoadBitmap();    //Ū����������Ϥ�
		void StartMove();     //��������}�l����
		void Reset();         //��������^�_��l���A
	private:
		int x, y;
		bool move;            //�x�s������ثe�����A
		CMovingBitmap	bmp;
	};
}