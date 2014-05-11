/************************************************************************
     File:        Track.cpp

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

#include "Track.H"
#include "ObjectControl.h"
//****************************************************************************
//
// * Constructor
//============================================================================
CTrack::
CTrack(Ogre::SceneManager *tSm) : mSm(tSm), mCount(0)
//============================================================================
{
	resetPoints();
}

//****************************************************************************
//
// * provide a default set of points
//============================================================================
void CTrack::
resetPoints()
//============================================================================
{
	mDeleteAll();
	CPs.clear();
	mAdd(ControlPoint(Ogre::Vector3(  50,	 10,	  0)));
	mAdd(ControlPoint(Ogre::Vector3(   0,	 10,	 50)));
	mAdd(ControlPoint(Ogre::Vector3( -50,	 10,	  0)));
	mAdd(ControlPoint(Ogre::Vector3(   0,	 10,	-50)));
}

//****************************************************************************
//
// * Handy utility to break a string into a list of words
//============================================================================
void breakString(char* str, std::vector<const char*>& words) 
//============================================================================
{
	// start with no words
	words.clear();

	// scan through the string, starting at the beginning
	char* p = str;

	// stop when we hit the end of the string
	while(*p) {
		// skip over leading whitespace - stop at the first character or end of string
		while (*p && *p<=' ') p++;

		// now we're pointing at the first thing after the spaces
		// make sure its not a comment, and that we're not at the end of the string
		// (that's actually the same thing)
		if (! (*p) || *p == '#')
		break;

		// so we're pointing at a word! add it to the word list
		words.push_back(p);

		// now find the end of the word
		while(*p > ' ') p++;	// stop at space or end of string

		// if its ethe end of the string, we're done
		if (! *p) break;

		// otherwise, turn this space into and end of string (to end the word)
		// and keep going
		*p = 0;
		p++;
	}
}

//****************************************************************************
//
// * The file format is simple
//   first line: an integer with the number of control points
//	  other lines: one line per control point
//   either 3 (X,Y,Z) numbers on the line, or 6 numbers (X,Y,Z, orientation)
//============================================================================
void CTrack::
readPoints(const char* filename)
//============================================================================
{
	mDeleteAll();

	FILE* fp = fopen(filename,"r");
	if (!fp) {
		printf("Can't Open File!\n");
	} 
	else {
		char buf[512];

		// first line = number of points
		fgets(buf,512,fp);
		size_t npts = (size_t) atoi(buf);

		if( (npts<4) || (npts>65535)) {
			printf("Illegal Number of Points Specified in File");
		} else {
			CPs.clear();
			// get lines until EOF or we have enough points
			while( (CPs.size() < npts) && fgets(buf,512,fp) ) {
				Ogre::Vector3 pos,orient;
				std::vector<const char*> words;
				breakString(buf,words);
				if (words.size() >= 3) {
					pos.x = (float) strtod(words[0],0);
					pos.y = (float) strtod(words[1],0);
					pos.z = (float) strtod(words[2],0);
				} else {
					pos.x=0;
					pos.y=0;
					pos.z=0;
				}
				if (words.size() >= 6) {
					orient.x = (float) strtod(words[3],0);
					orient.y = (float) strtod(words[4],0);
					orient.z = (float) strtod(words[5],0);
				} else {
					orient.x = 0;
					orient.y = 1;
					orient.z = 0;
				}
				orient.normalise();
				mAdd(ControlPoint(pos,orient));
			}
		}
		fclose(fp);
	}
}

//****************************************************************************
//
// * write the control points to our simple format
//============================================================================
void CTrack::
writePoints(const char* filename)
//============================================================================
{
	FILE* fp = fopen(filename,"w");
	if (!fp) {
		printf("Can't open file for writing");
	} else {
		fprintf(fp,"%d\n",CPs.size());
		for(size_t i=0; i<CPs.size(); ++i)
			fprintf(fp,"%g %g %g %g %g %g\n",
				CPs[i].pos.x, CPs[i].pos.y, CPs[i].pos.z, 
				CPs[i].orient.x, CPs[i].orient.y, CPs[i].orient.z);
		fclose(fp);
	}
}

// add a control point
Ogre::String CTrack::mAdd( ControlPoint tCP )
{
	Ogre::Entity *ent;
	char name[16];
	sprintf(name, "ControlPoint%d", mCount++);
	ent = mSm->createEntity(name, "point.mesh");
	ent->setQueryFlags(ObjectControl::CONTROL_POINT);

	Ogre::SceneNode *mCurrentObject = mSm->getRootSceneNode()->createChildSceneNode(std::string(name) + "Node", tCP.pos);
	mCurrentObject->attachObject(ent);
	mCurrentObject->setScale(0.05f, 0.05f, 0.05f);

	tCP.name = mCurrentObject->getName();

	CPs.push_back(tCP);

	return mCurrentObject->getName();
}

// delete a control point
void CTrack::mDelete( const Ogre::String& tName )
{
	for (CPV::iterator ii = CPs.begin(); ii != CPs.end(); ii++)
	{
		ControlPoint a = *ii;
		if (a.name == tName)
		{
			mSm->destroySceneNode(mSm->getSceneNode(a.name));
			mSm->destroyEntity(a.name);

			CPs.erase(ii);

			break;
		}
	}
}

// delete all control point
void CTrack::mDeleteAll()
{
	for (int i =0; i<CPs.size(); i++)
	{
		mSm->destroySceneNode(mSm->getSceneNode(CPs[i].name));
		mSm->destroyEntity(CPs[i].name);
	}

	CPs.clear();
}

// move a control point
void CTrack::mMove( const Ogre::String& tName, const Ogre::Vector3& tPos )
{
	for (CPV::iterator ii = CPs.begin(); ii != CPs.end(); ii++)
	{
		ControlPoint a = *ii;
		if (a.name == tName)
		{
			ii->pos = tPos;
			break;
		}
	}
}

// rotate a control point
void CTrack::mRotate( const Ogre::String& tName, const Ogre::Vector3& tOri )
{
	for (CPV::iterator ii = CPs.begin(); ii != CPs.end(); ii++)
	{
		ControlPoint a = *ii;
		if (a.name == tName)
		{
			ii->orient = tOri;
			break;
		}
	}
}

// get control point data through this method
ControlPoint CTrack::getItem( Ogre::String tName )
{
	for (CPV::iterator ii = CPs.begin(); ii != CPs.end(); ii++)
	{
		ControlPoint a = *ii;
		if (a.name == tName)
		{
			return a;
		}
	}

	return ControlPoint("NO");
}

ControlPoint CTrack::getItem( int i )
{
	if (i < CPs.size())
	{
		return CPs[i];
	}

	return ControlPoint("NO");
}

// return the number of the control point now
int CTrack::getSize()
{
	return CPs.size();
}
