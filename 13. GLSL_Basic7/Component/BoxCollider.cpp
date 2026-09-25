#include "BoxCollider.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Mesh.h"
#include "Material.h"
#include <gl/glm/gtc/type_ptr.hpp>
#include <gl/glew.h>

//main에서 선언된 shaders 맵을 extern으로 참조
extern map<string, GLuint> shaders;

BoxCollider::BoxCollider(vec3 center, vec3 size) : Collider(ColliderType::Box), center(center), size(size) {
	RecalculateCollision();
	InitDebugRender();
}

void BoxCollider::RecalculateCollision() {
	if (not gameObject) return;

	Transform* tr = gameObject->GetComponent<Transform>();
	if (not tr) return;

	//메시 데이터가 없을 때의 기본 박스 범위 설정
	vec3 meshMin{ -0.5f };
	vec3 meshMax{ 0.5f };

	MeshRenderer3D* mr = gameObject->GetComponent<MeshRenderer3D>();
	if (mr && mr->mesh) {
		meshMin = mr->mesh->minPos;
		meshMax = mr->mesh->max3Pos;
	}

	//중심점과 크기 계산
	vec3 meshCenter = (meshMin + meshMax) / 2.0f;
	vec3 meshExtent = (meshMax - meshMin) / 2.0f;

	vec3 finalExtent = meshExtent * size * tr->scale;
	
	vec3 finalCenter = meshCenter + center;
	vec3 worldCenter = vec3(tr->worldMatrix * vec4{ finalCenter, 1.0f });

	minPos = worldCenter - finalExtent;
	maxPos = worldCenter + finalExtent;
}

void BoxCollider::Start() {
	RecalculateCollision();
}

void BoxCollider::Render() {
	if (not isDebug) return;

	GLuint debugShader = shaders["Debug"];
	glUseProgram(debugShader);

	// minPos, maxPos는 이미 월드 좌표이므로 모델 변환 행렬을 단위 행렬(Identity)로 덮어씌움
	GLuint modelLoc = glGetUniformLocation(debugShader, "model");
	mat4 identity = mat4{ 1.0f };
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(identity));

	//minPos와 maxPos를 이용해 8개의 꼭짓점 계산
	float x1 = minPos.x, y1 = minPos.y, z1 = minPos.z;
	float x2 = maxPos.x, y2 = maxPos.y, z2 = maxPos.z;
	float g = 1.0f;

	float vertices[] = {
		x1, y1, z1,		0.0f, g, 0.0f,
		x2, y1, z1,		0.0f, g, 0.0f,
		x2, y2, z1,		0.0f, g, 0.0f,
		x1, y2, z1,		0.0f, g, 0.0f,
		x1, y1, z2,		0.0f, g, 0.0f,
		x2, y1, z2,		0.0f, g, 0.0f,
		x2, y2, z2,		0.0f, g, 0.0f,
		x1, y2, z2,		0.0f, g, 0.0f
	};

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

	glDrawElements(GL_LINES, 24, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);
}

void BoxCollider::InitDebugRender() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	//VBO 초기화
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 8 * 6 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//EBO 초기화
	GLubyte indices[] = {
		0,1, 1,2, 2,3, 3,0,
		4,5, 5,6, 6,7, 7,4,
		0,4, 1,5, 2,6, 3,7
	};
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
}