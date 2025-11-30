// include/Model.h
#pragma once
#include <string>
#include <vector>
#include <memory>

#include "Mesh.h"
#include "Shader.h"

class Model {
public:
    Model() = default;
    Model(const std::string& path);

    void draw(const Shader& shader) const;

private:
    std::vector<std::shared_ptr<Mesh>> meshes;

    void loadModel(const std::string& path);
    void processNode(const struct tinygltf::Node& node, const struct tinygltf::Model& gltfModel);
    std::shared_ptr<Mesh> processMesh(const struct tinygltf::Mesh& gltfMesh,
                                      const struct tinygltf::Model& gltfModel);
};
