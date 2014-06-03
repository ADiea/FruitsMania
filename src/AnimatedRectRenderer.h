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
#ifndef ANIMATEDRECTRENDERER_H
#define ANIMATEDRECTRENDERER_H
#include "Renderer.h"
#include "Texture.h" 
#include "ResourceManager.h"
#include <vector>

/*
* Describes a simple renderer that has multiple textures(frames) and animates them
*/
class AnimatedRectRenderer : virtual public Renderer
{
public:

    /**
     * Constructor
     */
    AnimatedRectRenderer (GameObject* gameObject, float width, float height);

    /**
     * Empty Destructor
     */
    virtual ~AnimatedRectRenderer ( );

    /**
     * Performs the rendering operation. Increments to the next frame based on the
     * animSpeed, animTime and number of frames. Loops around if bLoop is set
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    void Render (float frameTime );

private:
    std::vector<Texture*> frames;
    int currentFrame;
    bool bLoop;
    // The animation speed
    float animSpeed;
    // Total time elapsed since the animation started. Is set to 0 when an animation loops around
    float animTime;
	// width and height of the rectangle to be rendered
	float mWidth, mHeight;

public:

    /**
     * Set the value of currentFrame
     * @param new_var the new value of currentFrame
     */
    void setCurrentFrame ( int new_var );

    /**
     * Get the value of currentFrame
     * @return the value of currentFrame
     */
    int getCurrentFrame ( );


    /**
     * Set the value of bLoop
     * @param new_var the new value of bLoop
     */
    void setBLoop ( bool new_var );

    /**
     * Get the value of bLoop
     * @return the value of bLoop
     */
    bool getBLoop ( );


    /**
     * Set the value of animSpeed
     * The animation speed
     * @param new_var the new value of animSpeed
     */
    void setAnimSpeed ( float new_var );

    /**
     * Get the value of animSpeed
     * The animation speed
     * @return the value of animSpeed
     */
    float getAnimSpeed ( );


    /**
     * Set the value of animTime
     * Total time elapsed since the animation started. Is set to 0 when an animation
     * loops around
     * @param new_var the new value of animTime
     */
    void setAnimTime ( float new_var );

    /**
     * Get the value of animTime
     * Total time elapsed since the animation started. Is set to 0 when an animation
     * loops around
     * @return the value of animTime
     */
    float getAnimTime ( );

};

#endif // ANIMATEDRECTRENDERER_H
