#include<iostream>
#include<array>
#include<string>
#include<sstream>
#include<ranges>
#include<iterator>
#include<algorithm>
#include <vector>
#include<map>
#include<cmath>
using namespace std;

bool fboolean = false;

typedef struct Point{
	int index;
	int x;
	int y;
	int z;
	bool isValid;
	double distance;
	map<int, double> distanceMap;

	Point() : x(0), y(0), z(0), isValid(false) {}
	Point(int x, int y, int z) : x(x), y(y), z(z), isValid(true) {}

}POINT;

double getDistance(POINT& p1, POINT& p2) {
	double dx = static_cast<double>(p1.x - p2.x);
	double dy = static_cast<double>(p1.y - p2.y);
	double dz = static_cast<double>(p1.z - p2.z);
	return sqrt(dx * dx + dy * dy + dz * dz);
}

void printpList(array<POINT, 10> pList) {
	if (fboolean) {
		POINT origin(0, 0, 0);
		for (auto& p : pList) {
			if (p.isValid) {
				p.distance = getDistance(p, origin);
			}
		}

		sort(pList.begin(), pList.end(), [](const POINT& a, const POINT& b) {
			if (a.distance == 0) return false;
			if (b.distance == 0) return false;
			return a.distance < b.distance;
			});
	}
	
	for (auto& p : views::reverse(pList)) {
		cout << p.index << " | ";
		if (p.isValid) {
			cout << p.x << " " << p.y << " " << p.z;
			if (fboolean) {
				cout << " | 거리: " << p.distance;
			}
		}
		cout << endl;
	}
}

int main() {
	array<POINT, 10> pList{};
	for (auto& p : pList) p.index = distance(pList.data(), &p);
	printpList(pList);

	bool isRunning = true;
	string originCommand;

	while (isRunning)
	{
		cout << "명령어를 입력해 주세요: ";
		getline(cin, originCommand);

		stringstream ss(originCommand);
		string command;
		int x = -9999999;
		int y = -9999999;
		int z = -9999999;
		
		ss >> command >> x >> y >> z;

		//버텍스 추가(push)
		if (command == "+") {
			if (x == -9999999 || y == -9999999 || z == -9999999) {
				cout << "좌표를 입력해 주세요." << endl;
				continue;
			}
			int maxVindex = 0;
			int iVindex = 0;
			int count = 0;
			for (auto& p : pList){
				if (p.isValid) {
					maxVindex = distance(pList.data(), &p);
					count++;
				}
			}

			for (auto& p : pList) {
				if (!p.isValid) {
					iVindex = distance(pList.data(), &p);
					break;
				}
			}

			if (count == pList.size()) {
				cout << "더 이상 버텍스를 추가할 수 없습니다." << endl;
				continue;
			}

			if (maxVindex == pList.size() - 1) {
				cout << iVindex << endl;
				pList[iVindex] = POINT(x, y, z);
				pList[iVindex].index = iVindex;
			}
			else if(maxVindex == 0 && count == 0) {
				pList[0] = POINT(x, y, z);
				pList[0].index = 0;
			}
			else {
				pList[maxVindex + 1] = POINT(x, y, z);
				pList[maxVindex + 1].index = maxVindex + 1;
			}

			cout << "버텍스가 추가되었습니다." << endl;
			printpList(pList);
		
		}

		//버텍스 제거(pop)
		else if (command == "-") {
			int index = 0;
			int count = 0;
			for (auto& p : pList)
			{
				if (p.isValid) {
					index = distance(pList.data(), &p);
					count++;
				}
			}
			if (count == 0) {
				cout << "제거할 버텍스가 없습니다." << endl;
				continue;
			}

			pList[index] = POINT();
			pList[index].index = index;
			cout << "버텍스가 제거되었습니다." << endl;
			printpList(pList);
		}

		//버텍스 추가(앞에서)
		else if (command == "e") {
			if (x == -9999999 || y == -9999999 || z == -9999999) {
				cout << "좌표를 입력해 주세요." << endl;
				continue;
			}
			int minVindex = 0;
			int maxVindex = 0;
			int minIVindex = 0;
			int count = 0;
			for (auto& p : pList) {
				if (p.isValid) {
					minVindex = distance(pList.data(), &p);
					break;
				}
			}
			for (auto& p : pList) {
				if (p.isValid) {
					maxVindex = distance(pList.data(), &p);
					count++;
				}
			}
			for (auto& p : pList) {
				if (!p.isValid) {
					minIVindex = distance(pList.data(), &p);
					break;
				}
			}

			if (count == pList.size()) {
				cout << "더 이상 버텍스를 추가할 수 없습니다." << endl;
				continue;
			}

			if (minIVindex < minVindex) {
				pList[minIVindex] = POINT(x, y, z);
				pList[minIVindex].index = minIVindex;
			}
			else if (minIVindex > minVindex && minIVindex < maxVindex) {
				copy_backward(pList.begin(), pList.begin() + minIVindex, pList.begin() + minIVindex + 1);
				pList[minVindex] = POINT(x, y, z);
				pList[minVindex].index = minVindex;
			}
			else if (minIVindex > maxVindex) {
				copy_backward(pList.begin() + minVindex, pList.begin() + maxVindex + 1, pList.begin() + maxVindex + 2);
				pList[minVindex] = POINT(x, y, z);
				pList[minVindex].index = minVindex;
			}

			cout << "버텍스가 추가되었습니다." << endl;
			printpList(pList);
		}

		//버텍스 제거(앞에서)
		else if (command == "d") {
			int index = 0;
			int count = 0;
			for (auto& p : pList) {
				if (p.isValid) count++;
			}

			for (auto& p : pList) {
				if (p.isValid) {
					index = distance(pList.data(), &p);
					break;
				}
			}

			if (count == 0) {
				cout << "제거할 버텍스가 없습니다." << endl;
				continue;
			}

			pList[index] = POINT();
			pList[index].index = index;
			cout << "버텍스가 제거되었습니다." << endl;
			printpList(pList);
		}

		//리스트에 저장된 점의 개수
		else if (command == "a") {
			int count = 0;
			for (auto& p : pList) {
				if (p.isValid) count++;
			}
			cout << "리스트에 저장된 점의 개수: " << count << endl;
		}

		//점들의 리스트 위치를 한 칸씩 내려보내기
		else if (command == "b") {
			int count = 0;
			POINT temp;
			for (auto& p : pList) {
				if (count == 0) {
					temp = p;
				}
				else {
					pList[count - 1] = p;
				}
				count++;
			}
			pList[pList.size() - 1] = temp;
			printpList(pList);
		}

		//리스트 비우기
		else if (command == "c") {
			for (auto& p : pList) {
				p = POINT();
				p.index = distance(pList.data(), &p);
			}
			cout << "리스트가 비워졌습니다." << endl;
			printpList(pList);
		}

		//원점과 거리 계산 후, 정렬 출력
		else if (command == "f") {
			fboolean = !fboolean;
			printpList(pList);
		}

		//저장된 점들끼리의 모든 조합의 거리를 계산 후, 가장 먼 두 점, 가장 가까운 두 점을 출력
		else if (command == "g") {
			vector<pair<pair<int, int>, double>> distancePairs;
			for (int i = 0; i < pList.size(); i++) {
				if (!pList[i].isValid) continue;
				for (int j = i + 1; j < pList.size(); j++) {
					if (!pList[j].isValid) continue;

					pList[i].distanceMap[j] = getDistance(pList[i], pList[j]);
					distancePairs.push_back({ {i, j}, pList[i].distanceMap[j] });
				}
			}

			for (auto& p : pList) {
				for (int key : p.distanceMap | views::keys) {
					cout << "점 " << p.index << "과 점 " << key << "의 거리: " << p.distanceMap[key] << endl;
				}
			}
			cout << endl;

			double maxDistance = max_element(distancePairs.begin(), distancePairs.end(), [](const auto& a, const auto& b) {
				return a.second < b.second;
				})->second;
			double minDistance = min_element(distancePairs.begin(), distancePairs.end(), [](const auto& a, const auto& b) {
				return a.second < b.second;
				})->second;
			vector<pair<int, int>> maxDistancePairs;
			vector<pair<int, int>> minDistancePairs;

			for (auto& pair : distancePairs) {
				if (pair.second == maxDistance) {
					maxDistancePairs.push_back(pair.first);
				}
				else if (pair.second == minDistance) {
					minDistancePairs.push_back(pair.first);
				}
			}

			cout << "가장 먼 두 점의 거리: " << endl;
			for (auto& pair : maxDistancePairs) {
				cout << "점 " << pair.first << "과 점 " << pair.second << "의 거리: " << maxDistance << endl;
			}
			cout << "가장 가까운 두 점의 거리: " << endl;
			for (auto& pair : minDistancePairs) {
				cout << "점 " << pair.first << "과 점 " << pair.second << "의 거리: " << minDistance << endl;
			}
			cout << endl;
		}

		else if (command == "q") isRunning = false;
		else cout << "잘못된 명령어입니다." << endl;
	}

	system("pause");
}