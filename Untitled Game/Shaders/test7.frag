#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

// float circle(in vec2 st, in float radius) {
//     float dist = sqrt(pow(st.x - 0.5, 2.0) + pow(st.y - 0.5, 2.0));
//     return smoothstep(0.3-radius, 0.3-radius, dist);
// }

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec2 bl = smoothstep(vec2(0.1),vec2(0.2),st);
    float pct = bl.x * bl.y;
    vec3 color = vec3(pct);

    
    //float alpha = circle(st, 0.01);

    //vec3 color = vec3(0.0, 0.0, 0.0);
    //gl_FragColor = vec4(color, alpha);
    gl_FragColor = vec4(color, 1.0);
}
