#include <iostream>
#include <random>
#include <string>
#include <ranges>
#include "CMatrix.h"
using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution<int> uid{ 1, 9 };

int main(void) {
	CMatrix matrix1{
		uid(dre), uid(dre), uid(dre), uid(dre),
		uid(dre), uid(dre), uid(dre), uid(dre),
		uid(dre), uid(dre), uid(dre), uid(dre),
		uid(dre), uid(dre), uid(dre), uid(dre)
	};

	CMatrix matrix2{
		uid(dre), uid(dre), uid(dre), uid(dre),
		uid(dre), uid(dre), uid(dre), uid(dre),
		uid(dre), uid(dre), uid(dre), uid(dre),
		uid(dre), uid(dre), uid(dre), uid(dre)
	};

	CMatrix matrix1Origin = matrix1;
	CMatrix matrix2Origin = matrix2;

	int rowMinList1[4] = { 0, 0, 0, 0 };
	int rowMinList2[4] = { 0, 0, 0, 0 };

	int colMinList1[4] = { 0, 0, 0, 0 };
	int colMinList2[4] = { 0, 0, 0, 0 };

	string command;
	bool isRunning = true;
	bool eboolean = false;
	bool fboolean = false;

	cout << "Matrix 1:" << endl;
	matrix1.printMatrix();
	cout << endl;
	cout << "Matrix 2:" << endl;
	matrix2.printMatrix();

	while(isRunning) {
		cout << "\"help\"를 통해 명령어를 확인할 수 있습니다." << endl;
		cout << "명령어 입력: ";
		cin >> command;

		// 행렬곱
		if (command == "m") {
			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;

			cout << "곱셈 결과:" << endl;
			CMatrix result = matrix1 * matrix2;
			result.printMatrix();
		}

		//행렬 덧셈
		else if (command == "a") {
			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;

			cout << "덧셈 결과:" << endl;
			CMatrix result = matrix1 + matrix2;
			result.printMatrix();
		}

		//행렬 뺄셈
		else if (command == "d") {
			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;

			cout << "뺄셈 결과:" << endl;
			CMatrix result = matrix1 - matrix2;
			result.printMatrix();
		}

		//행렬식
		else if (command == "r") {
			cout << "Matrix 1 행렬식 : " << matrix1.getDet() << endl;
			cout << "Matrix 2 행렬식 : " << matrix2.getDet() << endl;
		}

		//전치행렬
		else if (command == "t") {
			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;

			cout << "Matrix 1 전치행렬:" << endl;
			matrix1.printtMatrix();
			cout << "Matrix 1 전치행렬 행렬식 : " << matrix1.gettDet() << endl;
			cout << endl;
			cout << "Matrix 2 전치행렬:" << endl;
			matrix2.printtMatrix();
			cout << "Matrix 2 전치행렬 행렬식 : " << matrix2.gettDet() << endl;
			cout << endl;
		}

		//각 행에서 최소값 찾아서 행에서 빼기
		else if (command == "e") {
			if (!eboolean) {
				//matrix1
				for (int row : views::iota(0, 4)) {
					int min = matrix1.getData(row, 0);
					// 각 행에서 최소값 찾기
					for (int col : views::iota(0, 4)){
						if (matrix1.getData(row, col) < min) {
							min = matrix1.getData(row, col);
						}
						rowMinList1[row] = min;
					}

					//행에서 최소값 빼기
					for (int col : views::iota(0, 4)) {
						matrix1.setData(row, col, matrix1.getData(row, col) - min);
					}
				}
				cout << "Matrix 1 행 최소값 빼기 결과:" << endl;
				matrix1.printMatrix();

				//matrix2
				for (int row : views::iota(0, 4)) {
					int min = matrix2.getData(row, 0);
					// 각 행에서 최소값 찾기
					for (int col : views::iota(0, 4)) {
						if (matrix2.getData(row, col) < min) {
							min = matrix2.getData(row, col);
						}
					}
					rowMinList2[row] = min;

					//행에서 최소값 빼기
					for (int col : views::iota(0, 4)) {
						matrix2.setData(row, col, matrix2.getData(row, col) - min);
					}
				}
				cout << "Matrix 2 행 최소값 빼기 결과:" << endl;
				matrix2.printMatrix();
				eboolean = true;
			}

			else {
				for (int row : views::iota(0, 4)) {
					for (int col : views::iota(0, 4)) {
						matrix1.setData(row, col, matrix1.getData(row, col) + rowMinList1[row]);
						matrix2.setData(row, col, matrix2.getData(row, col) + rowMinList2[row]);
					}
				}

				cout << "Matrix 1:" << endl;
				matrix1.printMatrix();
				cout << endl;
				cout << "Matrix 2:" << endl;
				matrix2.printMatrix();
				cout << endl;
			}
		}

		//각 열에서 최소값 찾아서 열에서 빼기
		else if (command == "f") {
			if (!fboolean) {
				//matrix1
				for (int col : views::iota(0, 4)) {
					int min = matrix1.getData(0, col);
					// 각 열에서 최소값 찾기
					for (int row : views::iota(0, 4)) {
						if (matrix1.getData(row, col) < min) {
							min = matrix1.getData(row, col);
						}
					}
					colMinList1[col] = min;
					//열에서 최소값 빼기
					for (int row : views::iota(0, 4)) {
						matrix1.setData(row, col, matrix1.getData(row, col) - min);
					}
				}
				cout << "Matrix 1 열 최소값 빼기 결과:" << endl;
				matrix1.printMatrix();
				//matrix2
				for (int col : views::iota(0, 4)) {
					int min = matrix2.getData(0, col);
					// 각 열에서 최소값 찾기
					for (int row : views::iota(0, 4)) {
						if (matrix2.getData(row, col) < min) {
							min = matrix2.getData(row, col);
						}
					}
					colMinList2[col] = min;
					//열에서 최소값 빼기
					for (int row : views::iota(0, 4)) {
						matrix2.setData(row, col, matrix2.getData(row, col) - min);
					}
				}
				cout << "Matrix 2 열 최소값 빼기 결과:" << endl;
				matrix2.printMatrix();
				fboolean = true;
			}

			else {
				for (int row : views::iota(0, 4)) {
					for (int col : views::iota(0, 4)) {
						matrix1.setData(row, col, matrix1.getData(row, col) + colMinList1[col]);
						matrix2.setData(row, col, matrix2.getData(row, col) + colMinList2[col]);
					}
				}

				cout << "Matrix 1:" << endl;
				matrix1.printMatrix();
				cout << endl;
				cout << "Matrix 2:" << endl;
				matrix2.printMatrix();
				cout << endl;
			}
		}

		//행렬의 모든 값에 +1
		else if (command == "+"){
			for (int row : views::iota(0, 4)) {
				for (int col : views::iota(0, 4)) {
					matrix1.setData(row, col, (matrix1.getData(row, col) + 1) % 10);
					matrix2.setData(row, col, (matrix2.getData(row, col) + 1) % 10);
				}
			}

			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;
		}

		//행렬의 모든 값에 -1
		else if (command == "-") {
			for (int row : views::iota(0, 4)) {
				for (int col : views::iota(0, 4)) {
					matrix1.setData(row, col, (matrix1.getData(row, col) - 1) < 0 ? (matrix1.getData(row, col) - 1) + 10 : (matrix1.getData(row, col) - 1));
					matrix2.setData(row, col, (matrix2.getData(row, col) - 1) < 0 ? (matrix2.getData(row, col) - 1) + 10 : (matrix2.getData(row, col) - 1));
				}
			}
			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;
		}

		//행렬 초기화
		else if (command == "c") {
			matrix1 = matrix1Origin;
			matrix2 = matrix2Origin;

			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;
		}

		//행렬 랜덤 재배치
		else if (command == "s") {
			for (int row : views::iota(0, 4)) {
				for (int col : views::iota(0, 4)) {
					matrix1.setData(row, col, uid(dre));
					matrix2.setData(row, col, uid(dre));
				}
			}
			matrix1Origin = matrix1;
			matrix2Origin = matrix2;

			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;
		}

		//명령어 목록
		else if (command == "help") {
			cout << "명령어 목록:" << endl;
			cout << "m: 행렬곱" << endl;
			cout << "a: 행렬덧셈" << endl;
			cout << "d: 행렬뺄셈" << endl;
			cout << "r: 행렬식" << endl;
			cout << "t: 전치행렬" << endl;
			cout << "e: 각 행에서 최소값 찾아서 행에서 빼기" << endl;
			cout << "f: 각 열에서 최소값 찾아서 열에서 빼기" << endl;
			cout << "+: 행렬의 모든 값에 +1" << endl;
			cout << "-: 행렬의 모든 값에 -1" << endl;
			cout << "c: 행렬 초기화" << endl;
			cout << "s: 행렬 랜덤 재배치" << endl;
			cout << "q: 프로그램 종료" << endl;
		}

		// 프로그램 종료
		else if (command == "q") isRunning = false;
		else cout << "잘못된 명령어입니다. \"help\"를 통해 명령어를 확인할 수 있습니다." << endl;
	}

	system("pause");
}