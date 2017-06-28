#ifndef _UC_TRANCSFORM_H_
#define _UC_TRANCSFORM_H_
//
#include "UcVector3.h"
#include "UcMatrix.h"

namespace Unicorn
{
	class Transform
	{
	public:
		//
		Transform();
		Transform(Matrix4x4 model);
		~Transform();
		//
		void transformTo(Transform parent);
		void transformTo(Matrix4x4 mat);
		//
		void setModel(const Matrix4x4& mat);
		Matrix4x4 getModel();
		//
		Matrix4x4 getMVP() const;
		//
		Matrix4x4 translate(const Matrix4x4& mat4,const Vector3& vec);
		Matrix4x4 translate(const Vector3& vec);
		//rotate with clockwise
		//the former two func use quaternion to rotate, late use euler
		Matrix4x4 rotate(const Matrix4x4& mat4,const float& degree, const Vector3& axis);
		Matrix4x4 rotate(const float& degree, const Vector3& axis);
		Matrix4x4 rotateWithEuler(const Vector3& euler);
		//

		Matrix4x4 scale(const Matrix4x4& mat4, const Vector3& scaleFactor);
		Matrix4x4 scale(const Vector3& scaleFactor);
		
		//
		Vector3 Position() const;
		Vector3 Scale() const;
		Vector3 Euler() const;
		//
		void setPosition(const Vector3& pos);
	
	private:
		//
		Matrix4x4 _model;
		//transform attribute
		Vector3 _position;
		Vector3 _scale;
		Vector3 _euler;
	};
}



#endif