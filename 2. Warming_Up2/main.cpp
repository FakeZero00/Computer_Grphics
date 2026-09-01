#include<iostream>
#include<string>
#include<vector>
#include<ranges>
#include<fstream>
#include<sstream>
#include<cctype>
#include<windows.h>
using namespace std;

bool cboolean = false;

void printData(const vector<vector<string>>& data) {
	if (!cboolean)
	{
		for (const auto& row : data) {
			for (const auto& word : row) {
				cout << word << " ";
			}
			cout << endl;
		}
	}
	else {
		for (auto& row : data) {
			int count = 0;
			for (auto& word : row) {
				if (isupper(word[0])) {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
					cout << word << " ";
					count++;
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << word << " ";
				}
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

			}
			cout << "[대문자로 시작되는 단어 개수]: " << count << endl;
		}
	}
}

int main()
{
	ifstream in { "data.txt" };
	if (not in) {
		cout << "파일을 열 수 없습니다." << endl;
		system("pause");
		return 20260901;
	}

	vector<vector<string>> data;
	vector<vector<string>> originData;
	string line;

	while (getline(in, line)) {
		stringstream ss(line);
		string word;
		vector<string> row;

		while (ss >> word) {
			row.push_back(word);
		}

		if (!row.empty()) {
			data.push_back(row);
		}
	}
	originData = data;

	bool isRunning = true;
	string command;

	cout << "읽어온 데이터:" << endl;
	printData(data);

	while (isRunning){
		cout << "명령어를 입력하세요: ";
		cin >> command;

		//대소문자 역전
		if (command == "a") {
			for (auto& row : data) {
				for (auto& word : row) {
					for (char& c : word) {
						if (isupper(c)) {
							c = tolower(c);
						}
						else if (islower(c)) {
							c = toupper(c);
						}
					}
				}
			}
			printData(data);
			cout << endl;
		}

		//문장에 쓰인 단어 개수 출력
		else if (command == "b") {
			for (auto& row : data) {
				for (auto& word : row) {
					cout << word << " ";
				}
				cout << "[단어 개수]: " << row.size() << endl;
			}
			cout << endl;
		}

		//대문자로 시작되는 단어를 찾아서 그 단어를 찾아 그 단어를 다른 색으로 출력, 개수도 출력
		else if (command == "c") {
			cboolean = !cboolean;
			printData(data);
			cout << endl;
		}

		//프로그램 종료
		else if (command == "q") isRunning = false;
		else cout << "잘못된 명령어입니다." << endl;
	}

	system("pause");
}