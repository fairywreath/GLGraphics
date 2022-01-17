#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>

#include "../shading/Texture.h"
#include "../shading/ShaderProgram.h"

class Mesh
{
public:
	enum class TOPOLOGY
	{
		POINTS,
		LINES,
		LINE_STRIP,
		TRIANGLES,
		TRIANGLE_STRIP,
		TRIANGLE_FAN,
	};
	
	Mesh();
	virtual ~Mesh();

	virtual void init();
	void draw() const;


public:
	static constexpr int ATTRIBUTE_POSITION = 0;
	static constexpr int ATTRIBUTE_NORMAL = 1;
	static constexpr int ATTRIBUTE_TEXCOORDS = 2;
	static constexpr int ATTRIBUTE_TANGENT = 3;
	static constexpr int ATTRIBUTE_BITANGENT = 4;

	std::vector<glm::vec3> Positions;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec3> Tangents;
	std::vector<glm::vec3> Bitangents;

	std::vector<glm::vec2> TexCoords;
	
	std::vector<unsigned int> Indices;

	std::vector<Texture> Textures;

	TOPOLOGY Topology = TOPOLOGY::TRIANGLES;
	GLuint VAO;

	ShaderProgram* pShader = nullptr;

private:
	GLuint mVerticesVBO;
	GLuint mNormalsVBO;
	GLuint mTexCoordsVBO;

	GLuint mEBO;
};



#endif