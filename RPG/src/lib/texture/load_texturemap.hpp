/*
** BENSUPERPC PROJECT, 2020
** Texture
** File description:
** load_texturemap.hpp
*/

#ifndef LOAD_TEXTUREMAP_HPP_
#define LOAD_TEXTUREMAP_HPP_

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

namespace texture
{
void load_texturemap(std::unordered_map<int, std::string> &, const std::string &);

} // namespace texture

#endif
