attribute vec4 vertexPosition;
attribute vec3 vertexColor;

uniform mat4 mvpMatrix;

varying highp vec3 color;

void main(){
	gl_position = mvpMatrix * vertexPosition;
	color = vertexColor;
}