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
}

Component* RailGenerator::CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects) {
	RailGenerator* railGenerator = obj->AddComponent<RailGenerator>();

	railGenerator->count = props["count"];

	return railGenerator;
}

REGISTER_COMPONENT(RailGenerator)