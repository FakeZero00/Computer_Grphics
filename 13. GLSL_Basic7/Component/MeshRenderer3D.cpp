#include "MeshRenderer3D.h"
#include "Mesh.h"
#include "Material.h"
#include "Object.h"
#include "Transform.h"
#include <gl/glew.h>
#include <gl/glm/gtc/type_ptr.hpp>

void MeshRenderer3D::Render() {
	//셰이더 사용
	material->Use();

	//Transform의 worldMatrix를 셰이더에 전달
	Transform* transform = gameObject->GetComponent<Transform>();
	if (transform) {
		GLuint modelLoc = glGetUniformLocation(material->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(transform->worldMatrix));
	}

	//VAO 바인딩
	mesh->Bind();

	//폴리곤 그리기
	glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_BYTE, 0);
	glBindVertexArray(0);
}