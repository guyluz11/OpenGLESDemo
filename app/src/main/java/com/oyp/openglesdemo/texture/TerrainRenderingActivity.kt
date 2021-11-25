package com.oyp.openglesdemo.texture

import android.opengl.GLSurfaceView
import com.oyp.openglesdemo.BaseGLActivity

class TerrainRenderingActivity : BaseGLActivity() {
    override fun getSurfaceView(): GLSurfaceView {
        return GLSurfaceView(this)
    }

    override fun getRender(): GLSurfaceView.Renderer {
        return TerrainRenderer(this)
    }
}