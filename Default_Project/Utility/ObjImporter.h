#pragma once
#include <vector>
#include <GL/glew.h>
#include <string>
#include "Vertex.h"
using namespace std;

vector<Vertex> GetVerticesFromObj(vector<vector<string>>& objData);
vector<GLubyte> GetIndicesFromObj(vector<vector<string>>& objData);