#include "ofApp.h"
// 20161255 장원태
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("20161255 Final Project: Sorting Game");
	ofSetFrameRate(15);
	ofBackground(255, 255, 255); // 흰 바탕
	srand(time(NULL)); // 난수 생성
	gameover = false; gamestart = false; gamebegun = false; // 게임 시작도 안했고, 게임 오버도 아니도록 초기화
	life = 3; // 라이프는 3개로 초기화
	correct = -1; // 처음에는 맞음/틀림을 판단하지 않음
	record = 0; // 기록 초기화
	height = ofGetHeight(); // 윈도우의 높이
	width = ofGetWidth(); // 윈도우의 너비
	centerx = width * 0.5f; centery = height * 0.5f; // 윈도우의 정가운데의 좌표
	int fontsize = 20; // 폰트 크기
	font.load("verdana.ttf", fontsize); // 폰트 받아오기
	ReadBestRecord(); // 최고기록 읽기
	printHowToPlay(); // 조작법 및 최고기록 출력
	setTileColor(); // 타일 색깔 정하기
	InitBlockColor(); // 초기 블록 색깔 정하기
}

//--------------------------------------------------------------
void ofApp::update(){
	if (life <= 0) { gameover = true; } // 라이프가 모두 소진되면 게임오버
	if (gamebegun) { // 게임 시작 시
		gamebegun = false; // update 함수에서 다시 과정을 반복하지 않도록 false로 재설정
		ofResetElapsedTimeCounter(); // 타이머 초기화
	}
	if (correct == 1) { // 블록을 올바르게 보냄
		correct = -1; // 판정 끝
		if (gamestart && !gameover && ofGetElapsedTimef() >= 3.0f) { // 게임이 시작된 상태이고, 시작할 때의 3초 카운트 다운 이후인 경우, 점수 획득 및 블록 재배열
			ChangeBlockColor(); // 블록 재배열
			record++; // 점수 1 획득
		}
	}
	else if (!correct) { // 블록을 올바르게 보내지 못함
		correct = -1; // 판정 끝
		if (gamestart && !gameover && ofGetElapsedTimef() >= 3.0f) life--; // 게임이 시작된 상태이고, 시작할 때의 3초 카운트 다운 이후인 경우, 라이프 1 삭감
	}
	if (gamestart && ofGetElapsedTimef() > 33.0f) gameover = true; // 게임이 시작되고부터 카운트다운 3초, 게임시간 30초로 총 33초가 지나면 게임오버
}

//--------------------------------------------------------------
void ofApp::draw(){
	int i;
	if (!gamestart) { // 게임 시작 전
		ofSetColor(255, 0, 0); 
		font.drawString("SORT", centerx - 130.0f, centery - 200.0f); // 빨강색
		ofSetColor(0, 255, 0);
		font.drawString("ING", centerx - 50.0f, centery - 200.0f); // 초록색
		ofSetColor(0, 0, 255);
		font.drawString("GAME", centerx + 20.0f, centery - 200.0f); // 파랑색
		ofSetColor(255, 0, 128);
		font.drawString("Check the console for 'How to Play'", centerx - 240.0f, centery + 40.0f); // 분홍색
		ofSetColor(0, 0, 0);
		font.drawString("Press 's' to start", centerx - 120.0f, centery + 250.0f); // 검은색
		font.drawString("Made by 20161255 Chang Won Tae", centerx + 20.0f, height - 20.0f); // 검은색
	}
	else if (!gameover) { // 게임 시작 후, 게임 화면
		DrawTile(); // 네 개의 타일 그리기
		DrawLife(); // 라이프 그리기
		DrawTime(); // 시간 그리기
		if (ofGetElapsedTimef() >= 3.0f) DrawBlock(); // 게임시작 전 3초 카운트다운이 끝나면 블록 표시
	}
	else { // 게임 오버 시
		ofSetColor(255, 0, 0);
		font.drawString("GAME OVER", centerx-80.0f, centery); // 빨강색
		ofSetColor(0, 0, 0);
		font.drawString("Press 'x' to exit...", centerx - 120.0f, height - 40.0f); // 검은색
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's' || key == 'S') { // 게임 시작
		if (!gamestart) gamebegun = true; // 초기 시작 시
		gamestart = true;
	}

	if (key == OF_KEY_LEFT) { // 왼쪽으로 보내기: 왼쪽 타일과 현재 블록의 색이 일치하면 correct, 아니면 incorrect
		if (tile[0] == block[0]) correct = 1; 
		else correct = 0;
	}
	
	if (key == OF_KEY_UP) { // 위쪽으로 보내기: 위쪽 타일과 현재 블록의 색이 일치하면 correct, 아니면 incorrect
		if (tile[1] == block[0]) correct = 1;
		else correct = 0;
	}

	if (key == OF_KEY_RIGHT) { // 오른쪽으로 보내기: 오른쪽 타일과 현재 블록의 색이 일치하면 correct, 아니면 incorrect
		if (tile[2] == block[0]) correct = 1;
		else correct = 0;
	}

	if (key == 'x' || key == 'X') { // 게임 종료
		printf("----------------------------------------------------------\n");
		printf("당신의 기록은 %d장입니다.\n", record); // 기록 표시
		if (record > Bestrecord) { // 최고 기록보다 높은 경우
			WriteBestRecord(); // 최고 기록 갱신
			printf("************NEW RECORD!!************\n");
			printf("최고 기록 달성입니다!! 축하드립니다!\n");
		}
		printf("다음에 봐요!\n");
		ofExit();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::printHowToPlay() { // 조작법 및 최고 기록 출력
	printf("You need to send the block to the tile with same color.\n");
	printf("Press up arrow key to send to the top.\n");
	printf("Press left arrow key to send to the left.\n");
	printf("Press right arrow key to send to the right.\n");
	printf("\nYou have 30 seconds to play.\n");
	printf("Good Luck!\n\n");
	printf("****BEST SCORE: %d ****\n\n", Bestrecord);
	printf("----------------------------------------------------------\n");
	printf("각 블록을 색이 같은 타일로 보내십시오.\n");
	printf("위 방향키를 눌러 위쪽 타일로 보냅니다.\n");
	printf("왼쪽 방향키를 눌러 왼쪽 타일로 보냅니다.\n");
	printf("오른쪽 방향키를 눌러 오른쪽 타일로 보냅니다.\n");
	printf("\n제한 시간은 30초입니다.\n");
	printf("행운을 빕니다!\n\n");
	printf("****최고 기록: %d ****\n", Bestrecord);
}


void ofApp::setTileColor() { // 타일 색 정하기
	int i, random[3];
	random[0] = rand() % 3; // 왼쪽 타일에 대한 난수
	do {
		random[1] = rand() % 3;
	} while (random[0] == random[1]); // 위쪽 타일에 대한 난수, 단 왼쪽 타일과 같으면 다시 난수 생성
	for (i = 0; i < 3; i++) { // 오른쪽 타일에 대한 난수. 왼쪽 타일과 위쪽 타일의 색을 제외하고 남는 색깔 배정
		if (random[0] != i && random[1] != i)
			random[2] = i;
	}
	for (i = 0; i < 3; i++) { // 각 난수에 대해 색깔 배정 : 0 - 빨강, 1 - 초록, 2 - 파랑
		switch (random[i]) {
		case 0:
			tile[i] = Red;
			break;
		case 1:
			tile[i] = Green;
			break;
		case 2:
			tile[i] = Blue;
			break;
		}
	}
}

void ofApp::DrawTile() { // 타일 그리기
	ofNoFill();
	ofSetColor(255, 128, 255); // 가운데: 분홍색
	ofDrawRectangle(centerx - 40.0f, centery - 40.0f, 80.0f, 80.0f);
	ofDrawRectangle(centerx - 50.0f, centery - 50.0f, 100.0f, 100.0f);
	// 타일 색깔에 따라 색 설정
	switch (tile[0]) { // 왼쪽 타일
	case Red:
		ofSetColor(255, 0, 0);
		break;
	case Green:
		ofSetColor(0, 255, 0);
		break;
	case Blue:
		ofSetColor(0, 0, 255);
		break;
	}
	ofDrawRectangle(200.0f, centery - 40.0f, 80.0f, 80.0f);

	switch (tile[1]) { // 위쪽 타일
	case Red:
		ofSetColor(255, 0, 0);
		break;
	case Green:
		ofSetColor(0, 255, 0);
		break;
	case Blue:
		ofSetColor(0, 0, 255);
		break;
	}
	ofDrawRectangle(centerx - 40.0f, 60.0f, 80.0f, 80.0f);

	switch (tile[2]) { // 오른쪽 타일
	case Red:
		ofSetColor(255, 0, 0);
		break;
	case Green:
		ofSetColor(0, 255, 0);
		break;
	case Blue:
		ofSetColor(0, 0, 255);
		break;
	}
	ofDrawRectangle(width - 280.0f, centery - 40.0f, 80.0f, 80.0f);
}

void ofApp::DrawLife() { // 라이프를 나타내는 부분을 그리는 함수
	ofFill();
	ofSetColor(255, 0, 128); // 분홍색
	font.drawString("LIFE", width * 0.8f, height * 0.1f);
	if (life >= 1) // 라이프 세 칸 중 첫째 칸: 1개, 2개, 3개일때 차있음
		ofDrawRectangle(width * 0.87f, height * 0.07f, width * 0.02f, 30.0f);
	if (life >= 2) // 라이프 세 칸 중 둘째 칸: 2개, 3개일때 차있음
		ofDrawRectangle(width * 0.895f, height * 0.07f, width * 0.02f, 30.0f);
	if (life >= 3) // 라이프 세 칸 중 셋째 칸: 3개일때만 차있음
		ofDrawRectangle(width * 0.92f, height * 0.07f, width * 0.02f, 30.0f);
}

void ofApp::DrawTime() { // 시간을 도식화하여 그려주는 함수
	ofFill();
	if (ofGetElapsedTimef() < 3.0f) { // 카운트다운
		ofSetColor(0, 0, 160); // 남색
		font.drawString("Get Ready!", centerx - 70.0f, centery - 100.0f);
		if (ofGetElapsedTimef() < 1.0f) font.drawString("3", centerx - 10.0f, centery - 60.0f); // 시작부터 1초: 카운트다운 3초
		else if (ofGetElapsedTimef() < 2.0f) font.drawString("2", centerx - 10.0f, centery - 60.0f); // 시작부터 2초: 카운트다운 2초
		else if (ofGetElapsedTimef() < 3.0f) font.drawString("1", centerx - 10.0f, centery - 60.0f); // 시작부터 3초: 카운트다운 1초
	}
	ofSetColor(128, 0, 255); // 보라색
	font.drawString("TIME", 20.0f, 20.0f);
	// 시간을 나타내는 칸의 각 칸은 5초를 의미함(초기 카운트다운 제외)
	if (ofGetElapsedTimef() < 33.0f) ofDrawRectangle(20.0f, 40.0f, 20.0f, 50.0f); // 시간 6칸 중 첫째칸: 끝날 때까지 차있음
	if (ofGetElapsedTimef() < 28.0f) ofDrawRectangle(45.0f, 40.0f, 20.0f, 50.0f); // 시간 6칸 중 둘째칸: 종료 5초 전까지 차있음
	if (ofGetElapsedTimef() < 23.0f) ofDrawRectangle(70.0f, 40.0f, 20.0f, 50.0f); // 시간 6칸 중 셋째칸: 종료 10초 전까지 차있음
	if (ofGetElapsedTimef() < 18.0f) ofDrawRectangle(95.0f, 40.0f, 20.0f, 50.0f); // 시간 6칸 중 넷째칸: 종료 15초 전까지 차있음
	if (ofGetElapsedTimef() < 13.0f) ofDrawRectangle(120.0f, 40.0f, 20.0f, 50.0f); // 시간 6칸 중 다섯째칸: 종료 20초 전까지 차있음
	if (ofGetElapsedTimef() < 8.0f) ofDrawRectangle(145.0f, 40.0f, 20.0f, 50.0f); // 시간 6칸 중 여섯째칸: 종료 25초 전까지 차있음

	if (ofGetElapsedTimef() > 32.0f) font.drawString("1", 70.0f, 75.0f); // 마지막 1초 카운트
	else if (ofGetElapsedTimef() > 31.0f) font.drawString("2", 70.0f, 75.0f); // 마지막 2초 카운트
	else if (ofGetElapsedTimef() > 30.0f) font.drawString("3", 70.0f, 75.0f); // 마지막 3초 카운트
	else if (ofGetElapsedTimef() > 29.0f) font.drawString("4", 70.0f, 75.0f); // 마지막 4초 카운트
	else if (ofGetElapsedTimef() > 28.0f) font.drawString("5", 70.0f, 75.0f); // 마지막 5초 카운트
}

void ofApp::InitBlockColor() { // 블록 색 초기 설정하는 함수(색이 겹쳐도 됨)
	int i, random;
	for (i = 0; i < 4; i++) {
		random = rand() % 3; // 난수 생성: 0-빨강, 1-초록, 2-파랑
		switch (random) {
		case 0:
			block[i] = Red;
			break;
		case 1:
			block[i] = Green;
			break;
		case 2:
			block[i] = Blue;
			break;
		}
	}
}

void ofApp::ChangeBlockColor() { // 블록을 올바르게 맞춘 경우 블록 앞당기기 및 4번째 블록 생성
	int random;
	block[0] = block[1]; // 2~4번째 블록을 1~3번째 블록으로 앞당기기
	block[1] = block[2];
	block[2] = block[3];
	random = rand() % 3; // 난수 생성: 0-빨강, 1-초록, 2-파랑 -> 4번째 블록의 색으로 지정
	switch (random) { 
	case 0:
		block[3] = Red;
		break;
	case 1:
		block[3] = Green;
		break;
	case 2:
		block[3] = Blue;
		break;
	}
}

void ofApp::DrawBlock() { // 네 블록을 화면에 그리는 함수
	int i;
	ofFill();
	for (i = 0; i < 4; i++) { // 각 4개의 블록 그리기
		switch (block[i]) { // 각 블록의 색깔에 따라 색 배정
		case Red:
			ofSetColor(255, 0, 0);
			break;
		case Green:
			ofSetColor(0, 255, 0);
			break;
		case Blue:
			ofSetColor(0, 0, 255);
			break;
		}
		ofDrawRectangle(centerx - 30.0f, centery - 30.0f + (float)i * 90.0f, 60.0f, 60.0f); // 각 블록을 그리되, 위에서 아래 순서대로 그림
	}
}

void ofApp::ReadBestRecord() { // 최고기록 읽어오는 함수
	FILE* file = fopen("BestRecord.txt", "r"); // bin 폴더에 있는 "BestRecord.txt" 읽어옴
	if (file == NULL) { // error handling
		printf("Error: BestRecord file is not found\n");
		ofExit();
	}
	fscanf(file, "%d", &Bestrecord); // 텍스트 파일에 있는 최고기록 읽어와 클래스 변수 Bestrecord에 저장
	fclose(file);
}

void ofApp::WriteBestRecord() { // 최고기록 갱신하는 함수
	FILE* file = fopen("BestRecord.txt", "w"); // bin 폴더에 "BestRecord.txt" 저장
	if (file == NULL) { // error handling
		printf("Error: BestRecord file is not found\n");
		ofExit();
	}
	fprintf(file, "%d", record); // record를 파일에 저장
	fclose(file);
}