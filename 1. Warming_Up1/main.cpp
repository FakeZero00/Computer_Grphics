#include <iostream>
#include <random>
#include <string>
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

	string command;
	bool isRunning = true;

	cout << "Matrix 1:" << endl;
	matrix1.printMatrix();
	cout << endl;
	cout << "Matrix 2:" << endl;
	matrix2.printMatrix();

	while(isRunning) {
		cout << "¸í·É¾î ÀÔ·Â: ";
		cin >> command;

		// Çà·Ä°ö
		if (command == "m") {
			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;

			cout << "°ö¼À °á°ú:" << endl;
			CMatrix result = matrix1 * matrix2;
			result.printMatrix();
		}

		//Çà·Ä µ¡¼À
		else if (command == "a") {
			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;

			cout << "µ¡¼À °á°ú:" << endl;
			CMatrix result = matrix1 + matrix2;
			result.printMatrix();
		}

		//Çà·Ä »¬¼À
		else if (command == "d") {
			cout << "Matrix 1:" << endl;
			matrix1.printMatrix();
			cout << endl;
			cout << "Matrix 2:" << endl;
			matrix2.printMatrix();
			cout << endl;

			cout << "»¬¼À °á°ú:" << endl;
			CMatrix result = matrix1 - matrix2;
			result.printMatrix();
		}

		//Çà·Ä½Ä
		else if (command == "r") {
			cout << "Matrix 1 Çà·Ä½Ä : " << endl;
			cout << matrix1.getDet() << endl;
			cout << "Matrix 2 Çà·Ä½Ä : " << matrix2.getDet() << endl;
		}

		// ÇÁ·Î±×·¥ Á¾·á
		else if (command == "q") isRunning = false;
	}

	system("pause");
}