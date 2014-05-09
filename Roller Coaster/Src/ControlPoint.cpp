/************************************************************************
     File:        ControlPoint.cpp

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

#include "ControlPoint.H"
//****************************************************************************
//
// * Default contructor
//============================================================================
ControlPoint::
ControlPoint() 
	: pos(0,0,0), orient(0,1,0)
//============================================================================
{
}

//****************************************************************************
//
// * Set up the position and set orientation to default (0, 1, 0)
//============================================================================
ControlPoint::
ControlPoint(const Ogre::Vector3 &_pos) 
	: pos(_pos), orient(0,1,0)
//============================================================================
{
}

//****************************************************************************
//
// * Set up the position and orientation
//============================================================================
ControlPoint::
ControlPoint(const Ogre::Vector3 &_pos, const Ogre::Vector3 &_orient) 
	: pos(_pos), orient(_orient)
//============================================================================
{
	orient.normalise();
}

ControlPoint::ControlPoint( const Ogre::String& tName )
	: name(tName), pos(0,0,0), orient(0,1,0)
{
}