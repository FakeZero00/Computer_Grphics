#pragma once
#include "../Common.h"
#include <json.hpp>
#include "gl/glm/glm.hpp"
using namespace std;
using namespace glm;
using json = nlohmann::json;

class SceneLoader {
public:
	ScreenSize screenSize;
	map<string, Mesh*> meshChache;
	map<string, Material*> materialChache;

	//생성자에서 mesh, material 캐시를 받아와서 초기화
	SceneLoader(ScreenSize screenSize, map<string, Mesh*> meshCache, map<string, Material*> materialCache)
		: screenSize(screenSize), meshChache(meshCache), materialChache(materialCache) {}

	void LoadScene(AppContext& ctx, const string& sceneFile);

private:
	void AttachComponent(Object* obj, const json& compData, map<string, Object*> spawnedObjects);
	Object* Instantiate(AppContext& ctx, string objName);
};