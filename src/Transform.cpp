/*
 * This source/header file is part of a test interview and is created & copyrighted (c) Andrei Diea <diea_andrei@yahoo.com> 2014
 * and is not to be distributed or used for commercial purposes without author consent.
 */
#include "Transform.h"
#include "GameObject.h"
/**
 * @param  pGameObject GameObject instance that this Transform is attached to. This
 * will be used to get the hieracly parent
 */
Transform::Transform (GameObject* pGameObject)
{
	mpGameObject = pGameObject;
}

/**
 * Translates the object in local space relative to its previous position.
 * @param  translateVector The relative translation vector that is to be applied to
 * this object's localTransform
 */
void Transform::Translate (Vector2& translateVector )
{

	//Update the final resulting transform of this object
	if(mpGameObject && mpGameObject->GetParent())
	{
		localTransform.mat[0][2] += translateVector.getX();
		localTransform.mat[1][2] += translateVector.getY();

		finalTransform = mpGameObject->GetParent()->getTransform().GetFinalTransform() * 
						 localTransform;
	}
	else
	{
		finalTransform.mat[0][2] += translateVector.getX();
		finalTransform.mat[1][2] += translateVector.getY();	
	}
}


/**
 * Scales the object in local space relative to it's previous scale
 * @param  scaleVector Scale vector used to scale the object
 */
void Transform::Scale (Vector2& scaleVector )
{

	//Update the final resulting transform of this object
	if(mpGameObject && mpGameObject->GetParent())
	{
		localTransform.mat[0][0] += scaleVector.getX();
		localTransform.mat[1][1] += scaleVector.getY();

		finalTransform = mpGameObject->GetParent()->getTransform().GetFinalTransform() * 
						 localTransform;
	}
	else
	{
		finalTransform.mat[0][0] += scaleVector.getX();
		finalTransform.mat[1][1] += scaleVector.getY();	
	}
}


/**
 * Sets the absolute position of the object in local space
 * @param  position Final position of the object in local space
 */
void Transform::SetPosition (Vector2& position )
{
	
	//Update the final resulting transform of this object
	if(mpGameObject && mpGameObject->GetParent())
	{
		localTransform.mat[0][2] = position.getX();
		localTransform.mat[1][2] = position.getY();

		finalTransform = mpGameObject->GetParent()->getTransform().GetFinalTransform() * 
						 localTransform;
	}
	else
	{
		finalTransform.mat[0][2] = position.getX();
		finalTransform.mat[1][2] = position.getY();	
	}
}


/**
 * Sets the absolute scale of the object in local space
 * @param  scale Final scale of the object in local space
 */
void Transform::SetScale (Vector2& scale )
{

	//Update the final resulting transform of this object
	if(mpGameObject && mpGameObject->GetParent())
	{
		localTransform.mat[0][0] = scale.getX();
		localTransform.mat[1][1] = scale.getY();
		Mat3 m = mpGameObject->GetParent()->getTransform().GetFinalTransform();
		finalTransform = m * 
						 localTransform;
	}
	else
	{
		finalTransform.mat[0][0] = scale.getX();
		finalTransform.mat[1][1] = scale.getY();	
	}
}


/**
 * Gets the absolute position of the object in local space
 * @param result Storage for the position
 */
void Transform::GetLocalPosition (Vector2& result )
{
	result.setX(localTransform.mat[0][2]);
	result.setY(localTransform.mat[1][2]);
}


/**
 * Gets the absolute scale of the object in local space
 * @param result Storage for the position
 */
void Transform::GetLocalScale (Vector2& result)
{
	result.setX(localTransform.mat[0][0]);
	result.setY(localTransform.mat[1][1]);
}


/**
 * Gets the absolute position of the object in world space
 * @param result Storage for the position
 */
void Transform::GetPosition (Vector2& result)
{
	result.setX(finalTransform.mat[0][2]);
	result.setY(finalTransform.mat[1][2]);
}


/**
 * Gets the absolute scale of the object in world space
 * @param result Storage for the position
 */
void Transform::GetScale (Vector2& result)
{
	result.setX(finalTransform.mat[0][0]);
	result.setY(finalTransform.mat[1][1]);
}


/**
 * Returns the local transform matrix
 * @return Mat3&
 */
Mat3& Transform::GetLocalTransform ( )
{
	return localTransform;
}

/**
* Returns the final transform matrix
* @return Mat3&
*/
Mat3& Transform::GetFinalTransform ( )
{
	return finalTransform;
}

