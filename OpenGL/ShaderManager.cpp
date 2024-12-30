#include <map>
#include <string>
#include <memory>
#include ""

class ShaderManager {
private:
    std::map<std::string, std::shared_ptr<Shader>> shaders;

public:
    void loadShader(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath) {
        shaders[name] = std::make_shared<Shader>(vertexPath, fragmentPath);
    }

    std::shared_ptr<Shader> getShader(const std::string& name) {
        if (shaders.find(name) != shaders.end()) {
            return shaders[name];
        }
        throw std::runtime_error("Shader not found: " + name);
    }
};

// 사용 예제
ShaderManager shaderManager;
shaderManager.loadShader("normal", "Shader/3.3_vertex.txt", "Shader/3.3_fragment.txt");
shaderManager.loadShader("lighting", "Shader/2.2.basic_lighting.txt", "Shader/2.2.basic_lightingfs.txt");

auto lightingShader = shaderManager.getShader("lighting");
lightingShader->use();
