#include "SceneLoader.h"

void SceneLoader::AttachComponent(Object* obj, const json& compData) {
	string type = compData["type"];

	if (type == "BoxCollider") {
		auto center = compData["center"];
		auto size = compData["size"];
		BoxCollider* boxCol = obj->AddComponent<BoxCollider>(vec3{center[0], center[1], center[2]},
			vec3(size[0], size[1], size[2]));
		if (compData.contains("isDebug")) boxCol->isDebug = compData["isDebug"];
	}
	else if (type == "Camera") {
		Camera* cam = obj->AddComponent<Camera>(compData["width"], compData["height"]);
		if (compData.contains("fov")) cam->fov = compData["fov"];
		if (compData.contains("nearPlane")) cam->nearPlane = compData["nearPlane"];
		if (compData.contains("farPlane")) cam->farPlane = compData["farPlane"];
	}
	else if (type == "MeshRenderer3D") {
		auto matData = compData["materials"][0];
		Material* material = materialChache[matData];

		if (matData.contains("vec4Uniforms")) {
			for (auto& [key, val] : matData["vec4Uniforms"].items()) {
				material->SetVec4()
			}
		}

		MeshRenderer3D* meshRenderer = obj->AddComponent<MeshRenderer3D>(meshChache[compData["mesh"]], materialChache[compData["material"]]);
	}
}