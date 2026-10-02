#include "Default_Scene.h"
#include "Dataset.h"
#include "Common.h"
#include "Mesh.h"
#include "Material.h"

extern map<string, GLuint> shaders;

//스크립트 불러오기
#include "ShapeGenerator.h"

Default_Scene::Default_Scene() {
	name = "Default_Scene";
}

void Default_Scene::LoadScene(AppContext& ctx) {
	//함수 작성 주의사항:
	// 1. Instantiate 함수를 사용하여 Object를 생성해야 합니다.
	// 2. Object에 컴포넌트를 추가할 때는 AddComponent 함수를 사용해야 합니다.
	// 3. Mesh, Material 객체 생성 시 new 키워드를 사용해야 합니다.
	
	//Mesh 객체 생성
	Mesh* isoPolyMesh = new Mesh(isoPolyvert, isoPolyidx);
	Mesh* rightPolyMesh = new Mesh(rightPolyvert, rightPolyidx);
	Mesh* rectMesh = new Mesh(rectvert, Rectidx);
	Mesh* regularPolyMesh = new Mesh(regularPolyvert, regularPolyidx);

	Material* bgMaterial = new Material(shaders["Standard"]);
	bgMaterial->SetVec4("tColor", vec4(0.3f, 0.3f, 0.3f, 1.0f));

	Object* bgObject = Instantiate(ctx, "Background");
	bgObject->AddComponent<MeshRenderer3D>(rectMesh, bgMaterial);
	Transform* bgTr = bgObject->GetComponent<Transform>();
	bgTr->SetLocalPosition(-0.7f, 0.0f, 0.0f);
	bgObject->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f })->isDebug = true;

	bgObject = Instantiate(ctx, "Background");
	bgObject->AddComponent<MeshRenderer3D>(rectMesh, bgMaterial);
	bgTr = bgObject->GetComponent<Transform>();
	bgTr->SetLocalPosition(-0.2f, 0.0f, 0.0f);
	bgObject->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f })->isDebug = true;

	Object* borderObj = Instantiate(ctx, "Border");
	borderObj->AddComponent<Spline>(rectCP, vec4{ 0.0f, 0.0f, 1.0f, 1.0f }, 3.0f);
	Transform* borderTr = borderObj->GetComponent<Transform>();
	borderTr->SetLocalPosition(-0.45f, 0.0f, 0.0f);
	borderObj->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f, 0.3f, 1.0f });

	Object* rectGeneratorObj = Instantiate(ctx, "RectGenerator");

}