#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <strstream>
#include "vec.h"
#include "triangle.h"
#include "Error.h"


struct Mesh
{
	friend class MeshManager;
public:
	Mesh(std::string filePath) { loadObj(filePath); };

	std::vector<triangle> tris;

	bool loadObj(std::string filePath)
	{
		std::ifstream fin;
		fin.open(filePath, std::ios::in);

		if (fin.fail())
		{
			Error::fatalError("There was an error opening the obj file at:\n" + filePath);
			return false;
		}

		std::vector<vec3> verts;

		std::string line;
		while (std::getline(fin, line))
		{
			std::strstream s;
			s << line;

			char prefix;

			if (line[0] == 'v')
			{
				vec3 v;
				s >> prefix >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}

			if (line[0] == 'f')
			{
				int f[3];
				s >> prefix >> f[0] >> f[1] >> f[2];
				
				triangle t = { verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] };
				tris.push_back(t);
			}
		}

		return true;
	}

	// Getter.
	int getId() { return m_id; }

private:
	int m_id;

	// Private setter for Mesh Manager.
	void setId(int id) { m_id = id; }
};