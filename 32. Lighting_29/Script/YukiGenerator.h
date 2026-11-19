#pragma once
#include "Component.h"
#include "../AllComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Object.h"
#include <random>
using namespace std;

extern map<string, Mesh*> meshChache;
extern map<string, Material*> materialChache;

class YukiGenerator : public Component {
private:
	Mesh* yukiMesh = meshChache["Sphere"];
	Material* yukiMaterial = materialChache["White"];

	random_device rd;
	default_random_engine dre{ rd() };
	uniform_real_distribution<float> distX{ -11.0f, 11.0f };
	uniform_real_distribution<float> distY{ -0.5f, 0.5f };
	uniform_real_distribution<float> distZ{ -11.0f, 11.0f };
	uniform_real_distribution<float> distSpeed{ 1.0f, 3.0f };

	vector<Object*> yukiObjects;
	vector<float> yukiSpeeds;
	vector<Transform*> yukiTransforms;

	InputManager* inputManager;

	bool isSnow = false;

public:
	void Start() override;
	void Update(float deltaTime) override;

	static Component* CreateFromJson(Object* obj, const json& props, const map<string, Object*>& spawnedObjects);
};