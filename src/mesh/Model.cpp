#include "Model.h"

#include <iostream>

Model::Model()
{
}

Model::Model(const std::string& path)
{
	loadModel(path);
}

void Model::init()
{
	for (auto& mesh : mMeshes) {
		mesh.pShader = pShader;
		mesh.init();
	}
}

void Model::drawCurrent()
{
	for (auto& mesh : mMeshes) {
		mesh.draw();
	}
}

void Model::loadModel(const std::string& path)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
		return;
	}
	mDirectory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	std::cout << "number of meshes: " << node->mNumMeshes << "\n";
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		mMeshes.push_back(processMesh(mesh, scene));
	}

	std::cout << "number of children: " << node->mNumChildren << "\n";

	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	Mesh res;

	std::cout << "start mesh processing, num of vertices: " << mesh->mNumVertices << "\n";

	// process mesh
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		glm::vec3 vec;

		// vert positions
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		res.Positions.push_back(vec);

		// normals
		if (mesh->mNormals != nullptr) {
			vec.x = mesh->mNormals[i].x;
			vec.y = mesh->mNormals[i].y;
			vec.z = mesh->mNormals[i].z;
			res.Normals.push_back(vec);
		}

		// tex coords
		glm::vec2 uv(0.0f, 0.0f);
		if (mesh->mTextureCoords[0] != nullptr) // does the mesh contain texture coordinates?
		{
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
		}
		res.TexCoords.push_back(uv);
	};

	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			res.Indices.push_back(face.mIndices[j]);
	}

	//std::cout << "done initial mesh processing\n";

	// process material
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		res.Textures.insert(res.Textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		res.Textures.insert(res.Textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return res;
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string filename = mDirectory + '/' + str.C_Str();
		std::cout << "texture filename: " << filename << std::endl;

		if (mLoadedTextures.find(filename) != mLoadedTextures.end()) {
			continue;
		}

		Texture texture;
		if (!texture.load(filename)) {
			continue;
		}

		if (typeName == "texture_diffuse") {
			texture.Type = Texture::TYPE::DIFFUSE;
		}
		else if (typeName == "texture_specular") {
			texture.Type = Texture::TYPE::SPECULAR;

		}
		//texture.path = str;
		textures.push_back(texture);
		mLoadedTextures.insert(filename);
	}
	return textures;
}

