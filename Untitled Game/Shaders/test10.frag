#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform vec2 circleCenter;
uniform float radius;

uniform sampler2D currentTexture;

vec4 circle(in vec2 _st, in float _radius, vec2 _circleCenter){
    float dist = sqrt(pow(_circleCenter.x - _st.x, 2) + pow(_circleCenter.y - _st.y, 2));
	if (dist < _radius) {
		return vec4(0, 0, 0, 0);
	}
	else {
		return vec4(0, 0, 0, 1);
	}
}

void main() {
	vec2 position = gl_FragCoord.xy / u_resolution;
	vec2 centerNorm = circleCenter.xy / u_resolution;
	
	vec4 circle1 = circle(position, radius, centerNorm);
	
	gl_FragColor = circle1;
}