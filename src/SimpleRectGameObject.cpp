/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "SimpleRectGameObject.h"
#include "Vector2.h"
#include "SimpleRectRenderer.h"
#include "RectangularCollider.h"

/**
* Constructs a simple rectangular game object 
* @param parent The parent GameObject of this object
* @param  textureID The texture id of this game object. 
* @param  position The position and dimensions in parent space of this gameobject
*/
SimpleRectGameObject::SimpleRectGameObject (GameObject *parent, TextureIds textureID, Rect position )
	: GameObject(parent)
{
	//Create a simple rectangular renderer
	pRenderer = new SimpleRectRenderer(this, textureID, position.width, position.height);

	//set up the transform
	transform.SetPosition(Vector2(position.x, position.y));
	transform.SetScale(Vector2(1,1));
	//create a rectangular non-offseted collider for this object
	pCollider = new RectangularCollider(this, 0,0, position.width, position.height); 
}

/**
* @param  frameTime Last frame time that is used as an inverse of the FPS to
* obtain FPS independent game behavior
*/
void SimpleRectGameObject::EarlyRender (float frameTime )
{
	if(pRenderer)
		pRenderer->Render(frameTime);
}