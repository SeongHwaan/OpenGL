#pragma once

#include <map>
#include <string>
#include <memory>
#include <Shader/shader.h>

class ShaderManager 
{
private:
    std::map<std::string, std::shared_ptr<Shader>> shaders;

public:
    void loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath);

    std::shared_ptr<Shader> getShader(const std::string& name);
};