/********************************************************************
	created:	2017/01/17
	filename: 	Unicorn.h
	file ext:	h
	author:		Yohiro  
	
	purpose:	
*********************************************************************/
#ifndef UNICORN_H
#define UNICORN_H
//---------------------
//to prevent from uncompiled
#include "gl/glew.h"
//#include "GLFW/glfw3.h"

//Base
#include "UcApplication.h"
#include "UcPackage.h"
#include "UcViewport.h"
#include "UcGame.h"
#include "UcMacros.h"
#include "UcConfig.h"
#include "UcObject.h"

//Event
#include "UcEvent.h"
#include "UcEventDispatcher.h"
#include "UcEventNode.h"

//Game
#include "UcEntity.h"

//Math
#include "UcMath.h"
#include "UcVector2.h"
#include "UcVector3.h"
#include "UcMatrix.h"
#include "UcQuaternion.h"
#include "UcRay.h"
#include "UcTransform.h"

//Render
#include "UcRenderMgr.h"
#include "UcTextureMgr.h"
#include "UcShaderMgr.h"
#include "UcShader.h"
#include "UcShaderProgram.h"
#include "UcScene.h"
#include "UcCamera.h"
#include "UcRenderableObject.h"
#include "UcRenderData.h"
#include "UcSkybox.h"
#include "UcModel.h"
#include "UcMesh.h"
#include "UcColor.h"
#include "UcLight.h"
#include "UcBillboard.h"
#include "UcParticleMgr.h"
#include "UcParticles.h"
#include "UcText.h"

//debug
#include "UcLogger.h"
using namespace Unicorn;

#endif // UNICORN_H
