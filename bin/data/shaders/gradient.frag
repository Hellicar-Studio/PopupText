#version 120

#define PI 3.141592

uniform sampler2DRect inputTexture;
uniform vec2 resolution;
uniform vec3 col1;
uniform vec3 col2;

void main() {
    
    vec2 uv = gl_FragCoord.xy / resolution;
    
    uv.y = 1.0 - uv.y;
    
    vec3 tc = texture2DRect(inputTexture, uv * resolution).rgb;
    
    if(tc.r > 0.99) {
        tc = mix(col1, col2, vec3(uv.y));
    }
    
    gl_FragColor = vec4(tc, 1.0);
}

