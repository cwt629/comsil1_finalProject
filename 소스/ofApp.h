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

		void ReadBestRecord(); // 최고 기록 읽어오는 함수
		void WriteBestRecord(); // 최고 기록 기록하는 함수
		void printHowToPlay(); // 조작법 및 최고기록을 출력하는 함수
		void setTileColor(); // 화면에 나올 세 타일(속이 빈 틀)의 색깔을 정하는 함수
		void DrawTile(); // 가운데 타일을 포함한 네 개의 타일을 화면에 그리는 함수
		void DrawLife(); // 라이프를 화면에 그리는 함수
		void DrawTime(); // 시간을 화면에 그리는 함수
		void InitBlockColor(); // 블록의 색깔을 초기화하는 함수
		void ChangeBlockColor(); // 블록을 올바르게 sort한 경우, 블록을 하나씩 땡기는 함수
		void DrawBlock(); // 블록 4개를 그리는 함수
		ofTrueTypeFont font; // 폰트

		float height, width, centerx, centery; // 윈도우의 너비, 높이, 너비의 절반, 높이의 절반
		int life; // 라이프: 3으로 시작
		int record; // 이번 시도에서 sort 성공하는 타일의 갯수 기록
		int Bestrecord = 0; // 기록되어 있는 최고기록
		enum colors{Red, Green, Blue}; // 가독성을 위해 각 색깔로 enumeration type 선언
		enum colors tile[3]; // 타일 3개
		enum colors block[4]; // 블록 4개

		bool gamestart, gameover, gamebegun; // 게임 시작, 게임 오버, 그리고 게임이 이미 시작됨(gamebegun: elapsed time을 초기화하기 위해 선언)
		int correct; // -1: 판단하지 않음 0: 틀림 1: 맞음
		
};
