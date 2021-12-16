//
// Created by OuyangPeng on 2021/12/15.
//

#ifndef OPENGLESDEMO_CLOUDSAMPLE_H
#define OPENGLESDEMO_CLOUDSAMPLE_H

#include <glm/gtc/matrix_transform.hpp>
#include <GLBaseSample.h>

class CloudSample : public GLBaseSample {

public:
    CloudSample();

    virtual ~CloudSample() = default;

    virtual void create();

    virtual void draw();

    virtual void shutdown();

    void UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY, float ratio) const;

private:
    GLint m_SamplerLoc;
    GLint m_TimeLoc;
    GLint m_SizeLoc;
    GLint m_MVPMatLoc;
    GLuint m_VaoId;
    GLuint m_VboIds[2];
    glm::mat4 m_MVPMatrix;

    int m_AngleX;
    int m_AngleY;
    float m_ScaleX;
    float m_ScaleY;
};


#endif //OPENGLESDEMO_CLOUDSAMPLE_H
