#include "Mesh.h"
#include <iostream>

Mesh::Mesh() :
	VAO(0),
	mVerticesVBO(0),
	mNormalsVBO(0),
	mTexCoordsVBO(0),
	mEBO(0)
{
}

Mesh::~Mesh()
{
}

void Mesh::init()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &mVerticesVBO);
	glGenBuffers(1, &mNormalsVBO);
	glGenBuffers(1, &mTexCoordsVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(VAO);
	
	// vertices positions
	if (Positions.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mVerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, Positions.size() * sizeof(Positions[0]), &Positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(Mesh::ATTRIBUTE_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Positions[0]), (void*)0);
		glEnableVertexAttribArray(Mesh::ATTRIBUTE_POSITION);
	}

	// normals
	if (Normals.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mNormalsVBO);
		glBufferData(GL_ARRAY_BUFFER, Normals.size() * sizeof(Normals[0]), &Normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(Mesh::ATTRIBUTE_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Normals[0]), (void*)0);
		glEnableVertexAttribArray(Mesh::ATTRIBUTE_NORMAL);
	}

	// tex coords
	if (TexCoords.size() > 0) {
		glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, TexCoords.size() * sizeof(TexCoords[0]), &TexCoords[0], GL_STATIC_DRAW);
		glVertexAttribPointer(Mesh::ATTRIBUTE_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(TexCoords[0]), (void*)0);
		glEnableVertexAttribArray(Mesh::ATTRIBUTE_TEXCOORDS);
	}

	// indices
	if (Indices.size() > 0) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);
	}

	// unbind vao
	glBindVertexArray(0);
}

void Mesh::draw() const
{
	if (pShader == nullptr) {
		return;
	}

	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	for (int i = 0; i < Textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
		std::string number;
		std::string name = "";
		if (Textures[i].Type == Texture::TYPE::DIFFUSE) {
			name = "texture_diffuse";
			number = std::to_string(diffuseNr++);
		}
		else if (Textures[i].Type == Texture::TYPE::SPECULAR) {
			name = "texture_specular";
			number = std::to_string(specularNr++);
		}

		pShader->setFloat(("material." + name + number).c_str(), (float)i);
		glBindTexture(GL_TEXTURE_2D, Textures[i].getID());
	}

	// only indexed triangles for now
	glBindVertexArray(VAO);

	if (Indices.size() > 0) {
		switch (Topology) {
			case TOPOLOGY::TRIANGLES:
				glDrawElements(GL_TRIANGLES, (GLsizei)Indices.size(), GL_UNSIGNED_INT, 0);
				break;
			case TOPOLOGY::TRIANGLE_STRIP:
				glDrawElements(GL_TRIANGLE_STRIP, (GLsizei)Indices.size(), GL_UNSIGNED_INT, 0);
				break;
			default:
				glDrawElements(GL_TRIANGLES, (GLsizei)Indices.size(), GL_UNSIGNED_INT, 0);
				break;
		}
	}
	else if (Positions.size() > 0) {
		switch (Topology) {
			case TOPOLOGY::TRIANGLES:
				glDrawArrays(GL_TRIANGLES, 0, Positions.size());
				break;
			case TOPOLOGY::TRIANGLE_STRIP:
				glDrawArrays(GL_TRIANGLE_STRIP, 0, Positions.size());
				break;
			default:
				glDrawArrays(GL_TRIANGLES, 0, Positions.size());
				break;
		}
	}
	else {
		std::cout << "WARNING::MESH:: No vertices present.\n";
	}


	glBindVertexArray(0);
}
