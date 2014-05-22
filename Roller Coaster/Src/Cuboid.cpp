/**
 *	@brief implementation of Cuboid extends ManualObject class
 *	modified from
 *	http://hsw625728.blog.163.com/blog/static/39570728200910823457100/
 */
#include "Cuboid.h"

Cuboid::Cuboid(const Ogre::String& name): Ogre::ManualObject(name)
{
	setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
    clear();
	begin(name, Ogre::RenderOperation::OT_TRIANGLE_LIST);
}

Cuboid::~Cuboid(){}

void Cuboid::setCorners(const Ogre::Vector3& right, const Ogre::Vector3& up, const Ogre::Vector3& front, const Ogre::Vector3& size)
{
	Ogre::Vector3 cord = *(new Ogre::Vector3());

    cord.x = size.x * (right.x + front.x + up.x);
    cord.y = size.y * (right.y + front.y + up.y);
    cord.z = size.z * (right.z + front.z + up.z); 

	// cord.x = height.x +  width / 2.0;
	// cord.y = height.y;
	// cord.z = height.z + length / 2.0;
    

    position(-cord.x, cord.y,-cord.z); normal( 0, cord.y, 0); //textureCoord(0,0); // 0
    position( cord.x, cord.y,-cord.z); normal( 0, cord.y, 0); //textureCoord(1,0); // 1
    position( cord.x, cord.y, cord.z); normal( 0, cord.y, 0); //textureCoord(1,1); // 2
    position(-cord.x, cord.y, cord.z); normal( 0, cord.y, 0); //textureCoord(0,1); // 3

    quad(3,2,1,0);

    position(-cord.x,-cord.y, cord.z); normal( 0,-cord.y, 0); //textureCoord(0,0); // 4
    position( cord.x,-cord.y, cord.z); normal( 0,-cord.y, 0); //textureCoord(1,0); // 5
    position( cord.x,-cord.y,-cord.z); normal( 0,-cord.y, 0); //textureCoord(1,1); // 6
    position(-cord.x,-cord.y,-cord.z); normal( 0,-cord.y, 0); //textureCoord(0,1); // 7

    quad(7,6,5,4);

    position( cord.x, cord.y, cord.z); normal( cord.x, 0, 0); //textureCoord(0,0); // 8
    position( cord.x, cord.y,-cord.z); normal( cord.x, 0, 0); //textureCoord(1,0); // 9
    position( cord.x,-cord.y,-cord.z); normal( cord.x, 0, 0); //textureCoord(1,1); //10
    position( cord.x,-cord.y, cord.z); normal( cord.x, 0, 0); //textureCoord(0,1); //11

    quad(11,10,9,8);

    position(-cord.x, cord.y,-cord.z); normal(-cord.x, 0, 0); //textureCoord(0,0); //12
    position(-cord.x, cord.y, cord.z); normal(-cord.x, 0, 0); //textureCoord(1,0); //13
    position(-cord.x,-cord.y, cord.z); normal(-cord.x, 0, 0); //textureCoord(1,1); //14
    position(-cord.x,-cord.y,-cord.z); normal(-cord.x, 0, 0); //textureCoord(0,1); //15

    quad(15,14,13,12);

    position( cord.x, cord.y,-cord.z); normal( 0, 0,-cord.z); //textureCoord(0,0); //16
    position(-cord.x, cord.y,-cord.z); normal( 0, 0,-cord.z); //textureCoord(1,0); //17
    position(-cord.x,-cord.y,-cord.z); normal( 0, 0,-cord.z); //textureCoord(1,1); //18
    position( cord.x,-cord.y,-cord.z); normal( 0, 0,-cord.z); //textureCoord(0,1); //19

    quad(19,18,17,16);

    position(-cord.x, cord.y, cord.z); normal( 0, 0, cord.z); //textureCoord(0,0); //20
    position( cord.x, cord.y, cord.z); normal( 0, 0, cord.z); //textureCoord(1,0); //21
    position( cord.x,-cord.y, cord.z); normal( 0, 0, cord.z); //textureCoord(1,1); //22
    position(-cord.x,-cord.y, cord.z); normal( 0, 0, cord.z); //textureCoord(0,1); //23

    quad(23,22,21,20);

    setVisible(true);

	// // Vertex
 //    position( -cord.x, -cord.y, -cord.z);  colour(0.0, 0.0, 0.0);  normal(1, 0, 0); //0
 //    position(  cord.x, -cord.y, -cord.z);  colour(0.0, 0.0, 0.0);  normal(1, 0, 0); //1
 //    position(  cord.x, -cord.y,  cord.z);  colour(0.0, 0.0, 0.0);  normal(1, 0, 0); //2
 //    position( -cord.x, -cord.y,  cord.z);  colour(0.0, 0.0, 0.0);  normal(1, 0, 0); //3
 //    position( -cord.x,  cord.y, -cord.z);  colour(0.0, 0.0, 0.0);  normal(1, 0, 0); //4
 //    position(  cord.x,  cord.y, -cord.z);  colour(0.0, 0.0, 0.0);  normal(1, 0, 0); //5
 //    position(  cord.x,  cord.y,  cord.z);  colour(0.0, 0.0, 0.0);  normal(1, 0, 0); //6
 //    position( -cord.x,  cord.y,  cord.z);  colour(0.0, 0.0, 0.0);  normal(1, 0, 0); //7

 //    // Index
 //    triangle(0, 2, 1);
 //    triangle(0, 2, 3);
 //    triangle(3, 4, 0);
 //    triangle(3, 7, 4);
 //    triangle(4, 7, 6);
 //    triangle(4, 6, 5);
 //    triangle(5, 2, 1);
 //    triangle(5, 6, 2);
 //    triangle(0, 4, 1);
 //    triangle(5, 1, 4);
 //    triangle(3, 6, 7);
 //    triangle(3, 2, 6);

    end();
}