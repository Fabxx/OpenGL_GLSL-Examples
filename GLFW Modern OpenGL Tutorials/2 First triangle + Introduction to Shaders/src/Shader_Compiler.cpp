#include "0Common_headers.hh"
#include "1Shader_Compiler.hh"

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
    //Exporting whole shader code into first position of p.
	p[0] = ShaderText;
	//saving string lenght into a GLint pointer, required for shader source.
	lenghts[0] = strlen(ShaderText);

	/** DETAIL :
	
	** We init the shader source by taking the shader generated, of p and lenght elements
	** 1 indicates that in each of p and lenghts arrays there's 1 element
	*/
	glShaderSource(Shader, 1, p, lenghts);
	glCompileShader(Shader);
	//CHecking for shader compilation errors, if not success, write the log into the buffer info.
	glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		GLchar info[1024];
		//*NULL here is the number of characters that it returns, but we're not interested in it.
		glGetShaderInfoLog(Shader, sizeof(info), NULL, info);
		fprintf(stderr, "Shader compilation of type %d failed: %s\n", ShaderType, info);
		exit(1);
	}
	//Exporting generated shader into ShaderProgram
	glAttachShader(ShaderProgram, Shader);
}

void CompileShaders()
{
	//REad file into sstream, export into string, convert into C string.
	std::stringstream vertexShader, fragmentShader;
	std::fstream VSFile, FSFile;
	std::string VSData, FSData;
	GLint success;
	
	//Allocating the handle for the program
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

	//Exporting data retreived from stringstream and converting into normal c++ string.
	VSData = vertexShader.str();
	FSData = fragmentShader.str();

	/** DETAIL
	 
	 ** Passing to our program handler the shader
     ** Reading shader content from saved shader string, and converting it into C style string (char/const char*)
	 ** GL_VERTEX_SHADER indicates the type of the shader we're passing., same for GL_FRAGMENT_SHADER
	 */
	
	AddShader(ShaderProgram, VSData.c_str(), GL_VERTEX_SHADER);
	AddShader(ShaderProgram, FSData.c_str(), GL_FRAGMENT_SHADER);

	//linking process, checking for errors again. 
	//*This time using GL_LINK_STATUS
	glLinkProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		GLchar info[1024];
		glGetProgramInfoLog(ShaderProgram, sizeof(info), NULL, info);
		fprintf(stderr, "Shader Linkage failed: %s\n", info);
		exit(1);
	}

	//Again, but for validation of the shader.
	//*This time using GL_VALIDATE_STATUS

	glValidateProgram(ShaderProgram);
	glGetProgramiv(ShaderProgram, GL_VALIDATE_STATUS, &success);

	if (!success)
	{
		GLchar info[1024];
		glGetProgramInfoLog(ShaderProgram, sizeof(info), NULL, info);
		fprintf(stderr, "Shader Validation failed: %s\n", info);
		exit(1);
	}
	//Giving shader to GPU.
	glUseProgram(ShaderProgram);
}