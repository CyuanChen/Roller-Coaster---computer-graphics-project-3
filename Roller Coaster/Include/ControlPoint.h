/************************************************************************
     File:        ControlPoint.H

     Author:     
                  Michael Gleicher, gleicher@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu
				  Chun-Wei Wang, genialpp@gmail.com

     Comment:     Data structure for control points

						These are not just points in space (see Point3D), 
						because they may have
						an orientation associated with them. For most people, 
						the orientation will
						just be ignored. However, if you try some advanced 
						features, you might find the orientation vectors handy.

						I assume the orientation points UP 
						(the positive Y axis), so that's the default.
						When things get drawn, the point "points" in that 
						direction

     Platform:    Visio Studio.Net 2003/2005

*************************************************************************/
#pragma once

#include <OgreVector3.h>
#include <OgreString.h>

class ControlPoint {
	public:
		// constructors
		// need a default constructor for making arrays
		ControlPoint();					

		// create by name
		ControlPoint(const Ogre::String& tName);								

		// create in a position
		ControlPoint(const Ogre::Vector3& pos);	

		// Create in a position and orientation
		ControlPoint(const Ogre::Vector3& pos, const Ogre::Vector3& orient);

	public:
		Ogre::String name;		   // Name of this control point
		Ogre::Vector3 pos;         // Position of this control point
		Ogre::Vector3 orient;	   // Orientation of this control point
		Ogre::Vector3 tangen;
};
