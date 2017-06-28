#ifndef _UC_PARTICLES_H_
#define _UC_PARTICLES_H_
//
#include "UcRenderableObject.h"
#include "UcShaderMgr.h"
#include "UcTextureMgr.h"
#include "UcRenderMgr.h"
#include "UcVector3.h"
#include "UcGame.h"

#include "UcRandomTexture.h"

namespace Unicorn
{
	//use transform feedback
	class Particles: public RenderableObject
	{
	public:
		//

		//
		enum ParticleType
		{
			LAUNCHER,			//particle launcher will not fade with life circle 
			SHELL,
			SECONDARUSHELL
		};

		//
		struct ParticleAttr
		{
			Vector3 position;
			
			Vector3 speed;
			//color
			unsigned char r, g, b, a; 

			float size, angle, weight;
			float lifeTime;
			float distanceToCam; 

			//sort by distance, the farthest will be drawed firstly 
			bool operator <(const ParticleAttr& that) const 
			{
				return this->distanceToCam > that.distanceToCam;
			}
		};

	public:
		//csn & dcsn
		Particles();
		~Particles();
		
		//
		bool initialize(const std::string& tex, const Vector3& pos = Vector3::ZERO);
		bool initialize(Texture* texture, const Vector3& pos = Vector3::ZERO);
		
		//overridable method
		virtual void onPreRender(Camera* cam);
		virtual void onPostRender();
		virtual void draw(float dt);
		virtual void destroy();

		//setter & getter
		GEN_SGET_FUNC_INLINE(Vector3, _velocity, Velocity);
		GEN_SGET_FUNC_INLINE(unsigned int, _particleCount, ParticleCount);
		GEN_SGET_FUNC_INLINE(float, _lifeCircle, LifeCircle);
		GEN_SGET_FUNC_INLINE(ColorFRGBA, _color, ParticleColor);
		GEN_SGET_FUNC_INLINE_UNCON(Texture*, _particleTexture, ParticleTexture);

	protected:
		//
		void _setup();

		//to update counter and switch buffers
		void _updateParticles(const float& dt, const Vector3& camPos);
		void _renderParticles();
		
		int _getParticleUnused();
		void _setupParticles(float dt);
		void _sortParticles();

	private:
		//
		GLint _shaderLoc[4];
	
		//------basement------
		ParticleAttr* _particleContainer;
		GLfloat* _particlePosBuffer;
		GLubyte* _particleColorBuffer;


		//to mark if the particle has generated
		bool _isParticleOn;

		//more attributes need to be added
		unsigned int _particleCount;

		//the time a single particle can exist.
		float _lifeCircle;

		//running time
		float _duration;

		//TODO: to use float as each color weight
		ColorFRGBA _color;

		//initial velocity.
		Vector3 _velocity;
		Vector3 _position;
		Vector3 _viewPoint;

		//
		Texture* _particleTexture;
		

		//
		int _lastParicleUnused;
		int _curParticleCount;
		
		//-----Render Resources-----
		GLuint _vao;
		GLuint _billboardVBO;
		GLuint _particlePosVBO;
		GLuint _particleColorVBO;



	};
}

#endif