#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>
#include<fstream>

using namespace std;
using namespace sf;

//Init game const
const double SCREEN_WIDTH=800;
const double SCREEN_HEIGH=600;
const int borderLeft=140;
const int borderRight=660;
const int racerWidth=40;
const int racerHeight=70;
string stringscore="";
int score=0;
double gameSpeed=0.3;
int gameoveronce = 0;
int HIGHSCORE = 0;
int pausedonce;
int lives = 2;
int timer = 0;
int show = 0;

//Create Main Windows
RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Car Racing");

//Creat random Number for game loop
int getRandomNumber(int a, int b);

// Create gameover screen
int gameOver();
int startGame();

int main()
{
there:
    timer = 0;
    std::ifstream readFile;
    readFile.open("Highscore.txt");
    if ( readFile.is_open() )
    {
        while( !readFile.eof() )
        {
            readFile >> HIGHSCORE;
        }
    }
    readFile.close();
    startGame();


here:
    lives = 2;
    if ( gameoveronce > 0 )
    {
        gameSpeed = 0.3;
        score = 0;
        gameoveronce++;
    }
    else
        gameoveronce++;

    //Init game music
    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("sound/fire_funk.ogg");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);


    sf::Clock clock;

    cout << gameSpeed << endl;
    Texture background, racer, obs1, obs2, obs3, obs4,gameover, explosion, Coin;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/xirod.ttf");

    app.setFramerateLimit(560);

    //Load all images
    if (!background.loadFromFile("cars/background.png"))
        return EXIT_FAILURE;
    if (!Coin.loadFromFile("cars/Coin2.png"))
        return EXIT_FAILURE;
    if (!explosion.loadFromFile("cars/explosion2.png"))
        return EXIT_FAILURE;
    if (!racer.loadFromFile("cars/racer.png"))
        return EXIT_FAILURE;
    if (!obs1.loadFromFile("cars/obs1.png"))
        return EXIT_FAILURE;
    if (!obs2.loadFromFile("cars/obs2.png"))
        return EXIT_FAILURE;
    if (!obs3.loadFromFile("cars/obs3.png"))
        return EXIT_FAILURE;
    if (!obs4.loadFromFile("cars/obs4.png"))
        return EXIT_FAILURE;

    //Create sprite


    Sprite Background(background),Background1(background),Racer(racer),Obs1(obs1),Obs2(obs2),Obs3(obs3),Obs4(obs4),Gameover(gameover), Explosion(explosion), coin(Coin);

    double RacerX, RacerY,Obs1X, Obs1Y,Obs2X, Obs2Y,Obs3X, Obs3Y,Obs4X, Obs4Y, CoinX, CoinY, ExplosionX, ExplosionY;

    //Set racer and Obs pos
    RacerX=SCREEN_WIDTH/2;
    RacerY=SCREEN_HEIGH-racerHeight;
    Obs1X=getRandomNumber(borderLeft,borderRight);
    Obs2X=getRandomNumber(borderLeft,borderRight);
    Obs3X=getRandomNumber(borderLeft,borderRight);
    CoinX = getRandomNumber(borderLeft,borderRight);
    Obs4X=getRandomNumber(borderLeft,borderRight);
    Obs1Y=0,Obs2Y=-100,Obs3Y=-200,Obs4Y=-300, CoinY = -1632;
    double BackgroundY1=0;
    double BackgroundY2=-600;

out :
    GameSound.play();
    GameSound.setLoop(true);


    //GAME LOOP
    while (app.isOpen())
    {
        show = 0;
        cout << clock.getElapsedTime().asSeconds() << endl;
        if ( pausedonce == 1 )
            pausedonce == 0;
        //Init and count score
        stringscore="SCORE:"+to_string(score);
        Text text(stringscore, myfont, 15);
        text.setPosition(5,0);

        //Set car position
        ExplosionX = RacerX, ExplosionY = RacerY;
        Racer.setPosition(RacerX,RacerY);
        Obs1.setPosition(Obs1X,Obs1Y);
        Obs2.setPosition(Obs2X,Obs2Y);
        Obs3.setPosition(Obs3X,Obs3Y);
        Obs4.setPosition(Obs4X,Obs4Y);
        Explosion.setPosition(ExplosionX,ExplosionY);
        coin.setPosition(CoinX,CoinY);

        //Creat scrolling background
        Background.setPosition(0,BackgroundY1);
        Background1.setPosition(0,BackgroundY2);
        if (BackgroundY2>0)
        {
            BackgroundY1=0;
            BackgroundY2=BackgroundY1-600;
        }
        BackgroundY1+=0.1;
        BackgroundY2+=0.1;
        timer++;

        //Set Obs LOOP
        if (Obs1Y>SCREEN_HEIGH)
        {
            Obs1Y=-25;
            Obs1X=getRandomNumber(borderLeft,borderRight);
            score++;
        }
        else
        {
            Obs1Y=Obs1Y+gameSpeed;
        }
        if (Obs2Y>SCREEN_HEIGH)
        {
            Obs2Y=-25;
            Obs2X=getRandomNumber(borderLeft,borderRight);
            score++;
        }
        else
        {
            Obs2Y=Obs2Y+gameSpeed;
        }
        if (Obs3Y>SCREEN_HEIGH)
        {
            Obs3Y=-25;
            Obs3X=getRandomNumber(borderLeft,borderRight);
            score++;
        }
        else
        {
            Obs3Y=Obs3Y+gameSpeed;
        }
        if (Obs4Y>SCREEN_HEIGH)
        {
            Obs4Y=-25;
            Obs4X=getRandomNumber(borderLeft,borderRight);
            score++;
        }
        else
        {
            Obs4Y=Obs4Y+gameSpeed;
        }
        CoinY=CoinY+gameSpeed;
        if ( CoinY > SCREEN_HEIGH )
        {
            CoinY = -3264;
            CoinX = getRandomNumber(borderLeft,borderRight);
        }


        //Game level
        string level = "Level " + to_string((score/50)+1) +" starts here";
        Text levelshower(level, myfont, 15);
        Text lifeshower( "Lives : " + to_string(lives), myfont, 15);
        levelshower.setPosition(300,200);
        lifeshower.setPosition(700, 0);
        lifeshower.setFillColor(Color::Cyan);
        if( score > 50 && score < 100)
        {
            gameSpeed = 0.4;
            if ( score < 55)
            {
                app.draw(levelshower);
            }
        }
        else if( score < 150 && score > 100)
        {
            gameSpeed = 0.5;
            if ( score < 105)
            {
                level = "Level 3 starts here";
            }
        }
        else if( score > 150 && score < 200)
        {
            gameSpeed = 0.6;
            if ( score < 155)
            {
                level = "Level 4 starts here";
            }
        }
        else if( score < 250 && score > 200)
        {
            gameSpeed = 0.7;
            if ( score < 205)
            {
                level = "Level 5 starts here";
            }
        }

        //Create event to handle input from keyboard
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if(RacerX>borderLeft)
                    {
                        RacerX=RacerX-20;
                    }
                }
                if (event.key.code == sf::Keyboard::Right)
                {
                    if(RacerX<borderRight)
                    {
                        RacerX=RacerX+20;
                    }
                }
                if (event.key.code == sf::Keyboard::Up)
                {
                    if(RacerY>0)
                    {
                        RacerY=RacerY-20;
                    }
                }
                if (event.key.code == sf::Keyboard::Down)
                {
                    if(RacerY<SCREEN_HEIGH-70)
                    {
                        RacerY=RacerY+20;
                    }
                }
                if ( event.key.code == sf::Keyboard::Escape )
                {
                    GameSound.pause();
                    pausedonce = 1;
                    int pchoice = 1;
                    //Background image for pause menu
                    Texture P_Background;
                    if ( !P_Background.loadFromFile("cars/download.jpg") )
                        return EXIT_FAILURE;
                    Sprite p_background(P_Background);

                    Font myfont2;
                    myfont2.loadFromFile("C:/Windows/Fonts/Jokerman.ttf");

                    string PMenu[4];
                    PMenu[0] = "Paused";
                    PMenu[1] = "Resume";
                    PMenu[2] = "Go Back To Main Menu";
                    PMenu[3] = "Exit";

                    Text pau(PMenu[0], myfont2, 30), res(PMenu[1], myfont2, 30), manu(PMenu[2], myfont2, 30), EX(PMenu[3], myfont2, 30 );

                    p_background.setPosition(0,0);
                    pau.setPosition(SCREEN_WIDTH/2-160, SCREEN_HEIGH/5*1);
                    res.setPosition(SCREEN_WIDTH/2-50, SCREEN_HEIGH/5*2);
                    manu.setPosition(SCREEN_WIDTH/2-50, SCREEN_HEIGH/5*3);
                    EX.setPosition(SCREEN_WIDTH/2-50, SCREEN_HEIGH/5*4);

                    pau.setFillColor(Color::Blue);
                    res.setFillColor(Color::Yellow);
                    manu.setFillColor(Color::Red);
                    EX.setFillColor(Color::Red);

                    pau.setOutlineThickness(5);
                    res.setOutlineThickness(5);
                    manu.setOutlineThickness(5);
                    EX.setOutlineThickness(5);

                    while ( app.isOpen() )
                    {
                        Event pauevent;
                        while ( app.pollEvent(pauevent) )
                        {
                            if ( pauevent.type == pauevent.Closed )
                                app.close();
                            if ( pchoice == 1 )
                            {
                                res.setFillColor(Color::Yellow);
                                manu.setFillColor(Color::Red);
                                EX.setFillColor(Color::Red);
                            }
                            if ( pchoice == 2 )
                            {
                                res.setFillColor(Color::Red);
                                manu.setFillColor(Color::Yellow);
                                EX.setFillColor(Color::Red);
                            }
                            if ( pchoice == 3 )
                            {
                                res.setFillColor(Color::Red);
                                manu.setFillColor(Color::Red);
                                EX.setFillColor(Color::Yellow);
                            }

                            if ( pauevent.type == pauevent.KeyPressed )
                            {
                                if ( pauevent.key.code == Keyboard::Up )
                                {
                                    pchoice--;
                                    if ( pchoice < 1 )
                                    {
                                        pchoice = 3;
                                    }
                                }
                                if ( pauevent.key.code == Keyboard::Down )
                                {
                                    pchoice++;
                                    if ( pchoice > 3 )
                                    {
                                        pchoice = 1;
                                    }
                                }
                                if ( pauevent.key.code == Keyboard::Escape )
                                    goto out;
                                if ( pauevent.key.code == Keyboard::Enter )
                                {
                                    if ( pchoice == 1 )
                                        goto out;
                                    if ( pchoice == 2 )
                                        goto there;
                                    if ( pchoice == 3 )
                                        app.close();
                                }
                            }
                        }
                        app.clear();
                        app.draw(p_background);
                        app.draw(pau);
                        app.draw(res);
                        app.draw(manu);
                        app.draw(EX);
                        app.display();
                    }
                }
            }
        }

        //Check if accident happen
        if ( ( ( RacerX >= ( Obs1X-30 ) ) && ( RacerX <= ( Obs1X+30 ) ) ) && ( ( RacerY+50 >= ( Obs1Y-30 ) )  && ( RacerY-50 ) <= ( Obs1Y+30 ) ) )
        {
            if (lives < 2 && clock.getElapsedTime().asSeconds() < 5)
            {
                ;
            }
            else if ( (lives == 2) || (lives < 2 && clock.getElapsedTime().asSeconds() > 5) )
             {
                lives--;
                RacerX = SCREEN_WIDTH/2;
                RacerY = SCREEN_HEIGH-racerHeight;
                Racer.setPosition(RacerX,RacerY);
                Time time1 = clock.restart();
             }
            cout << lives;
            if ( lives < 0 )
            {
                app.setFramerateLimit(10);
                GameSound.stop();
                app.clear();
                app.draw(Background);
                app.draw(Background1);
                app.draw(Obs2);
                app.draw(Obs3);
                app.draw(Obs4);
                app.draw(text);
                if ( ( (score > 50 && score < 60) || (score > 100 && score < 110) || (score > 150 && score < 160) || (score > 200 && score < 210) ) && timer % 400 < 201)
                {
                    app.draw(levelshower);
                }
                app.draw(Explosion);
                app.display();
                app.setFramerateLimit(60);
                if(gameOver() == 1)
                    goto here;
                else
                    goto there;
            }

                /*app.clear();
                app.draw(Background);
                app.draw(Background1);
                app.draw(Obs2);
                app.draw(Obs3);
                app.draw(Obs4);
                app.draw(text);
                if ( ( (score > 50 && score < 60) || (score > 100 && score < 110) || (score > 150 && score < 160) || (score > 200 && score < 210) ) && timer%400 < 201)
                {
                    app.draw(levelshower);
                }
                cout << "here";
                app.draw(Explosion);
                app.display();*/
                //app.setFramerateLimit
        }
        if (((RacerX>=(Obs2X-30)) &&(RacerX<=(Obs2X+30)))&&((RacerY>=(Obs2Y-30)) &&(RacerY-50)<=(Obs2Y+30))  )
        {
            if (lives < 2 && clock.getElapsedTime().asSeconds() < 5)
            {
                ;
            }
            else if ( (lives == 2) || (lives < 2 && clock.getElapsedTime().asSeconds() > 5) )
             {
                lives--;
                RacerX = SCREEN_WIDTH/2;
                RacerY = SCREEN_HEIGH-racerHeight;
                Racer.setPosition(RacerX,RacerY);
                Time time1 = clock.restart();
             }
            if ( lives < 0 )
            {
                app.setFramerateLimit(10);
                GameSound.stop();
                app.clear();
                app.draw(Background);
                app.draw(Background1);
                app.draw(Obs2);
                app.draw(Obs3);
                app.draw(Obs4);
                app.draw(text);
                if ( ( (score > 50 && score < 60) || (score > 100 && score < 110) || (score > 150 && score < 160) || (score > 200 && score < 210) ) && timer%400 < 201 )
                {
                    app.draw(levelshower);
                }
                app.draw(Explosion);
                app.display();
                app.setFramerateLimit(60);
                if(gameOver() == 1)
                    goto here;
                else
                    goto there;
            }
        };
        if (((RacerX>=(Obs3X-30)) &&(RacerX<=(Obs3X+30)))&&((RacerY-35>=(Obs3Y)) &&(RacerY-50)<=(Obs3Y+30))  )
        {
            if (lives < 2 && clock.getElapsedTime().asSeconds() < 5)
            {
                ;
            }
            else if ( (lives == 2) || (lives < 2 && clock.getElapsedTime().asSeconds() > 5) )
             {
                lives--;
                RacerX = SCREEN_WIDTH/2;
                RacerY = SCREEN_HEIGH-racerHeight;
                Racer.setPosition(RacerX,RacerY);
                Time time1 = clock.restart();
             }
            if ( lives < 0 )
            {
                app.setFramerateLimit(10);
                GameSound.stop();
                app.clear();
                app.draw(Background);
                app.draw(Background1);
                app.draw(Obs2);
                app.draw(Obs3);
                app.draw(Obs4);
                app.draw(text);
                if ( ( (score > 50 && score < 60) || (score > 100 && score < 110) || (score > 150 && score < 160) || (score > 200 && score < 210) ) && timer%400 < 201 )
                {
                    app.draw(levelshower);
                }
                app.draw(Explosion);
                app.display();
                app.setFramerateLimit(60);
                if(gameOver() == 1)
                    goto here;
                else
                    goto there;
            }
        };
        if (((RacerX>=(Obs4X-30)) &&(RacerX<=(Obs4X+30)))&&((RacerY>=(Obs4Y-30)) &&(RacerY-50)<=(Obs4Y+30)) )
        {
            if (lives < 2 && clock.getElapsedTime().asSeconds() < 5)
            {
                ;
            }
            else if ( (lives == 2) || (lives < 2 && clock.getElapsedTime().asSeconds() > 5) )
             {
                lives--;
                RacerX = SCREEN_WIDTH/2;
                RacerY = SCREEN_HEIGH-racerHeight;
                Racer.setPosition(RacerX,RacerY);
                Time time1 = clock.restart();
             }
            if ( lives < 0 )
            {
                app.setFramerateLimit(10);
                GameSound.stop();
                app.clear();
                app.draw(Background);
                app.draw(Background1);
                app.draw(Obs2);
                app.draw(Obs3);
                app.draw(Obs4);
                app.draw(text);
                if ( ( (score > 50 && score < 60) || (score > 100 && score < 110) || (score > 150 && score < 160) || (score > 200 && score < 210) ) && timer%400 < 201 )
                {
                    app.draw(levelshower);
                }
                app.draw(Explosion);
                app.display();
                app.setFramerateLimit(60);
                if(gameOver() == 1)
                    goto here;
                else
                    goto there;
            }
        };
        if (((RacerX>=(CoinX-35)) &&(RacerX<=(CoinX+65)))&&((RacerY>=(CoinY-95)) &&(RacerY-50)<=(CoinY+5)))
        {
            score += 5;
            CoinY=-1632;
            CoinX=getRandomNumber(borderLeft,borderRight);
            coin.setPosition(RacerX,RacerY);
        }
        //Clear and redraw position
        app.clear();
        app.draw(Background);
        app.draw(Background1);
        if ( lives <= 1 && clock.getElapsedTime().asSeconds() < 5 )
        {
            show = 1;
            if (( (clock.getElapsedTime().asSeconds() > 0) && (clock.getElapsedTime().asSeconds() < 0.5)) || ( (clock.getElapsedTime().asSeconds() > 1) && (clock.getElapsedTime().asSeconds() < 1.5) ) || ( (clock.getElapsedTime().asSeconds() > 2) && (clock.getElapsedTime().asSeconds() < 2.5)) || ( (clock.getElapsedTime().asSeconds() > 3) && (clock.getElapsedTime().asSeconds() < 3.5)) || ( (clock.getElapsedTime().asSeconds() > 4 ) && (clock.getElapsedTime().asSeconds() < 4.5)) )
                app.draw(Racer);
        }
        if ( show == 0 )
            app.draw(Racer);
        app.draw(Obs1);
        app.draw(Obs2);
        app.draw(Obs3);
        app.draw(Obs4);
        app.draw(text);
        app.draw(lifeshower);
        if ( ( (score > 50 && score < 60) || (score > 100 && score < 110) || (score > 150 && score < 160) || (score > 200 && score < 210) ) && timer%400 < 201 )
        {
            app.draw(levelshower);
        }
        app.draw(coin);
        app.display();
    }
    return EXIT_SUCCESS;
}
int startGame()
{
start :
    cout << 1;

    //menu music
    SoundBuffer menusoundbuffer;
    menusoundbuffer.loadFromFile("sound/Off Limits.wav");
    Sound MenuSound;
    MenuSound.setBuffer(menusoundbuffer);

    //Loading Background Image
    float yposition = SCREEN_HEIGH/6*2;
    Texture Background;
    if ( !Background.loadFromFile("cars/download.jpg") )
        return EXIT_FAILURE;
    Sprite background(Background);

    //Font for menu
    Font myfont;
    myfont.loadFromFile("C:/Windows/Fonts/Jokerman.ttf");

    //Text for Menu
    string menu[4], Game;
    Game = "Traffic Rush";
    menu[0] = "Play";
    menu[1] = "High Score";
    menu[2] = "Credits";
    menu[3] = " Exit";
    Text name ( Game, myfont, 60 ), game ( menu[0], myfont, 35 ), high ( menu[1], myfont, 35 ), cre ( menu[2], myfont, 35 ), exit ( menu[3], myfont, 35 ) ;

    //Text Design
    name.setOutlineThickness(2.5);
    game.setOutlineThickness(5);
    high.setOutlineThickness(5);
    cre.setOutlineThickness(5);
    exit.setOutlineThickness(5);
    name.setFillColor(sf::Color::Blue);
    game.setFillColor(sf::Color::Green);
    high.setFillColor(sf::Color::Red);
    cre.setFillColor(sf::Color::Red);
    exit.setFillColor(sf::Color::Red);


    //positions for options
    background.setPosition(0,0);
    name.setPosition(SCREEN_WIDTH/2-160, SCREEN_HEIGH/6*1);
    game.setPosition(SCREEN_WIDTH/2-50, SCREEN_HEIGH/6*2);
    high.setPosition(SCREEN_WIDTH/2-50, SCREEN_HEIGH/6*3);
    cre.setPosition(SCREEN_WIDTH/2-50, SCREEN_HEIGH/6*4);
    exit.setPosition(SCREEN_WIDTH/2-50, SCREEN_HEIGH/6*5);

    MenuSound.play();
    MenuSound.setLoop(true);


    while ( app.isOpen())
    {
        int highvisit = 0;
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if ( yposition == SCREEN_HEIGH/6*2 )
            {
                game.setStyle(Text::Italic);
                high.setStyle(Text::Regular);
                cre.setStyle(Text::Regular);
                exit.setStyle(Text::Regular);

                game.setFillColor(sf::Color::Green);
                high.setFillColor(sf::Color::Red);
                cre.setFillColor(sf::Color::Red);
                exit.setFillColor(sf::Color::Red);
            }
            else if ( yposition == SCREEN_HEIGH/6*3 )
            {
                game.setStyle(Text::Regular);
                high.setStyle(Text::Italic);
                cre.setStyle(Text::Regular);
                exit.setStyle(Text::Regular);

                game.setFillColor(sf::Color::Red);
                high.setFillColor(sf::Color::Green);
                cre.setFillColor(sf::Color::Red);
                exit.setFillColor(sf::Color::Red);
            }
            else if ( yposition == SCREEN_HEIGH/6*4 )
            {
                game.setStyle(Text::Regular);
                high.setStyle(Text::Regular);
                cre.setStyle(Text::Italic);
                exit.setStyle(Text::Regular);

                game.setFillColor(sf::Color::Red);
                high.setFillColor(sf::Color::Red);
                cre.setFillColor(sf::Color::Green);
                exit.setFillColor(sf::Color::Red);
            }
            else if ( yposition == SCREEN_HEIGH/6*5 )
            {
                game.setStyle(Text::Regular);
                high.setStyle(Text::Regular);
                cre.setStyle(Text::Regular);
                exit.setStyle(Text::Italic);


                game.setFillColor(sf::Color::Red);
                high.setFillColor(sf::Color::Red);
                cre.setFillColor(sf::Color::Red);
                exit.setFillColor(sf::Color::Green);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if ( event.key.code == sf::Keyboard::Enter )
                {
                    if ( yposition == SCREEN_HEIGH/6*2 )
                        return 0;
                    if ( yposition == SCREEN_HEIGH/6*3 )
                    {
                        string note = "High Score : " + to_string(HIGHSCORE);
                        Text highscore(note, myfont, 30), goback("Press Esc to go back to main menu", myfont, 30);
                        highscore.setPosition(SCREEN_WIDTH/2-160,SCREEN_HEIGH/2-160);
                        goback.setPosition(SCREEN_WIDTH/2-160,SCREEN_HEIGH/2);

                        //Text Style
                        highscore.setFillColor(Color::Magenta);
                        goback.setFillColor(Color::Blue);
                        highscore.setOutlineThickness(5);
                        goback.setOutlineThickness(5);

                        while (app.isOpen())
                        {
                            Event high_event;
                            while ( app.pollEvent(high_event) )
                            {
                                if ( high_event.type == high_event.Closed )
                                    app.close();
                                if ( high_event.type == high_event.KeyPressed)
                                {
                                    if ( high_event.key.code == sf::Keyboard::Escape )
                                        goto start;
                                }
                            }
                            app.clear();
                            app.draw(background);
                            app.draw(highscore);
                            app.draw(goback);
                            app.display();
                        }
                    }
                    if ( yposition == SCREEN_HEIGH/6*4 )
                    {
                        string Role1, Role2, Role3, Sir, Us[4], Internet;
                        Role1 = "Created under the guidance of";
                        Sir = "Quazi Ishtiaque Mahmud";
                        Role2 = "Developed By";
                        Us[0] = "Nafizur Rahman Sizan";
                        Us[1] = "Mohammed Mazhar Ali";
                        Us[2] = "aka";
                        Us[3] = "Team Genesis";
                        Role3 = "Source of sprites, images and music";
                        Internet = "Internet";
                        Text role1(Role1, myfont, 30), role2(Role2, myfont, 30), role3(Role3, myfont, 30), sir(Sir, myfont, 30), Nafiz(Us[0], myfont, 30), Shawon(Us[1], myfont, 30), faltu(Us[2], myfont, 30), Team(Us[3], myfont, 30), internet(Internet, myfont, 30);

                        role1.setFillColor(Color::Red);
                        role2.setFillColor(Color::Red);
                        role3.setFillColor(Color::Red);
                        sir.setFillColor(Color::Cyan);
                        Nafiz.setFillColor(Color::Cyan);
                        Shawon.setFillColor(Color::Cyan);
                        faltu.setFillColor(Color::Cyan);
                        Team.setFillColor(Color::Cyan);
                        internet.setFillColor(Color::Cyan);


                        role1.setPosition(SCREEN_WIDTH/2-220,SCREEN_HEIGH+30);
                        sir.setPosition(SCREEN_WIDTH/2-160,SCREEN_HEIGH+70);
                        role2.setPosition(SCREEN_WIDTH/2-100,SCREEN_HEIGH+170);
                        Nafiz.setPosition(SCREEN_WIDTH/2-160,SCREEN_HEIGH+210);
                        Shawon.setPosition(SCREEN_WIDTH/2-160,SCREEN_HEIGH+250);
                        faltu.setPosition(SCREEN_WIDTH/2-30,SCREEN_HEIGH+290);
                        Team.setPosition(SCREEN_WIDTH/2-80,SCREEN_HEIGH+330);
                        role3.setPosition(SCREEN_WIDTH/2-220,SCREEN_HEIGH+430);
                        internet.setPosition(SCREEN_WIDTH/2-40,SCREEN_HEIGH+470);

                        role1.setOutlineThickness(5);
                        sir.setOutlineThickness(5);
                        role2.setOutlineThickness(5);
                        Nafiz.setOutlineThickness(5);
                        Shawon.setOutlineThickness(5);
                        faltu.setOutlineThickness(5);
                        Team.setOutlineThickness(5);
                        role3.setOutlineThickness(5);
                        internet.setOutlineThickness(5);

                        while(app.isOpen())
                        {
                            app.setFramerateLimit(60);
                            Event Creditevent;
                            while( app.pollEvent(Creditevent) )
                            {
                                if ( Creditevent.type == Creditevent.Closed )
                                    app.close();
                                if ( Creditevent.type == Creditevent.KeyPressed && Creditevent.key.code == Keyboard::Escape )
                                    goto start;
                            }
                            role1.move(0, -1);
                            sir.move(0,-1);
                            role2.move(0, -1);
                            Nafiz.move(0, -1);
                            Shawon.move(0, -1);
                            faltu.move(0, -1);
                            Team.move(0, -1);
                            role3.move(0, -1);
                            internet.move(0, -1);

                            app.clear();
                            app.draw(background);
                            app.draw(role1);
                            app.draw(role2);
                            app.draw(role3);
                            app.draw(sir);
                            app.draw(Nafiz);
                            app.draw(Shawon);
                            app.draw(faltu);
                            app.draw(Team);
                            app.draw(internet);
                            app.display();
                        }


                    }
                    if ( yposition == SCREEN_HEIGH/6*5 )
                    {
                        app.close();
                    }
                }
                if ( event.key.code == sf::Keyboard::Up )
                {
                    yposition -= SCREEN_HEIGH/6;
                    if ( yposition < SCREEN_HEIGH / 6*2 )
                    {
                        yposition = SCREEN_HEIGH/6*5;
                    }
                }
                if ( event.key.code == sf::Keyboard::Down )
                {
                    yposition += SCREEN_HEIGH/6;
                    if ( yposition > SCREEN_HEIGH / 6*5 )
                    {
                        yposition = SCREEN_HEIGH/6*2;
                    }
                }
            }
        }
        app.clear();
        app.draw(background);
        app.draw(name);
        app.draw(game);
        app.draw(high);
        app.draw(cre);
        app.draw(exit);
        app.display();
    }
}
//Game over
int gameOver()
{
    std::ofstream writefile ("Highscore.txt");
    if ( writefile.is_open() )
    {
        if ( score > HIGHSCORE )
            HIGHSCORE = score;
        writefile << HIGHSCORE;
    }
    writefile.close();

    Texture gameover,troll, hightroll;
    if (!gameover.loadFromFile("cars/over.png"))
        return EXIT_FAILURE;
    if(!troll.loadFromFile("cars/troll.png"))
        return EXIT_FAILURE;
    if(!hightroll.loadFromFile("cars/troll2.png"))
        return EXIT_FAILURE;

    Sprite Gameover(gameover);
    Sprite Troll(troll);
    Sprite HighTroll(hightroll);
    Troll.setPosition(10,350);
    HighTroll.setPosition(10,350);
    SoundBuffer gameOver;
    gameOver.loadFromFile("sound/crash.wav");
    Sound GameOver;
    GameOver.setBuffer(gameOver);
    GameOver.play();

    Font myfont;
    myfont.loadFromFile("font/xirod.ttf");
    stringscore="YOUR SCORE:"+to_string(score);
    Text hiscore("New HighScore !!", myfont, 30);
    Text text(stringscore, myfont, 30);
    text.setPosition(210,400);
    hiscore.setPosition(210,100);
    string re = "Do you Want to Try Again?";
    string menu = "1. YES";
    string menu2 = "2. NO";
    Text returner( re, myfont, 30 );
    Text MENU( menu, myfont, 30), MENU2( menu2, myfont, 30);
    returner.setPosition(SCREEN_WIDTH/2-330,540);
    MENU.setPosition(SCREEN_WIDTH/2-260,570);
    MENU2.setPosition(SCREEN_WIDTH/2+130,570);

    //choice option color
    MENU.setFillColor(Color::Red);
    MENU2.setFillColor(Color::White);
    int choice = 1;

    while (app.isOpen())
    {
        Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed)
                app.close();
            if ( choice == 1 )
            {
                MENU.setFillColor(Color::Red);
                MENU2.setFillColor(Color::White);
            }
            if ( choice == 2 )
            {
                MENU.setFillColor(Color::White);
                MENU2.setFillColor(Color::Red);
            }
            if(event.type == Event::KeyPressed)
            {
                if ( event.key.code == Keyboard::Left )
                {
                    choice--;
                    if( choice < 1 )
                    {
                        choice = 2;
                    }
                }
                if ( event.key.code == Keyboard::Right )
                {
                    choice++;
                    if( choice > 2 )
                    {
                        choice = 1;
                    }
                }
                if ( event.key.code == Keyboard::Enter )
                {
                    if ( choice == 1 )
                        return 1;
                    else
                        return 2;
                }
            }
        }
        if ( score < HIGHSCORE )
        {
            app.clear();
            app.draw(Gameover);
            app.draw(text);
            app.draw(Troll);
            app.draw(returner);
            app.draw(MENU);
            app.draw(MENU2);
            app.display();
        }
        else
        {
            app.clear();
            app.draw(Gameover);
            app.draw(hiscore);
            app.draw(text);
            app.draw(HighTroll);
            app.draw(returner);
            app.draw(MENU);
            app.draw(MENU2);
            app.display();
        }
    }
    return 0;
}
int getRandomNumber(int a, int b)
{
    static bool first = true;
    if (first)
    {
        srand( time(NULL) );
        first = false;
    }
    int result = a + rand() % (( b + 1 ) - a);
    result=(result/10)*10;
    return result;
}
