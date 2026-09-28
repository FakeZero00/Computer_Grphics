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
	Mesh* rectMesh = new Mesh(Rectvert, Rectidx);

	Object* shapeGeneratorObj = Instantiate(ctx, "ShapeGenerator");
	shapeGeneratorObj->AddComponent<ShapeGenerator>(isoPolyMesh);

	//왼쪽 벽
	Object* rectObj_L = Instantiate(ctx, "Rect_L");
	rectObj_L->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
	BoxCollider* col_L = rectObj_L->AddComponent<BoxCollider>( vec3{ 0.0f }, vec3{ 1.0f });
	col_L->isDebug = true;
	Transform* rectTr_L = rectObj_L->GetComponent<Transform>();
	rectTr_L->SetLocalPosition(-1.05f, 0.0f, 0.0f);

	//오른쪽 벽
	Object* rectObj_R = Instantiate(ctx, "Rect_R");
	rectObj_R->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
	BoxCollider* col_R = rectObj_R->AddComponent<BoxCollider>( vec3{ 0.0f }, vec3{ 1.0f });
	col_R->isDebug = true;
	Transform* rectTr_R = rectObj_R->GetComponent<Transform>();
	rectTr_R->SetLocalPosition(1.05f, 0.0f, 0.0f);

	//위쪽 벽
	Object* rectObj_T = Instantiate(ctx, "Rect_T");
	rectObj_T->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
	BoxCollider* col_T = rectObj_T->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f });
	col_T->isDebug = true;
	Transform* rectTr_T = rectObj_T->GetComponent<Transform>();
	rectTr_T->SetLocalRotation(0.0f, 0.0f, 90.0f);
	rectTr_T->SetLocalPosition(0.0f, 1.05f, 0.0f);

	//아래쪽 벽
	Object* rectObj_B = Instantiate(ctx, "Rect_B");
	rectObj_B->AddComponent<MeshRenderer3D>(rectMesh, new Material{ shaders["Standard"] });
	BoxCollider* col_B = rectObj_B->AddComponent<BoxCollider>(vec3{ 0.0f }, vec3{ 1.0f });
	col_B->isDebug = true;
	Transform* rectTr_B = rectObj_B->GetComponent<Transform>();
	rectTr_B->SetLocalRotation(0.0f, 0.0f, 90.0f);
	rectTr_B->SetLocalPosition(0.0f, -1.05f, 0.0f);
}