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
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Transform.h"
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <vector>

/* Fwd class declarations */
class Renderer;
class Collider;
class GameTimer;
class GameObject;
class EventType;

typedef boost::shared_ptr<GameObject> GameObjectPtr;
typedef boost::shared_ptr<GameTimer> GameTimerPtr;

/**
  * struct Rect
  * Stores a Rectangular object with a left-top anchor point and a width and height
  */
struct Rect
{
    // X coordiate of the rect's left-top corner
    float x;
    // Y coordiate of the rect's left-top corner
    float y;
    // Width of the Rect
    float width;
    // Height of the Rect
    float height;
	Rect():x(0), y(0), width(0), height(0){}
	Rect(int _x, int _y, int _w, int _h):x(_x), y(_y), width(_w), height(_h){}
};


/**
  * class GameObject
  * This class describes a generic game object
  */
class GameObject
{
public:

    /**
     * Constructor
	 * @param parent  The parent GameObject of this object 
     */
    GameObject (GameObject* parent );

    /**
     * Empty Destructor
     */
    virtual ~GameObject ( );

    /**
     * Updates the game logic for this object and all of its children
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behaviour
     */
    void Update (float frameTime );

    /**
	 * Handles rendering for this object and all of its children
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    void Render (float frameTime );

    /**
	 * Called the first frame to set things up in the gameobject and all of its children
     */
    void Start ( );

    /** 
	 * Handles an event and passes it along to its children if needed
     * @param  pEvent Pointer to an EventType abstract base class describing the event
	 * @return bool Return false to stop propagating this event
     */
    bool OnEvent (EventType* pEvent );

    /**
     * Add a child GameObject to this instance
     * @param  pChild Child to be added to this GameObject instance
     */
    void AddChild (GameObjectPtr& child );

    /**
     * Remove  a child GameObject from this instance
     * @return bool Return true if the child was removed
     * @param  pChild Child to be removed from this GameObject instance
     */
    bool RemoveChild (GameObject* pChild );

    /**
     * Gets this instance's parent GameObject
     * @return GameObject*
     */
    GameObject* GetParent();

    /**
     * Get this object's Transform instance as reference
     * @return the value of transform
     */
    Transform& getTransform ( );

    /**
     * Returns the Renderer specialised class for this GameObject. 
	 * Can return NULL for a gameobject without renderer.
     * @return Renderer*
     */
    Renderer* getRenderer ( );
    /**
     * Get the value of pCollider
     * Pointer to the Collider of this instance
     * @return the value of pCollider
     */
    Collider* getCollider ( );

    /**
     * Returns true if the gameObject is enabled
	 */
	bool IsEnabled() {return bEnabled;}

    /**
     * Enables or disables the GameObject
	 */
	void Enable(bool enable) { bEnabled = enable;}

protected:

	/**
     * Updates the game logic. Called first by Update()
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behaviour
     */
    virtual void EarlyUpdate (float frameTime ) = 0;

    /**Renders this gameObject. Called first by Render()
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    virtual void EarlyRender (float frameTime ) = 0;

    /**
	 * Called the first frame to set things up in the gameobject. Called first by Start()
     */
    virtual void EarlyStart ( ) = 0;

    /**Handles an event Called first by OnEvent
     * @param  pEvent Pointer to an EventType abstract base class describing the event
	 * @return bool Return false to stop propagating this event 
     */
    virtual bool EarlyOnEvent (EventType* pEvent ) = 0;

	//This GameObject's parent. Will be NULL for the scene root node
	GameObject *mParent;
	//The transform component of the Game Object
    Transform transform;
    // Pointer to the Renderer of this instance
    Renderer* pRenderer;
    // Vector of children of this GameObject instance. Vector was chosen as container implementation because it is optimised for sequencial access, and that is done every frame. It is not optimised for removing children(a set would be) but that is not happening more often than seq access.
    std::vector<GameObjectPtr> children;
    // Pointer to the Collider of this instance
    Collider* pCollider;
    // This GameObject's instance collection of timers. Timers need to have their Update() function called every frame.
    std::vector<GameTimerPtr> timers;
	// A gameObject can be disabled, then its Update/Render/OnEvent methods and those corresponding to their children
	// will not be called
	bool bEnabled;

	/* Make the copy-constructor and signment op private so that GameObjects are always constructed
	with the new op*/
	GameObject(GameObject const&);
    void operator=(GameObject const&);
};

#endif // GAMEOBJECT_H
