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

	int horizontal, vertical;

	cout << "가로 칸 개수: ";
	cin >> horizontal;
	cout << "세로 칸 개수: ";
	cin >> vertical;
	

	Object* shapeGeneratorObj = Instantiate(ctx, "ShapeGenerator");
	shapeGeneratorObj->AddComponent<ShapeGenerator>(regularPolyMesh, rectMesh, horizontal, vertical);

	vector<vec3> controlPoints = {
		vec3(-1.0f, 0.0f, 0.0f),
		vec3(1.0f, 0.0f, 0.0f),
	};
	for (int i = 0; i < horizontal; i++) {
		float y = -1.0f + (2.0f / horizontal) * (i + 1);
		Object* borderObj = Instantiate(ctx, "Border");
		borderObj->AddComponent<Spline>(controlPoints, vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		Transform* borderTr = borderObj->GetComponent<Transform>();
		borderTr->SetLocalPosition(0.0f, y, 1.0f);
	}
	for (int i = 0; i < vertical; i++) {
		float x = -1.0f + (2.0f / vertical) * (i + 1);
		Object* borderObj = Instantiate(ctx, "Border");
		borderObj->AddComponent<Spline>(controlPoints, vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
		Transform* borderTr = borderObj->GetComponent<Transform>();
		borderTr->SetLocalPosition(x, 0.0f, 1.0f);
		borderTr->SetLocalRotation(0.0f, 0.0f, 90.0f);
	}
}