#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float circle(in vec2 st, in float radius) {
    
    float dist = sqrt(pow(st.x - 0.5, 2.0) + pow(st.y - 0.5, 2.0));
    return smoothstep(
        0.3-radius,
        0.4-radius,
        dist);
}

// float circle(in vec2 st, in float radius){
//     vec2 dist = st-vec2(0.5);
//     return 1.-smoothstep(
//         radius-(radius*0.01),
//         radius+(radius*0.01),
//         dot(dist,dist)*4.0);
// }

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.0, 0.3333, 1.0);
    //vec4 color = vec4(0.2941, 0.2941, 0.6706, 0.543);
    gl_FragColor = vec4(circle(st, 0.1), color);
   // gl_FragColor = color;
}
