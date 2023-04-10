#ifdef GL_ES
precision mediump float;
#endif


uniform vec2 u_resolution;
uniform vec2 u_mouse;
uniform float u_time;
uniform sampler2D texture;

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    //vec3 color = vec3(0.0, 0.0, 0.0);
    //float dist = sqrt(pow(st.x - 64.0, 2.0) + pow(st.y - 64.0, 2.0));
    vec2 bl = step(vec2(0.1), st);
    float pct = bl.x * bl.y;

    gl_FragColor = vec4(pct);
}