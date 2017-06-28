/********************************************************************
	author:		Yohiro	

	purpose:	Entry of Unicorn Engine to run game, When used,
	            create a class derived from  class scene, then 
				override the virtual method, like onSceneInitialized(
				see details in class scene).
*********************************************************************/
#include "Unicorn.h"
using namespace Unicorn;

int main(int argc, char* argv[])
{
	return Game::getInstance()->run();
}