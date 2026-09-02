#include<iostream>
#include<array>
#include<string>
#include<sstream>
#include<ranges>
#include<iterator>
using namespace std;

typedef struct Point{
	int x;
	int y;
	int z;
	bool isValid;

	Point() : x(0), y(0), z(0), isValid(false) {}
	Point(int x, int y, int z) : x(x), y(y), z(z), isValid(true) {}

}POINT;

void printpList(array<POINT, 10> pList) {
	int count = 9;
	for (auto& p : views::reverse(pList)) {
		cout << count << " | ";
		if (p.isValid) {
			cout << p.x << " " << p.y << " " << p.z;
		}
		cout << endl;
		count--;
	}
}

int main() {
	array<POINT, 10> pList{};
	printpList(pList);

	bool isRunning = true;
	string originCommand;

	while (isRunning)
	{
		cout << "명령어를 입력해 주세요: ";
		getline(cin, originCommand);

		stringstream ss(originCommand);
		string command;
		int x, y, z;
		
		ss >> command >> x >> y >> z;

		if (command == "+") {
			int index = 0;
			for (auto& p : pList)
			{
				if (p.isValid) index = distance(pList.data(), &p) + 1;
			}

			if (index == pList.size()) {
				cout << "더 이상 버텍스를 추가할 수 없습니다." << endl;
				continue;
			}
			pList[index] = POINT(x, y, z);

			cout << "버텍스가 추가되었습니다." << endl;
			printpList(pList);
		
		}

		else if (command == "-") {
			int index = 0;
			for (auto& p : pList)
			{
				if (p.isValid) index = distance(pList.data(), &p);
			}
			pList[index] = POINT();
			cout << "버텍스가 제거되었습니다." << endl;
			printpList(pList);
		}



		else if (command == "q") isRunning = false;
		else cout << "잘못된 명령어입니다." << endl;
	}

	system("pause");
}