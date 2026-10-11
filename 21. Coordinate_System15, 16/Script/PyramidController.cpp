#include "PyramidController.h"
#include "Object.h"
#include "Transform.h"
#include "MeshRenderer3D.h"
#include "Material.h"

extern map<string, GLuint> shaders;

void PyramidController::Start() {
	Material* localPosColorMat = new Material(shaders["LocalPosColor"]);

	for (int i = 0; i < 4; ++i) {
		Object* parentCenter = gameObject->Instantiate("ParentCenter_" + to_string(i));
		objects.push_back(parentCenter);
		Transform* parentCenterTr = parentCenter->GetComponent<Transform>();
		parentCenterTr->SetLocalRotation(0.0f, 90.0f * (float)i, 0.0f);

		Object* lineCenter = parentCenter->Instantiate("LineCenter_" + to_string(i));
		Transform* lineCenterTr = lineCenter->GetComponent<Transform>();
		lineCenterTr->SetLocalPosition(0.0f, 0.0f, 1.0f);
		lineCenterTr->SetLocalRotation(-63.5f, 0.0f, 180.0f);
		
		Object* polygon = lineCenter->Instantiate("Polygon_" + to_string(i));
		polygon->AddComponent<MeshRenderer3D>(meshes["Triangle"], localPosColorMat);
		Transform* polygonTr = polygon->GetComponent<Transform>();
		polygonTr->SetLocalPosition(0.0f, 0.0f, -2.236f);
		polygonTr->SetLocalRotation(-90.0f, 0.0f, 0.0f);
	}

	floorObject = gameObject->Instantiate("Floor");
	floorObject->AddComponent<MeshRenderer3D>(meshes["Plane"], localPosColorMat);
	objects.push_back(floorObject);
}

void PyramidController::Update(float deltaTime) {
	// Update logic for the pyramid controller can be added here
}