#version 400
layout(vertices = 3) out;

in vec3 vPosition[];
in vec3 vNormal[]; 
in vec2 vTexCoord0[];
in vec4 vColor[];

out vec3 tcPosition[];
out vec3 tcNormal[];
out vec2 tcTexCoord0[];
out vec4 tcColor[];
out vec3 b210[];
out vec3 b120[];
out vec3 b021[];
out vec3 b012[];
out vec3 b102[];
out vec3 b201[];
out vec3 b111[];
out vec3 n110[];
out vec3 n011[];
out vec3 n101[];

#define ID gl_InvocationID
#define float3 vec3
uniform float TessLevel;
void main()
{
    tcPosition[ID] = vPosition[ID];
    tcNormal[ID] = vNormal[ID];
    tcTexCoord0[ID] = vTexCoord0[ID];
    tcColor[ID] = vColor[ID];
    if (ID == 0) 
	{
		vec3 TessLevelSize,TessLevelSizeZ;
		TessLevelSize.x=length(vPosition[2].xy - vPosition[1].xy)/(vPosition[0].z);
		TessLevelSize.y=length(vPosition[0].xy - vPosition[2].xy)/(vPosition[1].z);
		TessLevelSize.z=length(vPosition[0].xy - vPosition[1].xy)/(vPosition[2].z);
		vec3 ANormal = vPosition[2] - vPosition[0];
		vec3 BNormal = vPosition[1] - vPosition[0];
		vec3 gFacetNormal = normalize(cross(ANormal, BNormal));
		vec3 gFacetNormal2=normalize(vNormal[0]+vNormal[1]+vNormal[2]);
		if(dot(gFacetNormal,gFacetNormal2)<0.0)
		gFacetNormal=-gFacetNormal;
		//gFacetNormal=abs(gFacetNormal);
				// Assign Positions
		float3 b003 = vPosition[0];
		float3 b030 = vPosition[1];
		float3 b300 = vPosition[2];
		// And Normals
		float3 n002 = vNormal[0];
		float3 n020 = vNormal[1];
		float3 n200 = vNormal[2];
			// Compute the cubic geometry control points
		// Edge control points
		b210[ID] = (2 * b003 + b030 - (dot(b030 - b003, n002) * n002)) / 3;
		b120[ID] = (2 * b030 + b003 - (dot(b003 - b030, n020) * n020)) / 3;
		b021[ID] = (2 * b030 + b300 - (dot(b300 - b030, n020) * n020)) / 3;
		b012[ID] = (2 * b300 + b030 - (dot(b030 - b300, n200) * n200)) / 3;
		b102[ID] = (2 * b300 + b003 - (dot(b003 - b300, n200) * n200)) / 3;
		b201[ID] = (2 * b003 + b300 - (dot(b300 - b003, n002) * n002)) / 3;
		// Center control point
		float3 e = (b210[ID] + b120[ID] + b021[ID] + b012[ID] + b102[ID] + b201[ID]) / 6;
		float3 v = (b003 + b030 + b300) / 3;
		b111[ID] =e+(e-v)*0.5 ;//mix(e, v, 0.5f);

		// Compute the quadratic normal control points, and rotate into world space
		float v12 = 2 * dot(b030 - b003, n002 + n020) / dot(b030 - b003, b030 - b003);
		n110[ID] = normalize(n002 + n020 - v12 * (b030 - b003));
		float v23 = 2 * dot(b300 - b030, n020 + n200) / dot(b300 - b030, b300 - b030);
		n011[ID] = normalize(n020 + n200 - v23 * (b300 - b030));
		float v31 = 2 * dot(b003 - b300, n200 + n002) / dot(b003 - b300, b003 - b300);
		n101[ID] = normalize(n200 + n002 - v31 * (b003 - b300));

		float DotN=dot(vNormal[0],vNormal[1])+dot(vNormal[2],vNormal[1]);
		if((dot(gFacetNormal,vec3(0.0,0.0,1.0))>0.0)&&(DotN<1.999))
		{
			gl_TessLevelInner[0] = TessLevel*min(1.0,10.0*abs(TessLevelSize.x));
			gl_TessLevelOuter[0] = TessLevel*min(1.0,10.0*abs(TessLevelSize.x));
			gl_TessLevelOuter[1] = TessLevel*min(1.0,10.0*abs(TessLevelSize.y));
			gl_TessLevelOuter[2] = TessLevel*min(1.0,10.0*abs(TessLevelSize.z));
		}
		else
		{
			gl_TessLevelInner[0] = 1;
			gl_TessLevelOuter[0] = 1;
			gl_TessLevelOuter[1] = 1;
			gl_TessLevelOuter[2] = 1;
		}
		
    }
}


