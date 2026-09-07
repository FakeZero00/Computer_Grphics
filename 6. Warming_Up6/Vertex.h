#pragma once
#include <format>
#include <string>
using namespace std;

class Vertex {
public:
	Vertex(double x, double y, double z) : x(x), y(y), z(z) {}

	double getX() const { return x; }
	double getY() const { return y; }
	double getZ() const { return z; }
	string toString() const {
		string formattedX = std::format("{:g}", x);
		string formattedY = std::format("{:g}", y);
		string formattedZ = std::format("{:g}", z);

		return "(" + formattedX + ", " + formattedY + ", " + formattedZ + ")";
	}

	bool operator == (const Vertex& other) const {
		return x == other.x && y == other.y && z == other.z;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
		os << "v " << vertex.x << " " << vertex.y << " " << vertex.z;
		return os;
	}

private:
	double x;
	double y;
	double z;
};