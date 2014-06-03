/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "ResourceManager.h"
#include "Texture.h"
// Destructor
ResourceManager::~ResourceManager ( ) 
{ 
	textures.clear();
}

/**
 * If texture is not already loaded, it loads it from file
 * @return bool
 * @param  texID ID of the texture that is being loaded
 * @param  texturePath Path of the texture to be loaded
 */
bool ResourceManager::LoadTexture (TextureIds texID, std::string texturePath )
{
	bool bResult = false;
	FreeTexture(texID);
	TexturePtr pTex = boost::make_shared<Texture>(texID);
	
	if(pTex->LoadFromFile(texturePath))
	{
		textures.insert(std::map<TextureIds, TexturePtr>::value_type(texID, pTex));
		bResult = true;
	}
	return bResult;
}

/**
* Gets the global renderer used to render all textures 
*/
SDL_Renderer* ResourceManager::GetGlobalRenderer()
{
	return mRenderer;
}

/**
* Sets the global renderer used to render all textures 
*/
void ResourceManager::SetGlobalRenderer(SDL_Renderer* newRenderer)
{
	mRenderer = newRenderer;
}

/**
 * @param  textureId ID of the needed texture
 */
Texture* ResourceManager::GetTexture (TextureIds textureId )
{
	 std::map<TextureIds, TexturePtr>::const_iterator itr = textures.find(textureId);
     if(itr == textures.end())
     {
         return NULL;
     }
	 return itr->second.get();
}

/**
 * @param  textureId ID of the texture to free
 * @return true if texture has been freed
 */
bool ResourceManager::FreeTexture (TextureIds textureId )
{
	 std::map<TextureIds, TexturePtr>::const_iterator itr = textures.find(textureId);
     if(itr == textures.end())
     {
         return false;
     }

	 textures.erase(itr);
	 return true;
}
