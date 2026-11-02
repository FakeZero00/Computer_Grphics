#include "BallGenerator.h"
#include "Object.h"

#include "BallMovement.h"

extern map<string, Mesh*> meshChache;
extern map<string, Material*> materialChache;

void BallGenerator::Start() {
	for (int i = 0; i < count; ++i) {
		Object* ball = gameObject->Instantiate("Ball");
		ball->AddComponent<MeshRenderer3D>(meshChache["Sphere"], materialChache["LocalPosColor"]);
		ball->AddComponent<BallMovement>();
	}
}

Component* BallGenerator::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	BallGenerator* ballGenerator = obj->AddComponent<BallGenerator>();
	
	if (props.contains("count")) {
		ballGenerator->count = props["count"].get<int>();
	}

	return ballGenerator;
}

REGISTER_COMPONENT(BallGenerator);