package com.oyp.openglesdemo.lesson

import android.opengl.GLSurfaceView
import com.oyp.openglesdemo.BaseGLActivity

class LessonThreeActivity : BaseGLActivity() {
    override fun getSurfaceView(): GLSurfaceView {
        return GLSurfaceView(this)
    }

    override fun getRender(): GLSurfaceView.Renderer {
        return LessonThreeNativeRenderer()
    }
}
