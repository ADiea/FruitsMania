/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "AnimatedRectRenderer.h"

AnimatedRectRenderer::AnimatedRectRenderer (GameObject* gameObject, float width, float height)
	: Renderer(gameObject), mWidth(width), mHeight(height)
{
}

AnimatedRectRenderer::~AnimatedRectRenderer ( ) { }

/**
 * Set the value of currentFrame
 * @param new_var the new value of currentFrame
 */
void AnimatedRectRenderer::setCurrentFrame ( int new_var ) {
    currentFrame = new_var;
}

/**
 * Get the value of currentFrame
 * @return the value of currentFrame
 */
int AnimatedRectRenderer::getCurrentFrame ( ) {
    return currentFrame;
}

/**
 * Set the value of bLoop
 * @param new_var the new value of bLoop
 */
void AnimatedRectRenderer::setBLoop ( bool new_var ) {
    bLoop = new_var;
}

/**
 * Get the value of bLoop
 * @return the value of bLoop
 */
bool AnimatedRectRenderer::getBLoop ( ) {
    return bLoop;
}

/**
 * Set the value of animSpeed
 * The animation speed
 * @param new_var the new value of animSpeed
 */
void AnimatedRectRenderer::setAnimSpeed ( float new_var ) {
    animSpeed = new_var;
}

/**
 * Get the value of animSpeed
 * The animation speed
 * @return the value of animSpeed
 */
float AnimatedRectRenderer::getAnimSpeed ( ) {
    return animSpeed;
}

/**
 * Set the value of animTime
 * Total time elapsed since the animation started. Is set to 0 when an animation
 * loops around
 * @param new_var the new value of animTime
 */
void AnimatedRectRenderer::setAnimTime ( float new_var ) {
    animTime = new_var;
}

/**
 * Get the value of animTime
 * Total time elapsed since the animation started. Is set to 0 when an animation
 * loops around
 * @return the value of animTime
 */
float AnimatedRectRenderer::getAnimTime ( ) {
    return animTime;
}

/**
 * Performs the rendering operation. Increments to the next frame based on the
 * animSpeed, animTime and number of frames. Loops around if bLoop is set
 * @param  frameTime Last frame time that is used as an inverse of the FPS to
 * obtain FPS independent game behavior
 */
void AnimatedRectRenderer::Render (float frameTime )
{
}

