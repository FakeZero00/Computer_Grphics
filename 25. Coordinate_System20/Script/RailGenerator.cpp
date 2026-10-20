#include "RailGenerator.h"
#include "Object.h"

#include "RailMovement.h"

extern map<string, Mesh*> meshChache;
extern map<string, Material*> materialChache;

void RailGenerator::Start() {
	float len1 = glm::distance(startPos1, endPos1);
	float len2 = 1.5f;
	float len3 = glm::distance(startPos2, endPos2);
	float totalLen = len1 + len2 + len3;

	// 전체 거리를 개수만큼 균등하게 나눈 간격
	float offset = totalLen / float(count);

	for (int i = 0; i < count; i++) {
		cout << offset * i << endl;
		Object* rail = gameObject->Instantiate("Rail_" + to_string(i));
		MeshRenderer3D* mr = rail->AddComponent<MeshRenderer3D>(meshChache["Rail"], materialChache["DarkGray"]);
		rail->AddComponent<RailMovement>(offset * i, startPos1, endPos1, startPos2, endPos2);
	}

	float cubeOffset = totalLen / 5.0f;

	Object* cube = gameObject->Instantiate("Cube1");
	cube->AddComponent<MeshRenderer3D>(meshChache["Cube"], materialChache["Red"]);
	Object* cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cube->AddComponent<RailMovement>(0.0f, startPos1, endPos1, startPos2, endPos2);

	cube = gameObject->Instantiate("Cube2");
	cube->AddComponent<MeshRenderer3D>(meshChache["Cube"], materialChache["Green"]);
	cube->AddComponent<RailMovement>(cubeOffset, startPos1, endPos1, startPos2, endPos2);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	Transform* cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(0.05f, 0.0f, 0.0f);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(-0.05f, 0.0f, 0.0f);

	cube = gameObject->Instantiate("Cube3");
	cube->AddComponent<MeshRenderer3D>(meshChache["Cube"], materialChache["Blue"]);
	cube->AddComponent<RailMovement>(cubeOffset * 2.0f, startPos1, endPos1, startPos2, endPos2);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(0.1f, 0.0f, 0.0f);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(-0.1f, 0.0f, 0.0f);

	cube = gameObject->Instantiate("Cube4");
	cube->AddComponent<MeshRenderer3D>(meshChache["Cube"], materialChache["Orange"]);
	cube->AddComponent<RailMovement>(cubeOffset * 3.0f, startPos1, endPos1, startPos2, endPos2);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(0.05f, 0.0f, 0.0f);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(0.15f, 0.0f, 0.0f);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(-0.05f, 0.0f, 0.0f);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(-0.15f, 0.0f, 0.0f);

	cube = gameObject->Instantiate("Cube5");
	cube->AddComponent<MeshRenderer3D>(meshChache["Cube"], materialChache["Purple"]);
	cube->AddComponent<RailMovement>(cubeOffset * 4.0f, startPos1, endPos1, startPos2, endPos2);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(0.1f, 0.0f, 0.0f);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(0.2f, 0.0f, 0.0f);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(-0.1f, 0.0f, 0.0f);
	cubeNumber = cube->Instantiate("Cube_Number");
	cubeNumber->AddComponent<MeshRenderer3D>(meshChache["Cube_Number"], materialChache["Black"]);
	cubeNumberTr = cubeNumber->GetComponent<Transform>();
	cubeNumberTr->SetLocalPosition(-0.2f, 0.0f, 0.0f);
}

Component* RailGenerator::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	RailGenerator* railGenerator = obj->AddComponent<RailGenerator>();

	railGenerator->count = props["count"];

	return railGenerator;
}

REGISTER_COMPONENT(RailGenerator)