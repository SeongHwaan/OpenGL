#include "header/ModelManager.h"

void ModelManager::loadModel(const std::string& name, string const& path)
{
    models[name] = std::make_shared<Model>(path);
}

std::shared_ptr<Model> ModelManager::getModel(const std::string& name)
{
    if (models.find(name) != models.end())
    {
        return models[name];
    }
    throw std::runtime_error("Model not found: " + name);
}
