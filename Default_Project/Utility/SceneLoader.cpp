#include "SceneLoader.h"
#include <fstream>

void SceneLoader::LoadScene(AppContext& ctx, const string& sceneFile) {
	ifstream in{ sceneFile };
	if (not in) {
		cout << "json 파일을 읽지 못했습니다: " << sceneFile << endl;
		return;
	}

	json sceneData;
	in >> sceneData;

	map<string, Object*> spawnedObjects;

	//[Pass 1] 모든 오브젝트 생성
	for (const auto& objData : sceneData["Objects"]) {
		string name = objData["name"];
		Object* newObj = Instantiate(ctx, name);
		spawnedObjects[name] = newObj;

		//Transform 설정
		Transform* tr = newObj->GetComponent<Transform>();
		auto pos = objData["transform"]["position"];
		auto rot = objData["transform"]["rotation"];
		auto scale = objData["transform"]["scale"];

		tr->SetLocalPosition(pos[0], pos[1], pos[2]);
		tr->SetLocalRotation(rot[0], rot[1], rot[2]);
		tr->SetLocalScale(scale[0], scale[1], scale[2]);
	}

	//[Pass 2] 부모 연결 및 모든 컴포넌트 추가
	for (const auto& objData : sceneData["Objects"]) {
		string name = objData["name"];
		Object* obj = spawnedObjects[name];
		//부모 연결
		if (objData.contains("parent")) {
			string parentName = objData["parent"];
			if (spawnedObjects.find(parentName) != spawnedObjects.end()) {
				Transform* parentTr = spawnedObjects[parentName]->GetComponent<Transform>();
				obj->GetComponent<Transform>()->SetParent(parentTr);
			}
		}
		//컴포넌트 추가
		if (objData.contains("components")) {
			for (const auto& compData : objData["components"]) {
				Object* targetObj = spawnedObjects[objData["name"]];

				AttachComponent(targetObj, compData);
			}
		}
	}
}

void SceneLoader::AttachComponent(Object* obj, const json& compData) {
	string type = compData["type"];
	const json& props = compData.contains("properties") ? compData["properties"] : compData;

	if (type == "BoxCollider") {
		if (props.contains("center") && props.contains("size")) {
			cout << obj->name << " 오브젝트의 BoxCollider 컴포넌트에 center와 size 속성이 필요합니다." << endl;
		}
		auto center = props["center"];
		auto size = props["size"];
		BoxCollider* boxCol = obj->AddComponent<BoxCollider>(vec3{center[0], center[1], center[2]},
			vec3(size[0], size[1], size[2]));
		if (props.contains("isDebug")) boxCol->isDebug = props["isDebug"];
	}
	else if (type == "Camera") {
		int width = props.contains("width") ? static_cast<int>(props["width"]) : screenSize.width;
		int height = props.contains("height") ? static_cast<int>(props["height"]) : screenSize.height;

		Camera* cam = obj->AddComponent<Camera>(width, height);
		if (props.contains("fov")) cam->fov = props["fov"];
		if (props.contains("nearPlane")) cam->nearPlane = props["nearPlane"];
		if (props.contains("farPlane")) cam->farPlane = props["farPlane"];
	}
	else if (type == "MeshRenderer3D") {
		if (props.contains("mesh") == false || props.contains("materials") == false) {
			cout << obj->name << " 오브젝트의 MeshRenderer3D 컴포넌트에 mesh와 materials 속성이 필요합니다." << endl;
			return;
		}

		auto matData = props["materials"][0];
		Material* material = materialChache[matData];

		if (matData.contains("boolUniforms")) {
			for (auto& [key, val] : matData["boolUniforms"].items()) {
				material->SetBool(key, val);
			}
		}
		if (matData.contains("intUniforms")) {
			for (auto& [key, val] : matData["intUniforms"].items()) {
				material->SetInt(key, val);
			}
		}
		if (matData.contains("floatUniforms")) {
			for (auto& [key, val] : matData["floatUniforms"].items()) {
				material->SetFloat(key, val);
			}
		}
		if (matData.contains("vec2Uniforms")) {
			for (auto& [key, val] : matData["vec2Uniforms"].items()) {
				material->SetVec2(key, vec2(val[0], val[1]));
			}
		}
		if (matData.contains("vec3Uniforms")) {
			for (auto& [key, val] : matData["vec3Uniforms"].items()) {
				material->SetVec3(key, vec3(val[0], val[1], val[2]));
			}
		}
		if (matData.contains("vec4Uniforms")) {
			for (auto& [key, val] : matData["vec4Uniforms"].items()) {
				material->SetVec4(key, vec4(val[0], val[1], val[2], val[3]));
			}
		}

		MeshRenderer3D* meshRenderer = obj->AddComponent<MeshRenderer3D>(meshChache[props["mesh"]], material);
	}
	else if (type == "Spline") {
		if(props.contains("controlPoints") == false || props.contains("color") == false) {
			cout << obj->name << " 오브젝트의 Spline 컴포넌트에 controlPoints와 color 속성이 필요합니다." << endl;
			return;
		}

		vector<vec3> controlPoints;
		for (int i = 0; i < props["controlPoints"].size(); i = i + 3) {
			vec3 point{ props["controlPoints"][i], props["controlPoints"][i + 1], props["controlPoints"][i + 2] };
			controlPoints.push_back(point);
		}
		vec4 colorVec{ props["color"][0], props["color"][1], props["color"][2], props["color"][3] };

		Spline* spline = obj->AddComponent<Spline>(controlPoints, colorVec);
		if (props.contains("lineWidth")) spline->lineWidth = props["lineWidth"];
	}
	else if (type == "SceneCamera") {
		obj->AddComponent<SceneCamera>();
	}
}

Object*	SceneLoader::Instantiate(AppContext& ctx, string objName) {
	auto newObj = make_unique<Object>(ctx, objName);
	Object* ptr = newObj.get();

	ctx.Hierarchy.push_back(move(newObj));
	return ptr;
}