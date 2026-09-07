#pragma once
class Face {
public:
	Face(int v1, int vt1,  int v2, int vt2, int v3, int vt3) : v1(v1), vt1(vt1), v2(v2), vt2(vt2), v3(v3), vt3(vt3) {}

	int getV1() const { return v1; }
	int getV2() const { return v2; }
	int getV3() const { return v3; }

	int getVT1() const { return vt1; }
	int getVT2() const { return vt2; }
	int getVT3() const { return vt3; }

	bool operator == (const Face& other) const {
		return v1 == other.v1 && vt1 == other.vt1 &&
			v2 == other.v2 && vt2 == other.vt2 &&
			v3 == other.v3 && vt3 == other.vt3;
	}

private:
	int v1;
	int vt1;

	int v2;
	int vt2;
	
	int v3;
	int vt3;
};