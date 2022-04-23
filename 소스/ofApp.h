#pragma once

#include "ofMain.h"
#include <ctime>
#include <windows.h>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		void ReadBestRecord(); // �ְ� ��� �о���� �Լ�
		void WriteBestRecord(); // �ְ� ��� ����ϴ� �Լ�
		void printHowToPlay(); // ���۹� �� �ְ����� ����ϴ� �Լ�
		void setTileColor(); // ȭ�鿡 ���� �� Ÿ��(���� �� Ʋ)�� ������ ���ϴ� �Լ�
		void DrawTile(); // ��� Ÿ���� ������ �� ���� Ÿ���� ȭ�鿡 �׸��� �Լ�
		void DrawLife(); // �������� ȭ�鿡 �׸��� �Լ�
		void DrawTime(); // �ð��� ȭ�鿡 �׸��� �Լ�
		void InitBlockColor(); // ����� ������ �ʱ�ȭ�ϴ� �Լ�
		void ChangeBlockColor(); // ����� �ùٸ��� sort�� ���, ����� �ϳ��� ����� �Լ�
		void DrawBlock(); // ��� 4���� �׸��� �Լ�
		ofTrueTypeFont font; // ��Ʈ

		float height, width, centerx, centery; // �������� �ʺ�, ����, �ʺ��� ����, ������ ����
		int life; // ������: 3���� ����
		int record; // �̹� �õ����� sort �����ϴ� Ÿ���� ���� ���
		int Bestrecord = 0; // ��ϵǾ� �ִ� �ְ���
		enum colors{Red, Green, Blue}; // �������� ���� �� ����� enumeration type ����
		enum colors tile[3]; // Ÿ�� 3��
		enum colors block[4]; // ��� 4��

		bool gamestart, gameover, gamebegun; // ���� ����, ���� ����, �׸��� ������ �̹� ���۵�(gamebegun: elapsed time�� �ʱ�ȭ�ϱ� ���� ����)
		int correct; // -1: �Ǵ����� ���� 0: Ʋ�� 1: ����
		
};
