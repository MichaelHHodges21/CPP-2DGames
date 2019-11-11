#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <ctime>

using namespace sf;

bool playing = false;
bool options = false;
bool touchingGround;
bool touchingGround2;
bool bulletShot1 = false;
bool bulletShot2 = false;
bool startUp = true;
bool falling = false;
bool DamFalling = false;
bool showHPUp = false;
bool showDamageUp = false;
bool bonus;
int bullet1Dir;
int bullet2Dir;
int jumpFrameCounter;
int jumpFrameCounter2;
int tillHeal;
int tillDam;
int P1Dam = 1;
int P2Dam = 1;
float player1HP = 100;
float player2HP = 100;

int main()
{
    RenderWindow window(VideoMode(500, 500), "...");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    RectangleShape player(Vector2f(20.0f, 20.0f));
    player.setPosition(150.0f, 250.0f);
    player.setFillColor(Color::Red);

    RectangleShape player2(Vector2f(20.0f, 20.0f));
    player2.setPosition(350.0f, 250.0f);
    player2.setFillColor(Color::Blue);

    RectangleShape object1(Vector2f(400.0f, 50.0f));
    object1.setPosition(Vector2f(50.0f, 450.0f));

    RectangleShape object2(Vector2f(100.0f, 20.0f));
    object2.setPosition(Vector2f(100.0f, 350.0f));

    RectangleShape object3(Vector2f(100.0f, 20.0f));
    object3.setPosition(Vector2f(300.0f, 350.0f));

    RectangleShape bullet1(Vector2f(10.0f, 5.0f));
    RectangleShape bullet2(Vector2f(10.0f, 5.0f));

    RectangleShape P1HP(Vector2f(player1HP, 10.0f));
    P1HP.setPosition(Vector2f(20.0f, 20.0f));
    P1HP.setFillColor(Color::Red);

    RectangleShape P2HP(Vector2f(player2HP, 10.0f));
    P2HP.setPosition(Vector2f(320.0f, 20.0f));
    P2HP.setFillColor(Color::Blue);

    RectangleShape playButton(Vector2f(250.0f, 100.0f));
    playButton.setPosition(Vector2f(250.0f, 250.0f));
    playButton.setOrigin(Vector2f(125.0f, 50.0f));

    RectangleShape exitButton(Vector2f(250.0f, 100.0f));
    exitButton.setPosition(Vector2f(250.0f, 400.0f));
    exitButton.setOrigin(Vector2f(125.0f, 50.0f));

    Texture titleTexture, mouseTexture, classicTexture, newTexture, HealTexture, DamageTexture;
    titleTexture.loadFromFile("Images/Title.png");
    mouseTexture.loadFromFile("Images/mouse.png");
    classicTexture.loadFromFile("Images/Classic.png");
    newTexture.loadFromFile("Images/NewStyle.png");
    HealTexture.loadFromFile("Images/Health.png");
    DamageTexture.loadFromFile("Images/Damage.png");

    Sprite title(titleTexture);
    title.setScale(Vector2f(10.0f, 10.0f));
    title.setPosition(Vector2f(70.0f, 20.0f));

    Sprite mousePointer(mouseTexture);
    mousePointer.setScale(Vector2f(1.5f, 1.5f));

    Sprite classic(classicTexture);
    classic.setScale(Vector2f(0.3f, 0.3f));
    classic.setPosition(Vector2f(50.0f, 200.0f));

    Sprite newStyle(newTexture);
    newStyle.setScale(Vector2f(0.3f, 0.3f));
    newStyle.setPosition(Vector2f(300.0f, 200.0f));

    Sprite HPUp(HealTexture);
    HPUp.setScale(Vector2f(1.5f, 1.5f));

    Sprite DamageUp(DamageTexture);
    DamageUp.setScale(Vector2f(1.5f, 1.5f));

    Music menuMusic;
    menuMusic.openFromFile("Audio/MenuMusic.wav");
    menuMusic.play();
    menuMusic.setLoop(true);

    Music gameMusic;
    gameMusic.openFromFile("Audio/GameMusic.wav");

    Font font;
    font.loadFromFile("Fonts/font.ttf");

    Text optionsText;
    optionsText.setFont(font);
    optionsText.setCharacterSize(80);
    optionsText.setColor(Color::White);
    optionsText.setPosition(Vector2f(50.0f, 20.0f));
    optionsText.setString("Chose a level:");

    Text WinText;
    WinText.setFont(font);
    WinText.setCharacterSize(55);
    WinText.setColor(Color::White);
    WinText.setPosition(Vector2f(50.0f, 190.0f));

    Text playText;
    playText.setFont(font);
    playText.setCharacterSize(30);
    playText.setColor(Color::Black);
    playText.setPosition(Vector2f(220.0f, 230.0f));
    playText.setString("Play");

    Text exitText;
    exitText.setFont(font);
    exitText.setCharacterSize(30);
    exitText.setColor(Color::Black);
    exitText.setPosition(Vector2f(220.0f, 380.0f));
    exitText.setString("Exit");

    Text creditsText;
    creditsText.setFont(font);
    creditsText.setCharacterSize(11);
    creditsText.setColor(Color::White);
    creditsText.setPosition(Vector2f(160.0f, 470.0f));
    creditsText.setString("A game made by Michael Hamer-Hodges");

    Clock clock;

    while (window.isOpen())
    {
        float timeTaken = clock.getElapsedTime().asMilliseconds();
        clock.restart();

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        ////UPDATE////
        srand(time(0));

        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;

        if(playing == false){
            mousePointer.setPosition(mouseX, mouseY);
            if(mousePointer.getGlobalBounds().intersects(playButton.getGlobalBounds())){
                playButton.setScale(Vector2f(0.9f, 0.9f));
            }else{
                playButton.setScale(Vector2f(1.0f, 1.0f));
            }
            if(mousePointer.getGlobalBounds().intersects(exitButton.getGlobalBounds())){
                exitButton.setScale(Vector2f(0.9f, 0.9f));
            }else{
                exitButton.setScale(Vector2f(1.0f, 1.0f));
            }

            if(mousePointer.getGlobalBounds().intersects(creditsText.getGlobalBounds()) && Mouse::isButtonPressed(Mouse::Left)){
                creditsText.setColor(Color::Yellow);
                bonus = true;
            }

            if(Mouse::isButtonPressed(Mouse::Left) && mousePointer.getGlobalBounds().intersects(playButton.getGlobalBounds()) && options == false){
                options = true;
                Sleep(200);
            }
            if(Mouse::isButtonPressed(Mouse::Left) && mousePointer.getGlobalBounds().intersects(exitButton.getGlobalBounds())){
                window.close();
            }

        }

        if(options == true){
            if(mousePointer.getGlobalBounds().intersects(classic.getGlobalBounds())){
                classic.setScale(Vector2f(0.35f, 0.35f));
            }else{
                classic.setScale(Vector2f(0.3f, 0.3f));
            }

            if(Mouse::isButtonPressed(Mouse::Left) && mousePointer.getGlobalBounds().intersects(classic.getGlobalBounds())){
                object1.setPosition(Vector2f(50.0f, 450.0f));
                object1.setSize(Vector2f(400.0f, 50.0f));
                object2.setPosition(Vector2f(100.0f, 350.0f));
                object2.setSize(Vector2f(100.0f, 20.0f));
                object3.setPosition(Vector2f(300.0f, 350.0f));
                object3.setSize(Vector2f(100.0f, 20.0f));
                playing = true;
                options = false;
            }

            if(mousePointer.getGlobalBounds().intersects(newStyle.getGlobalBounds())){
                newStyle.setScale(Vector2f(0.35f, 0.35f));
            }else{
                newStyle.setScale(Vector2f(0.3f, 0.3f));
            }

            if(Mouse::isButtonPressed(Mouse::Left) && mousePointer.getGlobalBounds().intersects(newStyle.getGlobalBounds())){
                object1.setPosition(Vector2f(100.0f, 450.0f));
                object1.setSize(Vector2f(100.0f, 20.0f));
                object2.setPosition(Vector2f(200.0f, 350.0f));
                object3.setPosition(Vector2f(300.0f, 450.0f));
                playing = true;
                options = false;
            }
        }

        if(playing == true){
            if(startUp == true){
                player1HP = 100;
                player2HP = 100;
                if(bonus == true){
                    player1HP = 1;
                    player2HP = 1;
                    creditsText.setColor(Color::White);
                }
                P1Dam = 1;
                P2Dam = 1;
                tillHeal = 500+(rand()%1500);
                tillDam = 1000+(rand()%2000);
                player.setPosition(150.0f, 250.0f);
                player2.setPosition(350.0f, 250.0f);
                menuMusic.stop();
                gameMusic.play();
                gameMusic.setLoop(true);
                bulletShot1 = false;
                bulletShot2 = false;
                falling = false;
                DamFalling = false;
                showHPUp = false;
                showDamageUp = false;
                startUp = false;
            }

            if(Keyboard::isKeyPressed(Keyboard::L)){
                tillHeal = 1;
                tillDam = 1;
            }

            if(tillHeal > 0){
                tillHeal--;
            }
            if(tillHeal <= 0){
                float SpawnForHp = 10+(rand()%480);
                HPUp.setPosition(SpawnForHp, 0);
                tillHeal = 500+(rand()%1500);
                falling = true;
                showHPUp = true;
            }

            if(falling == true){
                HPUp.move(Vector2f(0.0f, 0.2f * timeTaken));
                if(HPUp.getGlobalBounds().intersects(object1.getGlobalBounds()) || HPUp.getGlobalBounds().intersects(object2.getGlobalBounds()) || HPUp.getGlobalBounds().intersects(object3.getGlobalBounds())){
                    falling = false;
                }
            }

            if(showHPUp == true){
                if(player.getGlobalBounds().intersects(HPUp.getGlobalBounds())){
                    player1HP += 20;
                    showHPUp = false;
                }
                if(player2.getGlobalBounds().intersects(HPUp.getGlobalBounds())){
                    player2HP += 20;
                    showHPUp = false;
                }
            }

            if(tillDam > 0){
                tillDam--;
            }
            if(tillDam <= 0){
                float SpawnForDam = 10+(rand()%480);
                DamageUp.setPosition(SpawnForDam, 0);
                tillDam = 1000+(rand()%2000);
                DamFalling = true;
                showDamageUp = true;
            }
            if(DamFalling == true){
                DamageUp.move(Vector2f(0.0f, 0.2f * timeTaken));
                if(DamageUp.getGlobalBounds().intersects(object1.getGlobalBounds()) || DamageUp.getGlobalBounds().intersects(object2.getGlobalBounds()) || DamageUp.getGlobalBounds().intersects(object3.getGlobalBounds())){
                    DamFalling = false;
                }
            }

            if(showDamageUp == true){
                if(player.getGlobalBounds().intersects(DamageUp.getGlobalBounds())){
                    P1Dam++;
                    showDamageUp = false;
                }
                if(player2.getGlobalBounds().intersects(DamageUp.getGlobalBounds())){
                    P2Dam++;
                    showDamageUp = false;
                }
            }

            float playerX = player.getPosition().x;
            float playerY = player.getPosition().y;

            if(Keyboard::isKeyPressed(Keyboard::Up) && touchingGround == true){
                jumpFrameCounter = 30;
            }
            if(Keyboard::isKeyPressed(Keyboard::Left) && playerX >= 10){
                player.move(Vector2f(-0.3f * timeTaken, 0.0f));
                if(bulletShot1 == false){
                    bullet1Dir = 0;
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::Right) && playerX <= 470){
                player.move(Vector2f(0.3f * timeTaken, 0.0f));
                if(bulletShot1 == false){
                    bullet1Dir = 1;
                }
            }

            if(Keyboard::isKeyPressed(Keyboard::Space) && bulletShot1 == false){
                bulletShot1 = true;
                bullet1.setPosition(playerX, playerY + 10);
            }
            if(bulletShot1 == true){
                if(bullet1Dir == 0){
                    if(bullet1.getPosition().x < 0 || bullet1.getGlobalBounds().intersects(player2.getGlobalBounds())){
                        bulletShot1 = false;
                    }
                    bullet1.move(Vector2f(-0.7f * timeTaken, 0.0f));
                }
                if(bullet1Dir == 1){
                    if(bullet1.getPosition().x > 500 || bullet1.getGlobalBounds().intersects(player2.getGlobalBounds())){
                        bulletShot1 = false;
                    }
                    bullet1.move(Vector2f(0.7f * timeTaken, 0.0f));
                }

                if(bullet1.getGlobalBounds().intersects(player2.getGlobalBounds())){
                    player2HP -= P1Dam;
                }
            }

            if(jumpFrameCounter > 0){
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                player.move(Vector2f(0.0f, -0.045f * timeTaken));
                jumpFrameCounter -= 2;
            }

            if(player.getGlobalBounds().intersects(object1.getGlobalBounds()) || player.getGlobalBounds().intersects(object2.getGlobalBounds())  && jumpFrameCounter <= 0 || player.getGlobalBounds().intersects(object3.getGlobalBounds()) && jumpFrameCounter <= 0){
                touchingGround = true;
            }else{
                touchingGround = false;
            }

            if(touchingGround == false && jumpFrameCounter <= 0){
                player.move(Vector2f(0.0f, 0.1f * timeTaken));
                if(player.getGlobalBounds().intersects(object1.getGlobalBounds()) || player.getGlobalBounds().intersects(object2.getGlobalBounds())  && jumpFrameCounter <= 0 || player.getGlobalBounds().intersects(object3.getGlobalBounds()) && jumpFrameCounter <= 0){
                    touchingGround = true;
                }
                if(touchingGround == false && jumpFrameCounter <= 0){
                    player.move(Vector2f(0.0f, 0.1f * timeTaken));
                    if(player.getGlobalBounds().intersects(object1.getGlobalBounds()) || player.getGlobalBounds().intersects(object2.getGlobalBounds())  && jumpFrameCounter <= 0 || player.getGlobalBounds().intersects(object3.getGlobalBounds()) && jumpFrameCounter <= 0){
                        touchingGround = true;
                    }
                    if(touchingGround == false && jumpFrameCounter <= 0){
                        player.move(Vector2f(0.0f, 0.1f * timeTaken));
                        if(player.getGlobalBounds().intersects(object1.getGlobalBounds()) || player.getGlobalBounds().intersects(object2.getGlobalBounds())  && jumpFrameCounter <= 0 || player.getGlobalBounds().intersects(object3.getGlobalBounds()) && jumpFrameCounter <= 0){
                            touchingGround = true;
                        }
                        if(touchingGround == false && jumpFrameCounter <= 0){
                            player.move(Vector2f(0.0f, 0.1f * timeTaken));
                        }
                    }
                }
            }

            if(playerY > 460){
                player.setPosition(Vector2f(250.0f, 250.0f));
                player1HP -= 20;
            }


            float player2X = player2.getPosition().x;
            float player2Y = player2.getPosition().y;

            if(Keyboard::isKeyPressed(Keyboard::W) && touchingGround2 == true){
                jumpFrameCounter2 = 30;
            }
            if(Keyboard::isKeyPressed(Keyboard::A) && player2X >= 10){
                player2.move(Vector2f(-0.3f * timeTaken, 0.0f));
                if(bulletShot2 == false){
                    bullet2Dir = 0;
                }
            }
            if(Keyboard::isKeyPressed(Keyboard::D) && player2X <= 470){
                player2.move(Vector2f(0.3f * timeTaken, 0.0f));
                if(bulletShot2 == false){
                    bullet2Dir = 1;
                }
            }

            if(Keyboard::isKeyPressed(Keyboard::Q) && bulletShot2 == false){
                bulletShot2 = true;
                bullet2.setPosition(player2X, player2Y + 10);
            }
            if(bulletShot2 == true){
                if(bullet2Dir == 0){
                    if(bullet2.getPosition().x < 0 || bullet2.getGlobalBounds().intersects(player.getGlobalBounds())){
                        bulletShot2 = false;
                    }
                    bullet2.move(Vector2f(-0.7f * timeTaken, 0.0f));
                }
                if(bullet2Dir == 1){
                    if(bullet2.getPosition().x > 500 || bullet2.getGlobalBounds().intersects(player.getGlobalBounds())){
                        bulletShot2 = false;
                    }
                    bullet2.move(Vector2f(0.7f * timeTaken, 0.0f));
                }

                if(bullet2.getGlobalBounds().intersects(player.getGlobalBounds())){
                    player1HP -= P2Dam;
                }
            }

            if(jumpFrameCounter2 > 0){
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                player2.move(Vector2f(0.0f, -0.045f * timeTaken));
                jumpFrameCounter2 -= 2;
            }

            if(player2.getGlobalBounds().intersects(object1.getGlobalBounds()) || player2.getGlobalBounds().intersects(object2.getGlobalBounds())  && jumpFrameCounter2 <= 0 || player2.getGlobalBounds().intersects(object3.getGlobalBounds()) && jumpFrameCounter2 <= 0){
                touchingGround2 = true;
            }else{
                touchingGround2 = false;
            }

            if(touchingGround2 == false && jumpFrameCounter2 <= 0){
                player2.move(Vector2f(0.0f, 0.1f * timeTaken));
                if(player2.getGlobalBounds().intersects(object1.getGlobalBounds()) || player2.getGlobalBounds().intersects(object2.getGlobalBounds())  && jumpFrameCounter2 <= 0 || player2.getGlobalBounds().intersects(object3.getGlobalBounds()) && jumpFrameCounter2 <= 0){
                    touchingGround2 = true;
                }
                if(touchingGround2 == false && jumpFrameCounter2 <= 0){
                    player2.move(Vector2f(0.0f, 0.1f * timeTaken));
                    if(player2.getGlobalBounds().intersects(object1.getGlobalBounds()) || player2.getGlobalBounds().intersects(object2.getGlobalBounds())  && jumpFrameCounter2 <= 0 || player2.getGlobalBounds().intersects(object3.getGlobalBounds()) && jumpFrameCounter2 <= 0){
                        touchingGround2 = true;
                    }
                    if(touchingGround2 == false && jumpFrameCounter2 <= 0){
                        player2.move(Vector2f(0.0f, 0.1f * timeTaken));
                        if(player2.getGlobalBounds().intersects(object1.getGlobalBounds()) || player2.getGlobalBounds().intersects(object2.getGlobalBounds())  && jumpFrameCounter2 <= 0 || player2.getGlobalBounds().intersects(object3.getGlobalBounds()) && jumpFrameCounter2 <= 0){
                            touchingGround2 = true;
                        }
                        if(touchingGround2 == false && jumpFrameCounter2 <= 0){
                            player2.move(Vector2f(0.0f, 0.1f * timeTaken));
                        }
                    }
                }
            }

            if(player2Y > 460){
                player2.setPosition(Vector2f(250.0f, 250.0f));
                player2HP -= 20;
            }


            if(player1HP <= 0 && player2HP <= 0 && playing == true){
                window.clear();
                WinText.setString("The winner is: ERROR\nWAIT WHAT!!!\nIT'S A TIE!?");
                window.draw(WinText);
                window.display();
                Sleep(3000);
                playing = false;
                startUp = true;
                bonus = false;
                gameMusic.stop();
                menuMusic.play();
                menuMusic.setLoop(true);
            }

            if(player1HP <= 0 && playing == true){
                window.clear();
                WinText.setString("The winner is: P2!");
                window.draw(WinText);
                window.display();
                Sleep(3000);
                playing = false;
                startUp = true;
                bonus = false;
                gameMusic.stop();
                menuMusic.play();
                menuMusic.setLoop(true);
            }
            if(player2HP <= 0 && playing == true){
                window.clear();
                WinText.setString("The winner is: P1!");
                window.draw(WinText);
                window.display();
                Sleep(3000);
                playing = false;
                startUp = true;
                bonus = false;
                gameMusic.stop();
                menuMusic.play();
                menuMusic.setLoop(true);
            }

            P1HP.setSize(Vector2f(player1HP, 10.0f));
            P2HP.setSize(Vector2f(player2HP, 10.0f));
        }

        ////DRAW/////
        window.clear();
        if(playing == true){
            window.draw(object1);
            window.draw(object2);
            window.draw(object3);
            window.draw(player);
            window.draw(player2);
            window.draw(P1HP);
            window.draw(P2HP);
            if(showHPUp == true){
                window.draw(HPUp);
            }
            if(showDamageUp == true){
                window.draw(DamageUp);
            }
            if(bulletShot1 == true){
                window.draw(bullet1);
            }
            if(bulletShot2 == true){
                window.draw(bullet2);
            }
        }
        if(playing == false && options == false){
            window.draw(title);
            window.draw(playButton);
            window.draw(exitButton);
            window.draw(playText);
            window.draw(exitText);
            window.draw(creditsText);
        }
        if(options == true){
            window.draw(classic);
            window.draw(newStyle);
            window.draw(optionsText);
        }
        if(playing == false){
            window.draw(mousePointer);
        }
        window.display();
    }

    return 0;
}
