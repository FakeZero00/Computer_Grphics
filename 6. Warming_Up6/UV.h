#pragma once
#include <string>
#include <format>
using namespace std;

class UV {
public:
	UV(double u, double v) : u(u), v(v) {}

	double getU() const { return u; }
	double getV() const { return v; }

	string toString() const {
		string formattedU = std::format("{:g}", u);
		string formattedV = std::format("{:g}", v);
		return "(" + formattedU + ", " + formattedV + ")";
	}

	bool operator == (const UV& other) const {
		return u == other.u && v == other.v;
	}

	friend std::ostream& operator<<(std::ostream& os, const UV& uv) {
		os << "vt " << uv.u << " " << uv.v;
		return os;
	}

private:
	double u;
	double v;
};