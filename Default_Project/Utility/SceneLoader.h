#pragma once
#include "../Common.h"
#include <json.hpp>
#include "gl/glm/glm.hpp"
using namespace std;
using namespace glm;
using json = nlohmann::json;

class SceneLoader {
public:
	map<string, Mesh*> meshChache;
	map<string, Material*> materialChache;

	//생성자에서 mesh, material, shader 캐시를 받아와서 초기화
	SceneLoader(map<string, Mesh*> meshCache, map<string, Material*> materialCache, map<string, GLuint> shaderCache)
		: meshChache(meshCache), materialChache(materialCache), shaderChache(shaderCache) {}

	void LoadScene(AppContext& ctx, const string& sceneFile);

private:
	void AttachComponent(Object* obj, const json& compData);
};