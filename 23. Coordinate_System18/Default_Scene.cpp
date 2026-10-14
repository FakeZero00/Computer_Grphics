#include "Default_Scene.h"
#include "Common.h"
#include "SceneLoader.h"

extern map<string, GLuint> shaders;

//스크립트 불러오기//

/////////////////////

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
	map<string, Mesh*> meshChache = {
		{"Cube", new Mesh("Default_Cube.obj")},
		{"Pyramid", new Mesh("Default_Pyramid.obj")},
		{"Sphere", new Mesh("Default_Sphere.obj")},
		{"Torus", new Mesh("Default_Torus.obj")}
	};

	//Material 객체 생성
	Material* redMat = new Material(shaders["Standard"]);
	redMat->SetVec4("tColor", vec4(1.0f, 0.0f, 0.0f, 1.0f));
	Material* greenMat = new Material(shaders["Standard"]);
	greenMat->SetVec4("tColor", vec4(0.0f, 1.0f, 0.0f, 1.0f));
	Material* blueMat = new Material(shaders["Standard"]);
	blueMat->SetVec4("tColor", vec4(0.0f, 0.0f, 1.0f, 1.0f));

	map<string, Material*> materialChache = {
		{"LocalPosColor", new Material(shaders["LocalPosColor"])},
		{"Red", redMat},
		{"Green", greenMat},
		{"Blue", blueMat}
	};

	SceneLoader sceneLoader{screenSize, meshChache, materialChache };
	sceneLoader.LoadScene(ctx, "Default_Scene.json");

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