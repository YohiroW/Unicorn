#ifndef _UC_SKYBOX_H
#define _UC_SKYBOX_H
//
#include <vector>
#include "UcTexture.h"
#include "UcRenderData.h"
#include "UcRenderableObject.h"

namespace Unicorn
{
	class Camera;

	//default: cube skybox
	class Skybox: public RenderableObject
	{
	public:
		//
		static const int MAX_QUAD_COUNT;
		//
		static const char*	DEFAULT_SKYBOX_RIGHT;
		static const char*	DEFAULT_SKYBOX_LEFT;
		static const char*	DEFAULT_SKYBOX_TOP;
		static const char*	DEFAULT_SKYBOX_BOTTOM;
		static const char*	DEFAULT_SKYBOX_BACK;
		static const char*	DEFAULT_SKYBOX_FRONT;
		//
		enum FaceIndex
		{
			FI_RIGHT = 0,    //+x 
			FI_LEFT,         //-x
			FI_TOP,			 //+y
			FI_BOTTOM,		 //-y
			FI_BACK,         //+z
			FI_FRONT 		 //-z
		};

	public:
		Skybox();
		~Skybox();
		//
		bool initialize(const char* right = DEFAULT_SKYBOX_RIGHT, 
			            const char* left = DEFAULT_SKYBOX_LEFT,
						const char* top = DEFAULT_SKYBOX_TOP, 
						const char* bottom = DEFAULT_SKYBOX_BOTTOM,
						const char* back = DEFAULT_SKYBOX_BACK, 
						const char* front = DEFAULT_SKYBOX_FRONT);

		//override
		virtual void onPreRender(Camera* cam);
		virtual void onPostRender();
		virtual void draw(float dt);
		virtual void destroy();
		//
		TextureID getSkyboxMapHandler() const;


	protected:
		//
		void _setup();
		//ref to array in private
		TextureID _loadeCubeMap(std::vector<const GLchar*> faces);
		//
		void _bindCubeMaps();
		void _unbindCubeMaps();


	private:
		//        2-top
		//1-left  5-front  0-right  4-back          
		//        3-bottom
		std::vector<const GLchar*> _skyboxFaces;
		//skybox buffers
		GLuint _skyboxVAO, _skyboxVBO;
		//
		TextureID _cubeMapTexHadl;
		//
		GLint _shaderLoc[2];
	};
}


#endif