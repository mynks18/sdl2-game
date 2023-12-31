// creating a windows in SDL2

// standard c++ library
#include<iostream>

// importing SDL2 header
#include<SDL.h>

// include SDL_TTF
#include<SDL_ttf.h>

int main(int argc, char* argv[])
{
    // creating a window data type
    SDL_Window *window=nullptr;

    // error checking for sdl
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not be initialized\n";
        SDL_GetError();
    } else {
        std::cout << "Video system is ready to go\n";
    }

    // creating a windows using SDL_CreateWindow function
    // SDL_WINDOW_SHOWN is ignored by SDL_CreateWindow
    window = SDL_CreateWindow("C++ SDL2 Window", 0, 0, 640, 480, SDL_WINDOW_SHOWN);

    // creating an SDL_Renderer pointer
    SDL_Renderer *renderer = nullptr;

    // initializing SDL_Renderer
    // here "-1" will make choose sdl rendering driver automatically
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // initialize font system
    if(TTF_Init() == -1) {
        std::cout << "Could not initialize SDL2_ttf, error" << TTF_GetError() << std::endl;
    } else {
        std::cout << "SDL2_ttf system is ready to go!" << std::endl;
    }

    // load the font file and set the font size
    TTF_Font * outFont = TTF_OpenFont("./fonts/8bitOperatorPlus8-Regular.ttf", 32);
    
    // to confirm if the font is loaded or not
    if(outFont == nullptr) {
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }

    // load pixel from the text to a surface text
    // this is a tuple value {255, 255, 255}
    SDL_Surface *surfaceText = TTF_RenderText_Solid(outFont, "Mayank SDL2", {255, 255, 255});

    // creating a texture using surface
    SDL_Texture *textureText = SDL_CreateTextureFromSurface(renderer, surfaceText);

    // create a surface and load a BMP
    // SDL_Surface *surface = SDL_LoadBMP("./images/kong.bmp");
    // create a texture from surface
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    // freeing text sureface
    SDL_FreeSurface(surfaceText);
    // Free surface after the operation
    // SDL_FreeSurface(surface);

    // create a reactangle
    SDL_Rect rectangle;
    rectangle.x = 50;
    rectangle.y = 50;
    rectangle.w = 200;
    rectangle.h = 50;


    // infinite loop for application
    bool gameIsRunning = true;
    while(gameIsRunning)
    {
        SDL_Event event;
        // (1) handle inputs
        // event loop start
        while(SDL_PollEvent(&event))
        {
            // handle each specific event
            // SQL_QUIT is close button
            if(event.type == SDL_QUIT) {
                gameIsRunning = false;
            }
        }
        // (2) handle updates
        
        // set renderer bg color first
        // else it will be changed to line draw color
        SDL_SetRenderDrawColor(renderer, 0, 0, 0xFF, SDL_ALPHA_OPAQUE);            // black color
        // (3) clear and draw the screen
        SDL_RenderClear(renderer);

        // Set the render draw color
        // SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);      // white color
        // do our drawing here
        // SDL_RenderDrawLine(renderer, 5, 5, 200, 220);
        // SDL_RenderDrawRect(renderer, &rectangle);

        // Draw texture using SDL_RenderCopy
        SDL_RenderCopy(renderer, textureText, NULL, &rectangle);


        // finally render what have been drawn
        SDL_RenderPresent(renderer);
    }

    // destroying texture after being used
    SDL_DestroyTexture(textureText);

    // destroying created window
    SDL_DestroyWindow(window);

    // remember to close font subsystem 
    TTF_CloseFont(outFont);

    // SDL exit/quit function
    SDL_Quit();

    return 0;
}