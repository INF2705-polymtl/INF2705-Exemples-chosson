#version 410


uniform vec4 globalColor;

out vec4 fragColor;


void main() {
	// Appliquer la couleur.
	fragColor = globalColor;
}
