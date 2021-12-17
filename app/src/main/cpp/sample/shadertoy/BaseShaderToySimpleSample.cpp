//
// Created by OuyangPeng on 2021/12/15.
//

// 参考自：

// 原Shader地址【shadertoy】：https://www.shadertoy.com/view/3sBGzV
// https://glslsandbox.com/e#77894.0

#include "BaseShaderToySimpleSample.h"

BaseShaderToySimpleSample::BaseShaderToySimpleSample(int renderSampleType) {
    m_SamplerLoc = GL_NONE;
    m_MVPMatLoc = GL_NONE;

    m_VaoId = GL_NONE;

    m_AngleX = 0;
    m_AngleY = 0;

    m_ScaleX = 1.0f;
    m_ScaleY = 1.0f;

    mRenderSampleType = renderSampleType;
}

void BaseShaderToySimpleSample::create() {
    // 编译链接用于普通渲染的着色器程序
    VERTEX_SHADER = GLUtils::openTextFile(
            "vertex/vertex_shader_beating_heart.glsl");

    switch(mRenderSampleType){
        case SAMPLE_TYPE_KEY_SHADER_TOY_BEATING_HEART:
            mFragmentShaderPath = "fragment/fragment_shader_toy_beating_heart.glsl";
            break;
        case SAMPLE_TYPE_KEY_SHADER_TOY_CLOUD:
            mFragmentShaderPath = "fragment/fragment_shader_toy_cloud.glsl";
            break;
        case SAMPLE_TYPE_KEY_SHADER_TOY_SKY_PATH:
            mFragmentShaderPath = "fragment/fragment_shader_toy_sky_path.glsl";
            break;
        case SAMPLE_TYPE_KEY_SHADER_TOY_A_DAY:
            mFragmentShaderPath = "fragment/fragment_shader_toy_a_day_1.glsl";
            break;
        default:
            mFragmentShaderPath = GL_NONE;
            break;
    }

    LOGD("BaseShaderToySimpleSample::create() mRenderSampleType =%d, mFragmentShaderPath = %s",
         mRenderSampleType, mFragmentShaderPath)

    if(mFragmentShaderPath == GL_NONE){
         LOGD("BaseShaderToySimpleSample::create() mFragmentShaderPath == GL_NONE 直接return")
        return;
    }

    // 用于普通渲染的片段着色器脚本，简单纹理映射
    FRAGMENT_SHADER = GLUtils::openTextFile(mFragmentShaderPath);

    mProgram = GLUtils::createProgram(&VERTEX_SHADER, &FRAGMENT_SHADER);
    if (mProgram == GL_NONE) {
        LOGE("CoordSystemSample::Init mProgram == GL_NONE")
        return;
    }

    m_SamplerLoc = glGetUniformLocation(mProgram, "s_TextureMap");
    m_MVPMatLoc = glGetUniformLocation(mProgram, "u_MVPMatrix");

    iResolution = glGetUniformLocation(mProgram, "iResolution");
    iTime = glGetUniformLocation(mProgram, "iTime");

    GLfloat verticesCoords[] = {
            -1.0f, 1.0f, 0.0f,  // Position 0
            -1.0f, -1.0f, 0.0f,  // Position 1
            1.0f, -1.0f, 0.0f,  // Position 2
            1.0f, 1.0f, 0.0f,  // Position 3
    };

    GLushort indices[] = {0, 1, 2, 0, 2, 3};

    // Generate VBO Ids and load the VBOs with data
    glGenBuffers(2, m_VboIds);
    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCoords), verticesCoords, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    // Generate VAO Id
    glGenVertexArrays(1, &m_VaoId);
    glBindVertexArray(m_VaoId);

    glBindBuffer(GL_ARRAY_BUFFER, m_VboIds[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VboIds[1]);
    glBindVertexArray(GL_NONE);

    // 设置清除颜色
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void BaseShaderToySimpleSample::draw() {
    LOGD("BaseShaderToySimpleSample::Draw()")

    if (mProgram == GL_NONE) return;

    glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Use the program object
    glUseProgram(mProgram);

    UpdateMVPMatrix(m_MVPMatrix, m_AngleX, m_AngleY, (float) mWidth / (float) mHeight);

    glBindVertexArray(m_VaoId);

    glUniformMatrix4fv(m_MVPMatLoc, 1, GL_FALSE, &m_MVPMatrix[0][0]);

    // 根据特效的不同类型，传递不同的iTime给片段着色器
    switch(mRenderSampleType){
        case SAMPLE_TYPE_KEY_SHADER_TOY_BEATING_HEART: {
            auto time = static_cast<float>(fmod(GetSysCurrentTime(), 2000) / 2000);
            LOGD("BeatingHeartSample::Draw() time=%f", time)
            // 控制输入时间周期为 2000ms
            glUniform1f(iTime, time);
            break;
        }
        case SAMPLE_TYPE_KEY_SHADER_TOY_CLOUD:
        case SAMPLE_TYPE_KEY_SHADER_TOY_SKY_PATH:
        case SAMPLE_TYPE_KEY_SHADER_TOY_A_DAY:{
            static int sFrameIndex = 0;
            sFrameIndex++;
            float time2 = sFrameIndex * 0.04f;
            LOGD("BaseShaderToySimpleSample::Draw() time=%f", time2)
            // 控制输入时间周期为 2000ms
            glUniform1f(iTime, time2);
            break;
        }
    }
    // 输入屏幕的尺寸
    glUniform2f(iResolution, mWidth, mHeight);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, nullptr);
}

void BaseShaderToySimpleSample::shutdown() {
    if (mProgram) {
        glDeleteProgram(mProgram);
        glDeleteBuffers(2, m_VboIds);
        glDeleteVertexArrays(1, &m_VaoId);
    }
}


void
BaseShaderToySimpleSample::UpdateMVPMatrix(glm::mat4 &mvpMatrix, int angleX, int angleY,
                                           float ratio) const {
    LOGD("BaseShaderToySimpleSample::UpdateMVPMatrix angleX = %d, angleY = %d, ratio = %f", angleX,
         angleY, ratio)
    angleX = angleX % 360;
    angleY = angleY % 360;

    //转化为弧度角
    auto radiansX = static_cast<float>(MATH_PI / 180.0f * angleX);
    auto radiansY = static_cast<float>(MATH_PI / 180.0f * angleY);


    // Projection matrix
    glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

    // View matrix
    glm::mat4 View = glm::lookAt(
            glm::vec3(0, 0, 4), // Camera is at (0,0,1), in World Space
            glm::vec3(0, 0, 0), // and looks at the origin
            glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    // Model matrix
    glm::mat4 Model = glm::mat4(1.0f);
    Model = glm::scale(Model, glm::vec3(m_ScaleX, m_ScaleY, 1.0f));
    Model = glm::rotate(Model, radiansX, glm::vec3(1.0f, 0.0f, 0.0f));
    Model = glm::rotate(Model, radiansY, glm::vec3(0.0f, 1.0f, 0.0f));
    Model = glm::translate(Model, glm::vec3(0.0f, 0.0f, 0.0f));

    mvpMatrix = Projection * View * Model;
}
