#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Vertex.h"
#include "UV.h"
#include "Face.h"
using namespace std;

bool vertexContains(const vector<Vertex>& vertices, const Vertex& vertex) {
	for (const auto& v : vertices) {
		if (v == vertex) {
			return true;
		}
	}
	return false;
}

bool uvContains(const vector<UV>& uvs, const UV& uv) {
	for (const auto& u : uvs) {
		if (u == uv) {
			return true;
		}
	}
	return false;
}

bool faceContains(const vector<Face>& faces, const Face& face) {
	for (const auto& f : faces) {
		if (f == face) {
			return true;
		}
	}
	return false;
}

int main() {
	string fileName;

	cout << "출력하고 싶은 데이터 세트를 입력하세요: ";
	cin >> fileName;
	fileName = fileName + ".txt";

	ifstream in{ fileName };
	if (not in) {
		cout << "파일을 열 수 없습니다." << endl;
		system("pause");
		return 20260908;
	}

	vector<vector<string>> data;
	string line;
	while (getline(in, line)) {
		stringstream ss(line);
		string word;
		vector<string> row;

		while (ss >> word) row.push_back(word);
		if (!row.empty()) data.push_back(row);
	}

	vector<Vertex> vertices;
	vector<UV> uvs;
	vector<Face> faces;

	for (auto& row : data) {
		if (row[0] == "v") {
			try {
				Vertex vertex{ stod(row[1]), stod(row[2]), stod(row[3]) };
				
				if (vertexContains(vertices, vertex)) {
					std::cerr << "[버텍스 입력] 중복된 버텍스 값이 입력되었습니다: " << vertex << std::endl;
					continue;
				}
				vertices.push_back(vertex);
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "[버텍스 입력] 유효하지 않은 좌표값이 입력되었습니다: " << e.what() << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "[버텍스 입력] double 자료형 범위를 벗어난 값이 입력되었습니다: " << e.what() << std::endl;
			}
		}
		else if (row[0] == "vt") {
			try {
				UV uv{ stod(row[1]), stod(row[2]) };

				if (uvContains(uvs, uv)) {
					std::cerr << "[UV 입력] 중복된 UV 좌표값이 입력되었습니다: " << uv << std::endl;
					continue;
				}
				uvs.push_back(uv);
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "[UV 입력] 유효하지 않은 UV 좌표값이 입력되었습니다: " << e.what() << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "[UV 입력] double 자료형 범위를 벗어난 값이 입력되었습니다: " << e.what() << std::endl;
			}
		}
		else if (row[0] == "f") {
			try {
				int v1 = row[1].find('/') != string::npos ? stoi(row[1].substr(0, row[1].find('/'))) - 1 : stoi(row[1]) - 1;
				int vt1 = row[1].find('/') != string::npos ? stoi(row[1].substr(row[1].find('/') + 1)) - 1 : -1;
				int v2 = row[2].find('/') != string::npos ? stoi(row[2].substr(0, row[2].find('/'))) - 1 : stoi(row[2]) - 1;
				int vt2 = row[2].find('/') != string::npos ? stoi(row[2].substr(row[2].find('/') + 1)) - 1 : -1;
				int v3 = row[3].find('/') != string::npos ? stoi(row[3].substr(0, row[3].find('/'))) - 1 : stoi(row[3]) - 1;
				int vt3 = row[3].find('/') != string::npos ? stoi(row[3].substr(row[3].find('/') + 1)) - 1 : -1;

				if(v1 >= (int)vertices.size() || v2 >= (int)vertices.size() || v3 >= (int)vertices.size() ||
					vt1 >= (int)uvs.size() || vt2 >= (int)uvs.size() || vt3 >= (int)uvs.size()) {
					std::cerr << "[Face 입력] 인덱스 값이 범위를 벗어났습니다." << std::endl;
					continue;
				}
				if(v1 == v2 || v2 == v3 || v1 == v3) {
					std::cerr << "[Face 입력] 중복된 버텍스 인덱스가 입력되었습니다." << std::endl;
					continue;
				}
				Face face{ v1, vt1, v2, vt2, v3, vt3 };

				if (faceContains(faces, face)) {
					std::cerr << "[Face 입력] 중복된 Face 값이 입력되었습니다." << std::endl;
					continue;
				}
				faces.push_back(face);
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "[Face 입력] 유효하지 않은 인덱스 값이 입력되었습니다: " << e.what() << std::endl;
			}
			catch (const std::out_of_range& e) {
				std::cerr << "[Face 입력] 인덱스 값이 int 범위를 벗어났습니다: " << e.what() << std::endl;
			}
		}
	}
	
	int count = 0;
	for (auto& vertex : vertices) {
		cout << count + 1 << " | " << vertex << endl;
		count++;
	}

	cout << "==============================================" << endl;

	count = 0;
	for (auto& uv : uvs) {
		cout << count + 1 << " | " << uv << endl;
		count++;
	}

	cout << "==============================================" << endl;

	count = 0;
	for (auto& face : faces) {
		cout << "Face " << count + 1 << "(" << face.getV1() + 1 << "," << face.getV2() + 1 << "," << face.getV3() + 1 << "):" << endl;
		cout << "\tvertex: " << vertices[face.getV1()].toString() << vertices[face.getV2()].toString() << vertices[face.getV3()].toString() << endl;
		cout << "\ttexture: ";

		if (face.getVT1() == -1) cout << "(텍스쳐 적용 안됨)";
		else cout << uvs[face.getVT1()].toString();

		if (face.getVT2() == -1) cout << "(텍스쳐 적용 안됨)";
		else cout << uvs[face.getVT2()].toString();

		if (face.getVT3() == -1) cout << "(텍스쳐 적용 안됨)";
		else cout << uvs[face.getVT3()].toString();

		cout << endl;
		count++;
	}

	system("pause");
}