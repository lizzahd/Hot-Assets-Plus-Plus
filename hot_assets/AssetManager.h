//
// Created by xerox on 3/14/2026.
//

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <raylib-cpp.hpp>

class AssetManager {
public:
    explicit AssetManager(const std::string &rootDirectory);
    ~AssetManager();

    raylib::Texture2D& getTex(const std::string& name);
    void playSound(const std::string& name);

    // Graphics
    std::unordered_map<std::string, raylib::Texture2D> m_textures;

    // Sound
    std::unordered_map<std::string, Sound> m_sounds;
    std::unordered_map<std::string, std::vector<Sound>> m_soundAliases;
    int m_soundAliasCount = 8;
};
