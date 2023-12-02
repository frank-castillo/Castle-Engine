#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::CEMath;
using namespace CASTLEEngine::Graphics;

namespace
{
    Color GetNextColor(int& index)
    {
        constexpr Color colorTable[] = {
        Colors::DarkMagenta,
        Colors::LightSkyBlue,
        Colors::Yellow,
        Colors::Green,
        Colors::Red,
        Colors::Aquamarine,
        Colors::Beige,
        Colors::Blue,
        Colors::Aqua,
        Colors::BlueViolet,
        Colors::DarkRed,
        Colors::Salmon,
        };

        index = (static_cast<size_t>(index) + 1) % std::size(colorTable);
        return colorTable[index];
    }

    void CreateCubeIndices(std::vector<uint32_t>& indices)
    {
        indices = {
            // Front Face
            0, 1, 3,
            1, 2, 3,

            // Back Face
            5, 4, 7,
            5, 7, 6,

            // Right Face
            1, 5, 2,
            5, 6, 2,

            // Left Face
            4, 0, 3,
            4, 3, 7,

            // Top Face
            0, 4, 1,
            4, 5, 1,

            // Bottom Face
            6, 7, 3,
            6, 3, 2
        };
    }

    void CreatePlaneIndices(std::vector<uint32_t>& indices, int numRows, int numColumns)
    {
        for (int r = 0; r < numRows; ++r)
        {
            for (int c = 0; c < numColumns; ++c)
            {
                int i = r * (numColumns + 1) + c; // This gives me the index of the vertex

                // Triangle 1
                indices.push_back(i);                   // Get the initial vertex top
                indices.push_back(i + numColumns + 1);    // This one gets the index from the next row. The lower vertex of the triangle
                indices.push_back(i + 1);              // Get the next vertex, right next to it ->

                // Triangle 2
                indices.push_back(i + 1);             // The top right index
                indices.push_back(i + numColumns + 1);    // This one gets the index from the next row. The lower vertex of the triangle
                indices.push_back(i + numColumns + 2);    // The next bottom vertex
            }
        }
    }

    void CreateCapsIndices(std::vector<uint32_t>& indices, int slices, int topIndex)
    {
        int bottomIndex = topIndex + 1;

        for (int s = 0; s < slices; ++s)
        {
            // Bottom triangle
            indices.push_back(s);
            indices.push_back(s + 1);
            indices.push_back(bottomIndex);

            // Top triangle
            // We go back one whole slice so we can draw it
            int topRow = topIndex - slices - 1 + s;
            indices.push_back(topIndex);
            indices.push_back(topRow + 1);
            indices.push_back(topRow);
        }
    }

    void CreateCapsPC(MeshPC& mesh, int slices, float halfHeight)
    {
        int index = rand() % 100;

        int topIndex = mesh.vertices.size();
        int bottomIndex = topIndex + 1;

        // Top Center
        mesh.vertices.push_back({ { 0.0f, halfHeight, 0.0f }, GetNextColor(index) });

        // Bottom Center
        mesh.vertices.push_back({ { 0.0f, -halfHeight, 0.0f }, GetNextColor(index) });

        CreateCapsIndices(mesh.indices, slices, topIndex);
    }
}

MeshPC MeshBuilder::CreateCubePC(float size)
{
    MeshPC mesh;

    float hs = size * 0.5f;
    int colorIndex = 0;

    // Face
    mesh.vertices.push_back({ { -hs, hs, -hs }, GetNextColor(colorIndex) });   // FTL  0
    mesh.vertices.push_back({ { hs, hs, -hs }, GetNextColor(colorIndex) });    // FTR  1
    mesh.vertices.push_back({ { hs, -hs, -hs }, GetNextColor(colorIndex) });   // FBR  2
    mesh.vertices.push_back({ { -hs, -hs, -hs }, GetNextColor(colorIndex) });  // FBL  3

    // Back
    mesh.vertices.push_back({ { -hs, hs, hs }, GetNextColor(colorIndex) });    // BTL  4
    mesh.vertices.push_back({ { hs, hs, hs }, GetNextColor(colorIndex) });     // BTR  5
    mesh.vertices.push_back({ { hs, -hs, hs }, GetNextColor(colorIndex) });    // BBR  6
    mesh.vertices.push_back({ { -hs, -hs, hs }, GetNextColor(colorIndex) });   // BBL  7

    CreateCubeIndices(mesh.indices);

    return mesh;
}

MeshPC MeshBuilder::CreateRectanglePC(float width, float height, float depth)
{
    MeshPC mesh;

    float hw = width * 0.5f;
    float hh = height * 0.5f;
    float hd = depth * 0.5f;
    int colorIndex = 0;

    // Face
    mesh.vertices.push_back({ { -hw, hh, -hd }, GetNextColor(colorIndex) });   // FTL  0
    mesh.vertices.push_back({ { hw, hh, -hd }, GetNextColor(colorIndex) });    // FTR  1
    mesh.vertices.push_back({ { hw, -hh, -hd }, GetNextColor(colorIndex) });   // FBR  2
    mesh.vertices.push_back({ { -hw, -hh, -hd }, GetNextColor(colorIndex) });  // FBL  3

    // Back
    mesh.vertices.push_back({ { -hw, hh, hd }, GetNextColor(colorIndex) });    // BTL  4
    mesh.vertices.push_back({ { hw, hh, hd }, GetNextColor(colorIndex) });     // BTR  5
    mesh.vertices.push_back({ { hw, -hh, hd }, GetNextColor(colorIndex) });    // BBR  6
    mesh.vertices.push_back({ { -hw, -hh, hd }, GetNextColor(colorIndex) });   // BBL  7

    mesh.indices = {
        // Front Face
        0, 1, 3,
        1, 2, 3,

        // Back Face
        5, 4, 7,
        5, 7, 6,

        // Right Face
        1, 5, 2,
        5, 6, 2,

        // Left Face
        4, 0, 3,
        4, 3, 7,

        // Top Face
        0, 4, 1,
        4, 5, 1,

        // Bottom Face
        6, 7, 3,
        6, 3, 2
    };

    return mesh;
}

MeshPC MeshBuilder::CreateQuadPC(float length, float width)
{
    MeshPC mesh;

    float hh = length * 0.5f;
    float hw = width * 0.5f;
    int colorIndex = 0;

    // Face
    mesh.vertices.push_back({ { hw, -hh, -hw }, GetNextColor(colorIndex) });   // FBR  0
    mesh.vertices.push_back({ { -hw, -hh, -hw }, GetNextColor(colorIndex) });  // FBL  1

    // Back
    mesh.vertices.push_back({ { hw, -hh, hw }, GetNextColor(colorIndex) });    // BBR  2
    mesh.vertices.push_back({ { -hw, -hh, hw }, GetNextColor(colorIndex) });   // BBL  3

    mesh.indices = {
        1, 3, 0,
        3, 2, 0
    };

    return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(int numRows, int numColumns, float spacing)
{
    MeshPC mesh;
    // Offset here will work towards moving the origin to the center of the plane
    const float posOffsetX = spacing * -0.5f;
    const float posOffsetZ = spacing * -0.5f;
    const float xStep = spacing / (numRows);
    const float zStep = spacing / (numColumns);
    const int numVertsX = numColumns + 1;
    const int numVertsZ = numRows + 1;

    // Similar to Quad in the positioning of vertices
    // Spacing is the distance between the vertices that make the individual quads
    // To calculate vertices, we always need one additional count to the number of rows and columns
    int colorIndex = 0;
    const uint32_t numVertices = numVertsZ * numVertsX; // Total number of vertices we will have for the whole plane
    const uint32_t numIndices = numRows * numColumns * 6; // Total number of indices per grid that makes up the plane
    mesh.Initialize(numVertices, numIndices);

    // Add vertices
    for (int z = 0; z < numVertsZ; ++z)
    {
        for (int x = 0; x < numVertsX; ++x)
        {
            const uint32_t index = x + (z * numVertsX);
            mesh.GetVertex(index).position = { posOffsetX + (x * xStep), posOffsetZ + (z * zStep), 0.0f };
            mesh.GetVertex(index).color = GetNextColor(colorIndex);
        }
    }

    // Now you need to create and fill the array of indices for the index buffer.To keep the index array simple, it is going to be filled with a series of triangles to create a triangle list.
    // The first step is the sizing of the indices array. Each cell you create will require two triangles for a total of six vertices.
    // The index array is sized to allow for all six vertices per cell.
    // Each cell is made up of a quad, so the inside of the loops will need to create two triangles.
    // The triangles themselves are going to be laid out in a counterclockwise manner, making sure that all the triangles have the same winding order.
    // Because the grid is being generated with triangle lists, there are going to be some vertices that are duplicated

    // Fill the indices array to create the triangles needed for the terrain
    // The triangles are created in a counterclockwise direction
    uint32_t index = 0;
    for (int z = 0; z < numRows; ++z)
    {
        for (int x = 0; x < numColumns; ++x)
        {
            // Current vertex to build off of
            const int currVertex = x + (z * numVertsX);
            const int currTopVertex = currVertex + numVertsX;
            const int currVertexAddOne = currVertex + 1;

            // Create the indices for the first triangle
            mesh.GetIndex(index++) = currVertex;
            mesh.GetIndex(index++) = currTopVertex;
            mesh.GetIndex(index++) = currVertexAddOne;

            // Create the indices for the second triangle
            mesh.GetIndex(index++) = currVertexAddOne;
            mesh.GetIndex(index++) = currTopVertex;
            mesh.GetIndex(index++) = currTopVertex + 1;
        }
    }

    return mesh;
}

MeshPC MeshBuilder::CreateUnitPlanePC(int numRows, int numColumns, float spacing)
{
    MeshPC mesh;
    int index = rand() % 100;

    const float halfPlaneWidth = static_cast<float>(numColumns) * spacing * 0.5f;
    const float halfPlaneHeight = static_cast<float>(numRows) * spacing * 0.5f;

    float x = -halfPlaneWidth;
    float y = -halfPlaneHeight;

    for (int r = 0; r <= numRows; ++r)
    {
        for (int c = 0; c <= numColumns; ++c)
        {
            mesh.vertices.push_back({ {x, y, 0.0f}, GetNextColor(index) });
            x += spacing; // To move the next x position for the next vertex
        }
        x = -halfPlaneWidth;
        y += spacing; // Move vertically to the next row and start the process again
    }

    CreatePlaneIndices(mesh.indices, numRows, numColumns);

    return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(int slices, int rings)
{
    // Imagine you are folding paper
    // Learn how to make a circle
    // Create top and bottom circles, keeping in mind the rendering angle
    // Then apply that to a plane
    // Vertex in middle and map the external points to create several triangles
    // Once we know those points we use them on a plane and we get a cylinder

    MeshPC mesh;
    int index = rand() % 100;
    const float halfHeight = static_cast<float>(rings) * 0.5f;

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r); // Cast number of ring

        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * CEMath::Constants::kTwoPi; // Gets the roation all the way around

            mesh.vertices.push_back
            ({
                {
                    sin(rotation),
                    ring - halfHeight,
                    -cos(rotation)
                }, GetNextColor(index)
                });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    CreateCapsPC(mesh, slices, halfHeight);

    return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(int slices, int rings, float radius)
{
    MeshPC mesh;
    int index = rand() % 100;

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r); // Cast number of ring
        float phi = r * (CEMath::Constants::kPi / static_cast<float>((rings - 1))); // Angle between each arc of the cilinder

        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * CEMath::Constants::kTwoPi; // Gets the roation all the way around

            mesh.vertices.push_back
            ({
                {
                    radius * sin(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * cos(rotation) * sin(phi)
                }, GetNextColor(index)
                });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}

MeshPX MeshBuilder::CreateCubePX(float size)
{
    MeshPX mesh;

    float hs = size * 0.5f;
    int colorIndex = 0;

    // Face
    mesh.vertices.push_back({ { -hs, hs, -hs }, {0.25f, 0.33f} });   // FTL  0
    mesh.vertices.push_back({ { hs, hs, -hs }, {0.5f, 0.33f} });    // FTR  1
    mesh.vertices.push_back({ { hs, -hs, -hs }, {0.5f, 0.66f} });   // FBR  2
    mesh.vertices.push_back({ { -hs, -hs, -hs }, {0.25f, 0.66f} });  // FBL  3

    // Back
    mesh.vertices.push_back({ { -hs, hs, hs }, {0.0f, 0.33f } });    // BTL  4
    mesh.vertices.push_back({ { hs, hs, hs }, {0.5f, 0.0f} });     // BTR  5
    mesh.vertices.push_back({ { hs, -hs, hs }, {0.5f, 1.0f} });    // BBR  6
    mesh.vertices.push_back({ { -hs, -hs, hs }, {0.25f, 1.0f} });   // BBL  7

    CreateCubeIndices(mesh.indices);

    return mesh;
}

MeshPX MeshBuilder::CreateSpherePX(int slices, int rings, float radius)
{
    MeshPX mesh;
    int index = rand() % 100;
    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r); // Cast number of ring
        float phi = r * (CEMath::Constants::kPi / static_cast<float>((rings - 1))); // Angle between each arc of the cilinder

        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * CEMath::Constants::kTwoPi; // Gets the roation all the way around

            float u = 1.0f - (uStep * slice);
            float v = vStep * ring;

            mesh.vertices.push_back
            ({
                {
                    radius * sin(rotation) * sin(phi),
                    radius * cos(phi),
                    radius * cos(rotation) * sin(phi)
                }, {u,v} // Get pixel color at that point
                });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}

MeshPX MeshBuilder::CreateScreenQuad()
{
    MeshPX mesh;

    mesh.vertices.push_back({ { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } });
    mesh.vertices.push_back({ { -1.0f, 1.0f, 0.0f },  { 0.0f, 0.0f } });
    mesh.vertices.push_back({ { 1.0f, 1.0f, 0.0f },   { 1.0f, 0.0f } });
    mesh.vertices.push_back({ { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } });

    mesh.indices = { 0,1,2,0,2,3 };

    return mesh;
}

Mesh MeshBuilder::CreateCube(float size)
{
    Mesh mesh;

    float hs = size * 0.5f;

    // FRONT
    mesh.vertices.push_back({ Vector3{  hs,  hs, -hs }, Vector3::ZAxis, Vector3::XAxis, Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ Vector3{ -hs, -hs, -hs }, Vector3::ZAxis, Vector3::XAxis, Vector2(0.25f, 0.66f) }); // Bottom Left Close
    mesh.vertices.push_back({ Vector3{  hs, -hs, -hs }, Vector3::ZAxis, Vector3::XAxis, Vector2(0.5f, 0.66f) }); // Bottom Right Close

    mesh.vertices.push_back({ Vector3{  hs,  hs, -hs }, Vector3::ZAxis, Vector3::XAxis, Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ Vector3{ -hs,  hs, -hs }, Vector3::ZAxis, Vector3::XAxis, Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ Vector3{ -hs, -hs, -hs }, Vector3::ZAxis, Vector3::XAxis, Vector2(0.25f, 0.66f) }); // Bottom Left Close

    // BACK
    mesh.vertices.push_back({ Vector3{ -hs,  hs,  hs }, -Vector3::ZAxis, -Vector3::XAxis, Vector2(1.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ Vector3{  hs, -hs,  hs }, -Vector3::ZAxis, -Vector3::XAxis, Vector2(0.75f, 0.66f) }); // Bottom Right Far
    mesh.vertices.push_back({ Vector3{ -hs, -hs,  hs }, -Vector3::ZAxis, -Vector3::XAxis, Vector2(1.0f, 0.66f) }); // Bottom Left Far

    mesh.vertices.push_back({ Vector3{ -hs,  hs,  hs }, -Vector3::ZAxis, -Vector3::XAxis, Vector2(1.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ Vector3{  hs,  hs,  hs }, -Vector3::ZAxis, -Vector3::XAxis, Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ Vector3{  hs, -hs,  hs }, -Vector3::ZAxis, -Vector3::XAxis, Vector2(0.75f, 0.66f) }); // Bottom Right Far

    // RIGHT
    mesh.vertices.push_back({ Vector3{  hs,  hs,  hs }, Vector3::XAxis, Vector3::ZAxis, Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ Vector3{  hs, -hs, -hs }, Vector3::XAxis, Vector3::ZAxis, Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ Vector3{  hs, -hs,  hs }, Vector3::XAxis, Vector3::ZAxis, Vector2(0.75f, 0.66f) }); // Bottom Right Far

    mesh.vertices.push_back({ Vector3{  hs,  hs,  hs }, Vector3::XAxis, Vector3::ZAxis, Vector2(0.75f, 0.33f) }); // Top Right Far
    mesh.vertices.push_back({ Vector3{  hs,  hs, -hs }, Vector3::XAxis, Vector3::ZAxis, Vector2(0.5f, 0.33f) }); // Top Right Close
    mesh.vertices.push_back({ Vector3{  hs, -hs, -hs }, Vector3::XAxis, Vector3::ZAxis, Vector2(0.5f, 0.66f) }); // Bottom Right Close

    // Left
    mesh.vertices.push_back({ Vector3{ -hs,  hs, -hs }, -Vector3::XAxis, -Vector3::ZAxis, Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ Vector3{ -hs, -hs,  hs }, -Vector3::XAxis, -Vector3::ZAxis, Vector2(0.0f, 0.66f) }); // Bottom Left Far
    mesh.vertices.push_back({ Vector3{ -hs, -hs, -hs }, -Vector3::XAxis, -Vector3::ZAxis, Vector2(0.25f, 0.66f) }); // Bottom Left Close

    mesh.vertices.push_back({ Vector3{ -hs,  hs, -hs }, -Vector3::XAxis, -Vector3::ZAxis, Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ Vector3{ -hs,  hs,  hs }, -Vector3::XAxis, -Vector3::ZAxis, Vector2(0.0f, 0.33f) }); // Top Left Far
    mesh.vertices.push_back({ Vector3{ -hs, -hs,  hs }, -Vector3::XAxis, -Vector3::ZAxis, Vector2(0.0f, 0.66f) }); // Bottom Left Far

    // Top
    mesh.vertices.push_back({ Vector3{  hs,  hs,  hs }, Vector3::YAxis, Vector3::XAxis, Vector2(0.5f,  0.0f) }); // Top Right Far
    mesh.vertices.push_back({ Vector3{ -hs,  hs, -hs }, Vector3::YAxis, Vector3::XAxis, Vector2(0.25f, 0.33f) }); // Top Left Close
    mesh.vertices.push_back({ Vector3{  hs,  hs, -hs }, Vector3::YAxis, Vector3::XAxis, Vector2(0.5f, 0.33f) }); // Top Right Close

    mesh.vertices.push_back({ Vector3{  hs,  hs,  hs }, Vector3::YAxis, Vector3::XAxis, Vector2(0.5f,  0.0f) }); // Top Right Far
    mesh.vertices.push_back({ Vector3{ -hs,  hs,  hs }, Vector3::YAxis, Vector3::XAxis, Vector2(0.25f,  0.0f) }); // Top Left Far
    mesh.vertices.push_back({ Vector3{ -hs,  hs, -hs }, Vector3::YAxis, Vector3::XAxis, Vector2(0.25f, 0.33f) }); // Top Left Close

    // Bottom
    mesh.vertices.push_back({ Vector3{  hs, -hs, -hs }, -Vector3::YAxis, -Vector3::XAxis, Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ Vector3{ -hs, -hs,  hs }, -Vector3::YAxis, -Vector3::XAxis, Vector2(0.25f,  1.0f) }); // Bottom Left Far
    mesh.vertices.push_back({ Vector3{  hs, -hs,  hs }, -Vector3::YAxis, -Vector3::XAxis, Vector2(0.5f,  1.0f) }); // Bottom Right Far

    mesh.vertices.push_back({ Vector3{  hs, -hs, -hs }, -Vector3::YAxis, -Vector3::XAxis, Vector2(0.5f, 0.66f) }); // Bottom Right Close
    mesh.vertices.push_back({ Vector3{ -hs, -hs, -hs }, -Vector3::YAxis, -Vector3::XAxis, Vector2(0.25f, 0.66f) }); // Bottom Left Close
    mesh.vertices.push_back({ Vector3{ -hs, -hs,  hs }, -Vector3::YAxis, -Vector3::XAxis, Vector2(0.25f,  1.0f) }); // Bottom Left Far

    int i = 0;
    for (const auto& vertex : mesh.vertices)
    {
        mesh.indices.push_back(i);
        ++i;
    }

    return mesh;
}

Mesh MeshBuilder::CreatePlane(int numRows, int numColumns, float spacing)
{
    Mesh mesh;

    const float hpw = static_cast<float>(numColumns) * spacing * 0.5f;
    const float hph = static_cast<float>(numRows) * spacing * 0.5f;
    const float uInc = 1.0f / (hpw * 2.0f);
    const float vInc = 1.0f / (hph * 2.0f);

    float x = -hpw;
    float z = -hph;
    float u = 0.0f;
    float v = 1.0f;

    for (int r = 0; r <= numRows; ++r)
    {
        for (int c = 0; c <= numColumns; ++c)
        {
            mesh.vertices.push_back({
                {x, 0.0f, z},
                {0.0f, 1.0f, 0.0f},
                {0.0f, 0.0f, 1.0f},
                { u, v } });
            x += spacing;
            u += uInc;
        }
        u = 0.0f;
        v -= vInc;
        x = -hpw;
        z += spacing;
    }

    CreatePlaneIndices(mesh.indices, numRows, numColumns);

    return mesh;
}

Mesh MeshBuilder::CreateSphere(int slices, int rings, float radius)
{
    Mesh mesh;
    int index = rand() % 100;
    float uStep = 1.0f / static_cast<float>(slices);
    float vStep = 1.0f / static_cast<float>(rings);

    for (int r = 0; r <= rings; ++r)
    {
        float ring = static_cast<float>(r); // Cast number of ring
        float phi = r * (CEMath::Constants::kPi / static_cast<float>((rings - 1))); // Angle between each arc of the cilinder

        for (int s = 0; s < slices + 1; ++s)
        {
            float slice = static_cast<float>(s);
            float rotation = (slice / static_cast<float>(slices)) * CEMath::Constants::kTwoPi; // Gets the roation all the way around

            float u = 1.0f - (uStep * slice);
            float v = vStep * ring;

            float x = radius * sin(rotation) * sin(phi);
            float y = radius * cos(phi);
            float z = radius * cos(rotation) * sin(phi);

            const Vector3 pos = { x, y, z };
            const Vector3 norm = Normalize(pos);
            const Vector3 tan = Normalize({ -z, 0.0f, x });

            mesh.vertices.push_back({ pos, norm, tan, {u,v} });
        }
    }

    CreatePlaneIndices(mesh.indices, rings, slices);

    return mesh;
}

//Mesh MeshBuilder::CreatePlane(int numRows, int numColumns, float spacing)
//{
//    Mesh mesh;
//
//    const float halfPlaneWidth = static_cast<float>(numColumns) * spacing * 0.5f;
//    const float halfPlaneHeight = static_cast<float>(numRows) * spacing * 0.5f;
//
//    float x = -halfPlaneWidth;
//    float z = -halfPlaneHeight;
//
//    const float uStep = 1.0f / static_cast<float>(numColumns);
//    const float vStep = 1.0f / static_cast<float>(numRows);
//
//    const Vector3 n = CEMath::Vector3::YAxis;
//    const Vector3 t = CEMath::Vector3::XAxis;
//
//    for (int r = 0; r <= numRows; ++r)
//    {
//        float rf = static_cast<float>(r);
//        for (int c = 0; c <= numColumns; ++c)
//        {
//            float cf = static_cast<float>(c);
//
//            float u = (uStep * cf);
//            float v = 1.0f - (vStep * rf);
//
//            mesh.vertices.push_back({ {x, 0.0f, z}, n ,t, CEMath::Vector2(u,v) });
//            x += spacing; // To move the next x position for the next vertex
//        }
//        x = -halfPlaneWidth;
//        z += spacing; // Move vertically to the next row and start the process again
//    }
//
//    CreatePlaneIndices(mesh.indices, numRows, numColumns);
//
//    return mesh;
//}