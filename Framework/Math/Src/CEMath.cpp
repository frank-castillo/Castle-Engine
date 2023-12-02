#include "Precompiled.h"
#include "Math/Inc/CEMath.h"

using namespace CASTLEEngine::CEMath;

const Vector2 Vector2::Zero = Vector2(0.0f);
const Vector2 Vector2::One = Vector2(1.0f);
const Vector2 Vector2::XAxis = Vector2(1.0f, 0.0f);
const Vector2 Vector2::YAxis = Vector2(0.0f, 1.0f);

const Vector3 Vector3::Zero = Vector3(0.0f);
const Vector3 Vector3::One = Vector3(1.0f);
const Vector3 Vector3::XAxis = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::YAxis = Vector3(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::ZAxis = Vector3(0.0f, 0.0f, 1.0f);

const Vector4 Vector4::Zero = Vector4(0.0f);
const Vector4 Vector4::One = Vector4(1.0f);
const Vector4 Vector4::XAxis = Vector4(1.0f, 0.0f, 0.0f, 0.0f);
const Vector4 Vector4::YAxis = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
const Vector4 Vector4::ZAxis = Vector4(0.0f, 0.0f, 1.0f, 0.0f);
const Vector4 Vector4::WAxis = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

const Matrix3 Matrix3::Zero = Matrix3(0.0f);
const Matrix3 Matrix3::Identity = Matrix3(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f);

const Matrix4 Matrix4::Zero = Matrix4(0.0f);
const Matrix4 Matrix4::Identity = Matrix4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);