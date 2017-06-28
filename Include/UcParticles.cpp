#include "UcParticles.h"
#include "UcMath.h"
#include "UcLogger.h"
#include "UcRenderMgr.h"
#include <ctime>
NS_UNICORN;

Particles::Particles() :
RenderableObject(),
_isParticleOn(false),
_particleCount(MAX_PARTICLE_COUNT),
_duration(5.0f),
_color(ColorFRGBA::ORANGE),
_lifeCircle(8.0f),
_vao(INVALID_OGL_VALUE),
_particleColorVBO(INVALID_OGL_VALUE),
_particlePosVBO(INVALID_OGL_VALUE),
_billboardVBO(INVALID_OGL_VALUE),
_lastParicleUnused(0),
_curParticleCount(0)
{

}

Particles::~Particles()
{

}

bool Particles::initialize(const std::string& tex, const Vector3& pos /*= Vector3::ZERO*/)
{
	//
	return this->initialize(TextureMgr::getInstance()->createTexture(tex), pos);
}

bool Particles::initialize(Texture* texture, const Vector3& pos /*= Vector3::ZERO*/)
{
	if (!ShaderMgr::DEFAULT_PARTICLE)
	{
		ShaderMgr::DEFAULT_PARTICLE = ShaderMgr::getInstance()->createShaderProgram(ShaderMgr::DEFAULT_PARTICLE_VS,
																					ShaderMgr::DEFAULT_PARTICLE_FS);
	}
	_shader = ShaderMgr::DEFAULT_PARTICLE;
	_shader->apply();
	_shaderLoc[0] = _shader->getLocation("CameraRight_worldspace", true);
	_shaderLoc[1] = _shader->getLocation("CameraUp_worldspace", true);
	_shaderLoc[2] = _shader->getLocation("VP", true);
	_shaderLoc[3] = _shader->getLocation("myTextureSampler", true);


	if (!texture->load())
	{
		Log("Texture %s cant not be loaded in to memory", texture->getName());
	}

	_particleTexture = texture;
	_position = pos;
	_particleCount = MAX_PARTICLE_COUNT;

	_particleContainer = new ParticleAttr[_particleCount];
	_particleColorBuffer = new GLubyte[_particleCount * 4];
	_particlePosBuffer = new GLfloat[_particleCount * 4];


	for (int i = 0; i < MAX_PARTICLE_COUNT; ++i)
	{
		_particleContainer[i].lifeTime = -1.0f;
		_particleContainer[i].distanceToCam = -1.0f;
	}

	this->_setup();

	return true;
}


void Particles::_setup()
{
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	//
	glGenBuffers(1, &_billboardVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _billboardVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(RenderData::billboard), RenderData::billboard, GL_STATIC_DRAW);

	//
	glGenBuffers(1, &_particlePosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _particlePosVBO);
	glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLE_COUNT* 4* sizeof(float), NULL, GL_STREAM_DRAW);

	//
	glGenBuffers(1, &_particleColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, _particleColorVBO);
	glBufferData(GL_ARRAY_BUFFER, MAX_PARTICLE_COUNT* 4* sizeof(GLubyte), NULL, GL_STREAM_DRAW);

}

void Particles::onPreRender(Camera* cam)
{
	//set up shaders
	_shader->apply();

	Matrix4x4 viewMatrix = cam->getViewMatrix();
	_shader->setVector3(_shaderLoc[0], Vector3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]), true);
	_shader->setVector3(_shaderLoc[1], Vector3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]), true);
	_shader->setMatrix4(_shaderLoc[2], cam->getProjectionMatrix()* cam->getViewMatrix(), true);

	_particleTexture->bind();
	_shader->setInterger(_shaderLoc[3], _particleTexture->getTextureHandler(), true);

	_viewPoint = inverse(viewMatrix)[3];
}

void Particles::draw(float dt)
{
	this->_setupParticles(dt);

	this->_updateParticles(dt, _viewPoint);

	//setup particle position buffer
	glBindBuffer(GL_ARRAY_BUFFER, _particlePosVBO);
	glBufferData(GL_ARRAY_BUFFER, _particleCount * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(GLfloat)* 4, _particlePosBuffer);

	//setup particle color buffer
	glBindBuffer(GL_ARRAY_BUFFER, _particleColorVBO);
	glBufferData(GL_ARRAY_BUFFER, _particleCount * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, _particleCount * sizeof(GLubyte)* 4, _particleColorBuffer);

	//the particles might be transparent so.
	glEnable(GL_BLEND);
	//linear blend
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	this->_renderParticles();

}

void Particles::onPostRender()
{
	_particleTexture->unbind();
	_curParticleCount = 0;
}

void Particles::destroy()
{
	if (_particleColorVBO != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &_particleColorVBO);
	}

	if (_particlePosVBO != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &_particlePosVBO);
	}

	if (_billboardVBO != INVALID_OGL_VALUE)
	{
		glDeleteBuffers(1, &_billboardVBO);
	}

	if (_vao != INVALID_OGL_VALUE)
	{
		glDeleteVertexArrays(1, &_vao);
	}

	if (_particleTexture)
	{
		_particleTexture->destroy();
	}


	UCSafeDelete(_particleContainer);
	UCSafeDelete(_particlePosBuffer);
	UCSafeDelete(_particleColorBuffer);
}

void Particles::_updateParticles(const float& dt, const Vector3& camPos)
{
	for (int i = 0; i < _particleCount; ++i)
	{
		ParticleAttr& particle = _particleContainer[i];
		if (particle.lifeTime > 0.0f)
		{
			particle.lifeTime -= dt;
			if (particle.lifeTime > 0.0f)
			{
				//only simulate the gravity
				particle.speed = particle.speed + Vector3(0.0f, -9.81f, 0.0f) * dt * 0.5f;
				particle.position = particle.position + particle.speed* dt;	
				//Log("");
				particle.distanceToCam = Math::getLength2(particle.position - camPos);
				//particle.position = particle.position + Vector3(0.0f,10.0f, 0.0f) * dt;

				//fill up with gpu buffers
				_particlePosBuffer[4 * _curParticleCount + 0] = particle.position.x;
				_particlePosBuffer[4 * _curParticleCount + 1] = particle.position.y;
				_particlePosBuffer[4 * _curParticleCount + 2] = particle.position.z;
				_particlePosBuffer[4 * _curParticleCount + 3] = particle.size;

				_particleColorBuffer[4 * _curParticleCount + 0] = particle.r;
				_particleColorBuffer[4 * _curParticleCount + 1] = particle.g;
				_particleColorBuffer[4 * _curParticleCount + 2] = particle.b;
				_particleColorBuffer[4 * _curParticleCount + 3] = particle.a;

			}
			else
			{
				particle.distanceToCam = -1.0f;
			}
			++_curParticleCount;
		}//end if
	}//end for

	this->_sortParticles();
}

int Particles::_getParticleUnused()
{
	for (int i = _lastParicleUnused; i < _particleCount; ++i)
	{
		if (_particleContainer[i].lifeTime < 0)
		{
			_lastParicleUnused = i;
			return i;
		}
	}

	for (int i = 0; i < _lastParicleUnused; ++i)
	{
		if (_particleContainer[i].lifeTime < 0)
		{
			_lastParicleUnused = i;
			return i;
		}
	}

	return 0;
}

void Particles::_sortParticles()
{
	std::sort(&_particleContainer[0], &_particleContainer[_particleCount]);
}

void Particles::_setupParticles(float dt)
{
	//1/60 sec => 0.016
	int particlesReborn = (int)(dt * 10000.0);
	if (particlesReborn > (int)(0.016f * 10000.0))
	{
		particlesReborn = (int)(0.016f * 10000.0);
	}

	for (int i = 0; i < particlesReborn; ++i)
	{
		int particleIndex = this->_getParticleUnused();
		_particleContainer[particleIndex].lifeTime = _lifeCircle;
		_particleContainer[particleIndex].position = _position;

		float spreadFactor = 2.5f;
		Vector3 castDir = Vector3(0.0f, 10.0f, 0.0f);

		Vector3 randomDir = Vector3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f);

		_particleContainer[particleIndex].speed = castDir + randomDir* spreadFactor;

		_particleContainer[particleIndex].r = rand() % 256;
		_particleContainer[particleIndex].g = rand() % 256;
		_particleContainer[particleIndex].b = rand() % 256;
		_particleContainer[particleIndex].a = (rand() % 256) / 3;

		_particleContainer[particleIndex].size = (rand() % 1000) / 2000.0f + 0.1f;
	}

}

void Particles::_renderParticles()
{
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _billboardVBO);
	glVertexAttribPointer(
		0,                 
		3,               
		GL_FLOAT,        
		GL_FALSE,          
		0,                  
		(void*)0            
		);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _particlePosVBO);
	glVertexAttribPointer(
		1,                             
		4,                               
		GL_FLOAT,                  
		GL_FALSE,                    
		0,                                
		(void*)0                         
		);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _particleColorVBO);
	glVertexAttribPointer(
		2,                           
		4,                               
		GL_UNSIGNED_BYTE,                 
		GL_TRUE,                       
		0,                                
		(void*)0                      
		);


	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1); 
	glVertexAttribDivisor(2, 1);

	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, _curParticleCount);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

//
////default static varaibles
////--------------------------------------------
//const int Particles::MAX_PARTICLE_COUNT = 1000;
//
////
//Particles::Particles() :
//RenderableObject(),
//_isParticleOn(false),
//_particleCount(MAX_PARTICLE_COUNT),
//_duration(0.0f),
//_color(ColorFRGBA::ORANGE),
//_velocity(Vector3(0.0f,0.02f,0.0f)),
//_particleTexture(NULL),
//_billboardShader(NULL),
//_currentVB(0),
//_currentTF(1)
//{
//	MEM_SET_ZERO(_transformFeedback);
//	MEM_SET_ZERO(_particleBuffers);
//}
//
//Particles::~Particles()
//{
//
//}
//
//bool Particles::initialize(const std::string& tex, const Vector3& pos /* = Vector3::ZERO */)
//{
//	if (!_shader)
//		_shader = ShaderMgr::DEFAULT_PARTICLE;
//	if (!_billboardShader)
//		_billboardShader = ShaderMgr::DEFAULT_BILLBOARD;
//	//
//	_transform.setPosition(pos);
//	_particleTexture = TextureMgr::getInstance()->createTexture(tex);
//
//	//TODO:
//	//default formulation of particles
//	SimpleParticleAttr particles[MAX_PARTICLE_COUNT];
//	MEM_SET_ZERO(particles);
//
//	//just initialize the first particle as launcher
//	particles[0].type = ParticleType::LAUNCHER;
//	particles[0].position = pos;
//	particles[0].velocity = _velocity;
//	particles[0].duration = 0.0f;
//	
//	//generate transformfeedback buffers
//	glGenTransformFeedbacks(2, _transformFeedback);
//	glGenBuffers(2, _particleBuffers);
//
//	for (int i = 0; i < 2; ++i)
//	{
//		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _transformFeedback[i]);
//		glBindBuffer(GL_ARRAY_BUFFER, _particleBuffers[i]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_DYNAMIC_DRAW);
//		glBindBufferBase(GL_TRANSFORM_FEEDBACK, 0, _transformFeedback[i]);
//	}
//	//end TODO
//
//
//	return true;
//}
//
//bool Particles::initialize(Texture* texture, const Vector3& pos /* = Vector3::ZERO */)
//{
//	//_shader -> particle shader
//	if (!_shader)
//		_shader = ShaderMgr::DEFAULT_PARTICLE;
//	//
//	_transform.setPosition(pos);
//	_particleTexture = texture;
//
//	//TODO:
//	//default formulation of particles
//	SimpleParticleAttr particles[MAX_PARTICLE_COUNT];
//	MEM_SET_ZERO(particles);
//
//	//just initialize the first particle as launcher
//	particles[0].type = ParticleType::LAUNCHER;
//	particles[0].position = pos;
//	particles[0].velocity = _velocity;
//	particles[0].duration = 0.0f;
//
//	//generate transformfeedback buffers
//	glGenTransformFeedbacks(2, _transformFeedback);
//	glGenBuffers(2, _particleBuffers);
//
//	for (int i = 0; i < 2; ++i)
//	{
//		glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _transformFeedback[i]);
//		glBindBuffer(GL_ARRAY_BUFFER, _particleBuffers[i]);
//		glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_DYNAMIC_DRAW);
//		glBindBufferBase(GL_TRANSFORM_FEEDBACK, 0, _transformFeedback[i]);
//	}
//	//end TODO
//	
//	return true;
//}
//
//void Particles::onPreRender(Camera* cam)
//{
//
//	_transform.setModel(cam->getProjectionMatrix()* 
//		                cam->getViewMatrix());
//	
//	
//
//}
//
//void Particles::draw()
//{
//	_duration += RenderMgr::DELTA_TIME;
//	this->_updateParticles(RenderMgr::DELTA_TIME);
//	
//	_currentVB = _currentTF;
//	_currentTF = (_currentTF + 1) & 0x1;
//}
//
//void Particles::onPostRender()
//{
//
//}
//
//void Particles::destroy()
//{
//	_shader->destroy();
//	UCSafeDelete(_shader);
//
//	_particleTexture->destroy();
//	UCSafeDelete(_particleTexture);
//
//	if (_transformFeedback[0] != 0)
//	{
//		glDeleteBuffers(2, _transformFeedback);
//	}
//
//	if (_particleBuffers[0] != 0)
//	{
//		glDeleteBuffers(2, _particleBuffers);
//	}
//
//}
//
//Vector3 Particles::getPosition() const
//{
//	return _transform.Position();
//}
//
//void Particles::setPosition(const Vector3& pos)
//{
//	_transform.setPosition(pos);
//}
//
////------protected------
//
//void Particles::_updateParticles(float dt)
//{
//	//set particle(updated) shader uniforms
//	this->_setupParticleShader(dt);
//
//	//dicard rasterization, so that we can do it ourselves
//	glEnable(GL_RASTERIZER_DISCARD);
//	
//	glBindBuffer(GL_ARRAY_BUFFER, _particleBuffers[_currentVB]);
//	//when this method is invoked, all the results rendered will be reserved  into transformfeedback buffers
//	glBindBuffer(GL_TRANSFORM_FEEDBACK, _transformFeedback[_currentTF]);
//
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glEnableVertexAttribArray(2);
//	glEnableVertexAttribArray(3);
//
//	glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(SimpleParticleAttr), 0);                          // type
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleParticleAttr), (const GLvoid*)4);           // position
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(SimpleParticleAttr), (const GLvoid*)16);          // velocity
//	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(SimpleParticleAttr), (const GLvoid*)28);          // lifetime
//	
//
//	//setup transform feedback
//	glBeginTransformFeedback(GL_POINTS);
//
//	if (!_isParticleOn)
//	{
//		glDrawArrays(GL_POINTS, 0 ,1);
//		_isParticleOn = true;
//	}
//	else
//	{
//		glDrawTransformFeedback(GL_POINTS, _transformFeedback[_currentVB]);
//	}
//
//	glEndTransformFeedback();
//
//	//disable vertex attribute
//	glDisableVertexAttribArray(0);
//	glDisableVertexAttribArray(1);
//	glDisableVertexAttribArray(2);
//	glDisableVertexAttribArray(3);
//}
//
//void Particles::_renderParticles(Camera* cam)
//{
//	//set billboard shader uniforms
//	this->_setupBillboardShader(cam);
//
//	glDisable(GL_RASTERIZER_DISCARD);
//
//	glBindBuffer(GL_ARRAY_BUFFER, _particleBuffers[_currentTF]);
//
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(SimpleParticleAttr), (const GLvoid*)4);
//	
//	//draw
//	glDrawTransformFeedback(GL_POINTS, _transformFeedback[_currentTF]);
//	
//	//disable
//	glDisableVertexAttribArray(0);
//}
//
//bool Particles::_setupParticleShader(float dt)
//{
//	//set shader uniforms
//	_shader->apply();
//
//	//uniforms from VS or GS
//	const GLchar* varyings[4];
//	varyings[0] = "Type1";
//	varyings[1] = "Position1";
//	varyings[2] = "Velocity1";
//	varyings[3] = "Age1";
//
//	//
//	glTransformFeedbackVaryings(_shader->getShaderProgramID(),4,varyings, GL_INTERLEAVED_ATTRIBS);
//
//
//	_shader->setFloat("gDeltaTimeMillis", dt, true);
//	_shader->setFloat("gTime", Game::getInstance()->getTime(), true);
//	_shader->setFloat("gLauncherLifetime", _duration, true);
//	_shader->setFloat("gShellLifetime", _lifeCircle, true);
//	_shader->setFloat("gSecondaryShellLifetime", _lifeCircle* 0.5f, true);
//	_shader->setInterger("gRandomTexture", _particleTexture->getTextureHandler(), true);
//
//	return true;
//}
//
//bool Particles::_setupBillboardShader(Camera* cam)
//{
//	_billboardShader->apply();
//
//	_billboardShader->setMatrix4("gVP", _transform.getModel(), true);
//	_billboardShader->setVector3("gCameraPos", cam->getPosition(), true);
//
//
//	return true;
//}
//
//RandomTexture* Particles::_createRandomTexture(const int& size)
//{
//	RandomTexture* rndTex = new RandomTexture();
//	if (rndTex && rndTex->initialize(size))
//	{
//		_randomTexture = rndTex;
//		return rndTex;
//	}
//	else
//	{
//		UCSafeDelete(rndTex);
//		return NULL;
//	}
//}
//
