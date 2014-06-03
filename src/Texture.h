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
#ifndef TEXTURE_H
#define TEXTURE_H

#include "ResourceManager.h"
#include <string>
#include <SDL.h>
#include <stdio.h>

/**
  * class Texture
  * Texture to be blit on screen
  */
class Texture
{
public:

    /**
     * Constructs a texture instance
     */
    Texture (TextureIds _id);

    /**
     * Destructor
     */
    ~Texture ( );

    /**
     * Texture wrapper class
     * @return bool
     * @param  fileName The file path of the image
     */
    bool LoadFromFile (std::string fileName );


    /**
     * Set the Blend Mode preference for this texture
     * @param  blendMode the desired Blend Mode of the texture
     */
    void setBlendMode (SDL_BlendMode blendMode );


    /**
     * Set the blending alpha coefficient for this texture
     * @param  alpha The desired opacity between 0 and 1.0
     */
    void setAlpha (float alpha );


    /**
     * This renders current texture to the screen at desired position and with desired
     * clipped width/height
     * @param  x the X coordinate in screen space
     * @param  y the Y coordinate in screen space
     * @param  width the width at witch to clip the image. Default is zero meaning the
     * full texture width is rendered
     * @param  height the height at witch to clip the image. Default is zero meaning
     * the full texture height is rendered
     */
    void Render (int x, int y, int width = 0, int height = 0 );

	/**
     * Get the value of mTextureID
     * the ID of the texture
     * @return the value of mTextureID
     */
    TextureIds getTextureID ( );

    /**
     * @return true if successful
     */
    bool FreeTexture ( );

private:
    // the ID of the texture
    TextureIds mTextureID;
    // Alpha factor of the texture, used for blending
    float mAlpha;
    // Actual SDL texture
    SDL_Texture* mTexture;
	//Image dimensions
	int mWidth;
	int mHeight;
	//renderer for this texture
	SDL_Renderer* mRenderer;
};

#endif // TEXTURE_H
