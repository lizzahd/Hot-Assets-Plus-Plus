//
// Created by xerox on 3/14/2026.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <raylib-cpp.hpp>

struct Tileset {
    std::string m_texName;
    raylib::Vector2 m_cellSize;
};

using ShaderArg = std::tuple<const std::string &, const void *, const int>;

class AssetManager {
public:
    explicit AssetManager(const std::string &rootDirectory);
    ~AssetManager();

    raylib::Texture2D& getTex(const std::string& name);
    void createTileset(std::string name, const std::string &texName, raylib::Vector2 cellSize);
    void drawCell(const std::string &tilesetName, int cellIndex, raylib::Vector2 pos, raylib::Vector2 size, raylib::Color color);
    void drawCell(const std::string &tilesetName, int cellIndex, raylib::Vector2 pos, raylib::Color color);

    raylib::Shader& getShader(const std::string& name);
    void setShaderValue(const std::string &name, const std::string &propertyName, const void *value, int uniformType);
    void setShaderValue(const std::string &name, const ShaderArg &shaderArg);
    void beginShaderMode(const std::string &name, std::initializer_list<ShaderArg> args);

    void playSound(const std::string& name);

    // Graphics
    std::unordered_map<std::string, raylib::Texture2D> m_textures;
    std::unordered_map<std::string, Tileset> m_tilesets;
    std::unordered_map<std::string, raylib::Shader> m_shaders;

    // Sound
    std::unordered_map<std::string, Sound> m_sounds;
    std::unordered_map<std::string, std::vector<Sound>> m_soundAliases;
    int m_soundAliasCount = 8;
};
