#include "UcModel.h"
#include "UcTextureMgr.h"
#include "UcLogger.h" 
NS_UNICORN;

Model::Model():
RenderableObject()
{
}

Model::~Model()
{
}

bool Model::initialize(const char* modelPath)
{
	_shader = ShaderMgr::DEFAULT_MODEL;
	
	_shaderLoc[0] = _shader->getLocation("model");
	_shaderLoc[1] = _shader->getLocation("view");
	_shaderLoc[2] = _shader->getLocation("projection");
	_shaderLoc[3] = _shader->getLocation("lightPos");

	
	this->_loadModel(modelPath);

	return true;
}

Mesh Model::_setupMesh(aiMesh* mesh, const aiScene* scene)
{
	VertexList vertices;
	TextureInfoSet textures;
	IndexList indices;

	//
	for (GLuint i = 0; i < mesh->mNumVertices; ++i)
	{
		VertexInfo vertex;
		Vector3 vec;
		//position
		vec.x = mesh->mVertices[i].x;
		vec.y = mesh->mVertices[i].y;
		vec.z = mesh->mVertices[i].z;
		vertex.position = vec;

		//normal
		if (mesh->mNormals)
		{
			vec.x = mesh->mNormals[i].x;
			vec.y = mesh->mNormals[i].y;
			vec.z = mesh->mNormals[i].z;
			vertex.normal = vec;
		}
		else
		{
			vertex.normal = Vector3::IDENTITY;
		}
	
		//vec.x = mesh->mNormals[i].x;
		//vec.y = mesh->mNormals[i].y;
		//vec.z = mesh->mNormals[i].z;
		//vertex.normal = vec;
		
		//texture coordination
		if (mesh->mTextureCoords[0])
		{
			Vector2 texCoord;
			texCoord.x = mesh->mTextureCoords[0][i].x;
			texCoord.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = texCoord;
		}                                   
		else
		{
			vertex.texCoord = Vector2();
		}
		vertices.push_back(vertex);
	}

	//indices
	for (GLuint i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	//we got problem
	//materials
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		TextureList diffuseTex = _loadMaterialTex(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseTex.begin(), diffuseTex.end());

		TextureList specularTex = _loadMaterialTex(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularTex.begin(), specularTex.end());
	}

	return Mesh(vertices, textures, indices);
}

void Model::_loadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene* aiscene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	//
	if (aiscene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !aiscene || !aiscene->mRootNode)
	{
		//log error
		Log("ERROR: LOAD MODEL FAILED, SEE %s", importer.GetErrorString());
		return;
	}

	this->_directory = path.substr(0, path.find_last_of('/'));
	this->_setupNodes(aiscene->mRootNode, aiscene);
}

void Model::_setupNodes(aiNode* node, const aiScene* scene)
{
	for (GLuint i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		_meshList.push_back(this->_setupMesh(mesh, scene));
	}
	for (GLuint i = 0; i < node->mNumChildren; ++i)
	{
		this->_setupNodes(node->mChildren[i], scene);
	}
}

Model::TextureInfoSet Model::_loadMaterialTex(aiMaterial* material, aiTextureType textureType, std::string type)
{

	TextureList textures;
	for (GLuint i = 0; i < material->GetTextureCount(textureType); ++i)
	{
		aiString str;

		material->GetTexture(textureType, i, &str);
		GLboolean skip = false;
		//
		for (GLuint j = 0; j < _textureLoaded.size(); ++j)
		{
			if (strcmp(_textureLoaded[j].path.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(_textureLoaded[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			TextureInfo texture;
			//std::string filePath(_directory + "/ " + str.C_Str());
			texture.index = this->_getTextureFromFile(str.C_Str(),this->_directory);
			texture.path = str;
			texture.type = type;

			textures.push_back(texture);
			this->_textureLoaded.push_back(texture);
		}
	}

	return textures;
}

void Model::onPreRender(Camera* cam)
{
	_shader->apply();

	_shader->setMatrix4(_shaderLoc[0], _transform.getModel(), true);
	_shader->setMatrix4(_shaderLoc[1], cam->getViewMatrix(), true);
	_shader->setMatrix4(_shaderLoc[2], cam->getProjectionMatrix(), true);
	_shader->setVector3(_shaderLoc[3], _lightPos, true);
}

void Model::onPostRender()
{

}

void Model::draw(float dt)
{
	for (Mesh iter : _meshList)
	{
		iter.drawMesh(_shader);
	}
}

void Model::destroy()
{
	delete this;
	//

}

TextureID Model::_getTextureFromFile(const char* path, std::string directory)
{
	//Generate texture ID and load texture data 
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	GLuint textureID;
	glGenTextures(1, &textureID);

	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
	
	return textureID; 
}
