package com.oyp.openglesdemo.render

import android.app.Activity
import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import com.oyp.openglesdemo.IMyNativeRendererType
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class MyNativeRenderer(activity: Activity) : GLSurfaceView.Renderer, RenderAction {
    private var mActivity: Activity = activity
    var mSampleType = 0

    init {
        System.loadLibrary("ouyangpeng-opengles-lib")
    }

    ////////////////////////////////// Native 方法///////////////////////////////////////
    // 通用的
    private external fun nativeSurfaceCreate(assetManager: AssetManager)
    private external fun nativeSurfaceChange(width: Int, height: Int)
    private external fun nativeDrawFrame()
    private external fun nativeSetRenderType(sampleCategoryType: Int, renderSampleType: Int)
    private external fun nativeOnDestroy()

    // 特定的方法
    private external fun nativeSwitchBlendingMode()

    // 特定的方法
    private external fun nativeSetDelta(x: Float, y: Float)
    private external fun nativeSetMinFilter(filter: Int)
    private external fun nativeSetMagFilter(filter: Int)

    private external fun nativeSetImageData(
        format: Int,
        width: Int,
        height: Int,
        imageData: ByteArray?
    )

    private external fun nativeSetImageDataWithIndex(
        index: Int,
        format: Int,
        width: Int,
        height: Int,
        imageData: ByteArray?
    )

    private external fun nativeUpdateTransformMatrix(
        rotateX: Float,
        rotateY: Float,
        scaleX: Float,
        scaleY: Float
    )

    private external fun nativeSetAudioData(audioData: ShortArray)

    private external fun nativeSetTouchLocation(x: Float, y: Float)

    private external fun nativeSetGravityXY(x: Float, y: Float)

    ////////////////////////////////// Java 方法///////////////////////////////////////

    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        val assetManager: AssetManager = mActivity.assets
        nativeSurfaceCreate(assetManager)
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        nativeSurfaceChange(width, height)
    }

    override fun onDrawFrame(gl: GL10) {
        nativeDrawFrame()
    }

    fun setRenderType(sampleCategoryType: Int, renderSampleType: Int) {
        if (sampleCategoryType == IMyNativeRendererType.SAMPLE_TYPE) {
            mSampleType = renderSampleType
        }
        nativeSetRenderType(sampleCategoryType, renderSampleType)
    }

    fun onDestroy() {
        nativeOnDestroy()
    }

    override fun switchBlendingMode() {
        nativeSwitchBlendingMode()
    }

    override fun setMinFilter(filter: Int) {
        nativeSetMinFilter(filter)
    }

    override fun setMagFilter(filter: Int) {
        nativeSetMagFilter(filter)
    }

    override fun setDelta(deltaX: Float, deltaY: Float) {
        nativeSetDelta(deltaX, deltaY)
    }

    override fun setImageData(
        format: Int,
        width: Int,
        height: Int,
        imageData: ByteArray
    ) {
        nativeSetImageData(format, width, height, imageData)
    }

    override fun setImageDataWithIndex(
        index: Int,
        format: Int,
        width: Int,
        height: Int,
        imageData: ByteArray
    ) {
        nativeSetImageDataWithIndex(index, format, width, height, imageData)
    }

    override fun updateTransformMatrix(
        rotateX: Float,
        rotateY: Float,
        scaleX: Float,
        scaleY: Float
    ) {
        nativeUpdateTransformMatrix(rotateX, rotateY, scaleX, scaleY)
    }

    override fun setAudioData(audioData: ShortArray) {
        nativeSetAudioData(audioData)
    }

    override fun setTouchLocation(x: Float, y: Float) {
        nativeSetTouchLocation(x,y)
    }

    override fun setGravityXY(x: Float, y: Float){
        nativeSetGravityXY(x,y)
    }
}