#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "../scene/SceneNode.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <unordered_set>

class Model : public SceneNode
{
public:
	Model();
	Model(const std::string& path);

	void init() override;
	void loadModel(const std::string& path);

	ShaderProgram* pShader = nullptr;

private:

	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string typeName);

	void drawCurrent() override;

private:
	std::vector<Mesh> mMeshes;
	std::string mDirectory;

	// cache loaded textures for now
	std::unordered_set<std::string> mLoadedTextures;
};



#endif