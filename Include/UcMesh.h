#ifndef _UC_MESH_H_
#define _UC_MESH_H_
//
#include <gl/glew.h>
//cstd
#include <vector>
//unicorn
#include "UcMacros.h"
#include "UcVector2.h"
#include "UcVector3.h"
#include "UcMatrix.h"
#include "UcShaderProgram.h"
//assimp
#include <assimp/Importer.hpp>

namespace Unicorn
{
	typedef struct
	{
		Vector3 position;
		Vector3 normal;
		Vector2 texCoord;
	}VertexInfo;


	typedef struct
	{
		GLuint index;
		std::string type;
		aiString path;
	}TextureInfo;

	typedef std::vector<VertexInfo> VertexList;
	typedef std::vector<TextureInfo> TextureList;
	typedef std::vector<GLuint> IndexList;

	class Mesh
	{
	public:
		Mesh(VertexList vertexList,
			 TextureList textureList,
			 IndexList indexList);
		~Mesh();
		//
		bool initialize(VertexList vertexList, 
					    TextureList textureList, 
						IndexList indexList);
		//
		void drawMesh(ShaderProgram* shader);
		//	
		

	protected:
		void _setupMesh();

	private:
		VertexList _vertices;
		TextureList _textures;
		IndexList _indices;
		GLuint _vao;
		GLuint _vbo;
		GLuint _ebo;

		GLuint _textureUnit;
	};
}

#endif