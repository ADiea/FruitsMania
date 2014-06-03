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
#include "GameObject.h"
#include "GameTimer.h"
#include "Renderer.h"
#include "Collider.h"

/**
* Constructor
* @param parent  The parent GameObject of this object 
*/
GameObject::GameObject (GameObject* parent )
	:mParent(parent), transform(this), pCollider(NULL), pRenderer(NULL), bEnabled(true)
{}

GameObject::~GameObject ( ) 
{
	//Delete the renderer & collider. 
	//Virtual destructors make sure the corresponding derived objects are destroyed 
	//along with the base
	if(pRenderer)
	{
		delete pRenderer;
		pRenderer = NULL;
	}
	if(pCollider)
	{
		delete pCollider;
		pCollider = NULL;
	}
	
	//clear this gameObject's timers
	timers.clear();

	//at last, clear the children
	children.clear();
}

/**
 * Updates the game logic for this object and all of its children
 * @param  frameTime Last frame time that is used as an inverse of the FPS to
 * obtain FPS independent game behaviour
 */
void GameObject::Update (float frameTime )
{
	if(bEnabled)
	{
		std::vector<GameTimerPtr>::iterator iterTime = timers.begin();
		std::vector<GameObjectPtr>::iterator iterObject = children.begin();

		//update this gameObject
		EarlyUpdate(frameTime);

		//update this gameObject's timers
		for ( ; iterTime != timers.end(); ++iterTime )
		{
			if(*iterTime)
				(*iterTime)->Update(frameTime);
		}
		//update this gameObject's children
		for ( ; iterObject != children.end(); ++iterObject )
		{
			if(*iterObject)
				(*iterObject)->Update(frameTime);
		}
	}
}

/**
 * Handles rendering for this object and all of its children
 * @param  frameTime Last frame time that is used as an inverse of the FPS to
 * obtain FPS independent game behavior
 */
void GameObject::Render (float frameTime )
{
	if(bEnabled)
	{
		std::vector<GameObjectPtr>::iterator iterObject = children.begin();

		//render this gameObject
		EarlyRender(frameTime);

		//render this gameObject's children
		for ( ; iterObject != children.end(); ++iterObject )
		{
			if(*iterObject)
				(*iterObject)->Render(frameTime);
		}
	}
}

/**
 */
void GameObject::Start ( )
{
	//start this gameObject
	EarlyStart();

	std::vector<GameObjectPtr>::iterator iterObject = children.begin();

	//start this gameObject's children
	for ( ; iterObject != children.end(); ++iterObject )
	{
		if(*iterObject)
			(*iterObject)->Start();
	}
}

/** 
* Handles an event and passes it along to its children if needed
* @param  pEvent Pointer to an EventType abstract base class describing the event
* @return bool Return false to stop propagating this event
*/
bool GameObject::OnEvent (EventType* pEvent )
{
	bool bReturn = true;

	if(bEnabled)
	{
		std::vector<GameObjectPtr>::iterator iterObject = children.begin();
		//handle event for this gameObject
		if(EarlyOnEvent(pEvent))
		{
			//handle event for this gameObject's children
			for ( ; iterObject != children.end(); ++iterObject )
			{	
				if(*iterObject && !(*iterObject)->OnEvent(pEvent))
				{
					bReturn = false;
					break;
				}
			}
		}
		else bReturn = false;
	}

	return bReturn;
}

/**
 * Add a child GameObject to this instance
 * @param  pChild Child to be added to this GameObject instance
 */
void GameObject::AddChild (GameObjectPtr& child )
{
	children.push_back(child);
}

/**
 * Remove  a child GameObject from this instance
 * @return bool
 * @param  pChild Child to be removed from this GameObject instance
 */
bool GameObject::RemoveChild (GameObject* pChild )
{
	bool bResult = false;
	std::vector<GameObjectPtr>::iterator iterObject = children.begin();
	//find the child & sell him to the Circus
	for ( ; iterObject != children.end(); ++iterObject )
	{
		if(iterObject->get() == pChild)
		{
			bResult = true;
			children.erase(iterObject);
			break;
		}
	}

	return bResult;
}

/**
* Gets this instance's parent GameObject
* @return GameObject*
*/
GameObject* GameObject::GetParent()
{
	return mParent;
}

/**
* Get this object's Transform instance as reference
* @return the value of transform
*/
Transform& GameObject::getTransform ( )
{
	return transform;
}

/**
* Returns the Renderer specialised class for this GameObject. 
* Can return NULL for a gameobject without renderer.
* @return Renderer*
*/
Renderer* GameObject::getRenderer ( )
{
	return pRenderer;
}

/**
* Get the value of pCollider
* Pointer to the Collider of this instance
* @return the value of pCollider
*/
Collider* GameObject::getCollider ( )
{
	return pCollider;
}
