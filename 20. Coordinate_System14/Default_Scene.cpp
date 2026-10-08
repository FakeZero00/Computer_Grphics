#include "Default_Scene.h"
#include "Dataset.h"
#include "Common.h"
#include "Mesh.h"
#include "Material.h"

extern map<string, GLuint> shaders;

//스크립트 불러오기
#include "ObjectManagement.h"

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
	Mesh* cubeMesh = new Mesh("Default_Cube.obj");
	Mesh* pyramidMesh = new Mesh("Default_Pyramid.obj");

	Material* redMat = new Material(shaders["Standard"]);
	redMat->SetVec4("tColor", vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Material* localPosColorMat = new Material(shaders["LocalPosColor"]);

	Object* mainCamera = Instantiate(ctx, "MainCamera");
	mainCamera->AddComponent<Camera>(screenSize.width, screenSize.height);
	Transform* camTr = mainCamera->GetComponent<Transform>();
	camTr->SetLocalPosition(0.0f, 5.0f, -5.0f);
	camTr->SetLocalRotation(45.0f, 0.0f, 0.0f);
	mainCamera->AddComponent<SceneCamera>(45.0f, 0.0f);

	Object* cube = Instantiate(ctx, "Cube");
	cube->AddComponent<MeshRenderer3D>(cubeMesh, localPosColorMat);

	Object* pyramid = Instantiate(ctx, "Pyramid");
	pyramid->AddComponent<MeshRenderer3D>(pyramidMesh, localPosColorMat);

	Object* testObject = Instantiate(ctx, "Descriptor");
	testObject->AddComponent<ObjectManagement>(cube, pyramid);

	//XYZ 축 생성
	DrawAxis(ctx);
}

void Default_Scene::DrawAxis(AppContext& ctx) {
	//XYZ 축 생성
	vector<vec3> lineVertices = {
		vec3(-10.0f, 0.0f, 0.0f),
		vec3(10.0f, 0.0f, 0.0f)
	};

	Object* xAxis = Instantiate(ctx, "X_Axis");
	xAxis->AddComponent<Spline>(lineVertices, vec4(1.0f, 0.0f, 0.0f, 1.0f));

	Object* yAxis = Instantiate(ctx, "Y_Axis");
	yAxis->AddComponent<Spline>(lineVertices, vec4(0.0f, 1.0f, 0.0f, 1.0f));
	yAxis->GetComponent<Transform>()->SetLocalRotation(0.0f, 0.0f, 90.0f);

	Object* zAxis = Instantiate(ctx, "Z_Axis");
	zAxis->AddComponent<Spline>(lineVertices, vec4(0.0f, 0.0f, 1.0f, 1.0f));
	zAxis->GetComponent<Transform>()->SetLocalRotation(0.0f, 90.0f, 0.0f);
}