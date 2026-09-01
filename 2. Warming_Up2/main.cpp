#include<iostream>
#include<string>
#include<vector>
#include<ranges>
#include<fstream>
#include<sstream>
using namespace std;

int main()
{
	ifstream in { "data.txt" };
	if (not in) {
		cout << "파일을 열 수 없습니다." << endl;
		system("pause");
		return 20260901;
	}

	vector<vector<string>> data;
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

	cout << "읽어온 데이터:" << endl;
	for(const auto& row : data) {
		for(const auto& word : row) {
			cout << word << " ";
		}
		cout << endl;
	}



	system("pause");
}