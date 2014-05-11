/************************************************************************
     File:        Track.H

     Author:     
                  Michael Gleicher, gleicher@cs.wisc.edu
     Modifier
                  Yu-Chi Lai, yu-chi@cs.wisc.edu
				  Chun-Wei Wang, genialpp@gmail.com
     
     Comment:     Container for the "World"

						This provides a container for all of the "stuff" 
						in the world.

						It could have been all global variables, or it could 
						have just been
						contained in the window. The advantage of doing it 
						this way is that
						we might have multiple windows looking at the same 
						world. But, I don't	think we'll actually do that.

						See the readme for commentary on code style

     Platform:    Visio Studio.Net 2003/2005

*************************************************************************/
#pragma once

#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreEntity.h>
#include <vector>

// make use of other data structures from this project
#include "ControlPoint.h"

// Control Point Vector
typedef std::vector<ControlPoint> CPV; 

class CTrack {
	public:		
		// Constructor
		CTrack(Ogre::SceneManager *tSm);

	public:
		// when we want to clear the control points, we really "reset" them 
		// to have 4 default positions (since we should never have fewer
		// than 4 points)
		void resetPoints();

		// read and write to files
		void readPoints(const char* filename);
		void writePoints(const char* filename);

	private:
		// rather than have generic objects, we make a special case for these few
		// objects that we know that all implementations are going to need and that
		// we're going to have to handle specially
		CPV CPs;
		Ogre::SceneManager *mSm;	
		int mCount;

	public:	
		// add a control point
		Ogre::String mAdd(ControlPoint tCP); 
		// delete a control point
		void CTrack::mDelete( const Ogre::String& tName );
		// delete all control point
		void mDeleteAll();
		// move a control point
		void mMove(const Ogre::String& tName, const Ogre::Vector3& tPos); 
		// rotate a control point
		void mRotate(const Ogre::String& tName, const Ogre::Vector3& tOri);

		// get control point data through this method
		ControlPoint getItem(Ogre::String tName); 
		ControlPoint getItem(int i); 

		// return the number of the control point now 
		int getSize(); 

};