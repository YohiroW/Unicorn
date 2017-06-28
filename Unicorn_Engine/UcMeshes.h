#ifndef _UC_MESHES_H_
#define _UC_MESHES_H_
//
#include <GL/glew.h>
#include <vector>
#include <assimp/Importer.hpp>      // assimp importer interface
#include <assimp/scene.h>           // putput data structure
#include <assimp/postprocess.h>     // post processing flags
//
#include "UcVector2.h"
#include "UcCamera.h"
#include "UcTextureMgr.h"
#include "UcRenderableObject.h"

namespace Unicorn
{
	struct Vertex
	{
		Vector3 m_pos;
		Vector2 m_tex;
		Vector3 m_normal;

		Vertex() {}

		Vertex(const Vector3& pos, const Vector2& tex, const Vector3& normal)
		{
			m_pos = pos;
			m_tex = tex;
			m_normal = normal;
		}
	};


	class Meshes : public RenderableObject
	{
	public:
		Meshes();
		~Meshes();

		bool initialize(const std::string& Filename);

		virtual void onPreRender(Camera* cam);
		virtual void draw(float dt);
		virtual void onPostRender();
		virtual void destroy();

	private:
		//
		bool _initFromScene(const aiScene* pScene, const std::string& Filename);
		void _initMeshes(unsigned int Index, const aiMesh* paiMeshes);
		bool _initMaterials(const aiScene* pScene, const std::string& Filename);
		void _clear();

#define INVALID_MATERIAL 0xFFFFFFFF

		struct MeshEntry
		{
			MeshEntry();
			~MeshEntry();

			bool initialize(const std::vector<Vertex>& Vertices,
				const std::vector<unsigned int>& Indices);

			GLuint vbo;
			GLuint  ebo;
			unsigned int indicesNum;
			unsigned int materialIndex;
		};

		std::vector<MeshEntry> _entries;
		std::vector<Texture*> _textures;
	};
}

#endif