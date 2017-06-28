//#ifndef _UC_COM_RENDERER_H_
//#define _UC_COM_RENDERER_H_
////
//#include <vector>
//#include "UcComponent.h"
//
//namespace Unicorn
//{
//	class Mesh;
//
//	//Entity attached with RendererComponent can be rendered to
//	//view, which mean can be visible in the frustum.So,it should
//	//offer vertex data and textures
//	class RendererComponent : public Component
//	{
//	public:
//		typedef std::vector<Mesh> MeshSet;
//
//		enum RenderableShape
//		{
//			SPHERE,
//			CUBE,
//			PANEL
//
//		};
//
//	public:
//		RendererComponent();
//		~RendererComponent();
//		//
//		bool initializeWithModel(const char* modelPath);
//		bool initializeWithShape(RenderableShape shape);
//
//	
//	protected:
//		//type needs being defined
//		void _getCubeVertexData();
//		void _getSphereVertexData();
//	
//	private:
//		MeshSet _meshList;
//
//	};
//}
//
//
//#endif