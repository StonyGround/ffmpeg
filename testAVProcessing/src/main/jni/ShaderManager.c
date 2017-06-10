/**
 * OpenGL ES着色器程序与fbo管理
 * 主要包括着色器/fbo/相关属性变量创建及管理
 */

#include "AVProcessing.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

//**blur shader程序-------------------------------------------------------------------------------------------------/
static const char *blurVertexSrc =
		"attribute vec4 aPosition;\n"
		"attribute vec4 aTexCoord;\n"
		"const float ppt =  0.0025;\n"
		"const float npt = -0.0025;\n"
		"varying vec2 blurCoordinates[9];\n"
		"void main()\n"
		"{\n"
		"    gl_Position = aPosition;\n"
		"    blurCoordinates[0] = aTexCoord.xy;\n"
		"    blurCoordinates[1] = aTexCoord.xy + vec2(ppt, 0.0);\n"
		"	 blurCoordinates[2] = aTexCoord.xy + vec2(npt, 0.0);\n"
		"	 blurCoordinates[3] = aTexCoord.xy + vec2(0.0, ppt);\n"
		"	 blurCoordinates[4] = aTexCoord.xy + vec2(0.0, npt);\n"
		"	 blurCoordinates[5] = aTexCoord.xy + vec2(ppt, npt);\n"
		"	 blurCoordinates[6] = aTexCoord.xy + vec2(npt, ppt);\n"
		"	 blurCoordinates[7] = aTexCoord.xy + vec2(npt, npt);\n"
		"    blurCoordinates[8] = aTexCoord.xy + vec2(ppt, ppt);\n"
		"}\n" ;

static const char *blurFragmtSrc =
		"precision mediump float;\n"
		"uniform sampler2D uSTexture;\n"
		"varying vec2 blurCoordinates[9];\n"
		"void main()\n"
		"{\n"
		"    vec4 sum = vec4(0.0);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[0]);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[1]);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[2]);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[3]);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[4]);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[5]);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[6]);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[7]);\n"
		"	 sum += texture2D(uSTexture, blurCoordinates[8]);\n"
		"    gl_FragColor = sum * 0.1111111;\n"
		"}\n" ;
//**---------------------------------------------------------------------------------------------------------------/

//**logo shader程序-------------------------------------------------------------------------------------------------/
static const char *logoVertexSrc =
		"attribute vec4 aPosition;\n"
		"attribute vec4 aTexCoord;\n"
		"uniform   mat4 uTransMat;\n"
		"varying   vec2 vTextureCoordMain;\n"
		"varying   vec2 vTextureCoordLogo;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = aPosition;\n"
		"    vTextureCoordMain = aTexCoord.xy;\n"
		"    vTextureCoordLogo = (uTransMat * aTexCoord).xy;\n"
		"}\n" ;

static const char *logoFragmtSrc =
		"precision mediump float;\n"
		"varying   vec2 vTextureCoordMain;\n"
		"varying   vec2 vTextureCoordLogo;\n"
		"uniform sampler2D uLTexture;\n"
		"uniform sampler2D uSTexture;\n"
		"void main()\n"
		"{\n"
		"    vec4 mainColor = texture2D(uSTexture, vTextureCoordMain);\n"
		"	 vec4 logoColor = texture2D(uLTexture, vTextureCoordLogo);\n"
		"	 mainColor.r = logoColor.r + mainColor.r * mainColor.a * (1.0 - logoColor.a);\n"
		"	 mainColor.g = logoColor.g + mainColor.g * mainColor.a * (1.0 - logoColor.a);\n"
		"	 mainColor.b = logoColor.b + mainColor.b * mainColor.a * (1.0 - logoColor.a);\n"
		"	 mainColor.a = logoColor.a + mainColor.a * (1.0 - logoColor.a);\n"
		"	 gl_FragColor = mainColor;\n"
		"}\n" ;
//**---------------------------------------------------------------------------------------------------------------/

//**copy shader程序-------------------------------------------------------------------------------------------------/
static const char *copyVertexSrc =
		"attribute vec4 aPosition;\n"
		"attribute vec4 aTexCoord;\n"
		"varying   vec2 vTextureCoord;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = aPosition;\n"
		"    vTextureCoord = aTexCoord.xy;\n"
		"}\n" ;

static const char *copyFragmtSrc =
		"precision mediump float;\n"
		"varying vec2 vTextureCoord;\n"
		"uniform sampler2D uSTexture;\n"
		"void main()\n"
		"{\n"
		"    gl_FragColor = texture2D(uSTexture, vTextureCoord);\n"
		"}\n" ;
//**---------------------------------------------------------------------------------------------------------------/

//**main shader程序-----------------------------------------------------------------------------------------------/
static const char *mainVertexSrc =
		"attribute vec4 aPosition;\n"
		"attribute vec4 aTexCoord;\n"
		"uniform   mat4 uTransMat;\n"
		"varying   vec2 vTextureCoord;\n"
		"void main()\n"
		"{\n"
		"    gl_Position = aPosition;\n"
		"    vTextureCoord = (uTransMat * aTexCoord).xy;\n"
		"}\n" ;

static const char *mainFragmtSrc[7] = {
		// 默认
		"precision mediump float;\n"
		"varying vec2 vTextureCoord;\n"
		"uniform sampler2D uYTexture;\n"
		"uniform sampler2D uUTexture;\n"
		"uniform sampler2D uVTexture;\n"
		"uniform sampler2D uMTexture;\n"
		"const mat3 convertMat = mat3( 1.0, 1.0, 1.0, 0.0, -0.39465, 2.03211, 1.13983, -0.58060, 0.0 );\n"
		"void main()\n"
		"{\n"
		"    // yuv转rgb \n"
		"    vec3 yuv;\n"
		"    yuv.x = texture2D(uYTexture, vTextureCoord).r;\n"
		"    yuv.y = texture2D(uUTexture, vTextureCoord).r - 0.5;\n"
		"    yuv.z = texture2D(uVTexture, vTextureCoord).r - 0.5;\n"
		"    vec4 mainColor = vec4(convertMat * yuv, 1.0);\n"
		"    // 混合 \n"
		"    vec4 maskColor = texture2D(uMTexture, vTextureCoord);\n"
		"    mainColor.r = maskColor.r + mainColor.r * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.g = maskColor.g + mainColor.g * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.b = maskColor.b + mainColor.b * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.a = maskColor.a + mainColor.a * (1.0 - maskColor.a);\n"
		"    gl_FragColor = mainColor;\n"
		"}\n" ,

		// 香槟
		"precision mediump float;\n"
		"varying vec2 vTextureCoord;\n"
		"uniform sampler2D uYTexture;\n"
		"uniform sampler2D uUTexture;\n"
		"uniform sampler2D uVTexture;\n"
		"uniform sampler2D uMTexture;\n"
		"const float PI = 3.14159265;\n"
		"const mat3 convertMat = mat3( 1.0, 1.0, 1.0, 0.0, -0.39465, 2.03211, 1.13983, -0.58060, 0.0 );\n"
		"void main()\n"
		"{\n"
		"    // yuv转rgb \n"
		"    vec3 yuv;\n"
		"    yuv.x = texture2D(uYTexture, vTextureCoord).r;\n"
		"    yuv.y = texture2D(uUTexture, vTextureCoord).r - 0.5;\n"
		"    yuv.z = texture2D(uVTexture, vTextureCoord).r - 0.5;\n"
		"    vec3 color = convertMat * yuv;\n"
		"    // 亮度/对比度调节 \n"
		"    color += (1.0 - color) * 0.2362;\n"
		"    color = min(vec3(1.0), ((color - 0.5) * tan(0.328725 * PI) + 0.5));\n"
		"    // 调色 \n"
		"    color.g = color.g * 0.87 + 0.13;\n"
		"    color.b = color.b * 0.439 + 0.561;\n"
		"    color *= vec3(0.981, 0.862, 0.686);\n"
		"    // 混合 \n"
		"    vec4 mainColor = vec4(color, 1.0);\n"
		"    vec4 maskColor = texture2D(uMTexture, vTextureCoord);\n"
		"    mainColor.r = maskColor.r + mainColor.r * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.g = maskColor.g + mainColor.g * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.b = maskColor.b + mainColor.b * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.a = maskColor.a + mainColor.a * (1.0 - maskColor.a);\n"
		"    gl_FragColor = mainColor;\n"
		"}\n" ,

		// 拍立得
		"precision mediump float;\n"
		"varying vec2 vTextureCoord;\n"
		"uniform sampler2D uYTexture;\n"
		"uniform sampler2D uUTexture;\n"
		"uniform sampler2D uVTexture;\n"
		"uniform sampler2D uMTexture;\n"
		"const float PI = 3.14159265;\n"
		"const float sqrt2 = 1.414213562373;\n"
		"const mat4 filterMat = mat4( 1.438, -0.062, -0.062, 0.0, -0.122, 1.378, -0.122, 0.0, -0.016, -0.016, 1.483, 0.0, -0.03, 0.05, -0.02, 0.0 );\n"
		"const mat3 convertMat = mat3( 1.0, 1.0, 1.0, 0.0, -0.39465, 2.03211, 1.13983, -0.58060, 0.0 );\n"
		"void main()\n"
		"{\n"
		"    // yuv转rgb \n"
		"    vec3 yuv;\n"
		"    yuv.x = texture2D(uYTexture, vTextureCoord).r;\n"
		"    yuv.y = texture2D(uUTexture, vTextureCoord).r - 0.5;\n"
		"    yuv.z = texture2D(uVTexture, vTextureCoord).r - 0.5;\n"
		"    vec3 color = convertMat * yuv;\n"
		"    // 调色 \n"
		"    color = (filterMat * vec4(color, 1.0)).rgb;\n"
		"    // 亮度/对比度调节 \n"
		"    color += (1.0 - color) * 0.2;\n"
		"    color = min(vec3(1.0), ((color - 0.5) * tan(0.2 * PI) + 0.5));\n"
		"    // 暗角 \n"
		"    float len = distance(vTextureCoord, vec2(0.5)) * sqrt2;\n"
		"    len = smoothstep(0.7, 1.0, len);\n"
		"    color *= mix(0.5, 1.0, 1.0 - len);\n"
		"    // 混合 \n"
		"    vec4 mainColor = vec4(color, 1.0);\n"
		"    vec4 maskColor = texture2D(uMTexture, vTextureCoord);\n"
		"    mainColor.r = maskColor.r + mainColor.r * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.g = maskColor.g + mainColor.g * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.b = maskColor.b + mainColor.b * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.a = maskColor.a + mainColor.a * (1.0 - maskColor.a);\n"
		"    gl_FragColor = mainColor;\n"
		"}\n" ,

		// 复古
		"precision mediump float;\n"
		"varying vec2 vTextureCoord;\n"
		"uniform sampler2D uYTexture;\n"
		"uniform sampler2D uUTexture;\n"
		"uniform sampler2D uVTexture;\n"
		"uniform sampler2D uMTexture;\n"
		"const mat3 convertMat = mat3( 1.0, 1.0, 1.0, 0.0, -0.39465, 2.03211, 1.13983, -0.58060, 0.0 );\n"
		"void main()\n"
		"{\n"
		"    // yuv转rgb \n"
		"    vec3 yuv;\n"
		"    yuv.x = texture2D(uYTexture, vTextureCoord).r;\n"
		"    yuv.y = texture2D(uUTexture, vTextureCoord).r - 0.5;\n"
		"    yuv.z = texture2D(uVTexture, vTextureCoord).r - 0.5;\n"
		"    vec3 color = convertMat * yuv;\n"
		"    // 调色 \n"
		"    float gray = dot(color, vec3(0.299, 0.587, 0.114));\n"
		"    color = color * (color + 2.0 * vec3(gray) * (1.0 - color));\n"
		"    color = color * vec3(0.984, 0.949, 0.639) * 0.588235;\n"
		"    color = 1.0 - (1.0 - vec3(0.909, 0.396, 0.702) * 0.2) * (1.0 - color);\n"
		"    color = 1.0 - (1.0 - vec3(0.035, 0.286, 0.914) * 0.168627) * (1.0 - color);\n"
		"    // 亮度调节 \n"
		"    color += (1.0 - color) * 0.1;\n"
		"    // 混合 \n"
		"    vec4 mainColor = vec4(color, 1.0);\n"
		"    vec4 maskColor = texture2D(uMTexture, vTextureCoord);\n"
		"    mainColor.r = maskColor.r + mainColor.r * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.g = maskColor.g + mainColor.g * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.b = maskColor.b + mainColor.b * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.a = maskColor.a + mainColor.a * (1.0 - maskColor.a);\n"
		"    gl_FragColor = mainColor;\n"
		"}\n" ,

		// 紫罗兰
		"precision mediump float;\n"
		"varying vec2 vTextureCoord;\n"
		"uniform sampler2D uYTexture;\n"
		"uniform sampler2D uUTexture;\n"
		"uniform sampler2D uVTexture;\n"
		"uniform sampler2D uMTexture;\n"
		"const float PI = 3.14159265;\n"
		"const float sqrt2 = 1.414213562373;\n"
		"const mat3 convertMat = mat3( 1.0, 1.0, 1.0, 0.0, -0.39465, 2.03211, 1.13983, -0.58060, 0.0 );\n"
		"// 饱和度调节 \n"
		"vec3 saturation(vec3 color, float sat)\n"
		"{\n"
		"	const float lumaR = 0.212671;\n"
		"	const float lumaG = 0.715160;\n"
		"	const float lumaB = 0.072169;\n"
		"	float v = sat + 1.0;\n"
		"	float i = 1.0 - v;\n"
		"	float r = i * lumaR;\n"
		"	float g = i * lumaG;\n"
		"	float b = i * lumaB;\n"
		"	mat3 mat = mat3(r + v, r, r, g, g + v, g, b, b, b + v);\n"
		"	return mat * color;\n"
		"}\n"
		"void main()\n"
		"{\n"
		"    // yuv转rgb \n"
		"    vec3 yuv;\n"
		"    yuv.x = texture2D(uYTexture, vTextureCoord).r;\n"
		"    yuv.y = texture2D(uUTexture, vTextureCoord).r - 0.5;\n"
		"    yuv.z = texture2D(uVTexture, vTextureCoord).r - 0.5;\n"
		"    vec3 color = convertMat * yuv;\n"
		"    // 调色 \n"
		"    color.r = color.r * 0.843 + 0.157;\n"
		"    color.b = color.b * 0.882 + 0.118;\n"
		"    color = saturation(color, 0.65);\n"
		"    color *= vec3(1.0, 0.891, 0.733);\n"
		"    // 亮度调节 \n"
		"    color += (1.0 - color) * 0.1;\n"
		"    color = min(vec3(1.0), ((color - 0.5) * tan(0.225 * PI) + 0.5));\n"
		"    // 暗角 \n"
		"    float len = distance(vTextureCoord, vec2(0.5)) * sqrt2;\n"
		"    len = smoothstep(0.7, 1.0, len);\n"
		"    color *= mix(0.5, 1.0, 1.0 - len);\n"
		"    // 混合 \n"
		"    vec4 mainColor = vec4(color, 1.0);\n"
		"    vec4 maskColor = texture2D(uMTexture, vTextureCoord);\n"
		"    mainColor.r = maskColor.r + mainColor.r * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.g = maskColor.g + mainColor.g * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.b = maskColor.b + mainColor.b * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.a = maskColor.a + mainColor.a * (1.0 - maskColor.a);\n"
		"    gl_FragColor = mainColor;\n"
		"}\n" ,

		// 老照片
		"precision mediump float;\n"
		"varying vec2 vTextureCoord;\n"
		"uniform sampler2D uYTexture;\n"
		"uniform sampler2D uUTexture;\n"
		"uniform sampler2D uVTexture;\n"
		"uniform sampler2D uMTexture;\n"
		"const float PI = 3.14159265;\n"
		"const float sqrt2 = 1.414213562373;\n"
		"const mat3 filterMat = mat3( 0.393, 0.769, 0.189, 0.349, 0.686, 0.186, 0.272, 0.534, 0.131 );\n"
		"const mat3 convertMat = mat3( 1.0, 1.0, 1.0, 0.0, -0.39465, 2.03211, 1.13983, -0.58060, 0.0 );\n"
		"// 饱和度调节 \n"
		"vec3 saturation(vec3 color, float sat)\n"
		"{\n"
		"    const float lumaR = 0.212671;\n"
		"    const float lumaG = 0.715160;\n"
		"    const float lumaB = 0.072169;\n"
		"    float v = sat + 1.0;\n"
		"    float i = 1.0 - v;\n"
		"    float r = i * lumaR;\n"
		"    float g = i * lumaG;\n"
		"    float b = i * lumaB;\n"
		"    mat3 mat = mat3(r + v, r, r, g, g + v, g, b, b, b + v);\n"
		"    return mat * color;\n"
		"}\n"
		"void main()\n"
		"{\n"
		"    // yuv转rgb \n"
		"    vec3 yuv;\n"
		"    yuv.x = texture2D(uYTexture, vTextureCoord).r;\n"
		"    yuv.y = texture2D(uUTexture, vTextureCoord).r - 0.5;\n"
		"    yuv.z = texture2D(uVTexture, vTextureCoord).r - 0.5;\n"
		"    vec3 color = convertMat * yuv;\n"
		"    // 调色 \n"
		"    color *= filterMat;\n"
		"    // 对比度/饱和度调节 \n"
		"    color = min(vec3(1.0), ((color - 0.5) * tan(0.2 * PI) + 0.5));\n"
		"    color = saturation(color, 0.3);\n"
		"    // 暗角 \n"
		"    float len = distance(vTextureCoord, vec2(0.5)) * sqrt2;\n"
		"    len = smoothstep(0.7, 1.0, len);\n"
		"    color *= mix(0.5, 1.0, 1.0 - len);\n"
		"    // 混合 \n"
		"    vec4 mainColor = vec4(color, 1.0);\n"
		"    vec4 maskColor = texture2D(uMTexture, vTextureCoord);\n"
		"    mainColor.r = maskColor.r + mainColor.r * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.g = maskColor.g + mainColor.g * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.b = maskColor.b + mainColor.b * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.a = maskColor.a + mainColor.a * (1.0 - maskColor.a);\n"
		"    gl_FragColor = mainColor;\n"
		"}\n" ,

		// 黑白
		"precision mediump float;\n"
		"varying vec2 vTextureCoord;\n"
		"uniform sampler2D uYTexture;\n"
		"uniform sampler2D uUTexture;\n"
		"uniform sampler2D uVTexture;\n"
		"uniform sampler2D uMTexture;\n"
		"const float PI = 3.14159265;\n"
		"const mat3 convertMat = mat3( 1.0, 1.0, 1.0, 0.0, -0.39465, 2.03211, 1.13983, -0.58060, 0.0 );\n"
		"void main()\n"
		"{\n"
		"    // yuv转rgb \n"
		"    vec3 yuv;\n"
		"    yuv.x = texture2D(uYTexture, vTextureCoord).r;\n"
		"    yuv.y = texture2D(uUTexture, vTextureCoord).r - 0.5;\n"
		"    yuv.z = texture2D(uVTexture, vTextureCoord).r - 0.5;\n"
		"    vec3 color = convertMat * yuv;\n"
		"    // 彩色转灰度 \n"
		"    float gray = dot(color, vec3(0.299, 0.587, 0.114));\n"
		"    color = vec3(gray);\n"
		"    // 亮度/对比度调节 \n"
		"    color += (1.0 - color) * 0.2;\n"
		"    color = min(vec3(1.0), ((color - 0.5) * tan(0.2 * PI) + 0.5));\n"
		"    // 混合 \n"
		"    vec4 mainColor = vec4(color, 1.0);\n"
		"    vec4 maskColor = texture2D(uMTexture, vTextureCoord);\n"
		"    mainColor.r = maskColor.r + mainColor.r * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.g = maskColor.g + mainColor.g * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.b = maskColor.b + mainColor.b * mainColor.a * (1.0 - maskColor.a);\n"
		"    mainColor.a = maskColor.a + mainColor.a * (1.0 - maskColor.a);\n"
		"    gl_FragColor = mainColor;\n"
		"}\n"
};
//**---------------------------------------------------------------------------------------------------------------/

//**着色器程序管理-----------------------------------------------------------------------------------------------------/
int loadShader(int type, const char* source)
{
	int shaderHandle = glCreateShader(type);
	glShaderSource(shaderHandle, 1, &source, NULL);
	glCompileShader(shaderHandle);

	return shaderHandle;
}

int createShaderProgram(const char* vSource, const char* fSource)
{
	int fShaderHandle = 0, vShaderHandle = 0, programHandle;
	// 加载顶点及片元shader程序
	vShaderHandle = loadShader(GL_VERTEX_SHADER, vSource);
	fShaderHandle = loadShader(GL_FRAGMENT_SHADER, fSource);
	if (vShaderHandle == 0 || fShaderHandle == 0)
	{
		glDeleteShader(vShaderHandle);
		glDeleteShader(fShaderHandle);

		return 0;
	}

	// 创建着色器程序
	programHandle = glCreateProgram();
	glAttachShader(programHandle, vShaderHandle);
	glAttachShader(programHandle, fShaderHandle);
	glLinkProgram(programHandle);

	// 释放shader资源
	glDeleteShader(vShaderHandle);
	glDeleteShader(fShaderHandle);

	return programHandle;
}

// 创建着色器程序>>模糊/logo/拷贝/滤镜
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_createBlurShaderProgram(JNIEnv *env, jclass obj)
{
	return createShaderProgram(blurVertexSrc, blurFragmtSrc);
}

JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_createLogoShaderProgram(JNIEnv *env, jclass obj)
{
	return createShaderProgram(logoVertexSrc, logoFragmtSrc);
}

JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_createCopyShaderProgram(JNIEnv *env, jclass obj)
{
	return createShaderProgram(copyVertexSrc, copyFragmtSrc);
}

JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_createMainShaderProgram(JNIEnv *env, jclass obj, jint shaderId)
{
	return createShaderProgram(mainVertexSrc, mainFragmtSrc[shaderId]);
}

// 使用着色器程序
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_useShaderProgram(JNIEnv *env, jclass obj, jint programHandle)
{
	glUseProgram(programHandle);
}

// 根据shader程序内attribute/uniform变量名,获取相应变量名handle
JNIEXPORT jint JNICALL Java_com_xiuxiu_util_AVProcessing_getShaderHandle(JNIEnv *env, jclass obj, jstring name, jint programHandle)
{
	const char *handle_name = (*env)->GetStringUTFChars(env, name, 0);
	int handle = glGetAttribLocation(programHandle, handle_name);
	if (handle == -1)
	{
		handle = glGetUniformLocation(programHandle, handle_name);
	}
	(*env)->ReleaseStringUTFChars(env, name, handle_name);

	return handle;
}

// 释放着色器程序资源
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_deleteShaderProgram(JNIEnv *env, jclass obj, jint programHandle)
{
	glDeleteProgram(programHandle);
}
//**--------------------------------------------------------------------------------------------------------------/

//**Frame Buffer Object管理----------------------------------------------------------------------------------------/
static int defaultFBOHandle = 0;
static int frameBufferHandle = 0;
static int textureHandle = 0;
static int fboWidth = 0, fboHeight = 0;

// 初始化fbo
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_initFBO(JNIEnv *env, jclass obj, jint width, jint height)
{
	fboWidth = width;
	fboHeight = height;

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &defaultFBOHandle);

	// 生成fbo
	glGenFramebuffers(1, &frameBufferHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);

	// 生成纹理
	glGenTextures(1, &textureHandle);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fboWidth, fboHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	// 将纹理关联到fbo
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureHandle, 0);
}

// 绑定fbo
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_bindFBO(JNIEnv *env, jclass obj)
{
	glBindFramebuffer(GL_FRAMEBUFFER, defaultFBOHandle);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferHandle);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureHandle, 0);
	glViewport(0, 0, fboWidth, fboHeight);
}

// 使用fbo纹理
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_useFBOTexture(JNIEnv *env, jclass obj)
{
	glBindFramebuffer(GL_FRAMEBUFFER, defaultFBOHandle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureHandle);
}

// 释放fbo资源
JNIEXPORT void JNICALL Java_com_xiuxiu_util_AVProcessing_deleteFBO(JNIEnv *env, jclass obj)
{
	glDeleteFramebuffers(1, &frameBufferHandle);
	glDeleteTextures(1, &textureHandle);
	frameBufferHandle = 0;
	textureHandle = 0;
	fboWidth = fboHeight = 0;
}
//**--------------------------------------------------------------------------------------------------------------/
