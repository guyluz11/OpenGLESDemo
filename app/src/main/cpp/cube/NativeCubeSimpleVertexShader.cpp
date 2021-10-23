#include <cstring>
#include <malloc.h>
#include <math.h>
#include <sys/time.h>
#include "../log/LogUtils.h"
#include "../graphics/GLUtils.h"
#include "NativeCubeSimpleVertexShader.h"

namespace TRIANGLE_SIMPLE_VERTEXT_SHADER {
    void printGLString(const char *name, GLenum s) {
        const char *v = (const char *) glGetString(s);
        LOGI("GL %s = %s \n", name, v);
    }

    // 顶点着色器
    const char *VERTEX_SHADER_TRIANGLE =
            "#version 300 es                                        \n"
            "uniform mat4 u_mvpMatrix;                              \n"
            "layout(location = 0) in vec4 a_position;               \n"
            "layout(location = 1) in vec4 a_color;                  \n"
            "out vec4 v_color;                                      \n"
            "void main()                                            \n"
            "{                                                      \n"
            "   v_color = a_color;                                  \n"
            "   gl_Position = u_mvpMatrix * a_position;             \n"
            "}                                                      \n";

    // 片段着色器
    const char *FRAGMENT_SHADER_TRIANGLE =
            "#version 300 es                              \n"
            "precision mediump float;                     \n"
            "in vec4 v_color;                             \n"
            "layout(location = 0) out vec4 outColor;      \n"
            "void main()                                  \n"
            "{                                            \n"
            "   outColor = v_color;                       \n"
            "}                                            \n";

    NativeTriangle::NativeTriangle() {

    }

    NativeTriangle::~NativeTriangle() {

    }

    void NativeTriangle::create() {
        printGLString("Version", GL_VERSION);
        printGLString("Vendor", GL_VENDOR);
        printGLString("Renderer", GL_RENDERER);
        printGLString("Extensions", GL_EXTENSIONS);

        mProgram = GLUtils::createProgram(&VERTEX_SHADER_TRIANGLE, &FRAGMENT_SHADER_TRIANGLE);
        if (!mProgram) {
            LOGD("Could not create program");
            return;
        }

        // Get the uniform locations
        mvpLoc = glGetUniformLocation(mProgram, "u_mvpMatrix");

        // Generate the vertex data
        numIndices = esGenCube(1.0, &vertices, nullptr, nullptr, &indices);

        // Starting roating angle for cube
        angle = 45.0f;

        // 设置清除颜色
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    }

    void NativeTriangle::draw() {
        update(getDeltaTime());

        // Set the viewport
        glViewport(0, 0, mWidth, mHeight);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the program object
        glUseProgram(mProgram);

        // Load the vertex position
        glVertexAttribPointer(0, 3, GL_FLOAT,
                              GL_FALSE, 3 * sizeof(GLfloat), vertices);

        glEnableVertexAttribArray(0);

        // Set the vertex color to red
        glVertexAttrib4f(1, 1.0f, 0.0f, 0.0f, 1.0f);

        // Load the MVP matrix
        glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, (GLfloat *) &mvpMatrix.m[0][0]);

        // Draw the cube
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, indices);
    }

    float NativeTriangle::getDeltaTime() {
        struct timeval time{};
        if (mLastTime == 0) {
            // C++获取时间，精确到毫秒
            gettimeofday(&time, nullptr);
            mLastTime = time.tv_sec * 1000 + time.tv_usec / 1000;
        }
        gettimeofday(&time, nullptr);
        long currentTime = time.tv_sec * 1000 + time.tv_usec / 1000;
        long elapsedTime = currentTime - mLastTime;
        float deltaTime = (float) elapsedTime / 1000.0f;
        mLastTime = currentTime;
        return deltaTime;
    }

    void NativeTriangle::change(int width, int height) {
        mWidth = width;
        mHeight = height;
        LOGD("change() width = %d , height = %d\n", width, height);
    }

    int NativeTriangle::esGenCube(float scale, GLfloat **vertices, GLfloat **normals,
                                  GLfloat **texCoords, GLuint **indices) {
        int i;
        int numVertices = 24;
        int numIndices = 36;

        GLfloat cubeVerts[] =
                {
                        -0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f, 0.5f,
                        0.5f, -0.5f, 0.5f,
                        0.5f, -0.5f, -0.5f,
                        -0.5f, 0.5f, -0.5f,
                        -0.5f, 0.5f, 0.5f,
                        0.5f, 0.5f, 0.5f,
                        0.5f, 0.5f, -0.5f,
                        -0.5f, -0.5f, -0.5f,
                        -0.5f, 0.5f, -0.5f,
                        0.5f, 0.5f, -0.5f,
                        0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f, 0.5f,
                        -0.5f, 0.5f, 0.5f,
                        0.5f, 0.5f, 0.5f,
                        0.5f, -0.5f, 0.5f,
                        -0.5f, -0.5f, -0.5f,
                        -0.5f, -0.5f, 0.5f,
                        -0.5f, 0.5f, 0.5f,
                        -0.5f, 0.5f, -0.5f,
                        0.5f, -0.5f, -0.5f,
                        0.5f, -0.5f, 0.5f,
                        0.5f, 0.5f, 0.5f,
                        0.5f, 0.5f, -0.5f,
                };

        GLfloat cubeNormals[] =
                {
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,
                        0.0f, -1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 1.0f, 0.0f,
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, -1.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 1.0f,
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,
                        -1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                        1.0f, 0.0f, 0.0f,
                };

        GLfloat cubeTex[] =
                {
                        0.0f, 0.0f,
                        0.0f, 1.0f,
                        1.0f, 1.0f,
                        1.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f,
                        0.0f, 0.0f,
                        0.0f, 0.0f,
                        0.0f, 1.0f,
                        1.0f, 1.0f,
                        1.0f, 0.0f,
                        0.0f, 0.0f,
                        0.0f, 1.0f,
                        1.0f, 1.0f,
                        1.0f, 0.0f,
                        0.0f, 0.0f,
                        0.0f, 1.0f,
                        1.0f, 1.0f,
                        1.0f, 0.0f,
                        0.0f, 0.0f,
                        0.0f, 1.0f,
                        1.0f, 1.0f,
                        1.0f, 0.0f,
                };

        // Allocate memory for buffers
        if (vertices != nullptr) {
            *vertices = (GLfloat *) malloc(sizeof(GLfloat) * 3 * numVertices);
            memcpy(*vertices, cubeVerts, sizeof(cubeVerts));

            for (i = 0; i < numVertices * 3; i++) {
                (*vertices)[i] *= scale;
            }
        }

        if (normals != nullptr) {
            *normals = (GLfloat *) malloc(sizeof(GLfloat) * 3 * numVertices);
            memcpy(*normals, cubeNormals, sizeof(cubeNormals));
        }

        if (texCoords != nullptr) {
            *texCoords = (GLfloat *) malloc(sizeof(GLfloat) * 2 * numVertices);
            memcpy(*texCoords, cubeTex, sizeof(cubeTex));
        }


        // Generate the indices
        if (indices != nullptr) {
            GLuint cubeIndices[] =
                    {
                            0, 2, 1,
                            0, 3, 2,
                            4, 5, 6,
                            4, 6, 7,
                            8, 9, 10,
                            8, 10, 11,
                            12, 15, 14,
                            12, 14, 13,
                            16, 17, 18,
                            16, 18, 19,
                            20, 23, 22,
                            20, 22, 21
                    };

            *indices = (GLuint *) malloc(sizeof(GLuint) * numIndices);
            memcpy(*indices, cubeIndices, sizeof(cubeIndices));
        }

        return numIndices;
    }

    void NativeTriangle::update(float deltaTime) {
        ESMatrix perspective;
        ESMatrix modelview;
        float aspect;

        // Compute a rotation angle based on time to rotate the cube
        // 根据旋转立方体的时间计算旋转角度
        angle += (deltaTime * 40.0f);
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }

        // Compute the window aspect ratio
        // 计算窗口纵横比
        aspect = (GLfloat) mWidth / (GLfloat) mHeight;

        // Generate a perspective matrix with a 60 degree FOV
        // and near and far clip planes at 1.0 and 20.0
        esMatrixLoadIdentity(&perspective);
        esPerspective(&perspective, 60.0f, aspect, 1.0f, 20.0f);

        // Generate a model view matrix to rotate/translate the cube
        // 在modelview矩阵中加载一个单位矩阵
        esMatrixLoadIdentity(&modelview);

        // Translate away from the viewer
        // 单位矩阵结合一个平移，使物体远离观看者
        esTranslate(&modelview, 0.0, 0.0, -2.0);

        // Rotate the cube
        // 对modelview矩阵进行一次旋转，使物体饶向量(1.0,0.0,1.0) 以根据时间更新的角度连续旋转物体
        esRotate(&modelview, angle, 1.0, 0.0, 1.0);

        // Compute the final MVP by multiplying the
        // modevleiw and perspective matrices together
        // 计算MVP矩阵--- 模型-视图矩阵和投影矩阵的乘积
        esMatrixMultiply(&mvpMatrix, &modelview, &perspective);
    }

    void NativeTriangle::esMatrixLoadIdentity(NativeTriangle::ESMatrix *result) {
        memset(result, 0x0, sizeof(ESMatrix));
        result->m[0][0] = 1.0f;
        result->m[1][1] = 1.0f;
        result->m[2][2] = 1.0f;
        result->m[3][3] = 1.0f;
    }

    void NativeTriangle::esPerspective(NativeTriangle::ESMatrix *result, float fovy,
                                       float aspect, float nearZ, float farZ) {
        GLfloat frustumW, frustumH;

        frustumH = tanf(fovy / 360.0f * PI) * nearZ;
        frustumW = frustumH * aspect;

        esFrustum(result, -frustumW, frustumW, -frustumH, frustumH, nearZ, farZ);
    }


    void
    NativeTriangle::esFrustum(ESMatrix *result, float left, float right, float bottom, float top,
                              float nearZ, float farZ) {
        float deltaX = right - left;
        float deltaY = top - bottom;
        float deltaZ = farZ - nearZ;
        ESMatrix frust;

        if ((nearZ <= 0.0f)
            || (farZ <= 0.0f)
            || (deltaX <= 0.0f)
            || (deltaY <= 0.0f)
            || (deltaZ <= 0.0f)) {
            return;
        }

        frust.m[0][0] = 2.0f * nearZ / deltaX;
        frust.m[0][1] = frust.m[0][2] = frust.m[0][3] = 0.0f;

        frust.m[1][1] = 2.0f * nearZ / deltaY;
        frust.m[1][0] = frust.m[1][2] = frust.m[1][3] = 0.0f;

        frust.m[2][0] = (right + left) / deltaX;
        frust.m[2][1] = (top + bottom) / deltaY;
        frust.m[2][2] = -(nearZ + farZ) / deltaZ;
        frust.m[2][3] = -1.0f;

        frust.m[3][2] = -2.0f * nearZ * farZ / deltaZ;
        frust.m[3][0] = frust.m[3][1] = frust.m[3][3] = 0.0f;

        esMatrixMultiply(result, &frust, result);
    }

    void NativeTriangle::esMatrixMultiply(NativeTriangle::ESMatrix *result,
                                          NativeTriangle::ESMatrix *srcA,
                                          NativeTriangle::ESMatrix *srcB) {
        ESMatrix tmp;
        int i;

        for (i = 0; i < 4; i++) {
            tmp.m[i][0] = (srcA->m[i][0] * srcB->m[0][0]) +
                          (srcA->m[i][1] * srcB->m[1][0]) +
                          (srcA->m[i][2] * srcB->m[2][0]) +
                          (srcA->m[i][3] * srcB->m[3][0]);

            tmp.m[i][1] = (srcA->m[i][0] * srcB->m[0][1]) +
                          (srcA->m[i][1] * srcB->m[1][1]) +
                          (srcA->m[i][2] * srcB->m[2][1]) +
                          (srcA->m[i][3] * srcB->m[3][1]);

            tmp.m[i][2] = (srcA->m[i][0] * srcB->m[0][2]) +
                          (srcA->m[i][1] * srcB->m[1][2]) +
                          (srcA->m[i][2] * srcB->m[2][2]) +
                          (srcA->m[i][3] * srcB->m[3][2]);

            tmp.m[i][3] = (srcA->m[i][0] * srcB->m[0][3]) +
                          (srcA->m[i][1] * srcB->m[1][3]) +
                          (srcA->m[i][2] * srcB->m[2][3]) +
                          (srcA->m[i][3] * srcB->m[3][3]);
        }
        memcpy(result, &tmp, sizeof(ESMatrix));
    }

    void NativeTriangle::esTranslate(NativeTriangle::ESMatrix *result, GLfloat tx, GLfloat ty,
                                     GLfloat tz) {
        result->m[3][0] += (result->m[0][0] * tx + result->m[1][0] * ty + result->m[2][0] * tz);
        result->m[3][1] += (result->m[0][1] * tx + result->m[1][1] * ty + result->m[2][1] * tz);
        result->m[3][2] += (result->m[0][2] * tx + result->m[1][2] * ty + result->m[2][2] * tz);
        result->m[3][3] += (result->m[0][3] * tx + result->m[1][3] * ty + result->m[2][3] * tz);
    }

    void
    NativeTriangle::esRotate(NativeTriangle::ESMatrix *result, GLfloat angle, GLfloat x, GLfloat y,
                             GLfloat z) {
        GLfloat sinAngle, cosAngle;
        GLfloat mag = sqrtf(x * x + y * y + z * z);

        sinAngle = sinf(angle * PI / 180.0f);
        cosAngle = cosf(angle * PI / 180.0f);

        if (mag > 0.0f) {
            GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
            GLfloat oneMinusCos;
            ESMatrix rotMat;

            x /= mag;
            y /= mag;
            z /= mag;

            xx = x * x;
            yy = y * y;
            zz = z * z;
            xy = x * y;
            yz = y * z;
            zx = z * x;
            xs = x * sinAngle;
            ys = y * sinAngle;
            zs = z * sinAngle;
            oneMinusCos = 1.0f - cosAngle;

            rotMat.m[0][0] = (oneMinusCos * xx) + cosAngle;
            rotMat.m[0][1] = (oneMinusCos * xy) - zs;
            rotMat.m[0][2] = (oneMinusCos * zx) + ys;
            rotMat.m[0][3] = 0.0F;

            rotMat.m[1][0] = (oneMinusCos * xy) + zs;
            rotMat.m[1][1] = (oneMinusCos * yy) + cosAngle;
            rotMat.m[1][2] = (oneMinusCos * yz) - xs;
            rotMat.m[1][3] = 0.0F;

            rotMat.m[2][0] = (oneMinusCos * zx) - ys;
            rotMat.m[2][1] = (oneMinusCos * yz) + xs;
            rotMat.m[2][2] = (oneMinusCos * zz) + cosAngle;
            rotMat.m[2][3] = 0.0F;

            rotMat.m[3][0] = 0.0F;
            rotMat.m[3][1] = 0.0F;
            rotMat.m[3][2] = 0.0F;
            rotMat.m[3][3] = 1.0F;

            esMatrixMultiply(result, &rotMat, result);
        }
    }
}

// ====================================================================

static TRIANGLE_SIMPLE_VERTEXT_SHADER::NativeTriangle * nativeTriangle;

extern "C"
JNIEXPORT void JNICALL
Java_com_oyp_openglesdemo_cube_HelloCubeSimpleVertexShaderNativeRenderer_00024Companion_nativeSurfaceCreate(
        JNIEnv *env, jobject thiz) {
    nativeTriangle = new TRIANGLE_SIMPLE_VERTEXT_SHADER::NativeTriangle();
    if(nativeTriangle != nullptr){
        nativeTriangle->create();
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_oyp_openglesdemo_cube_HelloCubeSimpleVertexShaderNativeRenderer_00024Companion_nativeSurfaceChange(
        JNIEnv *env, jobject thiz, jint width, jint height) {
    if(nativeTriangle != nullptr){
        nativeTriangle->change(width,height);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_oyp_openglesdemo_cube_HelloCubeSimpleVertexShaderNativeRenderer_00024Companion_nativeDrawFrame(
        JNIEnv *env, jobject thiz) {
    if(nativeTriangle != nullptr){
        nativeTriangle->draw();
    }
}