#version 330 core

layout (location = 0) in vec3 Vertices;

const vec3 colors[3] = vec3[3]
                    (vec3(1.0, 0.0, 0.0),
                    vec3(0.0, 1.0, 0.0),
                    vec3(0.0, 0.0, 1.0) );
uniform mat4 Output;
out vec3 FragColor;

void main()
{
    gl_Position = Output * vec4(Vertices, 1.0);
    FragColor = colors[gl_VertexID];
}