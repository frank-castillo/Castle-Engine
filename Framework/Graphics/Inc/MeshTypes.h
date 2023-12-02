#pragma once

#include "VertexTypes.h"

namespace CASTLEEngine::Graphics
{
    template<class VertexT>
    struct MeshBase
    {
        using VertexType = VertexT;
        std::vector<VertexType> vertices;
        std::vector<uint32_t> indices;

        void Initialize(uint32_t numVertices, uint32_t numIndecies)
        {
            mNumIndices = numIndecies;
            mNumVertices = numVertices;

            indices.resize(mNumIndices);
            vertices.resize(mNumVertices);
        }

        VertexType& GetVertex(uint32_t index)
        {
            // ASSERT(index < NumVertices, "[Mesh] Index out of range.");
            return vertices[index];
        }

        uint32_t& GetIndex(uint32_t index)
        {
            // ASSERT(index < NumIndices, "[Mesh] Index out of range.");
            return indices[index];
        }
    private:
        uint32_t mNumIndices;
        uint32_t mNumVertices;
    };

    using MeshP = MeshBase<VertexP>;
    using MeshPC = MeshBase<VertexPC>;
    using MeshPX = MeshBase<VertexPX>;
    using Mesh = MeshBase<Vertex>; // Way more information than the others
}