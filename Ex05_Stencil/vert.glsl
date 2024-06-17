#version 410


uniform mat4 model = mat4(1);
uniform mat4 view = mat4(1);
uniform mat4 projection = mat4(1);


layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texCoords;


out vec2 texCoords;


void main() {
	// Les manipulations habituelles, on n'a pas besoin d'un nuanceur de sommets particulier pour faire la sélection.
	vec4 worldPosition = model * vec4(a_position, 1.0);
	vec4 viewPosition = view * worldPosition;
	vec4 normPosition = projection * viewPosition;

	gl_Position = normPosition;
	texCoords = a_texCoords;
}
