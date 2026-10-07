#include "Default_Scene.h"
#include "Dataset.h"
#include "Common.h"
#include "Mesh.h"
#include "Material.h"

extern map<string, GLuint> shaders;

//스크립트 불러오기
#include "ObjectRotate.h"

Default_Scene::Default_Scene(ScreenSize screenSize) {
	name = "Default_Scene";
	this->screenSize = screenSize;
}

void Default_Scene::LoadScene(AppContext& ctx) {
	//함수 작성 주의사항:
	// 1. Instantiate 함수를 사용하여 Object를 생성해야 합니다.
	// 2. Object에 컴포넌트를 추가할 때는 AddComponent 함수를 사용해야 합니다.
	// 3. Mesh, Material 객체 생성 시 new 키워드를 사용해야 합니다.
	
	//Mesh 객체 생성
	Mesh* isoPolyMesh = new Mesh(isoPolyvert, isoPolyidx);
	Mesh* rightPolyMesh = new Mesh(rightPolyvert, rightPolyidx);
	Mesh* rectMesh = new Mesh(rectvert, rectidx);
	Mesh* rectMesh2 = new Mesh(rectvert2, rectidx);
	Mesh* regularPolyMesh = new Mesh(regularPolyvert, regularPolyidx);

	Material* material = new Material(shaders["Standard"]);
	material->SetVec4("tColor", vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Material* material2 = new Material(shaders["Standard"]);
	material2->SetVec4("tColor", vec4(0.0f, 1.0f, 0.0f, 1.0f));

	Object* mainCamera = Instantiate(ctx, "MainCamera");
	mainCamera->AddComponent<Camera>(screenSize.width, screenSize.height);
	Transform* camTr = mainCamera->GetComponent<Transform>();
	camTr->SetLocalPosition(0.0f, 5.0f, -3.0f);
	camTr->SetLocalRotation(30.0f, 0.0f, 0.0f);
	mainCamera->AddComponent<SceneCamera>(30.0f, 0.0f);

	Object* testObject = Instantiate(ctx, "Test");
	testObject->AddComponent<MeshRenderer3D>(rectMesh, material);
	Transform* testTr = testObject->GetComponent<Transform>();
	testTr->SetLocalPosition(0.0f, 0.0f, 3.0f);
	testTr->SetLocalRotation(0.0f, 180.0f, 0.0f);

	Object* testObject2 = Instantiate(ctx, "Test");
	testObject2->AddComponent<MeshRenderer3D>(rectMesh, material2);
	Transform* testTr2 = testObject2->GetComponent<Transform>();
	testTr2->SetLocalPosition(0.0f, 0.0f, 4.0f);
	testTr2->SetLocalRotation(0.0f, 180.0f, 0.0f);
	testObject2->AddComponent<ObjectRotate>();

	vector<vec3> lineVertices = {
		vec3(-10.0f, 0.0f, 0.0f),
		vec3(10.0f, 0.0f, 0.0f)
	};

	//XYZ 축 생성
	Object* xAxis = Instantiate(ctx, "X_Axis");
	xAxis->AddComponent<Spline>(lineVertices, vec4(1.0f, 0.0f, 0.0f, 1.0f));
	
	Object* yAxis = Instantiate(ctx, "Y_Axis");
	yAxis->AddComponent<Spline>(lineVertices, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	yAxis->GetComponent<Transform>()->SetLocalRotation(0.0f, 0.0f, 90.0f);

	Object* zAxis = Instantiate(ctx, "Z_Axis");
	zAxis->AddComponent<Spline>(lineVertices, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	zAxis->GetComponent<Transform>()->SetLocalRotation(0.0f, 90.0f, 0.0f);
}