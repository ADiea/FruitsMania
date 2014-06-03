/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "Texture.h"
#include <SDL_image.h>

/**
* Constructs a texture instance
*/
Texture::Texture (TextureIds _id):mTextureID(_id), mTexture(NULL), mWidth(0), mHeight(0)
{
	mRenderer = ResourceManager::getResourceManager().GetGlobalRenderer();
}

/**
* Destructor
*/
Texture::~Texture ( )
{
	FreeTexture();
}

/**
* Texture wrapper class
* @return bool
* @param  fileName The file path of the image
*/
bool Texture::LoadFromFile (std::string fileName )
{
	//Clean up first
	FreeTexture();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( fileName.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( ResourceManager::getResourceManager().GetGlobalRenderer(),
												   loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", fileName.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}


/**
* Set the Blend Mode preference for this texture
* @param  blendMode the desired Blend Mode of the texture
*/
void Texture::setBlendMode (SDL_BlendMode blendMode )
{
	/* SDL glue*/
}


/**
* Set the blending alpha coefficient for this texture
* @param  alpha The desired opacity between 0 and 1.0
*/
void Texture::setAlpha (float alpha )
{
	if(alpha > 1) 
		alpha = 1;
	if(alpha < 0) 
		alpha = 0;
	mAlpha = alpha;
	/* SDL glue*/
}


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
void Texture::Render (int x, int y, int width, int height)
{
	if(!mTexture)
		return;
	if(!width)
		width = mWidth;
	if(!height)
		height = mHeight;
	//Set the clipping rect
	SDL_Rect renderRect = { x, y, width, height };
	//Render 
	
	SDL_RenderCopy( mRenderer, mTexture, NULL, &renderRect );

}

/**
* Get the value of mTextureID
* the ID of the texture
* @return the value of mTextureID
*/
TextureIds Texture::getTextureID ( )
{
	return mTextureID;
}

/**
* @return true if successful
*/
bool Texture::FreeTexture ( )
{
	if (mTexture != NULL)
	{		
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = mHeight = 0;
		return true;
	}
	return false;
}