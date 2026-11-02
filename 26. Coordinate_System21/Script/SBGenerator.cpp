#include "SBGenerator.h"
#include "Object.h"

extern map<string, Mesh*> meshChache;
extern map<string, Material*> materialChache;

void SBGenerator::Start() {
	Object* ball = gameObject->Instantiate("SB1");
	ball->AddComponent<MeshRenderer3D>(meshChache["Box"], materialChache["LocalPosColor"]);
	Transform* tr = ball->GetComponent<Transform>();
	tr->SetLocalScale(0.3f, 0.3f, 0.3f);
}

Component* SBGenerator::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	SBGenerator* sbGenerator = obj->AddComponent<SBGenerator>();

	return sbGenerator;
}

REGISTER_COMPONENT(SBGenerator);