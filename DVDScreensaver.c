#include <SFML/Graphics.h>

#define SCREEN_SIZE 768
#define COLOR_SPEED 1

sfVector2f dvdLogoSize = { 91, 53 }, dvdLogoPosition = { 10, 10 };
sfVideoMode video_mode = { SCREEN_SIZE, SCREEN_SIZE, 32 };

sfColor variationColor()
{
    static unsigned int state = 0;
    static sfColor c = { 0, 255, 0, 255 };
    if (state == 0)
    {
        c.r += COLOR_SPEED;
        c.g -= COLOR_SPEED;
        if (c.r >= 255)
            state = 1;
    }
    else if (state == 1)
    {
        c.b += COLOR_SPEED;
        c.r -= COLOR_SPEED;
        if (c.b >= 255)
            state = 2;
    }
    else
    {
        c.g += COLOR_SPEED;
        c.b -= COLOR_SPEED;
        if (c.g >= 255)
            state = 0;
    }
    return c;
}

void updateTexture(sfTexture *texture, sfImage *image, sfSprite *dvdlogo)
{
    sfColor colorGeneral = variationColor();
    for (unsigned int x = 0; x < dvdLogoSize.x; x++)
    {
        for (unsigned int y = 0; y < dvdLogoSize.y; y++)
        {
            sfColor colorPixel = sfImage_getPixel(image, x, y);
            if (colorPixel.a != 0)
                sfImage_setPixel(image, x, y, colorGeneral);
        }
    }
    sfTexture_updateFromImage(texture, image, 0, 0);
    sfSprite_setTexture(dvdlogo, texture, 1);
}

void moveLogo(sfSprite* dvdlogo)
{
    static signed int speedX = 2, speedY = 2;
    if (dvdLogoPosition.x >= (SCREEN_SIZE - dvdLogoSize.x))
        speedX = -2;
    else if (dvdLogoPosition.x <= 0)
        speedX = 2;

    if (dvdLogoPosition.y >= (SCREEN_SIZE - dvdLogoSize.y))
        speedY = -2;
    else if (dvdLogoPosition.y <= 0)
        speedY = 2;
    dvdLogoPosition.x += speedX;
    dvdLogoPosition.y += speedY;
    sfSprite_setPosition(dvdlogo, dvdLogoPosition);
}

int main(void)
{
    sfRenderWindow* window = NULL;
    sfClock* clock = NULL;
    sfTexture* texture = NULL;
    sfSprite* dvdlogo = NULL;
    sfImage* image = NULL;
    sfEvent event;
    
    clock = sfClock_create();

    window = sfRenderWindow_create(video_mode, "DVDScreensaver", sfResize | sfClose, NULL);
    if (!window)
        return 1;

    image = sfImage_createFromFile("dvdLogo.png");
    if (image == NULL)
        return 1;

    texture = sfTexture_createFromImage(image, NULL);


    dvdlogo = sfSprite_create();
    sfSprite_setTexture(dvdlogo, texture, 1);

    while (sfRenderWindow_isOpen(window))
    {
        sfSleep((sfMicroseconds(16666 - sfClock_getElapsedTime(clock).microseconds)));
        sfClock_restart(clock);
        sfRenderWindow_clear(window, sfBlack);

        while (sfRenderWindow_pollEvent(window, &event))
        {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        if (sfKeyboard_isKeyPressed(sfKeyEscape))
            sfRenderWindow_close(window);
        moveLogo(dvdlogo);
        updateTexture(texture, image, dvdlogo);

        sfRenderWindow_drawSprite(window, dvdlogo, NULL);
        sfRenderWindow_display(window);
    }

    sfSprite_destroy(dvdlogo);
    sfTexture_destroy(texture);
    sfImage_destroy(image);
    sfRenderWindow_destroy(window);
    sfClock_destroy(clock);
    return 0;
}