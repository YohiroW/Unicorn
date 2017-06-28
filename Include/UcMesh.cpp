#include "UcMesh.h"
#include "UcTextureMgr.h"
#include <iostream>
#include <sstream>
NS_UNICORN;

Mesh::Mesh(VertexList vertexList,
	       TextureList textureList,
	       IndexList indexList)
{
	_vertices = vertexList;
	_textures = textureList;
	_indices = indexList;


	this->_setupMesh();
}

Mesh::~Mesh()
{
}

//in fact, this method is not invoked 
bool Mesh::initialize(VertexList vertexList, TextureList textureList, IndexList indexList)
{
	_vertices = vertexList;
	_textures = textureList;
	_indices = indexList;

	this->_setupMesh();


	return true;
}

void Mesh::drawMesh(ShaderProgram* shader)
{
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;


	for (GLuint i = 0; i < _textures.size(); ++i)
	{
		std::stringstream ss;
		std::string type;
		std::string number;

		glActiveTexture(GL_TEXTURE0 + _textures[i].index);

		type = _textures[i].type;
		if (type == "texture_diffuse")
		{
			ss << diffuseNr++;
		}
		else if (type == "texture_specular")
		{
			ss << specularNr++;
		}
		number = ss.str();

		glUniform1i(glGetUniformLocation(shader->getShaderProgramID(), (type + number).c_str()), _textures[i].index);
		glBindTexture(GL_TEXTURE_2D, _textures[i].index);
	}

	glBindVertexArray(this->_vao);
	glDrawElements(GL_TRIANGLES,_indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//
	for (GLuint i = 0; i < this->_textures.size(); i++)
	{
		glActiveTexture(_textureUnit + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}


void Mesh::_setupMesh()
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	//bind vao first
	glBindVertexArray(_vao);
	//
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexInfo)* _vertices.size(), 
		         &this->_vertices[0], GL_STATIC_DRAW);
	//
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)* _indices.size(),
				 &this->_indices[0], GL_STATIC_DRAW);
	
	//position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, sizeof(VertexInfo), (GLvoid*)0);
	//normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (GLvoid*)offsetof(VertexInfo,normal));
	//texture coordination
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexInfo), (GLvoid*)offsetof(VertexInfo, texCoord));

	//
	glBindVertexArray(0);	
}
