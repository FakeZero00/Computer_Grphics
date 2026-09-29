#include "Major.h"
#include "MeshRenderer3D.h"
#include "Object.h"
#include "Transform.h"
#include "Spline.h"
#include "Material.h"
#include <gl/glm/gtc/quaternion.hpp>

#include "ShapeMovement.h"

void Major::MakeParticle() {
	Transform* tr = gameObject->GetComponent<Transform>();
	MeshRenderer3D* mr = gameObject->GetComponent<MeshRenderer3D>();
	vec4 color = mr->materials[0]->GetVec4("tColor");
	Object* particleObj = tr->parent->gameObject->Instantiate("Particle");
	Transform* ptr = particleObj->GetComponent<Transform>();
	ptr->SetLocalPosition(tr->position.x, tr->position.y, tr->position.z - 0.1f);
	particleObj->AddComponent<Spline>(particleControlPoints, color, 3.0f);
	particleObj->AddComponent<ShapeMovement>();
}

void Major::OnTriggerEnter(Object* other) {
	cout << "Major collided with " << other->name << endl;
	MakeParticle();
	Mesh* currentMesh;
	MeshRenderer3D* mr = gameObject->GetComponent<MeshRenderer3D>();
	MeshRenderer3D* otherMr = other->GetComponent<MeshRenderer3D>();
	quat currentRotation;
	vec3 currentScale;
	Transform* tr = gameObject->GetComponent<Transform>();
	Transform* otherTr = other->GetComponent<Transform>();

	currentMesh = mr->mesh;
	mr->mesh = otherMr->mesh;
	otherMr->mesh = currentMesh;

	currentScale = tr->scale;
	currentRotation = tr->rotation;
	tr->scale = otherTr->scale;
	tr->rotation = otherTr->rotation;
	otherTr->scale = currentScale;
	otherTr->rotation = currentRotation;

	tr->CalculateWorldMatrix();
	otherTr->CalculateWorldMatrix();
}