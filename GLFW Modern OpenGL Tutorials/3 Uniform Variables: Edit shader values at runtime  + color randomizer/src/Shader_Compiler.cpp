#include "0Common_headers.hh"
#include "1Shader_Compiler.hh"
#include "0VBO_init.hh"

void AddShader(GLuint ShaderProgram, const char *ShaderText, GLenum ShaderType)
{
	GLuint Shader = glCreateShader(ShaderType);
	const GLchar *p[1];
	GLint lenghts[1];
	GLint success;

	if (Shader == 0)
	{
		fprintf(stderr, "Failed to create shader object");
		exit(0);
	}

	p[0] = ShaderText;
	lenghts[0] = strlen(ShaderText);

	glShaderSource(Shader, 1, p, lenghts);
	glCompileShader(Shader);
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar info[1024];
		glGetShaderInfoLog(Shader, sizeof(info), NULL, info);
		fprintf(stderr, "Shader compilation of type %d failed: %s\n", ShaderType, info);
		exit(1);
	}
	glAttachShader(ShaderProgram, Shader);
}

void CompileShaders()
{
	std::stringstream vertexShader, fragmentShader;
	std::fstream VSFile, FSFile;
	std::string VSData, FSData;
	GLint success;
	
	GLuint ShaderProgram = glCreateProgram();

	if (ShaderProgram == 0)
	{
		fprintf(stderr, "failed to create handler");
		exit(0);
	}

	VSFile.open("VertexShader.glsl", std::ios::in);
	FSFile.open("FragmentShader.glsl", std::ios::in);

	if (VSFile.is_open())
	{
		 vertexShader << VSFile.rdbuf();
		 VSFile.close();
	}

	if (FSFile.is_open())
	{
		fragmentShader << FSFile.rdbuf();
		FSFile.close();
	}

	VSData = vertexShader.str();
	FSData = fragmentShader.str();

	AddShader(ShaderProgram, VSData.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, FSData.c_str(), GL_FRAGMENT_SHADER);

	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLchar info[1024];
		glGetProgramInfoLog(ShaderProgram, sizeof(info), NULL, info);
		fprintf(stderr, "Shader Linkage failed: %s\n", info);
		exit(1);
	}

	/**Via ShaderProgram, we can access the loaded shader code, and make use of the variables putted in the shader.
	**Don't call get uniform location before the linking, because before that there's nothing in the buffer.
	**We have to save the uniform we want to get, we do it via the extern variable declared in main.
	**NOTE: as the name suggests, the function can be used only to detect uniform variables from the shader.
	*/
	
	uniform_location = glGetUniformLocation(ShaderProgram, "scaling");
	
	if (uniform_location == -1) //reference to "scaling in VS")
	{
		fprintf(stderr, "Error in getting uniform location\n");
		exit(1);
	}

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &success);

	if (!success)
	{
		GLchar info[1024];
		glGetProgramInfoLog(ShaderProgram, sizeof(info), NULL, info);
		fprintf(stderr, "Shader Validation failed: %s\n", info);
		exit(1);
	}

	glUseProgram(ShaderProgram);
}