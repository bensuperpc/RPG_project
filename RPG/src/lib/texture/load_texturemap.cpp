/*
** BENSUPERPC PROJECT, 2020
** Texture
** File description:
** load_titlemap.cpp
*/

#include "load_texturemap.hpp"

void texture::load_texturemap(std::unordered_map<int, std::string> &texture_map, const std::string &file)
{
    std::string index = "";
    std::string path = "";
    std::string line;
    std::ifstream myfile(file);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            std::stringstream iss(line);
            std::getline(iss, index, ',');
            iss >> path;
            texture_map.insert(std::make_pair(std::stoi(index), path));
        }
    }
    myfile.close();
}