/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "SimpleRectRenderer.h"
#include "Vector2.h"
#include "GameObject.h"
/**
* Constructor
* @param texId The ID of the texture this renderer should use
*/
SimpleRectRenderer::SimpleRectRenderer ( GameObject* gameObject, TextureIds texId, float width, float height)
	: Renderer(gameObject), pCurrentTexture(NULL), mWidth(width), mHeight(height)
{
	pCurrentTexture = ResourceManager::getResourceManager().GetTexture(texId);
}

/**
* Change current texture
* @param  textureID The ID of the texture this renderer should use
*/
void SimpleRectRenderer::SetTexture(TextureIds texId)
{
	pCurrentTexture = ResourceManager::getResourceManager().GetTexture(texId);
}

/**
* Get the width and height of the rendered quad
* @param  result Reference to result variable
*/
void SimpleRectRenderer::GetSize(Vector2& result)
{
	result.setX(mWidth);
	result.setY(mHeight);
}

/**
* Gets the gameObject's position then perform the rendering operation
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behavior
*/
void SimpleRectRenderer::Render (float frameTime )
{
	int x=0,y=0, w=mWidth, h = mHeight;
	Vector2 position(0,0), scale(1,1);
	if(pGameObject)
	{
		pGameObject->getTransform().GetPosition(position);
		pGameObject->getTransform().GetScale(scale);
		x = position.getX();
		y = position.getY();
		w *= scale.getX();
		h *= scale.getY();
	}
	if(pCurrentTexture)
		pCurrentTexture->Render(x, y, w, h);
}