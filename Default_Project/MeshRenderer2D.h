#pragma once
#include "Component.h"

struct Position2D {
	float x;
	float y;
};

struct Color {
	float r;
	float g;
	float b;
	float a;
};

class MeshRenderer2D : public Component {
public:
	Position2D minPos;
	Position2D maxPos;

	float width;
	float height;
	Color color = { 1.0f, 1.0f, 1.0f, 1.0f }; //기본 색상 흰색

	MeshRenderer2D();
	MeshRenderer2D(float width, float height, Color color);

	void SetSize(float width, float height);

	void Render() override;
};