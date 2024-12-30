#include "header/ShaderManager.h"


void ShaderManager::loadShader(const std::string& name, const char* vertexPath, const char* fragmentPath)
{
    shaders[name] = std::make_shared<Shader>(vertexPath, fragmentPath);
}

std::shared_ptr<Shader> ShaderManager::getShader(const std::string& name)
{
    if (shaders.find(name) != shaders.end())
    {
        return shaders[name];
    }
    throw std::runtime_error("Shader not found: " + name);
}
