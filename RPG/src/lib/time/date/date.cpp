/*
** BENSUPERPC PROJECT, 2020
** RPG
** File description:
** date.cpp
*/

#include "date.hpp"

std::string date::get_date()
{
    auto &&t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
    return oss.str();
}
