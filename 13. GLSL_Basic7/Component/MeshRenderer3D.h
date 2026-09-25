#pragma once
#include "Component.h"

class Mesh;
class Material;

class MeshRenderer3D : public Component {
public:
	Mesh* mesh;
	Material* material;

	MeshRenderer3D(Mesh* mesh, Material* material) : mesh(mesh), material(material) {}

	void Render() override;
};