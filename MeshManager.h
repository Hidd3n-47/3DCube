#pragma once
#include <SDL/SDL.h>
#include "Mesh.h"
#include "Camera.h"

class MeshManager
{
public:
	MeshManager(const MeshManager&) = delete;

	static MeshManager& Instance()
	{
		static MeshManager instance;
		return instance;
	}

	void addMesh(Mesh* mesh);
	bool removeMesh(const int& meshId);

	void renderMeshes(SDL_Renderer* pRenderer, Camera* pCamera);

	void multiplyMatrixVector(const vec3& i, vec3& o, const mat4x4& m);
private:
	MeshManager() {}

	std::vector<Mesh*> m_meshes;
	int m_nextFreeId = 0;
	
	void fillTriangle(const triangle& tri, SDL_Renderer* pRenderer);
};

