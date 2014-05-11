#include "OgreRenderThread.h"
#include <windows.h>
void OgreRenderThread::run()
{

	while(1)
	{
		emit nextFrame();
		Sleep(1);
	}

}

void OgreRenderThread::update()
{
	emit nextFrame();
}
