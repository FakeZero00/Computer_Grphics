#include "MeshRenderer3D.h"
#include "Mesh.h"
#include "Material.h"
#include "Object.h"
#include "Transform.h"
#include <gl/glew.h>
#include <gl/glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

MeshRenderer3D::MeshRenderer3D(Mesh* mesh, Material* material) : mesh(mesh) {
	this->materials.push_back(material);
}

void MeshRenderer3D::Render() {
	for (auto& material : materials) {
		//셰이더 사용
		material->Use();

		//Transform의 worldMatrix를 셰이더에 전달
		Transform* transform = gameObject->GetComponent<Transform>();
		GLuint modelLoc = glGetUniformLocation(material->shaderProgram, "model");
		GLuint colorLoc = glGetUniformLocation(material->shaderProgram, "tColor");

		//VAO 바인딩
		mesh->Bind();

		//Pass1 : 외곽선 렌더링 처리
		if (material->isOutline) {
			mat4 outlineMatrix = transform->worldMatrix;
			outlineMatrix = glm::scale(outlineMatrix, vec3{ 1.5f }); //외곽선 확대
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(outlineMatrix));
			glUniform4f(colorLoc, 0.0f, 0.0f, 0.0f, 1.0f); //외곽선 색상 검정
			glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_BYTE, 0);
			
			//원래 색상 전달
			vec4 originalColor = material->GetVec4("tColor");
			glUniform4f(colorLoc, originalColor.r, originalColor.g, originalColor.b, originalColor.a);
		}

		//Pass2 : Mesh 데이터 그리기
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(transform->worldMatrix));
		glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_BYTE, 0);
		glBindVertexArray(0);
	}
}