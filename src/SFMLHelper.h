//
// Created by Cameron Moore on 4/21/24.
//

#ifndef SPOTIGATOR_SFMLHELPER_H
#define SPOTIGATOR_SFMLHELPER_H
#include "SFML/Graphics.hpp"
#include <iostream>

class SFMLHelper {
public:
    static void createSFMLImage(sf::Sprite &sprite, sf::Texture &texture);
    static void createSFMLText(sf::Text &check, std::string text, sf::Font &font, int charSize);
    static void createSFMLButton(sf::RectangleShape &rectangle, sf::Text &text, int xCoord, int yCoord);
    static void displayStartWindow();
    static std::vector<std::string> displayInputWindow();
    static void displayHelpWindow();
    static void displayResultsWindow(std::string hashString, std::string RBString);
    static bool validCountry(std::string &countryCode);
    static bool validDate(std::string &date);
};


#endif //SPOTIGATOR_SFMLHELPER_H
