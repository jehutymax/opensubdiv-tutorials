#include <iostream>

#include <opensubdiv/far/topologyDescriptor.h>
#include <opensubdiv/far/primvarRefiner.h>

#include "geometry/cube.h"

struct Vertex {
    Vertex()
    {
        Clear();
    };

    Vertex(Vertex const & source)
    {
        mPosition[0] = source.mPosition[0];
        mPosition[1] = source.mPosition[1];
        mPosition[2] = source.mPosition[2];
    }

    void Clear(void* = nullptr)
    {
        mPosition[0] = mPosition[1] = mPosition[2] = 0.0f;
    }

    void AddWithWeight(Vertex const & source, float weight)
    {
        mPosition[0] += weight * source.mPosition[0];
        mPosition[1] += weight * source.mPosition[1];
        mPosition[2] += weight * source.mPosition[2];
    }

    void setPosition(float x, float y, float z)
    {
        mPosition[0] = x;
        mPosition[1] = y;
        mPosition[2] = z;
    }

    [[nodiscard]]
    const float* getPosition() const
    {
        return mPosition;
    }

 private:
    float mPosition[3];
};

using namespace OpenSubdiv;

int main()
{
    std::cout << "Hello, OpenSubdiv!" << std::endl;

    // Populate the topology refiner.
    Sdc::SchemeType type = OpenSubdiv::Sdc::SCHEME_CATMARK;


    Sdc::Options options;
    options.SetVtxBoundaryInterpolation(Sdc::Options::VTX_BOUNDARY_EDGE_ONLY);

    Far::TopologyDescriptor descriptor;
    descriptor.numVertices = cube::nVerts;
    descriptor.numFaces = cube::nFaces;
    descriptor.numVertsPerFace = cube::verticesPerFace;
    descriptor.vertIndicesPerFace = cube::vertexIndices;

    Far::TopologyRefiner* refiner = Far::TopologyRefinerFactory<Far::TopologyDescriptor>::Create(descriptor,
        Far::TopologyRefinerFactory<Far::TopologyDescriptor>::Options(type, options));

    int maxLevel = 6;

    // uniformly refine the topology up to maxLevel
    refiner->RefineUniform(Far::TopologyRefiner::UniformOptions(maxLevel));

    // allocate a buffer for the primvar data
    std::cout << "Refiner: Total number of vertices = " << refiner->GetNumVerticesTotal() << std::endl;
    std::vector<Vertex> vertexBuffer(refiner->GetNumVerticesTotal());
    Vertex *vertices = &vertexBuffer[0];

    // initialize coarse mesh
    int numberCoarseVertices = cube::nVerts;
    for (int i = 0; i < numberCoarseVertices; ++i)
    {
        vertices[i].setPosition(cube::vertices[i][0], cube::vertices[i][1], cube::vertices[i][2]);
    }

    // interpolate vertex data
    Far::PrimvarRefiner primvarRefiner(*refiner);

    Vertex *source = vertices;
    for (int level = 1; level <= maxLevel; ++level)
    {
        Vertex *dest = source + refiner->GetLevel(level - 1).GetNumVertices();
        primvarRefiner.Interpolate(level, source, dest);
        source = dest;
    }

    // output the obj file with the most refined level
    Far::TopologyLevel const & refLastLevel = refiner->GetLevel(maxLevel);
    int numVerts = refLastLevel.GetNumVertices();
    int numFaces = refLastLevel.GetNumFaces();

    FILE* output = fopen("output1.obj", "w");

    int firstOfLastSetOfVertices = refiner->GetNumVerticesTotal() - numVerts;

    // vertex positions
    for (int vert = 0; vert < numVerts; ++vert)
    {
        float const* pos = vertices[firstOfLastSetOfVertices + vert].getPosition();
        fprintf(output, "v %f %f %f\n", pos[0], pos[1], pos[2]);
    }

    // faces
    for (int face = 0; face < numFaces; ++face)
    {
        Far::ConstIndexArray faceVertices = refLastLevel.GetFaceVertices(face);
        fprintf(output, "f ");
        for (int vert = 0; vert < faceVertices.size(); ++vert)
        {
            fprintf(output, "%d ", faceVertices[vert]+1);
        }
        fprintf(output, "\n");
    }

    fclose(output);

    return 0;
}
