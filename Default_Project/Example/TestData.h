#pragma once

const float vertexPosition[] = {
	0.0f, 0.4f, 0.0f,
	-0.4f, 0.1f, 0.0f,
	-0.2f, -0.3f, 0.0f,
	0.2f, -0.3f, 0.0f,
	0.4f, 0.1f, 0.0f
};

const float vertexColor[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f
};

const GLubyte vertexIndices[] = {
	0, 1, 2,
	2, 3, 0,
	0, 3, 4
};

const float vertexData[] = {
	0.0f, 0.4f, 0.0f,		1.0f, 0.0f, 0.0f,
	-0.4f, 0.1f, 0.0f,		0.0f, 1.0f, 0.0f,
	-0.2f, -0.3f, 0.0f,		0.0f, 0.0f, 1.0f,
	0.2f, -0.3f, 0.0f,		1.0f, 1.0f, 0.0f,
	0.4f, 0.1f, 0.0f,		1.0f, 0.0f, 1.0f
};