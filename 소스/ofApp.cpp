#include "ofApp.h"
// 20161255 �����
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("20161255 Final Project: Sorting Game");
	ofSetFrameRate(15);
	ofBackground(255, 255, 255); // �� ����
	srand(time(NULL)); // ���� ����
	gameover = false; gamestart = false; gamebegun = false; // ���� ���۵� ���߰�, ���� ������ �ƴϵ��� �ʱ�ȭ
	life = 3; // �������� 3���� �ʱ�ȭ
	correct = -1; // ó������ ����/Ʋ���� �Ǵ����� ����
	record = 0; // ��� �ʱ�ȭ
	height = ofGetHeight(); // �������� ����
	width = ofGetWidth(); // �������� �ʺ�
	centerx = width * 0.5f; centery = height * 0.5f; // �������� ������� ��ǥ
	int fontsize = 20; // ��Ʈ ũ��
	font.load("verdana.ttf", fontsize); // ��Ʈ �޾ƿ���
	ReadBestRecord(); // �ְ��� �б�
	printHowToPlay(); // ���۹� �� �ְ��� ���
	setTileColor(); // Ÿ�� ���� ���ϱ�
	InitBlockColor(); // �ʱ� ��� ���� ���ϱ�
}

//--------------------------------------------------------------
void ofApp::update(){
	if (life <= 0) { gameover = true; } // �������� ��� �����Ǹ� ���ӿ���
	if (gamebegun) { // ���� ���� ��
		gamebegun = false; // update �Լ����� �ٽ� ������ �ݺ����� �ʵ��� false�� �缳��
		ofResetElapsedTimeCounter(); // Ÿ�̸� �ʱ�ȭ
	}
	if (correct == 1) { // ����� �ùٸ��� ����
		correct = -1; // ���� ��
		if (gamestart && !gameover && ofGetElapsedTimef() >= 3.0f) { // ������ ���۵� �����̰�, ������ ���� 3�� ī��Ʈ �ٿ� ������ ���, ���� ȹ�� �� ��� ��迭
			ChangeBlockColor(); // ��� ��迭
			record++; // ���� 1 ȹ��
		}
	}
	else if (!correct) { // ����� �ùٸ��� ������ ����
		correct = -1; // ���� ��
		if (gamestart && !gameover && ofGetElapsedTimef() >= 3.0f) life--; // ������ ���۵� �����̰�, ������ ���� 3�� ī��Ʈ �ٿ� ������ ���, ������ 1 �谨
	}
	if (gamestart && ofGetElapsedTimef() > 33.0f) gameover = true; // ������ ���۵ǰ���� ī��Ʈ�ٿ� 3��, ���ӽð� 30�ʷ� �� 33�ʰ� ������ ���ӿ���
}

//--------------------------------------------------------------
void ofApp::draw(){
	int i;
	if (!gamestart) { // ���� ���� ��
		ofSetColor(255, 0, 0); 
		font.drawString("SORT", centerx - 130.0f, centery - 200.0f); // ������
		ofSetColor(0, 255, 0);
		font.drawString("ING", centerx - 50.0f, centery - 200.0f); // �ʷϻ�
		ofSetColor(0, 0, 255);
		font.drawString("GAME", centerx + 20.0f, centery - 200.0f); // �Ķ���
		ofSetColor(255, 0, 128);
		font.drawString("Check the console for 'How to Play'", centerx - 240.0f, centery + 40.0f); // ��ȫ��
		ofSetColor(0, 0, 0);
		font.drawString("Press 's' to start", centerx - 120.0f, centery + 250.0f); // ������
		font.drawString("Made by 20161255 Chang Won Tae", centerx + 20.0f, height - 20.0f); // ������
	}
	else if (!gameover) { // ���� ���� ��, ���� ȭ��
		DrawTile(); // �� ���� Ÿ�� �׸���
		DrawLife(); // ������ �׸���
		DrawTime(); // �ð� �׸���
		if (ofGetElapsedTimef() >= 3.0f) DrawBlock(); // ���ӽ��� �� 3�� ī��Ʈ�ٿ��� ������ ��� ǥ��
	}
	else { // ���� ���� ��
		ofSetColor(255, 0, 0);
		font.drawString("GAME OVER", centerx-80.0f, centery); // ������
		ofSetColor(0, 0, 0);
		font.drawString("Press 'x' to exit...", centerx - 120.0f, height - 40.0f); // ������
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's' || key == 'S') { // ���� ����
		if (!gamestart) gamebegun = true; // �ʱ� ���� ��
		gamestart = true;
	}

	if (key == OF_KEY_LEFT) { // �������� ������: ���� Ÿ�ϰ� ���� ����� ���� ��ġ�ϸ� correct, �ƴϸ� incorrect
		if (tile[0] == block[0]) correct = 1; 
		else correct = 0;
	}
	
	if (key == OF_KEY_UP) { // �������� ������: ���� Ÿ�ϰ� ���� ����� ���� ��ġ�ϸ� correct, �ƴϸ� incorrect
		if (tile[1] == block[0]) correct = 1;
		else correct = 0;
	}

	if (key == OF_KEY_RIGHT) { // ���������� ������: ������ Ÿ�ϰ� ���� ����� ���� ��ġ�ϸ� correct, �ƴϸ� incorrect
		if (tile[2] == block[0]) correct = 1;
		else correct = 0;
	}

	if (key == 'x' || key == 'X') { // ���� ����
		printf("----------------------------------------------------------\n");
		printf("����� ����� %d���Դϴ�.\n", record); // ��� ǥ��
		if (record > Bestrecord) { // �ְ� ��Ϻ��� ���� ���
			WriteBestRecord(); // �ְ� ��� ����
			printf("************NEW RECORD!!************\n");
			printf("�ְ� ��� �޼��Դϴ�!! ���ϵ帳�ϴ�!\n");
		}
		printf("������ ����!\n");
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

void ofApp::printHowToPlay() { // ���۹� �� �ְ� ��� ���
	printf("You need to send the block to the tile with same color.\n");
	printf("Press up arrow key to send to the top.\n");
	printf("Press left arrow key to send to the left.\n");
	printf("Press right arrow key to send to the right.\n");
	printf("\nYou have 30 seconds to play.\n");
	printf("Good Luck!\n\n");
	printf("****BEST SCORE: %d ****\n\n", Bestrecord);
	printf("----------------------------------------------------------\n");
	printf("�� ����� ���� ���� Ÿ�Ϸ� �����ʽÿ�.\n");
	printf("�� ����Ű�� ���� ���� Ÿ�Ϸ� �����ϴ�.\n");
	printf("���� ����Ű�� ���� ���� Ÿ�Ϸ� �����ϴ�.\n");
	printf("������ ����Ű�� ���� ������ Ÿ�Ϸ� �����ϴ�.\n");
	printf("\n���� �ð��� 30���Դϴ�.\n");
	printf("����� ���ϴ�!\n\n");
	printf("****�ְ� ���: %d ****\n", Bestrecord);
}


void ofApp::setTileColor() { // Ÿ�� �� ���ϱ�
	int i, random[3];
	random[0] = rand() % 3; // ���� Ÿ�Ͽ� ���� ����
	do {
		random[1] = rand() % 3;
	} while (random[0] == random[1]); // ���� Ÿ�Ͽ� ���� ����, �� ���� Ÿ�ϰ� ������ �ٽ� ���� ����
	for (i = 0; i < 3; i++) { // ������ Ÿ�Ͽ� ���� ����. ���� Ÿ�ϰ� ���� Ÿ���� ���� �����ϰ� ���� ���� ����
		if (random[0] != i && random[1] != i)
			random[2] = i;
	}
	for (i = 0; i < 3; i++) { // �� ������ ���� ���� ���� : 0 - ����, 1 - �ʷ�, 2 - �Ķ�
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

void ofApp::DrawTile() { // Ÿ�� �׸���
	ofNoFill();
	ofSetColor(255, 128, 255); // ���: ��ȫ��
	ofDrawRectangle(centerx - 40.0f, centery - 40.0f, 80.0f, 80.0f);
	ofDrawRectangle(centerx - 50.0f, centery - 50.0f, 100.0f, 100.0f);
	// Ÿ�� ���� ���� �� ����
	switch (tile[0]) { // ���� Ÿ��
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

	switch (tile[1]) { // ���� Ÿ��
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

	switch (tile[2]) { // ������ Ÿ��
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

void ofApp::DrawLife() { // �������� ��Ÿ���� �κ��� �׸��� �Լ�
	ofFill();
	ofSetColor(255, 0, 128); // ��ȫ��
	font.drawString("LIFE", width * 0.8f, height * 0.1f);
	if (life >= 1) // ������ �� ĭ �� ù° ĭ: 1��, 2��, 3���϶� ������
		ofDrawRectangle(width * 0.87f, height * 0.07f, width * 0.02f, 30.0f);
	if (life >= 2) // ������ �� ĭ �� ��° ĭ: 2��, 3���϶� ������
		ofDrawRectangle(width * 0.895f, height * 0.07f, width * 0.02f, 30.0f);
	if (life >= 3) // ������ �� ĭ �� ��° ĭ: 3���϶��� ������
		ofDrawRectangle(width * 0.92f, height * 0.07f, width * 0.02f, 30.0f);
}

void ofApp::DrawTime() { // �ð��� ����ȭ�Ͽ� �׷��ִ� �Լ�
	ofFill();
	if (ofGetElapsedTimef() < 3.0f) { // ī��Ʈ�ٿ�
		ofSetColor(0, 0, 160); // ����
		font.drawString("Get Ready!", centerx - 70.0f, centery - 100.0f);
		if (ofGetElapsedTimef() < 1.0f) font.drawString("3", centerx - 10.0f, centery - 60.0f); // ���ۺ��� 1��: ī��Ʈ�ٿ� 3��
		else if (ofGetElapsedTimef() < 2.0f) font.drawString("2", centerx - 10.0f, centery - 60.0f); // ���ۺ��� 2��: ī��Ʈ�ٿ� 2��
		else if (ofGetElapsedTimef() < 3.0f) font.drawString("1", centerx - 10.0f, centery - 60.0f); // ���ۺ��� 3��: ī��Ʈ�ٿ� 1��
	}
	ofSetColor(128, 0, 255); // �����
	font.drawString("TIME", 20.0f, 20.0f);
	// �ð��� ��Ÿ���� ĭ�� �� ĭ�� 5�ʸ� �ǹ���(�ʱ� ī��Ʈ�ٿ� ����)
	if (ofGetElapsedTimef() < 33.0f) ofDrawRectangle(20.0f, 40.0f, 20.0f, 50.0f); // �ð� 6ĭ �� ù°ĭ: ���� ������ ������
	if (ofGetElapsedTimef() < 28.0f) ofDrawRectangle(45.0f, 40.0f, 20.0f, 50.0f); // �ð� 6ĭ �� ��°ĭ: ���� 5�� ������ ������
	if (ofGetElapsedTimef() < 23.0f) ofDrawRectangle(70.0f, 40.0f, 20.0f, 50.0f); // �ð� 6ĭ �� ��°ĭ: ���� 10�� ������ ������
	if (ofGetElapsedTimef() < 18.0f) ofDrawRectangle(95.0f, 40.0f, 20.0f, 50.0f); // �ð� 6ĭ �� ��°ĭ: ���� 15�� ������ ������
	if (ofGetElapsedTimef() < 13.0f) ofDrawRectangle(120.0f, 40.0f, 20.0f, 50.0f); // �ð� 6ĭ �� �ټ�°ĭ: ���� 20�� ������ ������
	if (ofGetElapsedTimef() < 8.0f) ofDrawRectangle(145.0f, 40.0f, 20.0f, 50.0f); // �ð� 6ĭ �� ����°ĭ: ���� 25�� ������ ������

	if (ofGetElapsedTimef() > 32.0f) font.drawString("1", 70.0f, 75.0f); // ������ 1�� ī��Ʈ
	else if (ofGetElapsedTimef() > 31.0f) font.drawString("2", 70.0f, 75.0f); // ������ 2�� ī��Ʈ
	else if (ofGetElapsedTimef() > 30.0f) font.drawString("3", 70.0f, 75.0f); // ������ 3�� ī��Ʈ
	else if (ofGetElapsedTimef() > 29.0f) font.drawString("4", 70.0f, 75.0f); // ������ 4�� ī��Ʈ
	else if (ofGetElapsedTimef() > 28.0f) font.drawString("5", 70.0f, 75.0f); // ������ 5�� ī��Ʈ
}

void ofApp::InitBlockColor() { // ��� �� �ʱ� �����ϴ� �Լ�(���� ���ĵ� ��)
	int i, random;
	for (i = 0; i < 4; i++) {
		random = rand() % 3; // ���� ����: 0-����, 1-�ʷ�, 2-�Ķ�
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

void ofApp::ChangeBlockColor() { // ����� �ùٸ��� ���� ��� ��� �մ��� �� 4��° ��� ����
	int random;
	block[0] = block[1]; // 2~4��° ����� 1~3��° ������� �մ���
	block[1] = block[2];
	block[2] = block[3];
	random = rand() % 3; // ���� ����: 0-����, 1-�ʷ�, 2-�Ķ� -> 4��° ����� ������ ����
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

void ofApp::DrawBlock() { // �� ����� ȭ�鿡 �׸��� �Լ�
	int i;
	ofFill();
	for (i = 0; i < 4; i++) { // �� 4���� ��� �׸���
		switch (block[i]) { // �� ����� ���� ���� �� ����
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
		ofDrawRectangle(centerx - 30.0f, centery - 30.0f + (float)i * 90.0f, 60.0f, 60.0f); // �� ����� �׸���, ������ �Ʒ� ������� �׸�
	}
}

void ofApp::ReadBestRecord() { // �ְ��� �о���� �Լ�
	FILE* file = fopen("BestRecord.txt", "r"); // bin ������ �ִ� "BestRecord.txt" �о��
	if (file == NULL) { // error handling
		printf("Error: BestRecord file is not found\n");
		ofExit();
	}
	fscanf(file, "%d", &Bestrecord); // �ؽ�Ʈ ���Ͽ� �ִ� �ְ��� �о�� Ŭ���� ���� Bestrecord�� ����
	fclose(file);
}

void ofApp::WriteBestRecord() { // �ְ��� �����ϴ� �Լ�
	FILE* file = fopen("BestRecord.txt", "w"); // bin ������ "BestRecord.txt" ����
	if (file == NULL) { // error handling
		printf("Error: BestRecord file is not found\n");
		ofExit();
	}
	fprintf(file, "%d", record); // record�� ���Ͽ� ����
	fclose(file);
}