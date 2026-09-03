#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include "Board.h"
using namespace std;

map<string, pair<size_t, size_t>> posMap = {
	{"a0", {0, 0}}, {"a1", {1, 0}}, {"a2", {2, 0}}, {"a3", {3, 0}}, {"a4", {4, 0}}, {"a5", {5, 0}},
	{"b0", {0, 1}}, {"b1", {1, 1}}, {"b2", {2, 1}}, {"b3", {3, 1}}, {"b4", {4, 1}}, {"b5", {5, 1}},
	{"c0", {0, 2}}, {"c1", {1, 2}}, {"c2", {2, 2}}, {"c3", {3, 2}}, {"c4", {4, 2}}, {"c5", {5, 2}},
	{"d0", {0, 3}}, {"d1", {1, 3}}, {"d2", {2, 3}}, {"d3", {3, 3}}, {"d4", {4, 3}}, {"d5", {5, 3}},
	{"e0", {0, 4}}, {"e1", {1, 4}}, {"e2", {2, 4}}, {"e3", {3, 4}}, {"e4", {4, 4}}, {"e5", {5, 4}},
	{"f0", {0, 5}}, {"f1", {1, 5}}, {"f2", {2, 5}}, {"f3", {3, 5}}, {"f4", {4, 5}}, {"f5", {5, 5}}
};

int main() {
	size_t row, col;
	Board board;
	bool isRunning = true;
	bool isReset = true;
	string command;

	while (isRunning)
	{
		if (isReset) {
			cout << "보드의 크기 입력(가로, 세로 3~6): ";
			getline(cin, command);
			stringstream ss(command);
			ss >> row >> col;

			if (row >= 3 && row <= 6 && col >= 3 && col <= 6) {
				board = Board(row, col);
				isReset = false;
			}
			else {
				cout << "3 ~ 6 범위의 수를 입력해 주세요." << endl;
				system("pause");
				system("cls");
				continue;
			}
		}

		system("cls");
		board.print();

		cout << "뒤집을 좌표(예: \"a1 b2\")나 명령어(\"help\"로 명령어들을 볼 수 있습니다)를 입력하세요\n";
		cout << "명령어 입력: ";
		getline(cin, command);

		//리셋하고 다시 시작
		if (command == "r") {
			isReset = true;
			system("cls");
		}

		//일시적으로 모든 칸을 뒤집음
		else if (command == "h") {
			system("cls");
			board.printAll();
			system("pause");

			system("cls");
		}

		//종료
		else if (command == "q") isRunning = false;

		//명령어 목록
		else if (command == "help") {
			cout << "명령어 목록:\n";
			cout << "r: 보드를 리셋하고 다시 시작\n";
			cout << "h: 모든 칸을 일시적으로 뒤집음\n";
			cout << "q: 게임 종료\n";
		}

		else {
			stringstream ss(command);
			string pos1, pos2;
			ss >> pos1 >> pos2;

			if (posMap.contains(pos1) && posMap.contains(pos2)) {
				board.setVisited(posMap[pos1].first, posMap[pos1].second, true);
				board.setVisited(posMap[pos2].first, posMap[pos2].second, true);

				if (board.getCell(posMap[pos1].first, posMap[pos1].second) == board.getCell(posMap[pos2].first, posMap[pos2].second)) {
					board.setSuccess(posMap[pos1].first, posMap[pos1].second, true);
					board.setSuccess(posMap[pos2].first, posMap[pos2].second, true);
				}

				else if (board.getCell(posMap[pos1].first, posMap[pos1].second) == '@' ||
						board.getCell(posMap[pos2].first, posMap[pos2].second) == '@') {
					if(board.getCell(posMap[pos1].first, posMap[pos1].second) == '@') board.setSuccess(posMap[pos1].first, posMap[pos1].second, true);
					else if(board.getCell(posMap[pos2].first, posMap[pos2].second) == '@') board.setSuccess(posMap[pos2].first, posMap[pos2].second, true);

					board.openJoker();
				}

				system("cls");
				board.print();
				system("pause");

				board.clearVisited();
			}
			else {
				cout << pos1 << " " << pos2 << endl;
				cout << "잘못된 좌표나 명령어 입니다. 다시 입력해주세요." << endl;
				system("pause");
				system("cls");
			}
		}
	}

	system("pause");
}