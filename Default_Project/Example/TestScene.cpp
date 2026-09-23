#include "TestScene.h"
#include "TestData.h"
#include "Mesh.h"
#include "Material.h"

TestScene::TestScene() {
	name = "TestScene";
}

void TestScene::LoadScene(AppContext& ctx, map<string, GLuint>& shaders) {
	Object* testObj = Instantiate(ctx, "TestObject");
	testObj->AddComponent<MeshRenderer3D>(new Mesh(vertexData, sizeof(vertexData), vertexIndices, sizeof(vertexIndices)), new Material(shaders["Test"]));
	BoxCollider* col = testObj->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f });
	col->isDebug = true;
}