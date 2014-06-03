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
#ifndef SIMPLERECTRENDERER_H
#define SIMPLERECTRENDERER_H
#include "Renderer.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Vector2.h"

/**
  * class SimpleRectRenderer
  * Renders a simple Texture on a Rectangular area
  */
class SimpleRectRenderer : public Renderer
{
public:
    /**
     * Constructor
	 * @param texId The ID of the texture this renderer should use
     */
    SimpleRectRenderer ( GameObject* gameObject, TextureIds texId, float width, float height);

	/**
     * Change currenttexture
     * @param  textureID The ID of the texture this renderer should use
     */
    void SetTexture(TextureIds texId);

    /**
     * Perform the rendering operation
     * @param  frameTime Last frame time that is used as an inverse of the FPS to
     * obtain FPS independent game behavior
     */
    void Render (float frameTime );

    /**
     * Get the width and height of the rendered quad
     * @param  result Reference to result variable
     */
	void GetSize(Vector2& result);

private:

    // Current texture that is rendered
    Texture* pCurrentTexture;
	// width and height of the rectangle to be rendered
	float mWidth, mHeight;
};

#endif // SIMPLERECTRENDERER_H
