/**
 *	@brief a class to made cuboid object in Ogre
 *	@author Yukai Huang
 *	@file Cuboid.h
 */

#include "OgreManualObject.h"
 
class Cuboid : public Ogre::ManualObject
{
public :
	Cuboid(const Ogre::String& name);
	~Cuboid(void);
 	
	void setCorners(const Ogre::Vector3& right, const Ogre::Vector3& up, const Ogre::Vector3& front, const Ogre::Vector3& size);
};