#version 300 es
// 使用的是 highp 精度，但是当使用 mediump 精度时，会出现由于精度不够导致的毛刺现象，
precision highp float;

// 参考自博客：
// 不瞒你说，我被这个特效感动哭了（OpenGL ES 特效） https://blog.csdn.net/Kennethdroid/article/details/104536532
// 【ShaderToy】跳动的心❤️https://blog.csdn.net/candycat1992/article/details/44040273
// 心跳的原Shader地址【shadertoy】：https://www.shadertoy.com/view/XsfGRn
// 心脏线的定义：https://baike.baidu.com/item/%E5%BF%83%E8%84%8F%E7%BA%BF/10323843?fr=aladdin

// 输出
layout(location = 0) out vec4 outColor;
//时间偏移量
uniform float iTime;
//屏幕尺寸 宽和高
uniform vec2 iResolution;


// --------[ Original ShaderToy begins here ]---------- //
// Created by inigo quilez - iq/2013
//   https://www.youtube.com/c/InigoQuilez
//   https://iquilezles.org/
// I share this piece (art and code) here in Shadertoy and through its Public API, only for educational purposes.
// You cannot use, sell, share or host this piece or modifications of it as part of your own commercial or non-commercial product, website or project.
// You can share a link to it or an unmodified screenshot of it provided you attribute "by Inigo Quilez, @iquilezles and iquilezles.org".
// If you are a teacher, lecturer, educator or similar and these conditions are too restrictive for your needs, please contact me and we'll work it out.

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    // 先计算了每个像素点到中心的方向,然后再除以屏幕的高度（或宽度）
    // 这样的计算结果可以保存每个像素点距离中心的方向、远近等信息。
    vec2 p = (2.0 * fragCoord - iResolution.xy) / min(iResolution.y, iResolution.x);

    // background color  计算背景颜色 bcol
    // length(p) 表示计算当前片元（像素）与屏幕中心点的距离，
    // 背景颜色以 vec3(1.0,0.8,0.8) 该颜色为基础，距离屏幕越远颜色越暗。

    // bcol可以认为是一个主背景颜色和像素距离中心点远近值的乘积。
    // 其中， (1.0-0.25*length(p))是我们对上一步得到的距离进行进一步计算，
    // 由于 length(p)的值可能大于1（如果屏幕x轴大于y轴，那么p的x方向的绝对值有些会大于1；
    // 反之，如果屏幕y轴大于x轴，那么p的y方向的绝对值有些会大于1），
    // 因此，我们需要在 length ( p )的基础上乘以系数0.25。

    // 当然，0.25是经验值，我们可以把这个参数做成shader的一个属性，供调节。
    // vec3(1.0,0.8,0.7-0.07*p.y)中， vec3 ( 1.0 , 0.8 , 0.7)是背景主色调，我们同样可以把它做成一个shader属性。
    // 后面会给出。而在B通道上减去 0.07 * p . y可以当成是一个轻微的效果修正，即在y方向上，可以有些许颜色变化，其中0.07也是一个经验值，可以更改。
    vec3 bcol = vec3(1.0,0.8,0.7-0.07*p.y)*(1.0-0.25*length(p));
//    vec3 bcol = vec3(1.0, 0.8, 0.8) * (1.0-0.25 * length(p));



    // animate
    // 跳动效果的实现，其原理就是对屏幕像素在 x、y 方向进行周期性偏移，偏移幅度由特殊的函数来控制。
    //iTime 为周期性输入的时间，由C++程序控制输入
    float tt = mod(iTime,1.5)/1.5;
    float ss = pow(tt, 0.2) * 0.5 + 0.5;
    // 控制幅度的函数
    ss = 1.0 + ss * 0.5 * sin(tt * 6.2831 * 3.0 + p.y * 0.5) * exp(-tt * 4.0);
    p *= vec2(0.5, 1.5) + ss * vec2(0.5, -0.5);



    // shape 接着绘制心形 主要利用反正切函数值和当前片元（像素）与屏幕中心点的距离相比较，来确定心形状的边界。
    // GLES 中的反正切函数 atan(p.x,p.y) 取值范围是[-π, π]，然后除以 PI 后，取值范围变成了 [-1, 1] 。
    #if 0
    p *= 0.8;
    p.y = -0.1 - p.y * 1.2 + abs(p.x) * (1.0 - abs(p.x));
    float r = length(p);
    float d = 0.5;
    #else
    // 向屏幕下方偏移 0.25 个单位
    // 移动中心点的位置来控制渐变。代码中是将y减去了0.25，即将中心点向上移动了屏幕高度的0.25/2=0.125个单位。
    p.y -= 0.25;
    // π
    float PI = 3.141592653;
    // GLES 中的反正切函数 atan(p.x,p.y) 取值范围是[-π, π]，然后除以 PI 后，取值范围变成了 [-1, 1]
    // 先来看a的含义。它是该像素对应方向的反正切值和π相除的结果。
    // atan对应CG中的 atan2函数，它的值域为[-π, π]。
    // 我们可以理解为，它返回的是X轴旋转到该方向所需要转过的角度（不超过正负180°）。
    // 因此，a得到的其实是一个范围在[-1.0, 1.0]之间的浮点值。
    // 我们就可以通过判断该像素对应方向的长度r和a的差来判断该像素是否在心形内了。
    float a = atan(p.x, p.y) / PI;
    // length(p) 表示计算当前片元（像素）与屏幕中心点的距离，
    float r = length(p);
    // h对a取绝对值，使得a的负值区域同样可以得到半个心形。
    float h = abs(a);
    // 而d对h进行修正，使心的形状更加扁平化
    float d = (13.0*h - 22.0 * h * h + 10.0 * h * h * h) / (6.0-5.0 * h);
    #endif



    //  计算心的颜色hcol
    // 根据p的x方向来得到一个在x方向上的渐变
    float s = 0.75 + 0.75 * p.x;
    // 根据 r(即：p的距离) 产生渐变
    s *= 1.0-0.4 * r;
    // 使用类似半兰伯特的方法，增亮了左侧暗部区域
    s = 0.3 + 0.7 * s;
    // 借助变量 r/d 分出了心形内外的区域颜色
    // 重要：最后一步中，使用pow+clamp分割区域的方法也是我们值得借鉴的地方。
    s *= 0.5 + 0.5 * pow(1.0 - clamp(r/d, 0.0, 1.0), 0.1);

    // hcol 是心的颜色
    // 可以看出心的颜色是红色，且由屏幕中心向四周红色逐渐减弱，然后产生一系列渐变，最后分出心形内外的区域颜色。

    // vec3 ( 1.0 , 0.5 * r , 0.3 )完成的是一个简单的由中心向外渐变的颜色，这个渐变色没有考虑心形的约束。
    // s的计算则相对复杂。它用于修正上面的渐变颜色，使得在心形内外的颜色有所区别。
    vec3 hcol = vec3(1.0, 0.4 * r, 0.3) * s;

    // 绘制心形的关键函数，hcol 是心的颜色，bcol 是背景色。

    // smoothstep( -0.01, 0.01, d-r)决定了我们是使用背景颜色还是心的颜色。
    // 当它值为0时，表示该像素不在心形内，则使用背景颜色，返回1时，则使用心的颜色；
    // 否则，就在背景颜色和心的颜色之间进行插值。而 smoothstep( -0.01, 0.01, d-r)的返回值范围就是[0, 1]。
    // smoothstep是CG函数，当第三个参数比-0.01小时，返回0，比0.01大时返回1，如果在-0.01和0.01之间，则返回0到1之间的值。
    // 这里， d-r其实已经表明该像素是否在心形内（后面会讲原因）：
    // 若 d-r > 0，则在心形内，若 d-r  < 0，则在心形外。

    // 那么为什么这里要使用smoothstep呢？其实是为了使心形的边缘模糊化，更美观。
    // smoothstep控制模糊效果的原理在于，在心形的边界部分，d-r的值在正负0左右波动，
    // 我们可以通过添加一个[-0.01, 0.01]范围内的平缓过渡，来平缓d-r的值在正负交界处的突变。
    // 当然，我们可以更改0.01的值，来控制模糊范围。

    // 重要：mix+smoothstep的组合，是实现这种模糊效果的很常见的搭配！
    vec3 col = mix(bcol, hcol, smoothstep(-0.01, 0.01, d-r));

    fragColor = vec4(col, 1.0);
}
// --------[ Original ShaderToy ends here ]---------- //

void main(void)
{
    mainImage(outColor, gl_FragCoord.xy);
}