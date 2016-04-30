//
//  main.cpp
//
//  Created by CSCI3081W Guru on 1/15/15.
//  Copyright (c) 2015 CSCI3081W Guru. All rights reserved.
//


#include "FlashPhoto.h"
#include "ColorData.h"

int main(int argc, char* argv[])
{
	FlashPhoto *app = new FlashPhoto(argc, argv,400,400, ColorData(1,1,0.95));
	app->runMainLoop();
	exit(0);
}
