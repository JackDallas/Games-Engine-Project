#include "Shader.h"

#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <algorithm>

#include "Logger.h"
#include "FileUtils.h"

/**
https://github.com/nlguillemot/ShaderSet/blob/master/shaderset.cpp
**/
static uint64_t GetShaderFileTimestamp(const char* filename) {   
     uint64_t timestamp = 0;

    struct __stat64 stFileInfo;
    if (_stat64(filename, &stFileInfo) == 0)
    {
        timestamp = stFileInfo.st_mtime;
    }

    return timestamp;
}


Shader::Shader(std::string vertexShaderFile, std::string fragShaderFile, std::vector<std::string> uniforms, bool _liveReload ) {
    liveReload = _liveReload;

    loadVertFrag(vertexShaderFile, fragShaderFile, uniforms);
}

void Shader::loadVertFrag(std::string vertexShaderFile, std::string fragShaderFile, std::vector<std::string> uniforms ) {
    program = 0;
    
    vertFile = {vertexShaderFile, GetShaderFileTimestamp(vertexShaderFile.c_str())};
    fragFile = {fragShaderFile, GetShaderFileTimestamp(fragShaderFile.c_str())};

    Logger::Info("Loading Shaders: ");
    Logger::Info(vertexShaderFile);
    Logger::Info(fragShaderFile);

    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertShaderStr = FileUtils::readFileToString(vertexShaderFile);
    std::string fragShaderStr = FileUtils::readFileToString(fragShaderFile);

    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    // Compile vertex shader
    Logger::Info("Compiling vertex shader.");
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    bool vertSuccess = checkShaderCompileStatus(vertShader, "Vert");

    // Compile fragment shader
    Logger::Info("Compiling fragment shader.");
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    bool fragSuccess = checkShaderCompileStatus(fragShader, "Frag");

    if (vertSuccess && fragSuccess) {
        Logger::Info("Linking program");

        GLint tempProgram = glCreateProgram();
        glAttachShader(tempProgram, vertShader);
        glAttachShader(tempProgram, fragShader);
        glLinkProgram(tempProgram);

        //Print the log
        GLint logLength = 0;
        glGetProgramiv(tempProgram, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<GLchar> errorLog(logLength);
        glGetProgramInfoLog(tempProgram, logLength, NULL, &errorLog[0]);
        std::cout << "Program Log : " << std::endl;
        std::cout << "Log Length " << logLength << std::endl;
        for (GLchar errorLine : errorLog) {
            std::cout << errorLine;
        }

        //Check It compiled
        GLint programSuccess = 0;
        glGetProgramiv(tempProgram, GL_LINK_STATUS, &programSuccess);

        if (!programSuccess) {
            glDeleteProgram(tempProgram);
            std::cout << "The Program failed to compile" << std::endl;
        } else {
            glDeleteProgram(program);

            program = tempProgram;
            Logger::Info("Program Compiled Successfully!");
        }

    } else {
        Logger::Error("Vert / Frag Failed to compile");
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    //populate the shader uniforms
    if (!uniforms.empty()) {
        Logger::Info("We have uniforms, adding to map");
        for (std::string uniformID : uniforms) {
            uniformIDs.insert(std::pair<std::string, GLuint>(uniformID, glGetUniformLocation(program, uniformID.c_str())));
        }
    }
}

bool Shader::checkShaderCompileStatus(GLuint &shader, std::string shaderName) {
    GLint logLength = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<GLchar> errorLog(logLength);
    glGetShaderInfoLog(shader, logLength, NULL, &errorLog[0]);
    std::cout << shaderName << " Log : " << std::endl;
    std::cout << "Log Length " << logLength << std::endl;
    for (GLchar errorLine : errorLog) {
        std::cout << errorLine;
    }
    
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) std::cout << "The " + shaderName + " shader failed to compile" << std::endl;

    return success;
}

GLuint Shader::getUniformID(std::string id) {
    return uniformIDs.find(id)->second;//todo error handling
}

void Shader::checkForReload() {
    uint64_t vertTimestamp = GetShaderFileTimestamp(vertFile.location.c_str());
    uint64_t fragTimestamp = GetShaderFileTimestamp(fragFile.location.c_str());

     if (vertTimestamp > vertFile.lastTimestamp || fragTimestamp > fragFile.lastTimestamp) {
        loadVertFrag(vertFile.location,fragFile.location);
        
        vertFile.lastTimestamp = vertTimestamp;
        fragFile.lastTimestamp = fragTimestamp;
        
        Logger::Info("Shader Updated");
    }
}

Shader::~Shader() {
    glDeleteProgram(program);
}