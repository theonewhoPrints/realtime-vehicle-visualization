// shaders/basic.frag
#version 410 core

in vec3 vNormal;
in vec3 vWorldPos;

out vec4 FragColor;

uniform vec3 uCameraPos;
uniform vec3 uLightPos;
uniform vec3 uBaseColor;

void main() {
    vec3 N = normalize(vNormal);
    vec3 L = normalize(uLightPos - vWorldPos);
    vec3 V = normalize(uCameraPos - vWorldPos);
    vec3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(N, H), 0.0), 32.0);

    vec3 ambient = 0.1 * uBaseColor;
    vec3 diffuse = diff * uBaseColor;
    vec3 specular = spec * vec3(1.0);

    vec3 color = ambient + diffuse + specular;
    FragColor = vec4(color, 1.0);
}
