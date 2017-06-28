#ifndef _UC_MODEL_H_
#define _UC_MODEL_H_
//
#include <gl/glew.h>
#include "UcRenderableObject.h"
#include "UcMesh.h"
#include "UcCamera.h"
//assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace Unicorn
{
	class Model :public RenderableObject
	{
	public:
		typedef std::vector<Mesh> MeshSet;
		typedef std::vector<TextureInfo> TextureInfoSet;

	public:
		Model();
		~Model();
		//
		bool initialize(const char* modelPath);
		//invoked every frame, 
		virtual void onPreRender(Camera* cam);
		virtual void onPostRender();
		virtual void draw(float dt);
		virtual void destroy();
		//
		
	protected:
		Mesh _setupMesh(aiMesh* mesh, const aiScene* scene);
		void _setupNodes(aiNode* node, const aiScene* scene);
		void _loadModel(std::string path);
		TextureInfoSet _loadMaterialTex(aiMaterial* material, aiTextureType textureType, std::string type);
		TextureID _getTextureFromFile(const char* path, std::string directory);	
	private:
		//
		MeshSet _meshList;
		TextureInfoSet _textureLoaded;
		//
		std::string _directory;
		//
		GLint _shaderLoc[6];

	};
}


#endif