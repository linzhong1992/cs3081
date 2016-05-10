//
//  main.cpp
//
//  Created by CSCI3081W Guru on 1/15/15.
//  Copyright (c) 2015 CSCI3081W Guru. All rights reserved.
//


#include "MIAApp.h"
#include "ColorData.h"

int main(int argc, char* argv[])
{
	MIAApp *app = new MIAApp(argc, argv,400,400, ColorData(1,1,0.95));
	if(argc == 1) {
		app->runMainLoop();
	}
	else {
		app->parser();
	}
	exit(0);
}
