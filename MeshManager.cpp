#include "MeshManager.h"
#include <algorithm>
#include "Color.h"
#include "Math.h"

void MeshManager::addMesh(Mesh* mesh)
{
	m_meshes.push_back(mesh);
	m_meshes.back()->setId(m_nextFreeId++);
}

bool MeshManager::removeMesh(const int& meshId)
{
	bool foundMesh = false;

	for (Mesh* mesh : m_meshes)
	{
		if (mesh->getId() != meshId)
			continue;
		foundMesh = true;
		mesh = m_meshes.back();

		delete m_meshes.back();

		m_meshes.pop_back();

		return true;
	}
	
	return false;
}

void MeshManager::renderMeshes(SDL_Renderer* pRenderer, Camera* pCamera)
{
	// Projection Matrix.
	mat4x4 matProj;
	float near = 0.1f;
	float far = 10000.0f;
	float fov = 90.0f;
	float ar = (float)pCamera->getHeight() / (float)pCamera->getWidth();
	float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.14159f);

	matProj.m[0][0] = ar * fovRad;
	matProj.m[1][1] = fovRad;
	matProj.m[2][2] = far / (far - near);
	matProj.m[3][2] = (-far * near) / (far - near);
	matProj.m[2][3] = 1.0f;
	matProj.m[3][3] = ar * fovRad;

	// Roation matrices
	float speed = 0.01f;
	//mat4x4 matRotZ, matRotX;
	float theta = 1.0f * speed;
	/*matRotZ.m[0][0] = cosf(theta);
	matRotZ.m[0][1] = sinf(theta);
	matRotZ.m[1][0] = -sinf(theta);
	matRotZ.m[1][1] = cosf(theta);
	matRotZ.m[2][2] = 1;
	matRotZ.m[3][3] = 1;

	matRotX.m[0][0] = 1;
	matRotX.m[1][1] = cosf(theta * 0.5f);
	matRotX.m[1][2] = sinf(theta * 0.5f);
	matRotX.m[2][1] = -sinf(theta * 0.5f);
	matRotX.m[2][2] = cosf(theta * 0.5f);
	matRotX.m[3][3] = 1;*/

	std::vector<triangle> trisToRender;

	for(Mesh* mesh : m_meshes)
	{
		// Draw triangles.
		for (triangle& tri : mesh->tris)
		{

			// Rotate Z
			for (int i = 0; i < 3; i++)
				Math::rotateZ(tri.vertex[i], theta);

			// Rotate X (total rotation Z X)
			for (int i = 0; i < 3; i++)
				Math::rotateX(tri.vertex[i], theta * 0.5);

			triangle triTransform = tri;
			for (int i = 0; i < 3; i++)
				triTransform.vertex[i].z += 5.0f;

			// Normal calculation.
			vec3 normal, posVec1, posVec2;
			posVec1 = triTransform.vertex[1] - triTransform.vertex[0];
			posVec2 = triTransform.vertex[2] - triTransform.vertex[0];
			/*posVec1 = triTranslated.vertex[1] - triTranslated.vertex[0];
			posVec2 = triTranslated.vertex[2] - triTranslated.vertex[0];*/

			normal.x = posVec1.y * posVec2.z - posVec1.z * posVec2.y;
			normal.y = posVec1.z * posVec2.x - posVec1.x * posVec2.z;
			normal.z = posVec1.x * posVec2.y - posVec1.y * posVec2.x;

			float l = normal.magnitude();
			normal /= l;

			vec3 cameraToTri = triTransform.vertex[0] - pCamera->getPosition();
			//vec3 cameraToTri = triTranslated.vertex[0] - pCamera->getPosition();

			if (normal * cameraToTri < 0.0f)
			{
				// Illuminate the object
				vec3 lightDir = vec3(0.0f, 0.0f, -1.0f);
				l = lightDir.magnitude();
				lightDir /= l;

				float dotProduct = abs(normal * lightDir);

				unsigned char colVal = 255 * dotProduct;
				triTransform.color = Color(colVal, colVal, colVal, 255);
				//triProjected.color = Color(colVal, colVal, colVal, 255);

				// Project from 3D to 2D.
				for (int i = 0; i < 3; i++)
					Math::multiplyMatrixVector(triTransform.vertex[i], matProj);
				//Math::multiplyMatrixVector(triTranslated.vertex[i], triProjected.vertex[i], matProj);

				// Scale into view;
				for (int i = 0; i < 3; i++)
					triTransform.vertex[i] += vec3(1.0f, 1.0f, 0.0f);
				//triProjected.vertex[i] += vec3(1.0f, 1.0f, 0.0f);

				for (int i = 0; i < 3; i++)
				{
					triTransform.vertex[i].x *= 0.5 * (float)pCamera->getWidth();
					triTransform.vertex[i].y *= 0.5 * (float)pCamera->getHeight();
					/*triProjected.vertex[i].x *= 0.5 * (float)pCamera->getWidth();
					triProjected.vertex[i].y *= 0.5 * (float)pCamera->getHeight();*/
				}

				trisToRender.push_back(triTransform);
				//trisToRender.push_back(triProjected);
			}
	}

		sort(trisToRender.begin(), trisToRender.end(), [](triangle& t1, triangle& t2)
			{
				float z1 = (t1.vertex[0].z + t1.vertex[1].z + t1.vertex[2].z) / 3.0f;
		float z2 = (t2.vertex[0].z + t2.vertex[1].z + t2.vertex[2].z) / 3.0f;

		return z1 > z2;
			});

		for (const triangle& triProjected : trisToRender)
		{
			// Draw triangle by drawing lines
			SDL_RenderDrawLine(pRenderer, triProjected.vertex[0].x, triProjected.vertex[0].y,
				triProjected.vertex[1].x, triProjected.vertex[1].y);

			SDL_RenderDrawLine(pRenderer, triProjected.vertex[1].x, triProjected.vertex[1].y,
				triProjected.vertex[2].x, triProjected.vertex[2].y);

			SDL_RenderDrawLine(pRenderer, triProjected.vertex[2].x, triProjected.vertex[2].y,
				triProjected.vertex[0].x, triProjected.vertex[0].y);
			fillTriangle(triProjected, pRenderer);
		}
	}
}

void MeshManager::fillTriangle(const triangle& tri, SDL_Renderer* pRenderer)
{
	vec3 v1, v2, v3;
	short margineErrorLeft = 2.0;
	short margineErrorRight = margineErrorLeft;

	short highestVert = 1000000;
	short highestVertIndex = 0;
	for (int i = 0; i < 3; i++)
	{
		if (tri.vertex[i].y < highestVert)
		{
			highestVert = tri.vertex[i].y;
			highestVertIndex = i;
		} 
	}
	v1 = tri.vertex[highestVertIndex];
	if (tri.vertex[Math::mod3(highestVertIndex - 1)].y < tri.vertex[Math::mod3(highestVertIndex + 1)].y)
	{
		v2 = tri.vertex[Math::mod3(highestVertIndex - 1)];
		v3 = tri.vertex[Math::mod3(highestVertIndex + 1)];
	}
	else
	{
		v2 = tri.vertex[Math::mod3(highestVertIndex + 1)];
		v3 = tri.vertex[Math::mod3(highestVertIndex - 1)];
	}

	float m1 = (v3.y - v1.y) / (v3.x - v1.x);
	float m2;

	margineErrorLeft *= Math::sign(m1);

	short numVertPixles =  abs(v3.y - v1.y);
	short y, xleft, xright;
	for (int i = 1; i < numVertPixles; i++)
	{
		y = v1.y + i;
		xleft = (y - v1.y) / m1 + v1.x;

		if (y < v2.y)
		{
			m2 = (v1.y - v2.y) / (v1.x - v2.x);
			xright = (y - v2.y) / m2 + v2.x;
		}
		else
		{
			m2 = (v3.y - v2.y) / (v3.x - v2.x);
			xright = ((y - v2.y) / m2 + v2.x);
		}

		margineErrorRight *= Math::sign(m2);

		SDL_SetRenderDrawColor(pRenderer, tri.color.r, tri.color.g,tri.color.b, 255);
		SDL_RenderDrawLineF(pRenderer, xleft, y, xright, y);
	}
}

