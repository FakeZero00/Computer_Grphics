#include "Mesh.h"
#include <cfloat>
using namespace std;

Mesh::Mesh(const float* vertices, GLsizeiptr vertSize, const GLubyte* indices, GLsizeiptr indexSize) {
	indexCount = indexSize / sizeof(GLubyte);

	minPos = vec3{ FLT_MAX };
	max3Pos = vec3{ -FLT_MAX };

	//버텍스 데이터에서 최소, 최대 좌표 계산
	int stride = 6;
	int vertexCount = vertSize / (stride * sizeof(float));

	for (int i = 0; i < vertexCount; ++i) {
		vec3 pos{
			vertices[i * stride + 0],
			vertices[i * stride + 1],
			vertices[i * stride + 2]
		};
		minPos = glm::min(minPos, pos);
		max3Pos = glm::max(max3Pos, pos);
	}

	//VAO 객체 생성 및 바인딩
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	//VBO 객체 생성 및 바인딩
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//EBO 객체 생성 및 바인딩 및 데이터 설정
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, GL_STATIC_DRAW);

	//버텍스 데이터 설정
	glBufferData(GL_ARRAY_BUFFER, vertSize, vertices, GL_STATIC_DRAW);

	//버텍스 좌표: 속성 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//버텍스 색상: 속성 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// VAO 바인딩 해제
	glBindVertexArray(0);
}

void Mesh::Bind() const {
	glBindVertexArray(VAO);
}