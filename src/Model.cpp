// src/Model.cpp
#include "Model.h"
#include "tiny_gltf.h"

#include <iostream>
#include <glm/glm.hpp>

Model::Model(const std::string& path) {
    loadModel(path);
}

void Model::draw(const Shader& shader) const {
    for (auto& mesh : meshes) {
        mesh->draw(shader);
    }
}

void Model::loadModel(const std::string& path) {
    tinygltf::Model gltfModel;
    tinygltf::TinyGLTF loader;
    std::string err, warn;

    bool ret = loader.LoadASCIIFromFile(&gltfModel, &err, &warn, path);
    if (!warn.empty()) std::cout << "GLTF Warning: " << warn << "\n";
    if (!err.empty())  std::cerr << "GLTF Error: " << err << "\n";

    if (!ret) {
        std::cerr << "Failed to load glTF: " << path << "\n";
        return;
    }

    // Process all root nodes
    for (size_t i = 0; i < gltfModel.scenes[gltfModel.defaultScene].nodes.size(); i++) {
        int nodeIndex = gltfModel.scenes[gltfModel.defaultScene].nodes[i];
        processNode(gltfModel.nodes[nodeIndex], gltfModel);
    }
}

void Model::processNode(const tinygltf::Node& node, const tinygltf::Model& gltfModel) {
    if (node.mesh >= 0) {
        const tinygltf::Mesh& mesh = gltfModel.meshes[node.mesh];
        meshes.push_back(processMesh(mesh, gltfModel));
    }

    for (int child : node.children) {
        processNode(gltfModel.nodes[child], gltfModel);
    }
}

std::shared_ptr<Mesh> Model::processMesh(const tinygltf::Mesh& gltfMesh,
                                         const tinygltf::Model& gltfModel) {

    const tinygltf::Primitive& primitive = gltfMesh.primitives[0];

    const auto& posAccessor = gltfModel.accessors[primitive.attributes.find("POSITION")->second];
    const auto& posBufferView = gltfModel.bufferViews[posAccessor.bufferView];
    const auto& posBuffer = gltfModel.buffers[posBufferView.buffer];

    const auto& normAccessor = gltfModel.accessors[primitive.attributes.find("NORMAL")->second];
    const auto& normBufferView = gltfModel.bufferViews[normAccessor.bufferView];
    const auto& normBuffer = gltfModel.buffers[normBufferView.buffer];

    const auto& indexAccessor = gltfModel.accessors[primitive.indices];
    const auto& indexBufferView = gltfModel.bufferViews[indexAccessor.bufferView];
    const auto& indexBuffer = gltfModel.buffers[indexBufferView.buffer];

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    // Read vertex positions
    const float* posData = reinterpret_cast<const float*>(
        &posBuffer.data[posBufferView.byteOffset + posAccessor.byteOffset]
    );
    const float* normData = reinterpret_cast<const float*>(
        &normBuffer.data[normBufferView.byteOffset + normAccessor.byteOffset]
    );

    for (size_t i = 0; i < posAccessor.count; i++) {
        Vertex v;
        v.position = glm::vec3(posData[i*3+0], posData[i*3+1], posData[i*3+2]);
        v.normal   = glm::vec3(normData[i*3+0], normData[i*3+1], normData[i*3+2]);
        vertices.push_back(v);
    }

    // Read indices
    if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
        const unsigned int* buf = reinterpret_cast<const unsigned int*>(
            &indexBuffer.data[indexBufferView.byteOffset + indexAccessor.byteOffset]
        );
        indices.assign(buf, buf + indexAccessor.count);
    }

    return std::make_shared<Mesh>(vertices, indices);
}
