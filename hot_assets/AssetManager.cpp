//
// Created by xerox on 3/14/2026.
//

#include <filesystem>
#include <ranges>

#include "AssetManager.h"

namespace fs = std::filesystem;

AssetManager::~AssetManager() {
    // Unload textures
    for (const auto &tex: m_textures | std::views::values) {
        UnloadTexture(tex);
    }

    // Unload sounds and their aliases
    for (const auto& aliases: m_soundAliases | std::views::values) {
        for (const auto& alias : aliases) {
            UnloadSoundAlias(alias);
        }
    }

    for (const auto& sound : m_sounds | std::views::values) {
        UnloadSound(sound);
    }
}

void AssetManager::loadTextures(const std::string &directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        const fs::path& path = entry.path();
        if (path.extension() != ".png") {
            continue;
        }

        m_textures.emplace(path.stem().string(), LoadTexture(path.string().c_str()));
    }
}

void AssetManager::loadSounds(const std::string &directory) {
    // Load Sounds
    for (const auto& entry : fs::directory_iterator(directory)) {
        const fs::path& path = entry.path();
        if (path.extension() != ".wav") {
            continue;
        }

        // Sound
        std::string key = path.stem().string();
        m_sounds.emplace(key, LoadSound(path.string().c_str()));

        // Sound Alias
        auto& aliases = m_soundAliases[key];
        for (int i = 0; i < m_soundAliasCount; i++) {
            aliases.push_back(LoadSoundAlias(m_sounds[key]));
        }
    }
}

void AssetManager::loadShaders(const std::string &directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        const fs::path& path = entry.path();
        if (path.extension() != ".frag") {
            continue;
        }

        m_shaders.emplace(path.stem().string(), LoadShader(nullptr, path.string().c_str()));
    }
}

raylib::Texture2D &AssetManager::getTex(const std::string& name) {
    return m_textures[name];
}

void AssetManager::createTileset(const std::string& name, const std::string &texName, const raylib::Vector2 cellSize) {
    m_tilesets.insert({name, {texName, cellSize}});
}

void AssetManager::drawCell(const std::string &tilesetName, const int cellIndex, const raylib::Vector2 pos, raylib::Vector2 size, const raylib::Color color) {
    const auto &[texName, cellSize] = m_tilesets[tilesetName];
    if (size.x <= 0 || size.y <= 0) {
        size = cellSize;
    }

    const auto &tex = getTex(texName);
    const float sX = cellIndex % static_cast<int>(tex.width / cellSize.x);
    const float sY = cellIndex / static_cast<int>(tex.height / cellSize.y);
    const raylib::Rectangle src{sX * cellSize.x, sY * cellSize.y, cellSize.x, cellSize.y};
    const raylib::Rectangle dst{pos, size};
    tex.Draw(
        src,
        dst,
        {0, 0},
        0,
        color
    );
}

void AssetManager::drawCell(const std::string &tilesetName, const int cellIndex, const raylib::Vector2 pos, const raylib::Color color) {
    drawCell(tilesetName, cellIndex, pos, {0, 0}, color);
}

raylib::Shader &AssetManager::getShader(const std::string &name) {
    return m_shaders[name];
}

void AssetManager::playSound(const std::string& name) {
    for (const auto& alias : m_soundAliases[name]) {
        if (!IsSoundPlaying(alias)) {
            PlaySound(alias);
            return;
        }
    }
}
