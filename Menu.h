#pragma once
#include<SFML/Graphics.hpp>

#define MAX_NUMBER_of_ITEMS 5

class Menu
{
public :
    Menu( float width, float height );
    ~Menu();

    void draw(sf::RenderWindow &window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return SelectedItemIndex; }

private :

    int SelectedItemIndex;
    sf::Font font;
    sf::Text menu[MAX_NUMBER_of_ITEMS];
};
