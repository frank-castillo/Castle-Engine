//this file is autogenerated using stringify.bat (premake --stringify) in the build folder of this project
static const char* solverSetupCL =
    "/*\n"
    "Copyright (c) 2012 Advanced Micro Devices, Inc.  \n"
    "This software is provided 'as-is', without any express or implied warranty.\n"
    "In no event will the authors be held liable for any damages arising from the use of this software.\n"
    "Permission is granted to anyone to use this software for any purpose, \n"
    "including commercial applications, and to alter it and redistribute it freely, \n"
    "subject to the following restrictions:\n"
    "1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.\n"
    "2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.\n"
    "3. This notice may not be removed or altered from any source distribution.\n"
    "*/\n"
    "//Originally written by Takahiro Harada\n"
    "#ifndef B3_CONTACT4DATA_H\n"
    "#define B3_CONTACT4DATA_H\n"
    "#ifndef B3_FLOAT4_H\n"
    "#define B3_FLOAT4_H\n"
    "#ifndef B3_PLATFORM_DEFINITIONS_H\n"
    "#define B3_PLATFORM_DEFINITIONS_H\n"
    "struct MyTest\n"
    "{\n"
    "    int bla;\n"
    "};\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "//keep B3_LARGE_FLOAT*B3_LARGE_FLOAT < FLT_MAX\n"
    "#define B3_LARGE_FLOAT 1e18f\n"
    "#define B3_INFINITY 1e18f\n"
    "#define b3Assert(a)\n"
    "#define b3ConstArray(a) __global const a*\n"
    "#define b3AtomicInc atomic_inc\n"
    "#define b3AtomicAdd atomic_add\n"
    "#define b3Fabs fabs\n"
    "#define b3Sqrt native_sqrt\n"
    "#define b3Sin native_sin\n"
    "#define b3Cos native_cos\n"
    "#define B3_STATIC\n"
    "#endif\n"
    "#endif\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "    typedef float4    b3Float4;\n"
    "    #define b3Float4ConstArg const b3Float4\n"
    "    #define b3MakeFloat4 (float4)\n"
    "    float b3Dot3F4(b3Float4ConstArg v0,b3Float4ConstArg v1)\n"
    "    {\n"
    "        float4 a1 = b3MakeFloat4(v0.xyz,0.f);\n"
    "        float4 b1 = b3MakeFloat4(v1.xyz,0.f);\n"
    "        return dot(a1, b1);\n"
    "    }\n"
    "    b3Float4 b3Cross3(b3Float4ConstArg v0,b3Float4ConstArg v1)\n"
    "    {\n"
    "        float4 a1 = b3MakeFloat4(v0.xyz,0.f);\n"
    "        float4 b1 = b3MakeFloat4(v1.xyz,0.f);\n"
    "        return cross(a1, b1);\n"
    "    }\n"
    "    #define b3MinFloat4 min\n"
    "    #define b3MaxFloat4 max\n"
    "    #define b3Normalized(a) normalize(a)\n"
    "#endif \n"
    "        \n"
    "inline bool b3IsAlmostZero(b3Float4ConstArg v)\n"
    "{\n"
    "    if(b3Fabs(v.x)>1e-6 || b3Fabs(v.y)>1e-6 || b3Fabs(v.z)>1e-6)    \n"
    "        return false;\n"
    "    return true;\n"
    "}\n"
    "inline int    b3MaxDot( b3Float4ConstArg vec, __global const b3Float4* vecArray, int vecLen, float* dotOut )\n"
    "{\n"
    "    float maxDot = -B3_INFINITY;\n"
    "    int i = 0;\n"
    "    int ptIndex = -1;\n"
    "    for( i = 0; i < vecLen; i++ )\n"
    "    {\n"
    "        float dot = b3Dot3F4(vecArray[i],vec);\n"
    "            \n"
    "        if( dot > maxDot )\n"
    "        {\n"
    "            maxDot = dot;\n"
    "            ptIndex = i;\n"
    "        }\n"
    "    }\n"
    "    b3Assert(ptIndex>=0);\n"
    "    if (ptIndex<0)\n"
    "    {\n"
    "        ptIndex = 0;\n"
    "    }\n"
    "    *dotOut = maxDot;\n"
    "    return ptIndex;\n"
    "}\n"
    "#endif //B3_FLOAT4_H\n"
    "typedef  struct b3Contact4Data b3Contact4Data_t;\n"
    "struct b3Contact4Data\n"
    "{\n"
    "    b3Float4    m_worldPosB[4];\n"
    "//    b3Float4    m_localPosA[4];\n"
    "//    b3Float4    m_localPosB[4];\n"
    "    b3Float4    m_worldNormalOnB;    //    w: m_nPoints\n"
    "    unsigned short  m_restituitionCoeffCmp;\n"
    "    unsigned short  m_frictionCoeffCmp;\n"
    "    int m_batchIdx;\n"
    "    int m_bodyAPtrAndSignBit;//x:m_bodyAPtr, y:m_bodyBPtr\n"
    "    int m_bodyBPtrAndSignBit;\n"
    "    int    m_childIndexA;\n"
    "    int    m_childIndexB;\n"
    "    int m_unused1;\n"
    "    int m_unused2;\n"
    "};\n"
    "inline int b3Contact4Data_getNumPoints(const struct b3Contact4Data* contact)\n"
    "{\n"
    "    return (int)contact->m_worldNormalOnB.w;\n"
    "};\n"
    "inline void b3Contact4Data_setNumPoints(struct b3Contact4Data* contact, int numPoints)\n"
    "{\n"
    "    contact->m_worldNormalOnB.w = (float)numPoints;\n"
    "};\n"
    "#endif //B3_CONTACT4DATA_H\n"
    "#ifndef B3_CONTACT_CONSTRAINT5_H\n"
    "#define B3_CONTACT_CONSTRAINT5_H\n"
    "#ifndef B3_FLOAT4_H\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "#endif \n"
    "#endif //B3_FLOAT4_H\n"
    "typedef struct b3ContactConstraint4 b3ContactConstraint4_t;\n"
    "struct b3ContactConstraint4\n"
    "{\n"
    "    b3Float4 m_linear;//normal?\n"
    "    b3Float4 m_worldPos[4];\n"
    "    b3Float4 m_center;    //    friction\n"
    "    float m_jacCoeffInv[4];\n"
    "    float m_b[4];\n"
    "    float m_appliedRambdaDt[4];\n"
    "    float m_fJacCoeffInv[2];    //    friction\n"
    "    float m_fAppliedRambdaDt[2];    //    friction\n"
    "    unsigned int m_bodyA;\n"
    "    unsigned int m_bodyB;\n"
    "    int            m_batchIdx;\n"
    "    unsigned int m_paddings;\n"
    "};\n"
    "//inline    void setFrictionCoeff(float value) { m_linear[3] = value; }\n"
    "inline    float b3GetFrictionCoeff(b3ContactConstraint4_t* constraint) \n"
    "{\n"
    "    return constraint->m_linear.w; \n"
    "}\n"
    "#endif //B3_CONTACT_CONSTRAINT5_H\n"
    "#ifndef B3_RIGIDBODY_DATA_H\n"
    "#define B3_RIGIDBODY_DATA_H\n"
    "#ifndef B3_FLOAT4_H\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "#endif \n"
    "#endif //B3_FLOAT4_H\n"
    "#ifndef B3_QUAT_H\n"
    "#define B3_QUAT_H\n"
    "#ifndef B3_PLATFORM_DEFINITIONS_H\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "#endif\n"
    "#endif\n"
    "#ifndef B3_FLOAT4_H\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "#endif \n"
    "#endif //B3_FLOAT4_H\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "    typedef float4    b3Quat;\n"
    "    #define b3QuatConstArg const b3Quat\n"
    "    \n"
    "    \n"
    "inline float4 b3FastNormalize4(float4 v)\n"
    "{\n"
    "    v = (float4)(v.xyz,0.f);\n"
    "    return fast_normalize(v);\n"
    "}\n"
    "    \n"
    "inline b3Quat b3QuatMul(b3Quat a, b3Quat b);\n"
    "inline b3Quat b3QuatNormalized(b3QuatConstArg in);\n"
    "inline b3Quat b3QuatRotate(b3QuatConstArg q, b3QuatConstArg vec);\n"
    "inline b3Quat b3QuatInvert(b3QuatConstArg q);\n"
    "inline b3Quat b3QuatInverse(b3QuatConstArg q);\n"
    "inline b3Quat b3QuatMul(b3QuatConstArg a, b3QuatConstArg b)\n"
    "{\n"
    "    b3Quat ans;\n"
    "    ans = b3Cross3( a, b );\n"
    "    ans += a.w*b+b.w*a;\n"
    "//    ans.w = a.w*b.w - (a.x*b.x+a.y*b.y+a.z*b.z);\n"
    "    ans.w = a.w*b.w - b3Dot3F4(a, b);\n"
    "    return ans;\n"
    "}\n"
    "inline b3Quat b3QuatNormalized(b3QuatConstArg in)\n"
    "{\n"
    "    b3Quat q;\n"
    "    q=in;\n"
    "    //return b3FastNormalize4(in);\n"
    "    float len = native_sqrt(dot(q, q));\n"
    "    if(len > 0.f)\n"
    "    {\n"
    "        q *= 1.f / len;\n"
    "    }\n"
    "    else\n"
    "    {\n"
    "        q.x = q.y = q.z = 0.f;\n"
    "        q.w = 1.f;\n"
    "    }\n"
    "    return q;\n"
    "}\n"
    "inline float4 b3QuatRotate(b3QuatConstArg q, b3QuatConstArg vec)\n"
    "{\n"
    "    b3Quat qInv = b3QuatInvert( q );\n"
    "    float4 vcpy = vec;\n"
    "    vcpy.w = 0.f;\n"
    "    float4 out = b3QuatMul(b3QuatMul(q,vcpy),qInv);\n"
    "    return out;\n"
    "}\n"
    "inline b3Quat b3QuatInverse(b3QuatConstArg q)\n"
    "{\n"
    "    return (b3Quat)(-q.xyz, q.w);\n"
    "}\n"
    "inline b3Quat b3QuatInvert(b3QuatConstArg q)\n"
    "{\n"
    "    return (b3Quat)(-q.xyz, q.w);\n"
    "}\n"
    "inline float4 b3QuatInvRotate(b3QuatConstArg q, b3QuatConstArg vec)\n"
    "{\n"
    "    return b3QuatRotate( b3QuatInvert( q ), vec );\n"
    "}\n"
    "inline b3Float4 b3TransformPoint(b3Float4ConstArg point, b3Float4ConstArg translation, b3QuatConstArg  orientation)\n"
    "{\n"
    "    return b3QuatRotate( orientation, point ) + (translation);\n"
    "}\n"
    "    \n"
    "#endif \n"
    "#endif //B3_QUAT_H\n"
    "#ifndef B3_MAT3x3_H\n"
    "#define B3_MAT3x3_H\n"
    "#ifndef B3_QUAT_H\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "#endif \n"
    "#endif //B3_QUAT_H\n"
    "#ifdef __cplusplus\n"
    "#else\n"
    "typedef struct\n"
    "{\n"
    "    b3Float4 m_row[3];\n"
    "}b3Mat3x3;\n"
    "#define b3Mat3x3ConstArg const b3Mat3x3\n"
    "#define b3GetRow(m,row) (m.m_row[row])\n"
    "inline b3Mat3x3 b3QuatGetRotationMatrix(b3Quat quat)\n"
    "{\n"
    "    b3Float4 quat2 = (b3Float4)(quat.x*quat.x, quat.y*quat.y, quat.z*quat.z, 0.f);\n"
    "    b3Mat3x3 out;\n"
    "    out.m_row[0].x=1-2*quat2.y-2*quat2.z;\n"
    "    out.m_row[0].y=2*quat.x*quat.y-2*quat.w*quat.z;\n"
    "    out.m_row[0].z=2*quat.x*quat.z+2*quat.w*quat.y;\n"
    "    out.m_row[0].w = 0.f;\n"
    "    out.m_row[1].x=2*quat.x*quat.y+2*quat.w*quat.z;\n"
    "    out.m_row[1].y=1-2*quat2.x-2*quat2.z;\n"
    "    out.m_row[1].z=2*quat.y*quat.z-2*quat.w*quat.x;\n"
    "    out.m_row[1].w = 0.f;\n"
    "    out.m_row[2].x=2*quat.x*quat.z-2*quat.w*quat.y;\n"
    "    out.m_row[2].y=2*quat.y*quat.z+2*quat.w*quat.x;\n"
    "    out.m_row[2].z=1-2*quat2.x-2*quat2.y;\n"
    "    out.m_row[2].w = 0.f;\n"
    "    return out;\n"
    "}\n"
    "inline b3Mat3x3 b3AbsoluteMat3x3(b3Mat3x3ConstArg matIn)\n"
    "{\n"
    "    b3Mat3x3 out;\n"
    "    out.m_row[0] = fabs(matIn.m_row[0]);\n"
    "    out.m_row[1] = fabs(matIn.m_row[1]);\n"
    "    out.m_row[2] = fabs(matIn.m_row[2]);\n"
    "    return out;\n"
    "}\n"
    "__inline\n"
    "b3Mat3x3 mtZero();\n"
    "__inline\n"
    "b3Mat3x3 mtIdentity();\n"
    "__inline\n"
    "b3Mat3x3 mtTranspose(b3Mat3x3 m);\n"
    "__inline\n"
    "b3Mat3x3 mtMul(b3Mat3x3 a, b3Mat3x3 b);\n"
    "__inline\n"
    "b3Float4 mtMul1(b3Mat3x3 a, b3Float4 b);\n"
    "__inline\n"
    "b3Float4 mtMul3(b3Float4 a, b3Mat3x3 b);\n"
    "__inline\n"
    "b3Mat3x3 mtZero()\n"
    "{\n"
    "    b3Mat3x3 m;\n"
    "    m.m_row[0] = (b3Float4)(0.f);\n"
    "    m.m_row[1] = (b3Float4)(0.f);\n"
    "    m.m_row[2] = (b3Float4)(0.f);\n"
    "    return m;\n"
    "}\n"
    "__inline\n"
    "b3Mat3x3 mtIdentity()\n"
    "{\n"
    "    b3Mat3x3 m;\n"
    "    m.m_row[0] = (b3Float4)(1,0,0,0);\n"
    "    m.m_row[1] = (b3Float4)(0,1,0,0);\n"
    "    m.m_row[2] = (b3Float4)(0,0,1,0);\n"
    "    return m;\n"
    "}\n"
    "__inline\n"
    "b3Mat3x3 mtTranspose(b3Mat3x3 m)\n"
    "{\n"
    "    b3Mat3x3 out;\n"
    "    out.m_row[0] = (b3Float4)(m.m_row[0].x, m.m_row[1].x, m.m_row[2].x, 0.f);\n"
    "    out.m_row[1] = (b3Float4)(m.m_row[0].y, m.m_row[1].y, m.m_row[2].y, 0.f);\n"
    "    out.m_row[2] = (b3Float4)(m.m_row[0].z, m.m_row[1].z, m.m_row[2].z, 0.f);\n"
    "    return out;\n"
    "}\n"
    "__inline\n"
    "b3Mat3x3 mtMul(b3Mat3x3 a, b3Mat3x3 b)\n"
    "{\n"
    "    b3Mat3x3 transB;\n"
    "    transB = mtTranspose( b );\n"
    "    b3Mat3x3 ans;\n"
    "    //    why this doesn't run when 0ing in the for{}\n"
    "    a.m_row[0].w = 0.f;\n"
    "    a.m_row[1].w = 0.f;\n"
    "    a.m_row[2].w = 0.f;\n"
    "    for(int i=0; i<3; i++)\n"
    "    {\n"
    "//    a.m_row[i].w = 0.f;\n"
    "        ans.m_row[i].x = b3Dot3F4(a.m_row[i],transB.m_row[0]);\n"
    "        ans.m_row[i].y = b3Dot3F4(a.m_row[i],transB.m_row[1]);\n"
    "        ans.m_row[i].z = b3Dot3F4(a.m_row[i],transB.m_row[2]);\n"
    "        ans.m_row[i].w = 0.f;\n"
    "    }\n"
    "    return ans;\n"
    "}\n"
    "__inline\n"
    "b3Float4 mtMul1(b3Mat3x3 a, b3Float4 b)\n"
    "{\n"
    "    b3Float4 ans;\n"
    "    ans.x = b3Dot3F4( a.m_row[0], b );\n"
    "    ans.y = b3Dot3F4( a.m_row[1], b );\n"
    "    ans.z = b3Dot3F4( a.m_row[2], b );\n"
    "    ans.w = 0.f;\n"
    "    return ans;\n"
    "}\n"
    "__inline\n"
    "b3Float4 mtMul3(b3Float4 a, b3Mat3x3 b)\n"
    "{\n"
    "    b3Float4 colx = b3MakeFloat4(b.m_row[0].x, b.m_row[1].x, b.m_row[2].x, 0);\n"
    "    b3Float4 coly = b3MakeFloat4(b.m_row[0].y, b.m_row[1].y, b.m_row[2].y, 0);\n"
    "    b3Float4 colz = b3MakeFloat4(b.m_row[0].z, b.m_row[1].z, b.m_row[2].z, 0);\n"
    "    b3Float4 ans;\n"
    "    ans.x = b3Dot3F4( a, colx );\n"
    "    ans.y = b3Dot3F4( a, coly );\n"
    "    ans.z = b3Dot3F4( a, colz );\n"
    "    return ans;\n"
    "}\n"
    "#endif\n"
    "#endif //B3_MAT3x3_H\n"
    "typedef struct b3RigidBodyData b3RigidBodyData_t;\n"
    "struct b3RigidBodyData\n"
    "{\n"
    "    b3Float4                m_pos;\n"
    "    b3Quat                    m_quat;\n"
    "    b3Float4                m_linVel;\n"
    "    b3Float4                m_angVel;\n"
    "    int                     m_collidableIdx;\n"
    "    float                 m_invMass;\n"
    "    float                 m_restituitionCoeff;\n"
    "    float                 m_frictionCoeff;\n"
    "};\n"
    "typedef struct b3InertiaData b3InertiaData_t;\n"
    "struct b3InertiaData\n"
    "{\n"
    "    b3Mat3x3 m_invInertiaWorld;\n"
    "    b3Mat3x3 m_initInvInertia;\n"
    "};\n"
    "#endif //B3_RIGIDBODY_DATA_H\n"
    "    \n"
    "void b3PlaneSpace1 (b3Float4ConstArg n, b3Float4* p, b3Float4* q);\n"
    " void b3PlaneSpace1 (b3Float4ConstArg n, b3Float4* p, b3Float4* q)\n"
    "{\n"
    "  if (b3Fabs(n.z) > 0.70710678f) {\n"
    "    // choose p in y-z plane\n"
    "    float a = n.y*n.y + n.z*n.z;\n"
    "    float k = 1.f/sqrt(a);\n"
    "    p[0].x = 0;\n"
    "    p[0].y = -n.z*k;\n"
    "    p[0].z = n.y*k;\n"
    "    // set q = n x p\n"
    "    q[0].x = a*k;\n"
    "    q[0].y = -n.x*p[0].z;\n"
    "    q[0].z = n.x*p[0].y;\n"
    "  }\n"
    "  else {\n"
    "    // choose p in x-y plane\n"
    "    float a = n.x*n.x + n.y*n.y;\n"
    "    float k = 1.f/sqrt(a);\n"
    "    p[0].x = -n.y*k;\n"
    "    p[0].y = n.x*k;\n"
    "    p[0].z = 0;\n"
    "    // set q = n x p\n"
    "    q[0].x = -n.z*p[0].y;\n"
    "    q[0].y = n.z*p[0].x;\n"
    "    q[0].z = a*k;\n"
    "  }\n"
    "}\n"
    " \n"
    "void setLinearAndAngular( b3Float4ConstArg n, b3Float4ConstArg r0, b3Float4ConstArg r1, b3Float4* linear, b3Float4* angular0, b3Float4* angular1)\n"
    "{\n"
    "    *linear = b3MakeFloat4(n.x,n.y,n.z,0.f);\n"
    "    *angular0 = b3Cross3(r0, n);\n"
    "    *angular1 = -b3Cross3(r1, n);\n"
    "}\n"
    "float calcRelVel( b3Float4ConstArg l0, b3Float4ConstArg l1, b3Float4ConstArg a0, b3Float4ConstArg a1, b3Float4ConstArg linVel0,\n"
    "    b3Float4ConstArg angVel0, b3Float4ConstArg linVel1, b3Float4ConstArg angVel1 )\n"
    "{\n"
    "    return b3Dot3F4(l0, linVel0) + b3Dot3F4(a0, angVel0) + b3Dot3F4(l1, linVel1) + b3Dot3F4(a1, angVel1);\n"
    "}\n"
    "float calcJacCoeff(b3Float4ConstArg linear0, b3Float4ConstArg linear1, b3Float4ConstArg angular0, b3Float4ConstArg angular1,\n"
    "                    float invMass0, const b3Mat3x3* invInertia0, float invMass1, const b3Mat3x3* invInertia1)\n"
    "{\n"
    "    //    linear0,1 are normlized\n"
    "    float jmj0 = invMass0;//b3Dot3F4(linear0, linear0)*invMass0;\n"
    "    float jmj1 = b3Dot3F4(mtMul3(angular0,*invInertia0), angular0);\n"
    "    float jmj2 = invMass1;//b3Dot3F4(linear1, linear1)*invMass1;\n"
    "    float jmj3 = b3Dot3F4(mtMul3(angular1,*invInertia1), angular1);\n"
    "    return -1.f/(jmj0+jmj1+jmj2+jmj3);\n"
    "}\n"
    "void setConstraint4( b3Float4ConstArg posA, b3Float4ConstArg linVelA, b3Float4ConstArg angVelA, float invMassA, b3Mat3x3ConstArg invInertiaA,\n"
    "    b3Float4ConstArg posB, b3Float4ConstArg linVelB, b3Float4ConstArg angVelB, float invMassB, b3Mat3x3ConstArg invInertiaB, \n"
    "    __global struct b3Contact4Data* src, float dt, float positionDrift, float positionConstraintCoeff,\n"
    "    b3ContactConstraint4_t* dstC )\n"
    "{\n"
    "    dstC->m_bodyA = abs(src->m_bodyAPtrAndSignBit);\n"
    "    dstC->m_bodyB = abs(src->m_bodyBPtrAndSignBit);\n"
    "    float dtInv = 1.f/dt;\n"
    "    for(int ic=0; ic<4; ic++)\n"
    "    {\n"
    "        dstC->m_appliedRambdaDt[ic] = 0.f;\n"
    "    }\n"
    "    dstC->m_fJacCoeffInv[0] = dstC->m_fJacCoeffInv[1] = 0.f;\n"
    "    dstC->m_linear = src->m_worldNormalOnB;\n"
    "    dstC->m_linear.w = 0.7f ;//src->getFrictionCoeff() );\n"
    "    for(int ic=0; ic<4; ic++)\n"
    "    {\n"
    "        b3Float4 r0 = src->m_worldPosB[ic] - posA;\n"
    "        b3Float4 r1 = src->m_worldPosB[ic] - posB;\n"
    "        if( ic >= src->m_worldNormalOnB.w )//npoints\n"
    "        {\n"
    "            dstC->m_jacCoeffInv[ic] = 0.f;\n"
    "            continue;\n"
    "        }\n"
    "        float relVelN;\n"
    "        {\n"
    "            b3Float4 linear, angular0, angular1;\n"
    "            setLinearAndAngular(src->m_worldNormalOnB, r0, r1, &linear, &angular0, &angular1);\n"
    "            dstC->m_jacCoeffInv[ic] = calcJacCoeff(linear, -linear, angular0, angular1,\n"
    "                invMassA, &invInertiaA, invMassB, &invInertiaB );\n"
    "            relVelN = calcRelVel(linear, -linear, angular0, angular1,\n"
    "                linVelA, angVelA, linVelB, angVelB);\n"
    "            float e = 0.f;//src->getRestituitionCoeff();\n"
    "            if( relVelN*relVelN < 0.004f ) e = 0.f;\n"
    "            dstC->m_b[ic] = e*relVelN;\n"
    "            //float penetration = src->m_worldPosB[ic].w;\n"
    "            dstC->m_b[ic] += (src->m_worldPosB[ic].w + positionDrift)*positionConstraintCoeff*dtInv;\n"
    "            dstC->m_appliedRambdaDt[ic] = 0.f;\n"
    "        }\n"
    "    }\n"
    "    if( src->m_worldNormalOnB.w > 0 )//npoints\n"
    "    {    //    prepare friction\n"
    "        b3Float4 center = b3MakeFloat4(0.f,0.f,0.f,0.f);\n"
    "        for(int i=0; i<src->m_worldNormalOnB.w; i++) \n"
    "            center += src->m_worldPosB[i];\n"
    "        center /= (float)src->m_worldNormalOnB.w;\n"
    "        b3Float4 tangent[2];\n"
    "        b3PlaneSpace1(src->m_worldNormalOnB,&tangent[0],&tangent[1]);\n"
    "        \n"
    "        b3Float4 r[2];\n"
    "        r[0] = center - posA;\n"
    "        r[1] = center - posB;\n"
    "        for(int i=0; i<2; i++)\n"
    "        {\n"
    "            b3Float4 linear, angular0, angular1;\n"
    "            setLinearAndAngular(tangent[i], r[0], r[1], &linear, &angular0, &angular1);\n"
    "            dstC->m_fJacCoeffInv[i] = calcJacCoeff(linear, -linear, angular0, angular1,\n"
    "                invMassA, &invInertiaA, invMassB, &invInertiaB );\n"
    "            dstC->m_fAppliedRambdaDt[i] = 0.f;\n"
    "        }\n"
    "        dstC->m_center = center;\n"
    "    }\n"
    "    for(int i=0; i<4; i++)\n"
    "    {\n"
    "        if( i<src->m_worldNormalOnB.w )\n"
    "        {\n"
    "            dstC->m_worldPos[i] = src->m_worldPosB[i];\n"
    "        }\n"
    "        else\n"
    "        {\n"
    "            dstC->m_worldPos[i] = b3MakeFloat4(0.f,0.f,0.f,0.f);\n"
    "        }\n"
    "    }\n"
    "}\n"
    "#pragma OPENCL EXTENSION cl_amd_printf : enable\n"
    "#pragma OPENCL EXTENSION cl_khr_local_int32_base_atomics : enable\n"
    "#pragma OPENCL EXTENSION cl_khr_global_int32_base_atomics : enable\n"
    "#pragma OPENCL EXTENSION cl_khr_local_int32_extended_atomics : enable\n"
    "#pragma OPENCL EXTENSION cl_khr_global_int32_extended_atomics : enable\n"
    "#ifdef cl_ext_atomic_counters_32\n"
    "#pragma OPENCL EXTENSION cl_ext_atomic_counters_32 : enable\n"
    "#else\n"
    "#define counter32_t volatile global int*\n"
    "#endif\n"
    "typedef unsigned int u32;\n"
    "typedef unsigned short u16;\n"
    "typedef unsigned char u8;\n"
    "#define GET_GROUP_IDX get_group_id(0)\n"
    "#define GET_LOCAL_IDX get_local_id(0)\n"
    "#define GET_GLOBAL_IDX get_global_id(0)\n"
    "#define GET_GROUP_SIZE get_local_size(0)\n"
    "#define GET_NUM_GROUPS get_num_groups(0)\n"
    "#define GROUP_LDS_BARRIER barrier(CLK_LOCAL_MEM_FENCE)\n"
    "#define GROUP_MEM_FENCE mem_fence(CLK_LOCAL_MEM_FENCE)\n"
    "#define AtomInc(x) atom_inc(&(x))\n"
    "#define AtomInc1(x, out) out = atom_inc(&(x))\n"
    "#define AppendInc(x, out) out = atomic_inc(x)\n"
    "#define AtomAdd(x, value) atom_add(&(x), value)\n"
    "#define AtomCmpxhg(x, cmp, value) atom_cmpxchg( &(x), cmp, value )\n"
    "#define AtomXhg(x, value) atom_xchg ( &(x), value )\n"
    "#define SELECT_UINT4( b, a, condition ) select( b,a,condition )\n"
    "#define make_float4 (float4)\n"
    "#define make_float2 (float2)\n"
    "#define make_uint4 (uint4)\n"
    "#define make_int4 (int4)\n"
    "#define make_uint2 (uint2)\n"
    "#define make_int2 (int2)\n"
    "#define max2 max\n"
    "#define min2 min\n"
    "///////////////////////////////////////\n"
    "//    Vector\n"
    "///////////////////////////////////////\n"
    "__inline\n"
    "float fastDiv(float numerator, float denominator)\n"
    "{\n"
    "    return native_divide(numerator, denominator);    \n"
    "//    return numerator/denominator;    \n"
    "}\n"
    "__inline\n"
    "float4 fastDiv4(float4 numerator, float4 denominator)\n"
    "{\n"
    "    return native_divide(numerator, denominator);    \n"
    "}\n"
    "__inline\n"
    "float fastSqrtf(float f2)\n"
    "{\n"
    "    return native_sqrt(f2);\n"
    "//    return sqrt(f2);\n"
    "}\n"
    "__inline\n"
    "float fastRSqrt(float f2)\n"
    "{\n"
    "    return native_rsqrt(f2);\n"
    "}\n"
    "__inline\n"
    "float fastLength4(float4 v)\n"
    "{\n"
    "    return fast_length(v);\n"
    "}\n"
    "__inline\n"
    "float4 fastNormalize4(float4 v)\n"
    "{\n"
    "    return fast_normalize(v);\n"
    "}\n"
    "__inline\n"
    "float sqrtf(float a)\n"
    "{\n"
    "//    return sqrt(a);\n"
    "    return native_sqrt(a);\n"
    "}\n"
    "__inline\n"
    "float4 cross3(float4 a, float4 b)\n"
    "{\n"
    "    return cross(a,b);\n"
    "}\n"
    "__inline\n"
    "float dot3F4(float4 a, float4 b)\n"
    "{\n"
    "    float4 a1 = make_float4(a.xyz,0.f);\n"
    "    float4 b1 = make_float4(b.xyz,0.f);\n"
    "    return dot(a1, b1);\n"
    "}\n"
    "__inline\n"
    "float length3(const float4 a)\n"
    "{\n"
    "    return sqrtf(dot3F4(a,a));\n"
    "}\n"
    "__inline\n"
    "float dot4(const float4 a, const float4 b)\n"
    "{\n"
    "    return dot( a, b );\n"
    "}\n"
    "//    for height\n"
    "__inline\n"
    "float dot3w1(const float4 point, const float4 eqn)\n"
    "{\n"
    "    return dot3F4(point,eqn) + eqn.w;\n"
    "}\n"
    "__inline\n"
    "float4 normalize3(const float4 a)\n"
    "{\n"
    "    float4 n = make_float4(a.x, a.y, a.z, 0.f);\n"
    "    return fastNormalize4( n );\n"
    "//    float length = sqrtf(dot3F4(a, a));\n"
    "//    return 1.f/length * a;\n"
    "}\n"
    "__inline\n"
    "float4 normalize4(const float4 a)\n"
    "{\n"
    "    float length = sqrtf(dot4(a, a));\n"
    "    return 1.f/length * a;\n"
    "}\n"
    "__inline\n"
    "float4 createEquation(const float4 a, const float4 b, const float4 c)\n"
    "{\n"
    "    float4 eqn;\n"
    "    float4 ab = b-a;\n"
    "    float4 ac = c-a;\n"
    "    eqn = normalize3( cross3(ab, ac) );\n"
    "    eqn.w = -dot3F4(eqn,a);\n"
    "    return eqn;\n"
    "}\n"
    "#define WG_SIZE 64\n"
    "typedef struct\n"
    "{\n"
    "    int m_nConstraints;\n"
    "    int m_start;\n"
    "    int m_batchIdx;\n"
    "    int m_nSplit;\n"
    "//    int m_paddings[1];\n"
    "} ConstBuffer;\n"
    "typedef struct\n"
    "{\n"
    "    int m_solveFriction;\n"
    "    int m_maxBatch;    //    long batch really kills the performance\n"
    "    int m_batchIdx;\n"
    "    int m_nSplit;\n"
    "//    int m_paddings[1];\n"
    "} ConstBufferBatchSolve;\n"
    " \n"
    "typedef struct \n"
    "{\n"
    "    int m_valInt0;\n"
    "    int m_valInt1;\n"
    "    int m_valInt2;\n"
    "    int m_valInt3;\n"
    "    float m_val0;\n"
    "    float m_val1;\n"
    "    float m_val2;\n"
    "    float m_val3;\n"
    "} SolverDebugInfo;\n"
    "typedef struct\n"
    "{\n"
    "    int m_nContacts;\n"
    "    float m_dt;\n"
    "    float m_positionDrift;\n"
    "    float m_positionConstraintCoeff;\n"
    "} ConstBufferCTC;\n"
    "__kernel\n"
    "__attribute__((reqd_work_group_size(WG_SIZE,1,1)))\n"
    "void ContactToConstraintKernel(__global struct b3Contact4Data* gContact, __global b3RigidBodyData_t* gBodies, __global b3InertiaData_t* gShapes, __global b3ContactConstraint4_t* gConstraintOut, \n"
    "int nContacts,\n"
    "float dt,\n"
    "float positionDrift,\n"
    "float positionConstraintCoeff\n"
    ")\n"
    "{\n"
    "    int gIdx = GET_GLOBAL_IDX;\n"
    "    \n"
    "    if( gIdx < nContacts )\n"
    "    {\n"
    "        int aIdx = abs(gContact[gIdx].m_bodyAPtrAndSignBit);\n"
    "        int bIdx = abs(gContact[gIdx].m_bodyBPtrAndSignBit);\n"
    "        float4 posA = gBodies[aIdx].m_pos;\n"
    "        float4 linVelA = gBodies[aIdx].m_linVel;\n"
    "        float4 angVelA = gBodies[aIdx].m_angVel;\n"
    "        float invMassA = gBodies[aIdx].m_invMass;\n"
    "        b3Mat3x3 invInertiaA = gShapes[aIdx].m_initInvInertia;\n"
    "        float4 posB = gBodies[bIdx].m_pos;\n"
    "        float4 linVelB = gBodies[bIdx].m_linVel;\n"
    "        float4 angVelB = gBodies[bIdx].m_angVel;\n"
    "        float invMassB = gBodies[bIdx].m_invMass;\n"
    "        b3Mat3x3 invInertiaB = gShapes[bIdx].m_initInvInertia;\n"
    "        b3ContactConstraint4_t cs;\n"
    "        setConstraint4( posA, linVelA, angVelA, invMassA, invInertiaA, posB, linVelB, angVelB, invMassB, invInertiaB,\n"
    "            &gContact[gIdx], dt, positionDrift, positionConstraintCoeff,\n"
    "            &cs );\n"
    "        \n"
    "        cs.m_batchIdx = gContact[gIdx].m_batchIdx;\n"
    "        gConstraintOut[gIdx] = cs;\n"
    "    }\n"
    "}\n";