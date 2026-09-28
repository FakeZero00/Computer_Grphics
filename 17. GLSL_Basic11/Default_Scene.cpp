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

	Object* shapeGeneratorObj = Instantiate(ctx, "ShapeGenerator");
	shapeGeneratorObj->AddComponent<ShapeGenerator>(regularPolyMesh, rightPolyMesh, rectMesh, regularPolyCP, rightPolyCP, rectCP);

	vector<vec3> controlPoints = {
		vec3(0.55f, 1.0f, 0.0f),
		vec3(0.55f, -1.0f, 0.0f),
	};
	Object* borderObj = Instantiate(ctx, "Border");
	borderObj->AddComponent<Spline>(controlPoints, vec4{0.0f, 1.0f, 0.0f, 1.0f});
}