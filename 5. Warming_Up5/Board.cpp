#include "Square.h"
#include "Board.h"
using namespace std;

void Board::addSquare(const Square& square) {
	squares.push_back(square);
}

void Board::checkCollisions() {
	for (int i = 0; i < squares.size(); i++) {
		for (int j = i + 1; j < squares.size(); j++) {
			//사각형1의 왼쪽이 사각형2의 오른쪽보다 오른쪽
			if (squares[i].getMin().first > squares[j].getMax().first) continue;
			//사각형1의 오른쪽이 사각형2의 왼쪽보다 왼쪽
			else if (squares[i].getMax().first < squares[j].getMin().first) continue;
			//사각형1의 위가 사각형2의 아래보다 아래
			else if (squares[i].getMin().second > squares[j].getMax().second) continue;
			//사각형1의 아래가 사각형2의 위보다 위
			else if (squares[i].getMax().second < squares[j].getMin().second) continue;

			pair<int, int> iPos;
			pair<int, int> jPos;

			//범위 겹치는 사각형1의 X 구하기
			if (squares[i].getMin().first >= squares[j].getMin().first &&
				squares[i].getMin().first <= squares[j].getMax().first) iPos.first = squares[i].getMin().first;
			else if (squares[i].getMax().first >= squares[j].getMin().first &&
					squares[i].getMax().first <= squares[j].getMax().first) iPos.first = squares[i].getMax().first;

			//범위 겹치는 사각형1의 Y 구하기
			if (squares[i].getMin().second >= squares[j].getMin().second &&
				squares[i].getMin().second <= squares[j].getMax().second) iPos.second = squares[i].getMin().second;
			else if (squares[i].getMax().second >= squares[j].getMin().second &&
				squares[i].getMax().second <= squares[j].getMax().second) iPos.second = squares[i].getMax().second;

			//범위 겹치는 사각형2의 X 구하기
			if (squares[j].getMin().first >= squares[i].getMin().first &&
				squares[j].getMin().first <= squares[i].getMax().first) jPos.first = squares[j].getMin().first;
			else if (squares[j].getMax().first >= squares[i].getMin().first &&
				squares[j].getMax().first <= squares[i].getMax().first) jPos.first = squares[j].getMax().first;

			//범위 겹치는 사각형2의 Y 구하기
			if (squares[j].getMin().second >= squares[i].getMin().second &&
				squares[j].getMin().second <= squares[i].getMax().second) jPos.second = squares[j].getMin().second;
			else if (squares[j].getMax().second >= squares[i].getMin().second &&
				squares[j].getMax().second <= squares[i].getMax().second) jPos.second = squares[j].getMax().second;

			pair<int, int> minPos;
			pair<int, int> maxPos;

			minPos.first = min(iPos.first, jPos.first);
			minPos.second = min(iPos.second, jPos.second);
			maxPos.first = max(iPos.first, jPos.first);
			maxPos.second = max(iPos.second, jPos.second);

			hitCollisions.push_back(make_pair(minPos, maxPos));
		}
	}
}

void Board::printBoard() const {
	for (int u = 0; u < 30; u++) {
		for (int v = 0; v < 30; v++) {

		}
	}
}