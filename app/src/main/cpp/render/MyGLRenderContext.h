//
// Created by OuyangPeng on 2021/11/26.
//

#ifndef OPENGLESDEMO_MYGLRENDERCONTEXT_H
#define OPENGLESDEMO_MYGLRENDERCONTEXT_H

#include <BaseGLSample.h>

class MyGLRenderContext
{
    MyGLRenderContext();

    ~MyGLRenderContext();

public:
    void SetParamsInt(int paramType, int value0, int value1);

    void OnSurfaceCreated(JNIEnv *env, jobject assetManager);

    void OnSurfaceChanged(int width, int height);

    void OnDrawFrame();

    static MyGLRenderContext* GetInstance();

    static void DestroyInstance();

    void SwitchBlendingMode();

    void SetDelta(float x, float y);

    void SetMinFilter(int filter);

    void SetMagFilter(int filter);


private:
    static MyGLRenderContext *m_pContext;
    BaseGLSample *m_pBeforeSample;
    BaseGLSample *m_pCurSample;
    int m_ScreenW;
    int m_ScreenH;
};

#endif //OPENGLESDEMO_MYGLRENDERCONTEXT_H
