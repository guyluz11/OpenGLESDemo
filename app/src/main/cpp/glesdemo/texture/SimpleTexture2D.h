//
// Created by OuyangPeng on 2021/10/24.
//

#ifndef OPENGLESDEMO_SIMPLETEXTURE2D_H
#define OPENGLESDEMO_SIMPLETEXTURE2D_H

#include "../../utils/GLUtils.h"

#define SIMPLE_TEXTURE_2D_VERTEX_POS_INDEX       0
#define SIMPLE_TEXTURE_2D_VERTEX_TEXTCOORD_INDEX      1

class SimpleTexture2D : public BaseGLSample {

public:
    SimpleTexture2D();

    virtual ~SimpleTexture2D();

    virtual void create();

    virtual void change(int width, int height);

    virtual void draw();

    virtual void shutdown();

private:
    // Sampler location
    GLint samplerLoc;

    // Texture handle
    GLuint textureId;

    GLuint CreateSimpleTexture2D();
};

#endif //OPENGLESDEMO_SIMPLETEXTURE2D_H
