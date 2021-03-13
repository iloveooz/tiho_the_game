#include "TextureHolder.hpp"

void Textures::TextureHolder::load(Textures::ID id, const std::string &fileName) {
    std::unique_ptr<sf::Texture> texture(new sf::Texture());
    texture->loadFromFile(fileName);
    m_TextureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture &Textures::TextureHolder::get(Textures::ID id) {
    auto found = m_TextureMap.find(id);
    return *found->second;
}

const sf::Texture &Textures::TextureHolder::get(Textures::ID id) const {
    auto found = m_TextureMap.find(id);
    return *found->second;
}
