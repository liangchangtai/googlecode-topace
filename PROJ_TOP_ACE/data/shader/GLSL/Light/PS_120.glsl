#version 120
uniform mat4x4 WMatrix;
uniform ivec2 LightNums;
uniform float DiffuseTexTurnY;

uniform sampler2D DiffuseTex;
uniform samplerCube RefCubeTex;
uniform sampler2DShadow ShadowTex;

uniform vec4 OmniLight_Pos[8];
uniform vec4 OmniLight_Color[8];
uniform vec4 Material[3];
uniform vec4 Global_Ambient;
#define Material_diffuse Material[0]
#define Material_specular Material[1]
#define Material_emission Material[2]
#define Material_shininess Material[2].w

varying vec4 VertexEyeDir; 
varying vec3 Normal; 
varying vec2 TexCoord0;
varying vec4 Color;
varying vec4 ShadowDir;
vec2 OmniLight(vec4 LightPosEyeIn,float LightShininess)
{
	vec3 Nor=normalize(Normal);
	vec3 LightDir = normalize( LightPosEyeIn.xyz - VertexEyeDir.xyz );
	float NdotL = dot(Nor,LightDir);
	float specular = 0.0;

	vec3 HightLight =normalize( LightDir - normalize(VertexEyeDir.xyz));
	specular = pow(max(dot(Nor, HightLight), 0.0), LightShininess);

	NdotL = max(0.0,NdotL);
	return vec2(NdotL,specular);
}
void main()
{
	vec2 TexCoordDiffuse;
	TexCoordDiffuse.x=TexCoord0.x;
	TexCoordDiffuse.y=DiffuseTexTurnY*TexCoord0.y;

	vec4 shadowPos=ShadowDir-vec4(0.0,0.0,0.0025,0.0);
	float Shadow=shadow2DProj( ShadowTex, shadowPos ).x;

	vec4 DiffuseTexColor = texture2D(DiffuseTex, TexCoordDiffuse.xy);
	vec2 LightVal = OmniLight (OmniLight_Pos[0],Material_shininess)*Shadow;
	vec4 DiffuseColor=LightVal.x * OmniLight_Color[0] * Material_diffuse;
	vec4 SpecularColor=LightVal.y * OmniLight_Color[0] * Material_specular;

	float NOF=1.0-abs(dot(Normal,vec3(0.0,0.0,1.0)));
	NOF=max(0.0f,NOF)*0.25;
	vec3 Reflective=reflect( - normalize(VertexEyeDir.xyz),Normal);
    vec4 ReflectiveWorld = WMatrix*vec4(Reflective,0.0);
	float REFC=Material_shininess*0.002;

	gl_FragColor=DiffuseTexColor *(Global_Ambient+DiffuseColor+Material_emission)+SpecularColor+textureCube(RefCubeTex, ReflectiveWorld.xyz)*REFC;
	gl_FragColor.w=DiffuseTexColor.w*Material_diffuse.w+SpecularColor.w+NOF;
	//gl_FragColor.xyz=textureCube(RefCubeTex, ReflectiveWorld.xyz).xyz;
	//gl_FragColor.xyz=vec3(Shadow,Shadow,Shadow);
    return;
} 