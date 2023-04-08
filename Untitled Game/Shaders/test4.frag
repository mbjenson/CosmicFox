
#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;

float circle(in vec2 st, in float radius){
    vec2 dist = st-vec2(0.5);
    return 1.-smoothstep(
        radius-(radius*0.8),
        radius+(radius*0.01),
        dot(dist,dist)*4.0);
    
        
       
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    float pct = 0.0;

    vec3 color = vec3(circle(st, 0.5));

    gl_FragColor = vec4(color, 1.0);

}
