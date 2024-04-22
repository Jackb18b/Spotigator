//
// Created by Cameron Moore on 4/21/24.
//

#include "SFMLHelper.h"

void SFMLHelper::createSFMLText(sf::Text &check, std::string text, sf::Font &font, int charSize) {
    // This sets attributes to an existing sf::Text
    check.setString(text);
    check.setFont(font);
    check.setCharacterSize(charSize);
    sf::FloatRect textBounds = check.getGlobalBounds();
    check.setOrigin(textBounds.width /2.0f, textBounds.height / 2.0f);
}

void SFMLHelper::createSFMLImage(sf::Sprite &sprite, sf::Texture &texture) {
    // This creates an image using sprites and textures
    sprite.setTexture(texture);
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    sprite.setOrigin(spriteBounds.width / 2.0f, spriteBounds.height / 2.0f);
}

void SFMLHelper::createSFMLButton(sf::RectangleShape &rectangle, sf::Text &text, int xCoord, int yCoord) {
    // Creates a rectangle with text in the middle at x, y
    rectangle.setPosition(xCoord, yCoord);
    sf::Color green(66, 107, 31);
    rectangle.setFillColor(green);

    sf::FloatRect rectangleBounds = rectangle.getGlobalBounds();
    rectangle.setOrigin(rectangleBounds.width / 2.0f, rectangleBounds.height / 2.0f);

    rectangleBounds = rectangle.getLocalBounds();
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(rectangle.getPosition().x + (rectangleBounds.width - textBounds.width) / 2.0f,
                     rectangle.getPosition().y - 10);
}

bool SFMLHelper::validCountry(std::string &countryCode) {
    // Will check every country supported by API for proper code
    std::vector<std::string> countryCodes = {
            "ZA", "VN", "US", "UA", "TW", "TR", "TH", "SV", "SK", "SG",
            "SE", "SA", "RO", "PT", "PL", "PK", "PH", "PA", "NZ", "NO",
            "NI", "NG", "MY", "MX", "MA", "LV", "LU", "LT", "KZ", "KR",
            "JP", "IT", "IS", "IL", "IE", "ID", "HU", "HN", "HK", "GT",
            "GR", "GB", "FR", "FI", "ES", "EG", "EE", "DO", "DK", "DE",
            "CZ", "CR", "CH", "CA", "BY", "BR", "BO", "BG", "BE", "AU",
            "AT", "AR"
    };
    return (std::find(countryCodes.begin(), countryCodes.end(), countryCode) != countryCodes.end());
}

bool SFMLHelper::validDate(std::string &date) {
    if (date.length() != 11) {
        return false;
    }
    std::string month = date.substr(1, 2);
    std::string day = date.substr(4, 5);
    std::string year = date.substr(7, 10);
    // Year should always be 2024
    if (year == "2024") {
        // Gets range for January
        if (month == "01" && 12 < stoi(day) && stoi(day) < 32) return true;
        // Gets range for February
        if (month == "02" && 0 < stoi(day) && stoi(day) < 30) return true;
        // Gets range for March
        if (month == "03" && 0 < stoi(day) && stoi(day) < 8) return true;
    }
    return false;
}

void SFMLHelper::displayStartWindow() {
    const int width = 800, height = 500;
    sf::RenderWindow startWindow(sf::VideoMode(width, height), "Spotigator");
    sf::Font font;
    if (!font.loadFromFile("../SFMLFiles/font.ttf")) {
        std::cout << "Error loading font" << "\n";
        exit(0);
    }
    /////// Welcome screen /////////
    // Displays created by: on screen
    sf::Text authorText;
    SFMLHelper::createSFMLText(authorText, "Created by: Jonathon Brown, Cameron Moore, and Santiago Roa", font, 18);
    authorText.setPosition(sf::Vector2f(width / 2.0f, height - 480));

    // Displays Songfinder on screen
    sf::Text songfinderText;
    SFMLHelper::createSFMLText(songfinderText, "Songfinder", font, 32);
    songfinderText.setPosition(sf::Vector2f(width / 2.0f, height - 300));

    // Displays spotify.png on screen
    sf::Texture spotTexture;
    if (!spotTexture.loadFromFile("../SFMLFiles/spotify.png")) {
        std::cout << "error loading spotify" << "\n";
        exit(0);
    }
    sf::Sprite spotSprite;
    SFMLHelper::createSFMLImage(spotSprite, spotTexture);
    spotSprite.setPosition(width / 2.0f, height - 380);
    spotSprite.setScale(0.25f, 0.25f);

    // Background color hex
    sf::Color background(26, 0, 69);

    // Go! Button
    sf::Text goButtonText;
    SFMLHelper::createSFMLText(goButtonText, "Go!   -> ", font, 24);
    goButtonText.setFillColor(background);
    sf::RectangleShape goButton(sf::Vector2f(130, 40));
    SFMLHelper::createSFMLButton(goButton, goButtonText, width / 2.0f, height - 150);

    while (startWindow.isOpen()) {
        sf::Event event;
        startWindow.clear(background);
        startWindow.draw(authorText);
        startWindow.draw(songfinderText);
        startWindow.draw(spotSprite);
        startWindow.draw(goButton);
        startWindow.draw(goButtonText);
        startWindow.display();
        while (startWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                startWindow.close();
                exit(0);
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (goButton.getGlobalBounds().contains(startWindow.mapPixelToCoords(sf::Mouse::getPosition(startWindow)))) {
                    startWindow.close();
                }
            }
        }
    }
}

std::vector<std::string> SFMLHelper::displayInputWindow() {
    std::vector<std::string> returnVec;
    // Create a new window for the input window
    const int width = 800, height = 500;
    sf::RenderWindow inputWindow(sf::VideoMode(width, height), "Input Window");

    // Load a font for the input lines
    sf::Font font;
    if (!font.loadFromFile("../SFMLFiles/font.ttf")) {
        // Handle error loading the font
        std::cout << "couldnt load font\n";
        exit(0);
    }
    sf::Text countryPromptText;
    sf::Text inputCountryText;

    // Choose date and country text
    sf::Text chooseDateCountryText;
    std::string text = "Choose a date and country:                           ";
    createSFMLText(chooseDateCountryText, text, font, 24);
    chooseDateCountryText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    chooseDateCountryText.setPosition(sf::Vector2f(width / 2.0f - 29, (height / 2.0f) - 175));

    // Country: text
    createSFMLText(countryPromptText, "Country:", font, 18);
    countryPromptText.setStyle(sf::Text::Bold);
    countryPromptText.setPosition(sf::Vector2f(width / 2.0f - 300, height / 2.0f - 75));

    // Date: text
    sf::Text datePrompt;
    createSFMLText(datePrompt, "Date: ", font, 18);
    datePrompt.setStyle(sf::Text::Bold);
    datePrompt.setPosition(sf::Vector2f(width / 2.0f - 310, height / 2.0f + 72));

    //Display globe on right
    sf::Texture globeTexture;
    if (!globeTexture.loadFromFile("../SFMLFiles/world.png")) {
        std::cout << "error loading world" << "\n";
        exit(0);
    }
    sf::Sprite globeSprite;
    SFMLHelper::createSFMLImage(globeSprite, globeTexture);
    globeSprite.setPosition(width / 2.0f + 200, height / 2.0f);
    globeSprite.setScale(0.25f, 0.25f);




    // Country Input (shows what user is typing and the countryCursor)
    createSFMLText(inputCountryText, "", font, 18);
    inputCountryText.setFillColor(sf::Color::White);
    inputCountryText.setStyle(sf::Text::Bold);
    sf::FloatRect inputCountryTextBounds = inputCountryText.getGlobalBounds();
    sf::RectangleShape countryCursor(sf::Vector2f(2, 18));
    inputCountryText.setOrigin(sf::Vector2f(inputCountryTextBounds.width / 2.0f, inputCountryTextBounds.height / 2.0f));
    countryCursor.setOrigin(sf::Vector2f(1, 9));
    inputCountryText.setPosition(sf::Vector2f(width / 2.0f - 230, height / 2.0f - 75));
    countryCursor.setPosition(inputCountryText.getGlobalBounds().left + inputCountryText.getGlobalBounds().width,
                              inputCountryText.getGlobalBounds().top + 4);

    // Date Input (shows what user is typing and the countryCursor
    sf::Text inputDateText;
    createSFMLText(inputDateText, "", font, 18);
    inputDateText.setFillColor(sf::Color::White);
    inputDateText.setStyle(sf::Text::Bold);
    sf::FloatRect inputDateTextBounds = inputDateText.getGlobalBounds();
    sf::RectangleShape dateCursor(sf::Vector2f(2, 18));
    inputDateText.setOrigin(sf::Vector2f(inputDateTextBounds.width / 2.0f, inputDateTextBounds.height / 2.0f));
    dateCursor.setOrigin(sf::Vector2f(1, 9));
    inputDateText.setPosition(sf::Vector2f(width / 2.0f - 230, height / 2.0f + 60));
    dateCursor.setPosition(inputDateText.getGlobalBounds().left + inputDateText.getGlobalBounds().width,
                       inputDateText.getGlobalBounds().top + 13);

    // Help button
    sf::Color background(26, 0, 69);
    sf::Text helpButtonText;
    SFMLHelper::createSFMLText(helpButtonText, "Help   ", font, 24);
    helpButtonText.setFillColor(background);
    sf::RectangleShape helpButton(sf::Vector2f(130, 40));
    SFMLHelper::createSFMLButton(helpButton, helpButtonText, width / 2.0f, height - 100);
    std::string userCountryInput;
    std::string userDateInput;

    // Enter text
    sf::Text enterText;
    createSFMLText(enterText, "Press enter to proceed", font, 18);
    enterText.setStyle(sf::Text::Bold);
    enterText.setPosition(sf::Vector2f(width / 2.0f, height - 65));

    bool backspacePressed;
    bool onDate = false;
    std::string countryCode;
    while (inputWindow.isOpen()) {
        sf::Event event;
        inputWindow.clear(background);
        inputWindow.draw(globeSprite);
        inputWindow.draw(chooseDateCountryText);
        inputWindow.draw(countryPromptText);
        inputWindow.draw(datePrompt);
        inputWindow.draw(inputCountryText);
        inputWindow.draw(helpButton);
        inputWindow.draw(helpButtonText);
        inputWindow.draw(enterText);
        if (!onDate) {
            inputWindow.draw(countryCursor);
        }
        else {
            inputWindow.draw(dateCursor);
        }
        inputWindow.draw(datePrompt);
        inputWindow.draw(inputDateText);
        inputWindow.display();
        while (inputWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                inputWindow.close();
                exit(0);
            }
            if (event.type == event.MouseButtonPressed) {
                if (helpButton.getGlobalBounds().contains(inputWindow.mapPixelToCoords(sf::Mouse::getPosition(inputWindow)))) {
                    displayHelpWindow();
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                if (!onDate && validCountry(userCountryInput)) {
                    userCountryInput.at(0) = char(toupper(userCountryInput.at(0)));
                    countryCode = userCountryInput;
                    returnVec.push_back(countryCode);
                    onDate = true;
                }
                else if (validDate(userDateInput)) {
                    std::string correctedDate;
                    std::string month = userDateInput.substr(1, 2);
                    std::string day = userDateInput.substr(4, 5);
                    std::string year = userDateInput.substr(7, 10);
                    correctedDate = year + '-' + month + '-' + day;
                    correctedDate = correctedDate.substr(0, 10);
                    returnVec.push_back(correctedDate);
                    inputWindow.close();
                }

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace) && !backspacePressed) {
                if (!onDate) {
                    backspacePressed = true;
                    userCountryInput.pop_back();
                    inputCountryText.setString(userCountryInput);
                    inputCountryTextBounds = inputCountryText.getGlobalBounds();
                    inputCountryText.setOrigin(
                            sf::Vector2f(inputCountryTextBounds.width / 2.0f, inputCountryTextBounds.height / 2.0f));
                    countryCursor.setPosition(
                            inputCountryText.getGlobalBounds().left + inputCountryText.getGlobalBounds().width,
                            inputCountryText.getGlobalBounds().top + 4);
                }
                else if (1 < userDateInput.size()){
                    backspacePressed = true;
                    userDateInput.pop_back();
                    inputDateText.setString(userDateInput);
                    inputDateTextBounds = inputDateText.getGlobalBounds();
                    inputDateText.setOrigin(
                            sf::Vector2f(inputDateTextBounds.width / 2.0f - 20, inputDateTextBounds.height / 2.0f));
                    dateCursor.setPosition(
                            inputDateText.getGlobalBounds().left + inputDateText.getGlobalBounds().width,
                            inputDateText.getGlobalBounds().top + 13);
                }
                break;
            }  else if (event.type == sf::Event::TextEntered) {
                    if (!onDate && userCountryInput.size() < 2 && isalpha(event.text.unicode)) {
                        userCountryInput += toupper(event.text.unicode);
                        inputCountryText.setString(userCountryInput);
                        inputCountryTextBounds = inputCountryText.getGlobalBounds();
                        inputCountryText.setOrigin(sf::Vector2f(inputCountryTextBounds.width / 2.0f,
                                                                inputCountryTextBounds.height / 2.0f));
                        countryCursor.setPosition(
                                inputCountryText.getGlobalBounds().left + inputCountryText.getGlobalBounds().width,
                                inputCountryText.getGlobalBounds().top + 4);
                    }
                    else if (userDateInput.size() < 11 && countryCode.size() == 2 && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
                        userDateInput += toupper(event.text.unicode);
                        inputDateText.setString(userDateInput);
                        inputDateTextBounds = inputDateText.getGlobalBounds();
                        inputDateText.setOrigin(sf::Vector2f(inputDateTextBounds.width / 2.0f - 20,
                                                                inputDateTextBounds.height / 2.0f));
                        dateCursor.setPosition(
                                inputDateText.getGlobalBounds().left + inputDateText.getGlobalBounds().width,
                                inputDateText.getGlobalBounds().top + 11);
                    }
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Backspace)) {
                backspacePressed = false;
            }
        }
    }
    return returnVec;
}

void SFMLHelper::displayHelpWindow() {
    const int width = 700, height = 500;
    sf::RenderWindow helpWindow(sf::VideoMode(width, height), "Help");
    sf::Font font;
    if (!font.loadFromFile("../SFMLFiles/font.ttf")) {
        std::cout << "Error loading font" << "\n";
        exit(0);
    }

    // Displays Help
    sf::Text helpText;
    std::string song = "postion. song1 by person1 \n song 2 by person 2 \n song3...";
    SFMLHelper::createSFMLText(helpText, "Help", font, 24);
    helpText.setPosition(sf::Vector2f(width / 2.0f, height - 480));
    helpText.setStyle(sf::Text::Bold | sf::Text::Underlined);

    // Displays ISO info on screen
    std::vector<std::string> countryCodes = {
            "ZA", "VN", "US", "UA", "TW", "TR", "TH", "SV", "SK", "SG",
            "SE", "SA", "RO", "PT", "PL", "PK", "PH", "PA", "NZ", "NO",
            "NI", "NG", "MY", "MX", "MA", "LV", "LU", "LT", "KZ", "KR",
            "JP", "IT", "IS", "IL", "IE", "ID", "HU", "HN", "HK", "GT",
            "GR", "GB", "FR", "FI", "ES", "EG", "EE", "DO", "DK", "DE",
            "CZ", "CR", "CH", "CA", "BY", "BR", "BO", "BG", "BE", "AU",
            "AT", "AR"
    };
    sf::Text ISOText;
    std::string ISOCodes = "The following ISO Codes are accepted as input: \n";
    for (int i = 1; i < countryCodes.size() + 1; i++) {
        ISOCodes.append(countryCodes[i - 1] + " ");
        if (i % 10 == 0) ISOCodes.append("\n");
    }
    SFMLHelper::createSFMLText(ISOText, ISOCodes, font, 18);
    ISOText.setPosition(sf::Vector2f(width / 2.0f, height - 375));

    // Displays date info
    sf::Text dateText;
    SFMLHelper::createSFMLText(dateText, "Enter the date as MM/DD/YYYY. We only accept dates between: \n"
                                         "01/13/2024 - 03/07/2024", font, 18);
    dateText.setPosition(width / 2.0f, height - 150);




    // Background color hex
    sf::Color background(26, 0, 69);


    while (helpWindow.isOpen()) {
        sf::Event event;
        helpWindow.clear(background);
        helpWindow.draw(helpText);
        helpWindow.draw(ISOText);
        helpWindow.draw(dateText);
        helpWindow.display();
        while (helpWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                helpWindow.close();
            }
        }
    }
}

void SFMLHelper::displayResultsWindow(std::string hashString, std::string RBString) {
    const int width = 1000, height = 600;
    sf::RenderWindow resultWindow(sf::VideoMode(width, height), "Results");
    sf::Font font;
    if (!font.loadFromFile("../SFMLFiles/font.ttf")) {
        std::cout << "Error loading font" << "\n";
        exit(0);
    }

    // Displays Results
    sf::Text resultText;
    SFMLHelper::createSFMLText(resultText, "Results", font, 24);
    resultText.setPosition(sf::Vector2f(width / 2.0f, height - 550));
    resultText.setStyle(sf::Text::Bold | sf::Text::Underlined);


    // Displays date info
    sf::Text hashText;
    SFMLHelper::createSFMLText(hashText, hashString, font, 15);
    hashText.setPosition(width / 2.0f, height - 400);

    sf::Text RBText;
    SFMLHelper::createSFMLText(RBText, RBString, font, 15);
    RBText.setPosition(width / 2.0f, height - 180);




    // Background color hex
    sf::Color background(26, 0, 69);


    while (resultWindow.isOpen()) {
        sf::Event event;
        resultWindow.clear(background);
        resultWindow.draw(resultText);
        resultWindow.draw(hashText);
        resultWindow.draw(RBText);
        resultWindow.display();
        while (resultWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                resultWindow.close();
            }
        }
    }
}