#include "GLSL_Light.h"
#include "FileSysBace.h"
#include "CharSysBace.h"
#include "Glsl.h"
#include "Common.h"

GLhandleARB GH_VS[2][3];
GLhandleARB GH_TC;
GLhandleARB GH_TE;
GLhandleARB GH_GS[3];
GLhandleARB GH_PS[3];
GLhandleARB GH_PO[2][3];
GLint GLSL_Light_MMatrix[2][3];
GLint GLSL_Light_PMatrix[2][3];
GLint GLSL_Light_MVPMatrix[2][3];
GLint GLSL_Light_WMatrix[2][3];
GLint GLSL_Light_ShadowMatrix[2][3];
GLint GLSL_Light_RefCubeTex[2][3];
GLint GLSL_Light_DiffuseTex[2][3];
GLint GLSL_Light_SpecularTex[2][3];
GLint GLSL_Light_NormalTex[2][3];
GLint GLSL_Light_ShadowTex[2][3];
GLint GLSL_Light_ShadowTexSize[2][3];
GLint GLSL_Light_TexTurnY[2][3];
GLint GLSL_Light_LightNums[2][3];
GLint GLSL_Light_OmniLight_Pos[2][3];
GLint GLSL_Light_OmniLight_Color[2][3];
GLint GLSL_Light_Material[2][3];
GLint GLSL_Light_Global_Ambient[2][3];
GLint GLSL_Light_TessLevel[2][3];
bool GLSL_Light_OK[2][3]={false};
extern float WorldMatrix[16];
extern GLuint RefCubeTexID;
extern GLuint ShadowTexDepth;
extern float ShadowTexDepthSize[2];
void Init_GLSL_light(int LightSet)
{

	if(LightSet<2) return;
	GH_VS[SINGLBONE][GLSL120]=CompileShader(L"data/shader/GLSL/Light/VS_120_SINGLBONE.glsl",GL_VERTEX_SHADER);
	//GH_VS[MULTIBONE][GLSL120]=CompileShader(L"data/shader/GLSL/Light/VS_120_MULTIBONE.glsl",GL_VERTEX_SHADER);
	GH_PS			[GLSL120]=CompileShader(L"data/shader/GLSL/Light/PS_120.glsl",			GL_FRAGMENT_SHADER);
	GLSL_Light_OK[SINGLBONE][GLSL120]=CGLSL_Light_Link(&(GH_PO[SINGLBONE][GLSL120]),GH_VS[SINGLBONE][GLSL120],0,0,0,GH_PS[GLSL120]);Init_GLSL_light_Uniform(SINGLBONE,GLSL120);
	//CGLSL_Light_Link(&(GH_PO[MULTIBONE][GLSL120]),GH_VS[MULTIBONE][GLSL120],0,0,0,GH_PS[GLSL120]);Init_GLSL_light_Uniform(MULTIBONE,GLSL120);
	if(LightSet<3) return;
	GH_VS[SINGLBONE][GLSL150]=CompileShader(L"data/shader/GLSL/Light/VS_150_SINGLBONE.glsl",GL_VERTEX_SHADER);
	//GH_VS[MULTIBONE][GLSL150]=CompileShader(L"data/shader/GLSL/Light/VS_150_MULTIBONE.glsl",GL_VERTEX_SHADER);
	//GH_GS			[GLSL150]=CompileShader(L"data/shader/GLSL/Light/GS_150.glsl",			GL_GEOMETRY_SHADER);
	GH_PS			[GLSL150]=CompileShader(L"data/shader/GLSL/Light/PS_150.glsl",			GL_FRAGMENT_SHADER);
	GLSL_Light_OK[SINGLBONE][GLSL150]=CGLSL_Light_Link(&(GH_PO[SINGLBONE][GLSL150]),GH_VS[SINGLBONE][GLSL150],0,0,GH_GS[GLSL150],GH_PS[GLSL150]);Init_GLSL_light_Uniform(SINGLBONE,GLSL150);
	//CGLSL_Light_Link(&(GH_PO[MULTIBONE][GLSL150]),GH_VS[MULTIBONE][GLSL150],0,0,GH_GS[GLSL150],GH_PS[GLSL150]);Init_GLSL_light_Uniform(MULTIBONE,GLSL150);
	//if(LightSet<4) return;
	//GH_VS[SINGLBONE][GLSL400]=CompileShader(L"data/shader/GLSL/Light/VS_400_SINGLBONE.glsl",GL_VERTEX_SHADER);
	//GH_VS[MULTIBONE][GLSL400]=CompileShader(L"data/shader/GLSL/Light/VS_400_MULTIBONE.glsl",GL_VERTEX_SHADER);
	//GH_TC					 =CompileShader(L"data/shader/GLSL/Light/TC_400.glsl",			GL_TESS_CONTROL_SHADER);
	//GH_TE					 =CompileShader(L"data/shader/GLSL/Light/TE_400.glsl",			GL_TESS_EVALUATION_SHADER);
	//GH_GS			[GLSL400]=CompileShader(L"data/shader/GLSL/Light/GS_400.glsl",			GL_GEOMETRY_SHADER);
	//GH_PS			[GLSL400]=CompileShader(L"data/shader/GLSL/Light/PS_400.glsl",			GL_FRAGMENT_SHADER);
	//CGLSL_Light_Link(&(GH_PO[SINGLBONE][GLSL400]),GH_VS[SINGLBONE][GLSL400],GH_TC,GH_TE,GH_GS[GLSL400],GH_PS[GLSL400]);Init_GLSL_light_Uniform(SINGLBONE,GLSL400);
	//CGLSL_Light_Link(&(GH_PO[MULTIBONE][GLSL400]),GH_VS[MULTIBONE][GLSL400],GH_TC,GH_TE,GH_GS[GLSL400],GH_PS[GLSL400]);Init_GLSL_light_Uniform(MULTIBONE,GLSL400);
}
void Init_GLSL_light_Uniform(int boneType,int GLSLver)
{
	GLSL_Light_MMatrix[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"MMatrix");
	GLSL_Light_PMatrix[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"PMatrix");
	GLSL_Light_MVPMatrix[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"MVPMatrix");
	GLSL_Light_WMatrix[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"WMatrix");
	GLSL_Light_ShadowMatrix[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"ShadowMatrix");
	
	GLSL_Light_SpecularTex[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"SpecularTex");
	GLSL_Light_NormalTex[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"NormalTex");
	GLSL_Light_RefCubeTex[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"RefCubeTex");
	GLSL_Light_DiffuseTex[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"DiffuseTex");
	GLSL_Light_ShadowTex[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"ShadowTex");
	GLSL_Light_ShadowTexSize[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"ShadowTexSize");
	GLSL_Light_LightNums[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"LightNums");
	GLSL_Light_TexTurnY[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"TexTurnY");
	GLSL_Light_OmniLight_Pos[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"OmniLight_Pos");
	GLSL_Light_OmniLight_Color[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"OmniLight_Color");
	GLSL_Light_Material[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"Material");
	GLSL_Light_Global_Ambient[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"Global_Ambient");
	GLSL_Light_TessLevel[boneType][GLSLver] = glGetUniformLocation(GH_PO[boneType][GLSLver],"TessLevel");
}
void Deinit_GLSL_light()
{
	ClearShaderObject(GH_PO[SINGLBONE][GLSL120],GH_VS[SINGLBONE][GLSL120],0,0,0,GH_PS[GLSL120]);
	ClearShaderObject(GH_PO[MULTIBONE][GLSL120],GH_VS[MULTIBONE][GLSL120],0,0,0,GH_PS[GLSL120]);
	ClearShaderObject(GH_PO[SINGLBONE][GLSL150],GH_VS[SINGLBONE][GLSL150],0,0,GH_GS[GLSL150],GH_PS[GLSL150]);
	ClearShaderObject(GH_PO[MULTIBONE][GLSL150],GH_VS[MULTIBONE][GLSL150],0,0,GH_GS[GLSL150],GH_PS[GLSL150]);
	ClearShaderObject(GH_PO[SINGLBONE][GLSL400],GH_VS[SINGLBONE][GLSL400],GH_TC,GH_TE,GH_GS[GLSL400],GH_PS[GLSL400]);
	ClearShaderObject(GH_PO[MULTIBONE][GLSL400],GH_VS[MULTIBONE][GLSL400],GH_TC,GH_TE,GH_GS[GLSL400],GH_PS[GLSL400]);

	DelShader(GH_VS[SINGLBONE][GLSL120]);
	DelShader(GH_VS[MULTIBONE][GLSL120]);
	DelShader(GH_VS[SINGLBONE][GLSL150]);
	DelShader(GH_VS[MULTIBONE][GLSL150]);
	DelShader(GH_VS[SINGLBONE][GLSL400]);
	DelShader(GH_VS[MULTIBONE][GLSL400]);
	DelShader(GH_TC);
	DelShader(GH_TE);
	DelShader(GH_GS[GLSL120]);
	DelShader(GH_GS[GLSL150]);
	DelShader(GH_GS[GLSL400]);
	DelShader(GH_PS[GLSL120]);
	DelShader(GH_PS[GLSL150]);
	DelShader(GH_PS[GLSL400]);
}
void GLSL_Enable_Light(int boneType,int GLSLver_in, int OmniLightNum,int SpotLightNum,int TessLevel)
{
	int GLSLver=GLSLver_in;
	if(GLSLver>=GLSL400) glPatchParameteri(GL_PATCH_VERTICES, 3);
	while(!(GLSL_Light_OK[boneType][GLSLver]))
	{
		GLSLver=GLSLver-1;
		if(GLSLver<0)
			return;
	}
	int LightNums[2]={OmniLightNum,SpotLightNum};
	
	CO_SetGlslPO(GH_PO[boneType][GLSLver]);
	glUseProgramObjectARB( GH_PO[boneType][GLSLver] );
	glUniform1i(GLSL_Light_DiffuseTex[boneType][GLSLver],DifTexShot);
	glUniform1i(GLSL_Light_ShadowTex[boneType][GLSLver],ShaTexShot);
	glUniform1i(GLSL_Light_RefCubeTex[boneType][GLSLver],RefTexShot);
	glUniform1i(GLSL_Light_SpecularTex[boneType][GLSLver],SpeTexShot);
	glUniform1i(GLSL_Light_NormalTex[boneType][GLSLver],NorTexShot);

	glUniform2iv(GLSL_Light_LightNums[boneType][GLSLver],1,LightNums);
	//glUniform1f(GLSL_Light_TexTurnY[MULTIBONE][GLSL400],1.0f);
	glUniform1f(GLSL_Light_TessLevel[boneType][GLSLver],(float)max(1,TessLevel));
	glUniform2fv(GLSL_Light_ShadowTexSize[boneType][GLSLver],1,ShadowTexDepthSize);
	
	glUniformMatrix4fv(GLSL_Light_WMatrix[boneType][GLSLver],1,false,WorldMatrix);
	
	
	glActiveTexture(GL_TEXTURE0+ShaTexShot);	
	glBindTexture(GL_TEXTURE_2D,ShadowTexDepth);
	glActiveTexture(GL_TEXTURE0+RefTexShot);	
	glBindTexture(GL_TEXTURE_CUBE_MAP_EXT,RefCubeTexID);	
	

	glActiveTexture(GL_TEXTURE0);

	CO_SetTexTurnYGLSLLoc(GLSL_Light_TexTurnY[boneType][GLSLver]);
	float TexTurnY[4]={1.0f,1.0f,1.0f,1.0f};
	CO_SetTexTurnYToGLSL(TexTurnY);
	/*CO_SetMatrixsGLSLLoc(
		glGetUniformLocation(CO_GetGlslPO(),"MMatrix"),
		glGetUniformLocation(CO_GetGlslPO(),"PMatrix"),
		glGetUniformLocation(CO_GetGlslPO(),"MVPMatrix"));ShadowMatrix*/
	CommonMatrixs[CO_Matrix_ModelViewProj].GLSLLoc=GLSL_Light_MVPMatrix[boneType][GLSLver];
	CommonMatrixs[CO_Matrix_Proj].GLSLLoc=GLSL_Light_PMatrix[boneType][GLSLver];
	CommonMatrixs[CO_Matrix_ModelView].GLSLLoc=GLSL_Light_MMatrix[boneType][GLSLver];
	CommonMatrixs[CO_Matrix_World].GLSLLoc=-1;
	CommonMatrixs[CO_Matrix_ShadowViewProj].GLSLLoc=GLSL_Light_ShadowMatrix[boneType][GLSLver];
	/*CO_SetMatrixsGLSLLoc(
		GLSL_Light_MMatrix[boneType][GLSLver],
		GLSL_Light_PMatrix[boneType][GLSLver],
		GLSL_Light_MVPMatrix[boneType][GLSLver]);*/

	CO_SetOmniLightGLSLLoc(GLSL_Light_OmniLight_Pos[boneType][GLSLver],GLSL_Light_OmniLight_Color[boneType][GLSLver]);
	CO_SetOmniLightToGLSL();

	CO_SetMaterialGLSLLoc(GLSL_Light_Material[boneType][GLSLver]);
	CO_SetMaterialToGLSL(NULL);

	CO_SetGlobalAmbientGLSLLoc(GLSL_Light_Global_Ambient[boneType][GLSLver]);
	CO_SetGlobalAmbientToGLSL(NULL);
}
