#pragma once
#include "Component.h"
#include <vector>

class Mesh;
class Material;

class MeshRenderer3D : public Component {
public:
	Mesh* mesh;
	vector<Material*> materials;

	MeshRenderer3D(Mesh* mesh, Material* material);

	void Render() override;
};