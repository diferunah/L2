#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <windows.h>
#include <list>

using namespace std;
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80

void gotoxy(int x, int y)
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x; // Starts from 0
    dwPos.Y = y; // Starts from 0
    SetConsoleCursorPosition(hCon, dwPos);
}

void HideCursor()
{
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hCon, &cci);
}

void DrawWhiteSpace(int a_x, int a_y, int b_x, int b_y)
{
    for (int i = a_x; i < b_x; i++)
    {
        for (int j = a_y; j < b_y; j++)
        {
            gotoxy(i, j);
            printf(" ");
        }
    }
}

void DrawWindowFrame(int a_x, int a_y, int b_x, int b_y)
{
    DrawWhiteSpace(a_x, a_y, b_x, b_y);
    for (int i = a_x; i < b_x; i++)
    {
        gotoxy(i, a_y);
        printf("%c", 205);
        gotoxy(i, b_y);
        printf("%c", 205);
    }
    for (int i = a_y; i < b_y; i++)
    {
        gotoxy(a_x, i);
        printf("%c", 186);
        gotoxy(b_x, i);
        printf("%c", 186);
    }
    gotoxy(a_x, a_y);
    printf("%c", 201);
    gotoxy(b_x, a_y);
    printf("%c", 187);
    gotoxy(a_x, b_y);
    printf("%c", 200);
    gotoxy(b_x, b_y);
    printf("%c", 188);
}
void DrawGameLimits()
{                                  
    DrawWindowFrame(1, 2, 79, 23);
    gotoxy(2, 1);
    printf("HP:");
    gotoxy(16, 1);
    printf("ENERGY:");
    gotoxy(50, 1);
    printf("SCORE:");
}
void WelcomeMessage()
{
    int x = 13;
    int y = 6;
    gotoxy(x, y);
    printf(" _____                    _____ _           _           ");
    gotoxy(x, y + 1);
    printf("|   __|___ ___ ___ ___   |   __| |_ ___ ___| |_ ___ ___ ");
    gotoxy(x, y + 2);
    printf("|__   | . | .'|  _| -_|  |__   |   | . | . |  _| -_|  _|");
    gotoxy(x, y + 3);
    printf("|_____|  _|__,|___|___|  |_____|_|_|___|___|_| |___|_|  ");
    gotoxy(x, y + 4);
    printf("      |_|");
    gotoxy(x, y + 6);
    printf("                 Presione cualquier tecla para empezar");
}

void GameOverDefeatMessage()
{
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x, a_y, b_x, b_y);
    gotoxy(a_x + 1, a_y + 2);
    printf("      PERDISTE!!!");
}

void GameOverVictoryMessage()
{
    int a_x = 30;
    int a_y = 11;
    int b_x = a_x + 23;
    int b_y = a_y + 4;
    DrawWindowFrame(a_x, a_y, b_x, b_y);
    gotoxy(a_x + 1, a_y + 2);
    printf("      VICTORIA!!!");
}

void SpecialMessage()
{
    DrawWhiteSpace(1, 1, 80, 24);
    gotoxy(30, 11);
    printf("Gracias por jugar! :3");
}

class SpaceShip
{
private:
    int x;      
    int y;      
    int hp;     
    int energy;  // energia points
    bool imDead;

public:
    int X() { return x; }
    int Y() { return y; }
    int HP() { return hp; }

    bool isDead()
    {
        DrawSpaceShipInfo();
        return imDead;
    }

    SpaceShip(int _x, int _y)
    {
        x = _x;
        y = _y;
        hp = 3;         
        energy = 5;     
        imDead = false; 
    }

    void DrawSpaceShipInfo()
    {
        gotoxy(5, 1);
        printf("     ");
        for (int i = 0; i < hp; i++)
        {
            gotoxy(5 + i, 1);
            printf("%c", 3);
        }
        gotoxy(23, 1);
        printf("     ");
        for (int i = 0; i < energy; i++)
        {
            gotoxy(23 + i, 1);
            printf("%c", 222);
        }
    }

    void Draw()
    {
        gotoxy(x, y);
        printf("  %c  ", 30);
        gotoxy(x, y + 1);
        printf("  %c  ", 4);
        gotoxy(x, y + 2);
        printf("%c%c%c%c%c", 17, 30, 223, 30, 16);
    }

    void Erase()
    {
        gotoxy(x, y);
        printf("     ");
        gotoxy(x, y + 1);
        printf("     ");
        gotoxy(x, y + 2);
        printf("     ");
    }

    void Damage()
    {
        energy--;
        if (energy == 0)
        {
            Explosion();
        }
        else
        {
            Erase();
            gotoxy(x, y);
            printf("  *  ");
            gotoxy(x, y + 1);
            printf("  *  ");
            gotoxy(x, y + 2);
            printf("*****");
            Sleep(100);
        }
    }

    void Explosion()
    {
        hp--;
        Erase();
        gotoxy(x, y);
        printf("  *  ");
        gotoxy(x, y + 1);
        printf("  *  ");
        gotoxy(x, y + 2);
        printf("*****");
        Sleep(100);
        Erase();
        gotoxy(x, y);
        printf(" * * ");
        gotoxy(x, y + 1);
        printf("* * *");
        gotoxy(x, y + 2);
        printf(" * * ");
        Sleep(100);
        Erase();
        gotoxy(x, y);
        printf("*   *");
        gotoxy(x, y + 1);
        printf(" * * ");
        gotoxy(x, y + 2);
        printf("* * *");
        Sleep(100);
        if (hp > 0)
        {
            energy = 5;
        }
        else
        {
            imDead = true;
        }
    }

    void Move()
    {
        if (kbhit())
        {                    
            Erase();        
            char key = getch();
            switch (key)
            {
            case LEFT:
                if (x > 2)
                    x -= 1;
                break;
            case RIGHT:
                if (x + 4 < 77)
                    x += 1;
                break;
            case UP:
                if (y > 3)
                    y -= 1;
                break;
            case DOWN:
                if (y + 2 < 22)
                    y += 1;
                break;
            }
        }
        Draw();
    }
};

class Asteroid
{
private:
    int x;
    int y;

public:
    int X() { return x; }
    int Y() { return y; }

    Asteroid(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    void Draw()
    {
        gotoxy(x, y);
        printf("*");
    }
    void Collision(SpaceShip &ss)
    {
        if (((x >= ss.X()) && (x <= ss.X() + 5)) && ((y >= ss.Y()) && (y <= ss.Y() + 2)))
        {                
            ss.Damage(); 
            gotoxy(x, y);
            printf(" ");         
            x = rand() % 74 + 3;
            y = 4;
        }
        else
        {
            gotoxy(x, y);
            printf(" ");
            y++;
            if (y > 22)
            {                       
                x = rand() % 74 + 3;
                y = 4;
            }
            Draw();
        }
    }
};

class Bullet
{
private:
    int x;
    int y;

public:
    int X() { return x; }
    int Y() { return y; }
    Bullet(int _x, int _y)
    {
        x = _x;
        y = _y;
    }
    bool isOut()
    {
        if (y <= 3)
        {
            gotoxy(x, y);
            printf(" ");
            return true;
        }
        else
        {
            return false;
        }
    }

    void Move()
    {
        gotoxy(x, y);
        printf(" ");
        y--;
        gotoxy(x, y);
        printf(".");
    }
};

int starShip()
{
    HideCursor();
    WelcomeMessage();
    getch();
    DrawGameLimits();

    list<Bullet *> Bullets;         
    list<Bullet *>::iterator bullet;

    list<Asteroid *> Asteroids; 
    list<Asteroid *>::iterator asteroid;

    for (int i = 0; i < 10; i++) 
    {                           
        Asteroids.push_back(new Asteroid(rand() % 78 + 1, rand() % 4 + 3));
    }

    SpaceShip ss = SpaceShip(40, 20); 
    int score = 0;                   

    while (!ss.isDead() && score != 100)
    {
        if (kbhit())
        {
            char key = getch();
            if (key == ' ')
            { 
                Bullets.push_back(new Bullet(ss.X() + 2, ss.Y() - 1));
            }
        }
        for (bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
        { 
            (*bullet)->Move();
            if ((*bullet)->isOut())
            {                     
                delete (*bullet);
                bullet = Bullets.erase(bullet);
            }
        }
        for (asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
        { 
            (*asteroid)->Collision(ss);
        }
        for (asteroid = Asteroids.begin(); asteroid != Asteroids.end(); asteroid++)
        {
            for (bullet = Bullets.begin(); bullet != Bullets.end(); bullet++)
            {                                
                int astX = (*asteroid)->X(); 
                int astY = (*asteroid)->Y();
                int bulX = (*bullet)->X(); 
                int bulY = (*bullet)->Y();
                if ((astX == bulX) && ((astY == bulY) || (astY + 1 == bulY)))
                { 
                    gotoxy(bulX, bulY);
                    printf(" "); 
                    gotoxy(astX, astY);
                    printf("X");
                    printf(" ");      
                    delete (*bullet); 
                    bullet = Bullets.erase(bullet);
                    delete (*asteroid); 
                    asteroid = Asteroids.erase(asteroid);
                    Asteroids.push_back(new Asteroid(rand() % 78 + 1, rand() % 4 + 3)); 
                    score += 10;                                                        
                }
            }
        }
        ss.Move();
        gotoxy(56, 1);
        printf("%d", score);
        Sleep(30); 
    }
    
    if (!ss.isDead())
    { 
        GameOverVictoryMessage();
    }
    else
    { 
        GameOverDefeatMessage();
    }

    Sleep(5000);
    SpecialMessage(); 
    Sleep(5000);
    return 0;
}