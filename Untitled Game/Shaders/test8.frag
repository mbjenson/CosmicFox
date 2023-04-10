#version 330 core

precision mediump float;

layout(location = 0) out vec4 color;

in vec2 i_tex;

uniform sampler2D texture;

uniform vec2 playerPos;
uniform vec2 u_resolution;

void main() {
	vec2 uv	   = gl_FragCoord.xy / u_resolution;
	vec2 player = playerPos		 / u_resolution;

	player.y    = 1.0 - player.y;

	vec4 pixel = texture2D(texture, i_tex);

	float circle = 1.0 - length(uv - player) * 2.0;

	color = vec4(vec3(0.1), circle * (1.0 - pixel.b) * 1.35);
};