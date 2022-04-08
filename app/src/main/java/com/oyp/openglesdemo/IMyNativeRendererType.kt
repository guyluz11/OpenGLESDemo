package com.oyp.openglesdemo

object IMyNativeRendererType {

    const val RENDER_TYPE: String = "RENDER_TYPE"

    const val SAMPLE_TYPE = 100
    // 《OPENGL ES 3.0编程指南》里面的例子
    const val SAMPLE_TYPE_TRIANGLE                                               = SAMPLE_TYPE
    const val SAMPLE_TYPE_TRIANGLE2                                              = SAMPLE_TYPE + 1
    const val SAMPLE_TYPE_TRIANGLE3                                              = SAMPLE_TYPE + 2
    const val SAMPLE_TYPE_KEY_TRIANGLE_MAP_BUFFERS                               = SAMPLE_TYPE + 3
    const val SAMPLE_TYPE_KEY_TRIANGLE_VERTEX_ARRAY_OBJECT                       = SAMPLE_TYPE + 4
    const val SAMPLE_TYPE_KEY_TRIANGLE_VERTEX_BUFFER_OBJECT                      = SAMPLE_TYPE + 5
    const val SAMPLE_TYPE_KEY_CUBE_SIMPLE_VERTEX_SHADER                          = SAMPLE_TYPE + 6
    const val SAMPLE_TYPE_KEY_SIMPLE_TEXTURE_2D                                  = SAMPLE_TYPE + 7
    const val SAMPLE_TYPE_KEY_SIMPLE_TEXTURE_CUBE_MAP                            = SAMPLE_TYPE + 8
    const val SAMPLE_TYPE_KEY_MIPMAP_2D                                          = SAMPLE_TYPE + 9
    const val SAMPLE_TYPE_KEY_TEXTURE_WRAP                                       = SAMPLE_TYPE + 10
    const val SAMPLE_TYPE_KEY_MULTI_TEXTURE                                      = SAMPLE_TYPE + 11
    const val SAMPLE_TYPE_KEY_PARTICLE_SYSTEM                                    = SAMPLE_TYPE + 12
    const val SAMPLE_TYPE_KEY_PARTICLE_SYSTEM_TRANSFORM_FEEDBACK                 = SAMPLE_TYPE + 13
    const val SAMPLE_TYPE_KEY_NOISE3D                                            = SAMPLE_TYPE + 14
    const val SAMPLE_TYPE_KEY_MRT                                                = SAMPLE_TYPE + 15
    const val SAMPLE_TYPE_KEY_TERRAIN_RENDER                                     = SAMPLE_TYPE + 16
    const val SAMPLE_TYPE_KEY_SHADOWS                                            = SAMPLE_TYPE + 17


    // http://www.learnopengles.com/  里面的例子
    const val SAMPLE_TYPE_KEY_LESSON_ONE                                         = SAMPLE_TYPE + 18
    const val SAMPLE_TYPE_KEY_LESSON_TWO                                         = SAMPLE_TYPE + 19
    const val SAMPLE_TYPE_KEY_LESSON_THREE                                       = SAMPLE_TYPE + 20
    const val SAMPLE_TYPE_KEY_LESSON_FOUR                                        = SAMPLE_TYPE + 21
    const val SAMPLE_TYPE_KEY_LESSON_FIVE                                        = SAMPLE_TYPE + 22
    const val SAMPLE_TYPE_KEY_LESSON_SIX                                         = SAMPLE_TYPE + 23
    const val SAMPLE_TYPE_KEY_LESSON_SEVEN                                       = SAMPLE_TYPE + 24
    const val SAMPLE_TYPE_KEY_LESSON_EIGHT                                       = SAMPLE_TYPE + 25



    // 字节流动  的 例子
    const val SAMPLE_TYPE_KEY_TEXTURE_MAP                                        = SAMPLE_TYPE + 26
    const val SAMPLE_TYPE_KEY_YUV_RENDER                                         = SAMPLE_TYPE + 27
    const val SAMPLE_TYPE_KEY_FBO                                                = SAMPLE_TYPE + 28

    // EGL 渲染，单独启动一个EGLActivity
    const val SAMPLE_TYPE_KEY_EGL                                                = SAMPLE_TYPE + 29

    const val SAMPLE_TYPE_KEY_FBO_LEG                                            = SAMPLE_TYPE + 30
    const val SAMPLE_TYPE_KEY_COORD_SYSTEM                                       = SAMPLE_TYPE + 31
    const val SAMPLE_TYPE_KEY_BASE_LIGHT                                         = SAMPLE_TYPE + 32
    const val SAMPLE_TYPE_KEY_MULTI_LIGHT                                        = SAMPLE_TYPE + 33
    const val SAMPLE_TYPE_KEY_INSTANCING                                         = SAMPLE_TYPE + 34
    const val SAMPLE_TYPE_KEY_STENCIL_TESTING                                    = SAMPLE_TYPE + 35
    const val SAMPLE_TYPE_KEY_BLENDING                                           = SAMPLE_TYPE + 36
    const val SAMPLE_TYPE_KEY_PARTICLE_SYSTEM2                                   = SAMPLE_TYPE + 37
    const val SAMPLE_TYPE_KEY_SKYBOX                                             = SAMPLE_TYPE + 38
    const val SAMPLE_TYPE_KEY_PBO                                                = SAMPLE_TYPE + 39
    const val SAMPLE_TYPE_KEY_SHADER_TOY_BEATING_HEART                           = SAMPLE_TYPE + 40
    const val SAMPLE_TYPE_KEY_SHADER_TOY_CLOUD                                   = SAMPLE_TYPE + 41
    const val SAMPLE_TYPE_KEY_SHADER_TOY_TIME_TUNNEL                             = SAMPLE_TYPE + 42
    const val SAMPLE_TYPE_KEY_SHADER_TOY_MAIN_SEQUENCE_STAR                      = SAMPLE_TYPE + 43
    const val SAMPLE_TYPE_KEY_SHADER_TOY_SKY_PATH                                = SAMPLE_TYPE + 44
    const val SAMPLE_TYPE_KEY_SHADER_TOY_A_DAY                                   = SAMPLE_TYPE + 45
    const val SAMPLE_TYPE_KEY_SHADER_TOY_ATMOSPHERE_SYSTEM_TEST                  = SAMPLE_TYPE + 46
    const val SAMPLE_TYPE_KEY_BEZIER_CURVE                                       = SAMPLE_TYPE + 47
    const val SAMPLE_TYPE_KEY_BIG_EYES                                           = SAMPLE_TYPE + 48
    const val SAMPLE_TYPE_KEY_FACE_SLENDER                                       = SAMPLE_TYPE + 49
    const val SAMPLE_TYPE_KEY_BIG_HEAD                                           = SAMPLE_TYPE + 50
    const val SAMPLE_TYPE_KEY_RATARY_HEAD                                        = SAMPLE_TYPE + 51
    const val SAMPLE_TYPE_KEY_VISUALIZE_AUDIO                                    = SAMPLE_TYPE + 52
    const val SAMPLE_TYPE_KEY_SCRATCH_CARD                                       = SAMPLE_TYPE + 53
    const val SAMPLE_TYPE_KEY_AVATAR                                             = SAMPLE_TYPE + 54
    const val SAMPLE_TYPE_KEY_SHOCK_WAVE                                         = SAMPLE_TYPE + 55
    const val SAMPLE_TYPE_KEY_MRT2                                               = SAMPLE_TYPE + 56
    const val SAMPLE_TYPE_KEY_FBO_BLIT                                           = SAMPLE_TYPE + 57
    const val SAMPLE_TYPE_KEY_UBO                                                = SAMPLE_TYPE + 58
    const val SAMPLE_TYPE_KEY_RGB2YUV                                            = SAMPLE_TYPE + 59
    const val SAMPLE_TYPE_KEY_MULTI_THREAD_RENDER                                = SAMPLE_TYPE + 60
    const val SAMPLE_TYPE_KEY_TEXT_RENDER                                        = SAMPLE_TYPE + 61
    const val SAMPLE_TYPE_KEY_STAY_COLOR                                         = SAMPLE_TYPE + 62
    const val SAMPLE_TYPE_KEY_TRANSITIONS_1                                      = SAMPLE_TYPE + 63
    const val SAMPLE_TYPE_KEY_TRANSITIONS_2                                      = SAMPLE_TYPE + 64
    const val SAMPLE_TYPE_KEY_TRANSITIONS_3                                      = SAMPLE_TYPE + 65
    const val SAMPLE_TYPE_KEY_TRANSITIONS_4                                      = SAMPLE_TYPE + 66
    const val SAMPLE_TYPE_KEY_TRANSITIONS_5                                      = SAMPLE_TYPE + 67
    const val SAMPLE_TYPE_KEY_TRANSITIONS_6                                      = SAMPLE_TYPE + 68
    const val SAMPLE_TYPE_KEY_TRANSITIONS_7                                      = SAMPLE_TYPE + 69
    const val SAMPLE_TYPE_KEY_TRANSITIONS_8                                      = SAMPLE_TYPE + 70
    const val SAMPLE_TYPE_KEY_TRANSITIONS_9                                      = SAMPLE_TYPE + 71
    const val SAMPLE_TYPE_KEY_TRANSITIONS_10                                     = SAMPLE_TYPE + 72
    const val SAMPLE_TYPE_KEY_TRANSITIONS_11                                     = SAMPLE_TYPE + 73
    const val SAMPLE_TYPE_KEY_TRANSITIONS_12                                     = SAMPLE_TYPE + 74
    const val SAMPLE_TYPE_KEY_TRANSITIONS_13                                     = SAMPLE_TYPE + 75
    const val SAMPLE_TYPE_KEY_TRANSITIONS_14                                     = SAMPLE_TYPE + 76
    const val SAMPLE_TYPE_KEY_TRANSITIONS_15                                     = SAMPLE_TYPE + 77
    const val SAMPLE_TYPE_KEY_TRANSITIONS_16                                     = SAMPLE_TYPE + 78
    const val SAMPLE_TYPE_KEY_TRANSITIONS_17                                     = SAMPLE_TYPE + 79
    const val SAMPLE_TYPE_KEY_TRANSITIONS_18                                     = SAMPLE_TYPE + 80
    const val SAMPLE_TYPE_KEY_TRANSITIONS_19                                     = SAMPLE_TYPE + 81
    const val SAMPLE_TYPE_KEY_TRANSITIONS_20                                     = SAMPLE_TYPE + 82
    const val SAMPLE_TYPE_KEY_TRANSITIONS_21                                     = SAMPLE_TYPE + 83
    const val SAMPLE_TYPE_KEY_3D_MODEL                                           = SAMPLE_TYPE + 84

    const val SAMPLE_TYPE_KEY_AIR_HOCKEY                                         = SAMPLE_TYPE + 85


    const val SAMPLE_TYPE_KEY_RECTANGLE                                          = SAMPLE_TYPE + 86
    const val SAMPLE_TYPE_KEY_STICKER                                            = SAMPLE_TYPE + 87
    const val SAMPLE_TYPE_KEY_TIME_WATERMARK_STICKER                             = SAMPLE_TYPE + 88

    const val SAMPLE_TYPE_KEY_3D_MODEL2                                          = SAMPLE_TYPE + 89
    const val SAMPLE_TYPE_KEY_GREEN_SCREEN_MATTING                               = SAMPLE_TYPE + 90
    const val SAMPLE_TYPE_KEY_GREEN_SCREEN_MATTING_MIX                           = SAMPLE_TYPE + 91
    const val SAMPLE_TYPE_KEY_ROTATE_TEXTURE                                     = SAMPLE_TYPE + 92
}