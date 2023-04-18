#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 circleCenter;

uniform sampler2D currentTexture;

float circle(in vec2 _st, in float _radius, vec2 _circleCenter){
    vec2 dist = _st-vec2(_circleCenter.x, 1.f - _circleCenter.y);
	return 0.+smoothstep(_radius-(_radius*0.8),
                         _radius+(_radius*0.8),
                         dot(dist,dist)*4.0);
}

void main() {
	vec2 position = gl_FragCoord.xy / u_resolution;
	vec2 centerNorm = circleCenter.xy / u_resolution;
	float radius = 0.3;
	
	float circ = circle(position, radius, centerNorm);
	vec3 curCol = texture2D(currentTexture, gl_TexCoord[0].xy);
	
	gl_FragColor = vec4(curCol, circ);
}