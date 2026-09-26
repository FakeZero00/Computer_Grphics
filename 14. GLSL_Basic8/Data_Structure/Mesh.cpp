#include "Mesh.h"
#include <cfloat>
using namespace std;

Mesh::Mesh(const vector<Vertex>& vertices, const vector<GLubyte>& indices) {
	indexCount = indices.size();

	minPos = vec3{ FLT_MAX };
	max3Pos = vec3{ -FLT_MAX };

	//버텍스 데이터에서 최소, 최대 좌표 계산
	for (const auto& vertex : vertices) {
		minPos = glm::min(minPos, vertex.position);
		max3Pos = glm::max(max3Pos, vertex.position);
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	//버텍스 데이터 설정
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	//버텍스 좌표: 속성 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);

	//버텍스 색상: 속성 1
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(1);

	// VAO 바인딩 해제
	glBindVertexArray(0);
}

void Mesh::Bind() const {
	glBindVertexArray(VAO);
}