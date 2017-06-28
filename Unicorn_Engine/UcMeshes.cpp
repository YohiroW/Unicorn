#include "UcMeshes.h"
//
using namespace Unicorn;

Meshes::Meshes()
{
}

Meshes::~Meshes()
{
	_clear();
}

bool Meshes::initialize(const std::string& Filename)
{
	// Release the previously loaded mesh (if exists)
	_clear();

	if (!_shader)
		_shader = ShaderMgr::DEFAULT_MODEL;

	bool Ret = false;
	Assimp::Importer Importer;

	const aiScene* pScene = Importer.ReadFile(Filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);

	if (pScene)
	{
		Ret = _initFromScene(pScene, Filename);
	}
	else 
	{
		printf("Error parsing '%s': '%s'\n", Filename.c_str(), Importer.GetErrorString());
	}

	return Ret;
}

void Meshes::onPreRender(Camera* cam)
{
	_shader->apply();

	_shader->setMatrix4("model", _transform.getModel(), true);
	_shader->setMatrix4("view", cam->getViewMatrix(), true);
	_shader->setMatrix4("projection", cam->getProjectionMatrix(), true);

}

void Meshes::draw(float dt)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	for (unsigned int i = 0; i < _entries.size(); i++) 
	{
		glBindBuffer(GL_ARRAY_BUFFER, _entries[i].vbo);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)12);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)20);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _entries[i].ebo);
	
		const unsigned int MaterialIndex = _entries[i].materialIndex;
		
		if (MaterialIndex < _textures.size() && _textures[MaterialIndex]) 
		{
			_textures[MaterialIndex]->bind();
			//_shader->setInterger("texture_diffuse1", _textures[MaterialIndex].getTextureHandler());
		}

		glDrawElements(GL_TRIANGLES, _entries[i].indicesNum, GL_UNSIGNED_INT, 0);
	}//

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Meshes::onPostRender()
{

}

void Meshes::destroy()
{

}

bool Meshes::_initFromScene(const aiScene* pScene, const std::string& Filename)
{
	_entries.resize(pScene->mNumMeshes);
	_textures.resize(pScene->mNumMaterials);

	// Initialize the meshes in the scene one by one
	for (unsigned int i = 0; i < _entries.size(); i++) 
	{
		const aiMesh* paiMesh = pScene->mMeshes[i];
		_initMeshes(i, paiMesh);
	}

	return _initMaterials(pScene, Filename);
}

void Meshes::_initMeshes(unsigned int Index, const aiMesh* paiMeshes)
{
	_entries[Index].materialIndex = paiMeshes->mMaterialIndex;

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> Indices;

	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	for (unsigned int i = 0; i < paiMeshes->mNumVertices; i++) 
	{
		const aiVector3D* pPos = &(paiMeshes->mVertices[i]);
		const aiVector3D* pNormal = &(paiMeshes->mNormals[i]);
		const aiVector3D* pTexCoord = paiMeshes->HasTextureCoords(0) ? &(paiMeshes->mTextureCoords[0][i]) : &Zero3D;

		Vertex v(Vector3(pPos->x, pPos->y, pPos->z),
			     Vector2(pTexCoord->x, pTexCoord->y),
			     Vector3(pNormal->x, pNormal->y, pNormal->z));

		Vertices.push_back(v);
	}

	for (unsigned int i = 0; i < paiMeshes->mNumFaces; i++) 
	{
		const aiFace& Face = paiMeshes->mFaces[i];
		assert(Face.mNumIndices == 3);
		Indices.push_back(Face.mIndices[0]);
		Indices.push_back(Face.mIndices[1]);
		Indices.push_back(Face.mIndices[2]);
	}

	_entries[Index].initialize(Vertices, Indices);
}

bool Meshes::_initMaterials(const aiScene* pScene, const std::string& Filename)
{
	// Extract the directory part from the file name
	std::string::size_type SlashIndex = Filename.find_last_of("/");
	std::string Dir;

	if (SlashIndex == std::string::npos) 
	{
		Dir = ".";
	}
	else if (SlashIndex == 0) 
	{
		Dir = "/";
	}
	else 
	{
		Dir = Filename.substr(0, SlashIndex);
	}

	bool Ret = true;

	// Initialize the materials
	for (unsigned int i = 0; i < pScene->mNumMaterials; i++) 
	{
		const aiMaterial* pMaterial = pScene->mMaterials[i];

		_textures[i] = NULL;

		if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0) 
		{
			aiString Path;

			if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &Path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS) 
			{
				std::string p(Path.data);

				if (p.substr(0, 2) == ".\\") 
				{
					p = p.substr(2, p.size() - 2);
				}

				std::string FullPath = Dir + "/" + p;

				_textures[i] = TextureMgr::getInstance()->createTexture(FullPath.c_str());

				if (!_textures[i]->load())
				{
					printf("Error loading texture '%s'\n", FullPath.c_str());
					_textures[i]->destroy();
					Ret = false;
				}
				else 
				{
					printf("Loaded texture '%s'\n", FullPath.c_str());
				}
			}
		}
	}

	return Ret;
}

void Meshes::_clear()
{
	for (unsigned int i = 0; i < _textures.size(); i++) 
	{
		_textures[i]->destroy();
		UCSafeDelete(_textures[i]);
	}
}

Meshes::MeshEntry::MeshEntry()
{
	vbo = INVALID_OGL_VALUE;
	ebo = INVALID_OGL_VALUE;
	indicesNum = 0;
	materialIndex = INVALID_MATERIAL;
}

Meshes::MeshEntry::~MeshEntry()
{
	if (vbo != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &vbo);
	}

	if (ebo != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &ebo);
	}
}

bool Meshes::MeshEntry::initialize(const std::vector<Vertex>& Vertices, const std::vector<unsigned int>& Indices)
{
	indicesNum = Indices.size();

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* indicesNum, &Indices[0], GL_STATIC_DRAW);

	return GLCheckError();
}
