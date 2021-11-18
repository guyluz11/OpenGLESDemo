//
// Created by OuyangPeng on 2021/10/25.
//

#pragma once
#include "Noise3D.h"
#include "../../utils/GLUtils.h"

// Attribute locations
#define ATTRIB_LOCATION_POS      0
#define ATTRIB_LOCATION_COLOR    1
#define ATTRIB_LOCATION_TEXCOORD 2

#define NOISE_TABLE_MASK   255

#define FLOOR(x)           ((int)(x) - ((x) < 0 && (x) != (int)(x)))
#define smoothstep(t)      ( t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f ) )
#define lerp(t, a, b)      ( a + t * (b - a) )


class Noise3DRender {
public:
    Noise3DRender();

    ~Noise3DRender();

    void create();

    void change(int width, int height);

    void draw();

    void shutdown();

private:
    // Handle to a program object
    GLuint programObject;

    // Uniform locations
    GLint  mvpLoc;
    GLint  mvLoc;
    GLint  fogMinDistLoc;
    GLint  fogMaxDistLoc;
    GLint  fogColorLoc;
    GLint  noiseTexLoc;
    GLint  timeLoc;

    // Vertex daata
    GLfloat  *vertices;
    GLfloat  *texCoords;
    GLuint   *indices;
    int       numIndices;

    // Rotation angle
    GLfloat   angle;

    // Matrices
    ESMatrix  mvMatrix;
    ESMatrix  mvpMatrix;

    long mLastTime = 0;

    // Time
    float curTime;

    // Texture handle
    GLuint textureId;

    int mWidth;
    int mHeight;

    void update(float deltaTime);

    float getDeltaTime();
};

