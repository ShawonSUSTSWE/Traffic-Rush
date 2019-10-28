#include "Menu.h"

using namespace sf;

Menu::Menu ( float width, float height )

{
    if ( !font.loadFromFile("Comic Sans MS.ttf"));
    {

    }

    menu[0].setFont(font);
    menu[0].setColor(Color::Red);
    menu[0].setString("PLAY");
    menu[0].setPosition( Vector2f( width/2, height / (MAX_NUMBER_of_ITEMS+1) * 1 ));

    menu[1].setFont(font);
    menu[1].setColor(Color::White);
    menu[1].setString("Difficulty");
    menu[1].setPosition( Vector2f( width/2, height / (MAX_NUMBER_of_ITEMS+1) * 2 ));

    menu[2].setFont(font);
    menu[2].setColor(Color::White);
    menu[2].setString("High Scores");
    menu[2].setPosition( Vector2f( width/2, height / (MAX_NUMBER_of_ITEMS+1) * 3 ));

    menu[3].setFont(font);
    menu[3].setColor(Color::White);
    menu[3].setString("Instructions");
    menu[3].setPosition( Vector2f( width/2, height / (MAX_NUMBER_of_ITEMS+1) * 4 ));

    menu[3].setFont(font);
    menu[3].setColor(Color::White);
    menu[3].setString("Credits");
    menu[3].setPosition( Vector2f( width/2, height / (MAX_NUMBER_of_ITEMS+1) * 5 ));
}

Menu :: ~Menu()
{

}

void Menu::draw( RenderWindow &window)

{
    for ( int i = 0; i < MAX_NUMBER_of_ITEMS; i++ )
    {
        window.draw(menu[i]);
    }
}
