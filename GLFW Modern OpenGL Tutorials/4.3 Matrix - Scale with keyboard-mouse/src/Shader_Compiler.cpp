#include "Shader_Compiler.hh"

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

	Matrix_Scale_Location = glGetUniformLocation(ShaderProgram, "ScaleMatrix");

	if (Matrix_Scale_Location == -1)
	{
		fprintf(stderr, "Failed to retreive uniform location");
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