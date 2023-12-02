#pragma once

#include "MeshTypes.h"

namespace CASTLEEngine::Graphics
{
    class MeshBuilder
    {
    public:
        // Position and Colour
        static MeshPC CreateCubePC(float size);
        static MeshPC CreateRectanglePC(float width, float height, float depth);
        static MeshPC CreateQuadPC(float length, float width);
        static MeshPC CreatePlanePC(int numRows, int numColumns, float spacing);
        static MeshPC CreateUnitPlanePC(int numRows, int numColumns, float spacing);
        static MeshPC CreateCylinderPC(int slices, int rings);
        static MeshPC CreateSpherePC(int slices, int rings, float radius);

        // Position and UV
        static MeshPX CreateCubePX(float size);
        static MeshPX CreateSpherePX(int slices, int rings, float radius);
        static MeshPX CreateScreenQuad();

        // All data: Position, normal tangent, UV
        static Mesh CreateCube(float size);
        static Mesh CreatePlane(int numRows, int numColumns, float spacing);
        static Mesh CreateSphere(int slices, int rings, float radius);
    };
}