#pragma once

#include <map>
#include <string>
#include <memory>
#include <Model/model.h>

class ModelManager
{
private:
    std::map<std::string, std::shared_ptr<Model>> models;

public:

    void loadModel(const std::string& name, string const& path);

    std::shared_ptr<Model> getModel(const std::string& name);
};