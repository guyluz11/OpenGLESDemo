#ifndef OPEN_GL_LESSON_NATIVE_GL_UTILS_H_
#define OPEN_GL_LESSON_NATIVE_GL_UTILS_H_

#include <jni.h>
#include <GLES3/gl3.h>
#include <GLES3/gl3ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <android/asset_manager_jni.h>

#include "./graphics/Matrix.h"
#include "./log/LogUtils.h"
#include "./time/TimeUtils.h"
#include "esShapes.h"
#include "esTransform.h"

#include "../glesdemo/BaseGLSample.h"

class GLUtils {
public:
	/**
	 * Set Environment parameter
	 */
	static void setEnvAndAssetManager(JNIEnv* env, jobject assetManager);

	/**
	 *  Loads a file from assets/path into a char array.
	 */
	static char* openTextFile(const char* path);

	/**
	 * Loads a texture from assets/texture/<name>
	 */
	static GLuint loadTexture(const char* name);

	static GLuint loadTgaTexture(const char *fileName);
	/**
	 * Create a program with the given vertex and framgent
	 * shader source code.
	 */
	static GLuint createProgram(const char** vertexSource, const char** fragmentSource);

	static void checkGlError(const char* pGLOperation);

	static void printGLString(const char *name, GLenum s) {
		const char *v = (const char *) glGetString(s);
		LOGI("GL %s = %s \n", name, v);
	}

	// Print some OpenGL info
	static void printGLInfo(){
		printGLString("Version", GL_VERSION);
		printGLString("GLSL Version", GL_SHADING_LANGUAGE_VERSION);
		printGLString("Vendor", GL_VENDOR);
		printGLString("Renderer", GL_RENDERER);
		printGLString("Extensions", GL_EXTENSIONS);
	}
};

#endif //OPEN_GL_LESSON_NATIVE_GL_UTILS_H_
