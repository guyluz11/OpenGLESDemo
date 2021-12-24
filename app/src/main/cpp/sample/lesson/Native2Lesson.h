#ifndef OPENGLLESSON_NATIVE2LESSON_H
#define OPENGLLESSON_NATIVE2LESSON_H

#include <GLBaseSample.h>
#include "lesson_cube_data.h"
class Native2Lesson: public GLBaseSample {
public:
    Native2Lesson();

    virtual ~Native2Lesson();

    virtual void Create();

    virtual void Change(int width, int height);

    virtual void Draw();

    virtual void Shutdown();

private:
    Matrix *mViewMatrix;
    Matrix *mModelMatrix;
    Matrix *mProjectionMatrix;
    Matrix *mMVPMatrix;
    Matrix *mLightModelMatrix;

    GLuint mMVPMatrixHandle;
    GLuint mMVMatrixHandle;
    GLuint mLightPosHandle;

    GLuint mPerVertexProgramHandle;
    GLuint mPointProgramHandle;

    float mLightPosInModelSpace[4];
    float mLightPosInWorldSpace[4];
    float mLightPosInEyeSpace[4];

    void drawCube();

    void drawLight();
};

#endif //OPENGLLESSON_NATIVE2LESSON_H
