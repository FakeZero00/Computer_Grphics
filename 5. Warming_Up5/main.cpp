#include <iostream>
#include <sstream>
#include "Square.h"
#include "Board.h"
using namespace std;

int main() {
	// 세로 30줄, 가로 120글자 크기로 터미널 창 조절
	cout << "\x1b[8;45;200t";

	Board board{};
	
	bool isRunning = true;
	bool isReset = true;
	string command;

	while (isRunning) {
		while (isReset) {
			board.printBoard();

			int x1, y1, x2, y2;
			int x3, y3, x4, y4;
			while (true) {
				cout << "사각형1의 대각선 좌표를 입력하세요: ";
				cin >> x1 >> y1 >> x2 >> y2;

				if (x2 - x1 + 1 > board.getWidth()) {
					cout << "사각형1의 가로 길이가 보드의 가로 길이를 초과합니다. 다시 입력해주세요." << endl;
					continue;
				}
				else if (y2 - y1 + 1 > board.getHeight()) {
					cout << "사각형1의 세로 길이가 보드의 세로 길이를 초과합니다. 다시 입력해주세요." << endl;
					continue;
				}
				else if (x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0) {
					cout << "좌표는 음수일 수 없습니다. 다시 입력해주세요." << endl;
					continue;
				}
				else if (x1 >= board.getWidth() || x2 >= board.getWidth() || y1 >= board.getHeight() || y2 >= board.getHeight()) {
					cout << "좌표가 보드의 범위를 벗어났습니다. 다시 입력해주세요." << endl;
					continue;
				}
				else break;
			}

			Square square1(x1, y1, x2, y2);
			board.addSquare(square1);

			system("cls"); 
			board.printBoard();

			while (true) {
				cout << "사각형2의 대각선 좌표를 입력하세요: ";
				cin >> x3 >> y3 >> x4 >> y4;

				if (x4 - x3 + 1 > board.getWidth()) {
					cout << "사각형2의 가로 길이가 보드의 가로 길이를 초과합니다. 다시 입력해주세요." << endl;
					continue;
				}
				else if (y4 - y3 + 1 > board.getHeight()) {
					cout << "사각형2의 세로 길이가 보드의 세로 길이를 초과합니다. 다시 입력해주세요." << endl;
					continue;
				}
				else if (x3 < 0 || x4 < 0 || y3 < 0 || y4 < 0) {
					cout << "좌표는 음수일 수 없습니다. 다시 입력해주세요." << endl;
					continue;
				}
				else if (x3 >= board.getWidth() || x4 >= board.getWidth() || y3 >= board.getHeight() || y4 >= board.getHeight()) {
					cout << "좌표가 보드의 범위를 벗어났습니다. 다시 입력해주세요." << endl;
					continue;
				}
				else break;
			}
			
			Square square2(x3, y3, x4, y4);
			board.addSquare(square2);
			
			isReset = false;
		}

		system("cls");
		board.printBoard();
		cout << "명령어를 입력해주세요: ";
		cin >> command;

		//사각형1 오른쪽으로 이동
		if (command == "x1") board.moveSquare1(1, 0);
		//사각형1 왼쪽으로 이동
		else if (command == "X1") board.moveSquare1(-1, 0);
		//사각형2 오른쪽으로 이동
		else if (command == "x2") board.moveSquare2(1, 0);
		//사각형2 왼쪽으로 이동
		else if (command == "X2") board.moveSquare2(-1, 0);

		//사각형1 아래로 이동
		else if (command == "y1") board.moveSquare1(0, 1);
		//사각형1 위로 이동
		else if (command == "Y1") board.moveSquare1(0, -1);
		//사각형2 아래로 이동
		else if (command == "y2") board.moveSquare2(0, 1);
		//사각형2 위로 이동
		else if (command == "Y2") board.moveSquare2(0, -1);

		//사각형1 축소
		else if (command == "s1") board.zoomSquare1(-1, -1);
		//사각형1 확대
		else if (command == "S1") board.zoomSquare1(1, 1);
		//사각형2 축소
		else if (command == "s2") board.zoomSquare2(-1, -1);
		//사각형2 확대
		else if (command == "S2") board.zoomSquare2(1, 1);

		//사각형1 X방향 축소
		else if (command == "i1") board.zoomSquare1(-1, 0);
		//사각형1 X방향 확대
		else if (command == "I1") board.zoomSquare1(1, 0);
		//사각형2 X방향 축소
		else if (command == "i2") board.zoomSquare2(-1, 0);
		//사각형2 X방향 확대
		else if (command == "I2") board.zoomSquare2(1, 0);

		//사각형1 Y방향 축소
		else if (command == "j1") board.zoomSquare1(0, -1);
		//사각형1 Y방향 확대
		else if (command == "J1") board.zoomSquare1(0, 1);
		//사각형2 Y방향 축소
		else if (command == "j2") board.zoomSquare2(0, -1);
		//사각형2 Y방향 확대
		else if (command == "J2") board.zoomSquare2(0, 1);

		//사각형1 x축 확대, y축 축소
		else if (command == "a1") board.zoomSquare1(1, -1);
		//사각형1 x축 축소, y축 확대
		else if (command == "A1") board.zoomSquare1(-1, 1);
		//사각형2 x축 확대, y축 축소
		else if (command == "a2") board.zoomSquare2(1, -1);
		//사각형2 x축 축소, y축 확대
		else if (command == "A2") board.zoomSquare2(-1, 1);

		//사각형 면적 출력
		else if (command == "b") {
			cout << "사각형1 면적: " << board.getSquare1Width() << " x " << board.getSquare1Height() << " = " << board.getSquare1Width() * board.getSquare1Height() << endl;
			cout << "사각형2 면적: " << board.getSquare2Width() << " x " << board.getSquare2Height() << " = " << board.getSquare2Width() * board.getSquare2Height() << endl;
			system("pause");
		}

		//보드칸 늘리기
		else if (command == "c") {
			board.setWidth(board.getWidth() + 1);
			board.setHeight(board.getHeight() + 1);
		}
		//보드칸 줄이기
		else if (command == "d") {
			board.setWidth(board.getWidth() - 1);
			board.setHeight(board.getHeight() - 1);
		}

		else if (command == "r") {
			isReset = true;
			board = Board();
		}
		else if (command == "q") isRunning = false;
		else {
			cout << "잘못된 명령어입니다. 다시 입력해주세요." << endl;
			system("pause");
		}
	}

	system("pause");
}