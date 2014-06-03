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
#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SDL.h>
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

class Texture;
typedef boost::shared_ptr<Texture> TexturePtr;


//Textures needed by the game
enum TextureIds
{
	TEX_CLICK,
	TEX_MAINMENU,
	TEX_BACKGROUND,
	TEX_JEWEL_BLUE,
	TEX_JEWEL_GREEN,
	TEX_JEWEL_PURPLE,
	TEX_JEWEL_RED,
	TEX_JEWEL_YELLOW,
	TEX_FOREGROUND,
	TEX_DIGIT_0, 
	TEX_DIGIT_1, 
	TEX_DIGIT_2, 
	TEX_DIGIT_3, 
	TEX_DIGIT_4, 
	TEX_DIGIT_5, 
	TEX_DIGIT_6, 
	TEX_DIGIT_7, 
	TEX_DIGIT_8, 
	TEX_DIGIT_9,
	TEX_HUD
};

/**
  * class ResourceManager
  * Resource Manager singleton
  */
class ResourceManager
{
public:
    /**
	 * If texture is not already loaded, it loads it from file
     * @return bool True on successful operation
     * @param  texID ID of the texture that is being loaded
     * @param  texturePath Path of the texture to be loaded
     */
    bool LoadTexture (TextureIds texID, std::string texturePath );

    /**
	 * Gets the Texture* corresponding the textureId
     * @param  textureId ID of the needed texture
     */
    Texture* GetTexture (TextureIds textureId );

    /**
     * @return the ResourceManager instance
     */
    static ResourceManager& getResourceManager ( )
	{	// Instantiated on first use.
		static ResourceManager instance;
        return instance;
    }

	/**
	* Gets the global renderer used to render all textures 
	*/
	SDL_Renderer* GetGlobalRenderer();

	/**
	* Sets the global renderer used to render all textures 
	*/
	void SetGlobalRenderer(SDL_Renderer* newRenderer);

	/* Destructor */
	~ResourceManager ();
private:

	/**
	 * @param  textureId ID of the texture to free
	 * @return true if texture has been freed
	 */
	bool FreeTexture (TextureIds textureId );

	/* Declare constructor copy-ctor and asignment op private*/
	ResourceManager ():mRenderer(NULL){};
	ResourceManager(ResourceManager const&);
    void operator=(ResourceManager const&);
	//The global renderer used to render all textures
	SDL_Renderer* mRenderer;

	// A map of currently loaded textures with their corresponding textureIds as key
    std::map<TextureIds, TexturePtr> textures;
};

#endif // RESOURCEMANAGER_H
