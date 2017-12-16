#include "Shader.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <iostream>
#include <fstream>

#include <algorithm>

#include "Logger.h"
#include "FileUtils.h"

Shader::Shader(std::string vertexShaderFile, std::string fragShaderFile, std::vector<std::string> uniforms ) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Read shaders
    std::string vertShaderStr = FileUtils::readFileToString(vertexShaderFile);
    std::string fragShaderStr = FileUtils::readFileToString(fragShaderFile);

    //Logger::Debug("Vert Shader Length : " + vertShaderStr.length());
    //Logger::Debug("Frag Shader Length : " + fragShaderStr.length());

    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

////////////////////////////////////
    GLint success = 0;

    // Compile vertex shader
    Logger::Info("Compiling vertex shader.");
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

//Check It compiled
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint logLength = 0;
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(vertShader, logLength, NULL, &errorLog[0]);
        std::cout << "Log Length " << logLength << std::endl;
        std::cout << "The vertex shader failed to compile with the error:" << std::endl;
        for (GLchar errorLine : errorLog) {
            std::cout << errorLine;
        }
    }
//
    // Compile fragment shader
    Logger::Info("Compiling fragment shader.");
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

//Check It compiled
    success = 0;
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint logLength = 0;
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(fragShader, logLength, NULL, &errorLog[0]);
        std::cout << "Log Length " << logLength << std::endl;
        std::cout << "The frag shader failed to compile with the error:" << std::endl;
        for (GLchar errorLine : errorLog) {
            std::cout << errorLine;
        }
    }
//
    Logger::Info("Linking program");

    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

//Check It compiled
    success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_FALSE)
    {
        GLint logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> errorLog(logLength);
        glGetProgramInfoLog(program, logLength, NULL, &errorLog[0]);
        std::cout << "Log Length " << logLength << std::endl;
        std::cout << "The Program failed to compile with the error:" << std::endl;
        for (GLchar errorLine : errorLog) {
            std::cout << errorLine;
        }
    }
//

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    //populate the shader uniforms
    for (std::string uniformID : uniforms) {
        uniformIDs.insert(std::pair<std::string,GLuint>(uniformID, glGetUniformLocation(program, uniformID.c_str())));
    }

}
GLuint Shader::getUniformID(std::string id) {
    return uniformIDs.find(id)->second;//todo error handling
}

Shader::~Shader() {
    glDeleteProgram(program);
}