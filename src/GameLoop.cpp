/*
This file is part of the FruitsMania game project, distributed under the MIT license.

Repository: https://github.com/AndreiDiea/fruitsMania
Description: FruitsMania is a SDL match-three concept/prototype game.
Copyright: (c) 2014 Andrei Diea

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "GameStack.h"
#include "GameState_Menu.h"
#include "ResourceManager.h"
#include "EventTouch.h"

//Screen dimension constants
const int SCREEN_WIDTH = 755;
const int SCREEN_HEIGHT = 600;

//Starts up SDL and creates window
bool init();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;


bool init()
{
	//Initialization flag
	bool success = true;
	do
	{
		//Initialize SDL
		if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		{
			printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
			success = false;
			break;
		}

		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Jewels", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
			break;
		}
		
		//Create renderer for window
		gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
		if( gRenderer == NULL )
		{
			printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
			break;
		}

		ResourceManager::getResourceManager().SetGlobalRenderer(gRenderer);

		//Initialize renderer color
		SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

		//Initialize PNG loading
		int imgFlags = IMG_INIT_PNG;
		if( !( IMG_Init( imgFlags ) & imgFlags ) )
		{
			printf( "SDL_image could not initialize! SDL_mage Error: %s\n", IMG_GetError() );
			success = false;
		}

		//push first gamestate to gameStack
		boost::shared_ptr<GameState> newState = boost::make_shared<GameState_Menu>();
		GameStack::getGameStackInstance().PushState(newState);

	} while(false);	

	return success;
}

void close()
{
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Main loop flag
	bool quit = false;
	//Event handler
	SDL_Event e;
	//last frame time in ms
	unsigned int lastFrameTimeStamp = SDL_GetTicks();
	float frameTime = 0;

	do
	{
		//Start up SDL and create window
		if( !init() )
		{
			printf( "Failed to initialize!\n" );
			break;
		}
		
		//The game loop
		while( !quit )
		{
			//determine the last frametime, make sure it's not zero
			frameTime = (SDL_GetTicks() - lastFrameTimeStamp)/1000.0f + 0.001;
			lastFrameTimeStamp = SDL_GetTicks();
				
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT )
				{
					quit = true;
				}
				else if ( e.type == SDL_MOUSEBUTTONDOWN )
				{
					EventTouch* touchEv = new EventTouch(e.button.x, e.button.y, TouchType::TOUCH_START);
					GameStack::getGameStackInstance().OnEvent(touchEv);
					delete touchEv;
				}
				else if ( e.type == SDL_MOUSEBUTTONUP )
				{
					EventTouch* touchEv = new EventTouch(e.button.x, e.button.y, TouchType::TOUCH_END);
					GameStack::getGameStackInstance().OnEvent(touchEv);
					delete touchEv;
				}
			}

			/*update game, quit if update fails*/
			if(!GameStack::getGameStackInstance().Update(frameTime))
			{
				quit = true;
			}

			/* render game */
			SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
			SDL_RenderClear( gRenderer );

			//quit if render fails
			if(!GameStack::getGameStackInstance().Render(frameTime))
			{
				quit = true;
			}			

			//Update screen
			SDL_RenderPresent( gRenderer );
		}
	}while(false);

	//Free resources and close SDL
	close();

	return 0;
}