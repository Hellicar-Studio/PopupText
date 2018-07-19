// uniform float starDensity;
// uniform float maxSize;
// uniform float offsets[32];
#version 120

uniform vec3 planeCenter;
uniform vec3 planeNormal;
uniform vec3 lightPos;
uniform mat4 rotationMatrix;

varying vec3 col;

// struct Plane {
//     vec3 p;
//     vec3 n;
// }

// struct Line {
//     vec3 p1;
//     vec3 p2;
// }

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec3 planeLineIntersection(vec3 p3, vec3 N, vec3 p1, vec3 p2) {
    float denom = dot(N, p2 - p1);
    if(abs(denom) < 0.00001) {
        denom = (denom > 0) ? 0.00001 : -0.00001;
    }
    float u = dot(N, p3 - p1) / denom;
    
    vec3 i = u*p2 + (1-u) * p1;
    return i;
}

void main() {
    
    vec4 rotP = gl_Vertex * rotationMatrix;
    vec3 p = planeLineIntersection(planeCenter, planeNormal, rotP.xyz - lightPos, rotP.xyz);
    col = p;
    // vec3 p = gl_Vertex.xyz;
    // gl_Position   = gl_ModelViewProjectionMatrix * gl_Vertex;
    vec4 pos = gl_ModelViewProjectionMatrix * vec4(p, gl_Vertex.w);

    // vec3 sphere = cartToSpher(pos.xyz);
    // sphere.x -= 20.0;
    // pos.xyz = sphereToCart(sphere);
    gl_Position = pos;
	// float size    = gl_Normal.x;
	// float r = rand(gl_Vertex.xy);
	// if(r > starDensity)
	// size = 0.0;
    // gl_PointSize  = size * maxSize;
    gl_FrontColor = gl_Color;

}
