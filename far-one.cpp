#include <iostream>

#include <opensubdiv/far/topologyDescriptor.h>
#include <opensubdiv/far/primvarRefiner.h>

#include "geometry/cube.h"

struct Vertex {
    Vertex()
    {
        clear();
    };

    Vertex(Vertex const & source)
    {
        mPosition[0] = source.mPosition[0];
        mPosition[1] = source.mPosition[1];
        mPosition[2] = source.mPosition[2];
    }

    void clear(void* = nullptr)
    {
        mPosition[0] = mPosition[1] = mPosition[2] = 0.0f;
    }

    void addWithWeight(Vertex const & source, float weight)
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

    int maxLevel = 2;

    // uniformly refine the topology up to maxLevel
    refiner->RefineUniform(Far::TopologyRefiner::UniformOptions(maxLevel));

    return 0;
}
