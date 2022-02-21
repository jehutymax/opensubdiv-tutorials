//
// Created by rafael on 2/21/22.
//

#ifndef SUBD_TUTORIALS_GEOMETRY_CUBE_H_
#define SUBD_TUTORIALS_GEOMETRY_CUBE_H_

namespace cube
{
    static float vertices[8][3] = {
        { -0.5f, -0.5f, 0.5f },
        { 0.5f, -0.5f, 0.5f },
        { -0.5f, 0.5f, 0.5f },
        { 0.5f, 0.5f, 0.5f },
        { -0.5f, 0.5f, -0.5f },
        { 0.5f, 0.5f, -0.5f },
        { -0.5f, -0.5f, -0.5f },
        { 0.5f, -0.5f, -0.5f }};

    static int nVerts = 8;
    static int nFaces = 6;

    static int verticesPerFace[6] = { 4, 4, 4, 4, 4, 4 };

    static int vertexIndices[24] = { 0, 1, 3, 2,
                                     2, 3, 5, 4,
                                     4, 5, 7, 6,
                                     6, 7, 1, 0,
                                     1, 7, 5, 3,
                                     6, 0, 2, 4 };
}

#endif //SUBD_TUTORIALS_GEOMETRY_CUBE_H_
