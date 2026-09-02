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
bool eboolean = false;
bool hboolean = false;

bool isWordEqual(string word, string searchWord) {
	if (word.size() != searchWord.size()) return false;

	for (auto& c : word) c = tolower(c);
	for (auto& c : searchWord) c = tolower(c);

	return word == searchWord;
}

void printData(const vector<vector<string>>& data) {
	if (!cboolean)
	{
		for (const auto& row : data) {
			int wordCount = 0;
			for (const auto& word : row) {
				if (!hboolean) {
					cout << word << ((eboolean && wordCount != row.size() - 1) ? "*" : " ");
				}
				else {
					bool digitboolean = false;
					for (const auto& c : word) {
						cout << c;
						if (isdigit(c)) {
							digitboolean = true;
							cout << endl;
						}
					}
					if (!digitboolean) cout << ((eboolean && wordCount != row.size() - 1) ? "*" : " ");
				}
				wordCount++;
			}
			cout << endl;
		}
	}
	else {
		for (auto& row : data) {
			int count = 0;
			int wordCount = 0;
			for (auto& word : row) {
				if (!hboolean)
				{
					if (isupper(word[0])) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
						bool digitboolean = false;
						for (const auto& c : word) {
							cout << c;
							if (isdigit(c)) {
								digitboolean = true;
								cout << endl;
							}
						}
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						if (!digitboolean) cout << ((eboolean && wordCount != row.size() - 1) ? "*" : " ");
						count++;
					}
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						cout << word << ((eboolean && wordCount != row.size() - 1) ? "*" : " ");
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}
				
				else {
					if (isupper(word[0])) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
						cout << word;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						cout << ((eboolean && wordCount != row.size() - 1) ? "*" : " ");
						count++;
					}
					else {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
						bool digitboolean = false;
						for (const auto& c : word) {
							cout << c;
							if (isdigit(c)) {
								digitboolean = true;
								cout << endl;
							}
						}
						if (!digitboolean) cout << ((eboolean && wordCount != row.size() - 1) ? "*" : " ");
					}
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
				}

				wordCount++;
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
		cout << "\"help\"를 입력하면 명령어를 볼 수 있습니다." << endl;
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

		//각 문장별로 거꾸로 출력
		else if (command == "d") {
			for (auto& row : data) {
				for (auto& word : row) {
					reverse(word.begin(), word.end());
				}
				reverse(row.begin(), row.end());
			}

			printData(data);
			cout << endl;
		}

		//공백 *넣기
		else if (command == "e") {
			eboolean = !eboolean;
			printData(data);
			cout << endl;
		}

		//공백 기준으로 단어들 거꾸로 출력
		else if (command == "f") {
			for (auto& row : data) {
				for (auto& word : row) {
					reverse(word.begin(), word.end());
				}
			}
			printData(data);
			cout << endl;
		}

		else if (command == "g") {
			char oldChar, newChar;
			cout << "변경할 문자를 입력하세요: ";
			cin >> oldChar;
			cout << "새로운 문자를 입력하세요: ";
			cin >> newChar;

			for (auto& row : data) {
				for (auto& word : row) {
					for (char& c : word) {
						if (c == oldChar) {
							c = newChar;
						}
					}
				}
			}

			printData(data);
			cout << endl;
		}

		//숫자가 나오면 줄바꿈
		else if (command == "h") {
			hboolean = !hboolean;

			printData(data);
			cout << endl;
		}

		//특정 단어 찾기
		else if (command == "i") {
			string searchWord;
			int count = 0;
			cout << "찾을 단어를 입력하세요: ";
			cin >> searchWord;
			for (const auto& row : data) {
				for (const auto& word : row) {
					if (isWordEqual(word, searchWord)) {
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
						count++;
					}
					else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << word;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
					cout << " ";
				}
				cout << endl;
			}
			cout << "[찾은 단어 개수]: " << count << endl;
		}

		//문장의 순서 변경(하나씩 밑으로)
		else if (command == "j") {
			auto lastRow = data.back();
			data.pop_back();
			data.insert(data.begin(), lastRow);

			printData(data);
			cout << endl;
		}

		//리셋
		else if (command == "reset") {
			data = originData;
			printData(data);
			cout << endl;
		}

		//명령어 모음
		else if (command == "help") {
			cout << "명령어 모음:" << endl;
			cout << "a: 대소문자 역전" << endl;
			cout << "b: 문장에 쓰인 단어 개수 출력" << endl;
			cout << "c: 대문자로 시작되는 단어를 찾아서 그 단어를 다른 색으로 출력, 개수도 출력" << endl;
			cout << "d: 각 문장별로 거꾸로 출력" << endl;
			cout << "e: 공백 *넣기" << endl;
			cout << "f: 공백 기준으로 단어들 거꾸로 출력" << endl;
			cout << "g: 특정 문자 변경" << endl;
			cout << "h: 숫자가 나오면 줄바꿈" << endl;
			cout << "i: 특정 단어 찾기" << endl;
			cout << "j: 문장의 순서 변경(하나씩 밑으로)" << endl;
			cout << "reset: 리셋" << endl;
			cout << "q: 프로그램 종료" << endl;
		}

		//프로그램 종료
		else if (command == "q") isRunning = false;
		else cout << "잘못된 명령어입니다." << endl;
	}

	system("pause");
}