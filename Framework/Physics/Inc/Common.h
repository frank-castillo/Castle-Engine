#pragma once

// Referencing things here. Framework headers. <> to reference files not in the project. "" reference internal files in the project
#include <Math/Inc/CEMath.h>
#include <Core/Inc/Core.h>
#include <Graphics/Inc/Colors.h>
#include <Graphics/Inc/Transform.h>

// Bullet files
#include <Bullet/btBulletCollisionCommon.h>
#include <Bullet/btBulletDynamicsCommon.h>

template<class T>
inline void SafeDelete(T*& ptr)
{
    if (ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
}

inline btVector3 ConvertTobtVector3(const CASTLEEngine::CEMath::Vector3& vec)
{
    return { vec.x, vec.y, vec.z };
}

inline CASTLEEngine::CEMath::Vector3 ConvertToVector3(const btVector3& vec)
{
    return { vec.x(), vec.y(), vec.z() };
}

inline btQuaternion ConvertTobtQuaternion(const CASTLEEngine::CEMath::Quaternion& q)
{
    return { q.x, q.y, q.z, q.w };
}

inline CASTLEEngine::CEMath::Quaternion ConvertToQuaternion(const btQuaternion& q)
{
    return { q.x(), q.y(), q.z(), q.w()};
}

inline CASTLEEngine::Color ConvertToColor(const btVector3& btColor)
{
    return { btColor.x(), btColor.y(), btColor.z(), 1.0f };
}

inline btTransform ConvertTobtTransform(const CASTLEEngine::Graphics::Transform& trans)
{
    return btTransform(ConvertTobtQuaternion(trans.rotation), ConvertTobtVector3(trans.position));
}

inline CASTLEEngine::Graphics::Transform ConvertToTransform(const btTransform& btTrans)
{
    const auto& origin = btTrans.getOrigin();
    const auto& rotation = btTrans.getRotation();
    CASTLEEngine::Graphics::Transform retTrans;
    retTrans.position = ConvertToVector3(origin);
    retTrans.rotation = ConvertToQuaternion(rotation);
    return retTrans;
}

inline void ApplybtTransformToTransform(const btTransform& btTrans, CASTLEEngine::Graphics::Transform& trans)
{
    trans.position = ConvertToVector3(btTrans.getOrigin());
    trans.rotation = ConvertToQuaternion(btTrans.getRotation());
}