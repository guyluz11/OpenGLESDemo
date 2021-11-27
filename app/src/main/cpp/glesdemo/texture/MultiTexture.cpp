//
// Created by OuyangPeng on 2021/10/25.
//

#include "MultiTexture.h"

MultiTexture::MultiTexture() {

}

MultiTexture::~MultiTexture() {

}

void MultiTexture::create() {
	GLUtils::printGLInfo();

	// Main Program
	VERTEX_SHADER = GLUtils::openTextFile(
			"vertex/vertex_shader_multi_texture.glsl");
	FRAGMENT_SHADER = GLUtils::openTextFile(
			"fragment/fragment_shader_multi_texture.glsl");

	mProgram = GLUtils::createProgram(&VERTEX_SHADER, &FRAGMENT_SHADER);

	if (!mProgram) {
		LOGD("Could not create program")
		return;
	}

	// Get the sampler location
	baseMapLoc = glGetUniformLocation(mProgram, "s_baseMap");
	lightMapLoc = glGetUniformLocation(mProgram, "s_lightMap");

	// Load the textures
	// 从assets目录下 取出对应的Texture
	baseMapTexId = GLUtils::loadTexture("texture/basemap.png");
	lightMapTexId = GLUtils::loadTexture("texture/lightmap.png");

	if (baseMapTexId == 0 || lightMapTexId == 0)
	{
		return;
	}

	// 设置清除颜色
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}

void MultiTexture::change(int width, int height) {
	mWidth = width;
	mHeight = height;
	LOGD("change() width = %d , height = %d\n", width, height);
	// Set the viewport
	glViewport(0, 0, mWidth, mHeight);
}

void MultiTexture::draw() {
	GLfloat vVertices[] = {
			-0.5f,  0.5f, 0.0f,  // Position 0
			0.0f,  0.0f,        // TexCoord 0

			-0.5f, -0.5f, 0.0f,  // Position 1
			0.0f,  1.0f,        // TexCoord 1

			0.5f, -0.5f, 0.0f,  // Position 2
			1.0f,  1.0f,        // TexCoord 2

			0.5f,  0.5f, 0.0f,  // Position 3
			1.0f,  0.0f         // TexCoord 3
	};

	// 注意索引从0开始!
	GLushort indices[] = {
			0, 1, 2,		// 第一个三角形
			0, 2, 3			// 第二个三角形
	};

	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Use the program object
	glUseProgram(mProgram);

	// Load the vertex position
	glVertexAttribPointer(MULTI_TEXTURE_VERTEX_POS_INDX, 3, GL_FLOAT,
		GL_FALSE, 5 * sizeof(GLfloat), vVertices);
	// Load the texture coordinate
	glVertexAttribPointer(MULTI_TEXTURE_VERTEX_TEXCOORD_INDX, 2, GL_FLOAT,
		GL_FALSE, 5 * sizeof(GLfloat), &vVertices[3]);

	glEnableVertexAttribArray(MULTI_TEXTURE_VERTEX_POS_INDX);
	glEnableVertexAttribArray(MULTI_TEXTURE_VERTEX_TEXCOORD_INDX);

	// Bind the base map
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, baseMapTexId);

	// Set the base map sampler to texture unit to 0
	glUniform1i(baseMapLoc, 0);

	// Bind the light map
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightMapTexId);

	// Set the light map sampler to texture unit 1
	glUniform1i(lightMapLoc, 1);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);
}

void MultiTexture::shutdown() {
	// Delete texture object
	glDeleteTextures(1, &baseMapTexId);
	glDeleteTextures(1, &lightMapTexId);

	// Delete program object
	glDeleteProgram(mProgram);
}