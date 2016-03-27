//
//  BrushWorkApp.cpp
//  Originally created by the CSci-3081W TAs.
//


#include "BrushWorkApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "ToolFactory.h"
#include "Tool.h"

#include <cmath>
#include <iostream>

using std::cout;
using std::endl;

BrushWorkApp::BrushWorkApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : 
	BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50) {
	// Set the name of the window
	setCaption("BrushWork");
		
	// Initialize Interface
	initializeBuffers(backgroundColor, width, height);
	
	// Create array of tools and populate
	m_tools = new Tool* [ToolFactory::getNumTools()];
	for (int i = 0; i < ToolFactory::getNumTools(); i++) {
		m_tools[i] = ToolFactory::createTool(i);
	}
	
	initGlui();
	initGraphics();
}

void BrushWorkApp::display() {
	drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}



BrushWorkApp::~BrushWorkApp() {
	if (m_displayBuffer) {
		delete m_displayBuffer;
	}
	
	// Delete each of the tools before deleting the list of tool pointers.
	if (m_tools) {
		Tool ** toolsEnd =  m_tools + ToolFactory::getNumTools();
		for (Tool ** tool_i = m_tools; tool_i < toolsEnd; tool_i++) {
			Tool* tool = *tool_i;
			if (tool) {
				delete tool;
			}
		}
		
		delete [] m_tools;
	}
}


void BrushWorkApp::mouseDragged(int x, int y) {
	int max_steps = 30;

	// We implimented a smoothing feature by interpolating between
	// mouse events. This is at the expense of processing, though,
	// because we just "stamp" the tool many times between the two
	// even locations. you can reduce max_steps until it runs
	// smoothly on your machine.
	
	// Get the differences between the events
	// in each direction
	int delta_x = x-m_mouseLastX;
	int delta_y = y-m_mouseLastY;
	
	// Calculate the min number of steps necesary to fill
	// completely between the two event locations.
	float pixelsBetween = fmax(abs(delta_x), abs(delta_y));
	int step_count = pixelsBetween;
	int step_size = 1;
	
	// Optimize by maxing out at the max_steps,
	// and fill evenly between
	if (pixelsBetween > max_steps) 
	{
		step_size = pixelsBetween/max_steps;
		step_count = max_steps;
	}
	
	// Iterate between the event locations
	for (int i = 0; i < pixelsBetween; i+=step_size) 
	{
		int x = m_mouseLastX+(i*delta_x/pixelsBetween);
		int y = m_mouseLastY+(i*delta_y/pixelsBetween);
		
		m_tools[m_curTool]->applyToBuffer(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer);
	}
	
	// let the previous point catch up with the current.
	m_mouseLastX = x;
	m_mouseLastY = y;
}

void BrushWorkApp::mouseMoved(int x, int y) {
	
}


void BrushWorkApp::leftMouseDown(int x, int y) {
	m_tools[m_curTool]->applyToBuffer(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer);

	m_mouseLastX = x;
	m_mouseLastY = y;
}

void BrushWorkApp::leftMouseUp(int x, int y) {
}

void BrushWorkApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
	m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
}

void BrushWorkApp::initGlui() {
	// Select first tool (this activates the first radio button in glui)
	m_curTool = 0;
	
	GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
	GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
	
	// Create interface buttons for different tools:
	for (int i = 0; i < ToolFactory::getNumTools(); i++) {
		new GLUI_RadioButton(radio, m_tools[i]->getName().c_str());
	}
	
	GLUI_Panel *colPanel = new GLUI_Panel(m_glui, "Tool Color");
	
	m_curColorRed = 0;
	m_spinnerR  = new GLUI_Spinner(colPanel, "Red:", &m_curColorRed, UI_COLOR_R, s_gluicallback);
	m_spinnerR->set_float_limits(0, 1.0);
	
	m_curColorGreen = 0;
	m_spinnerG  = new GLUI_Spinner(colPanel, "Green:", &m_curColorGreen, UI_COLOR_G, s_gluicallback);
	m_spinnerG->set_float_limits(0, 1.0);
	
	m_curColorBlue = 0;
	m_spinnerB  = new GLUI_Spinner(colPanel, "Blue:", &m_curColorBlue, UI_COLOR_B, s_gluicallback);
	m_spinnerB->set_float_limits(0, 1.0);
	new GLUI_Button(colPanel, "Red", UI_PRESET_RED, s_gluicallback);
	new GLUI_Button(colPanel, "Orange", UI_PRESET_ORANGE, s_gluicallback);
	new GLUI_Button(colPanel, "Yellow", UI_PRESET_YELLOW, s_gluicallback);
	new GLUI_Button(colPanel, "Green", UI_PRESET_GREEN, s_gluicallback);
	new GLUI_Button(colPanel, "Blue", UI_PRESET_BLUE, s_gluicallback);
	new GLUI_Button(colPanel, "Purple", UI_PRESET_PURPLE, s_gluicallback);
	new GLUI_Button(colPanel, "White", UI_PRESET_WHITE, s_gluicallback);
	new GLUI_Button(colPanel, "Black", UI_PRESET_BLACK, s_gluicallback);
	
	
	new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
}


void BrushWorkApp::initGraphics() {
	// Initialize OpenGL for 2D graphics as used in the BrushWork app
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluOrtho2D(0, m_width, 0, m_height);
	glViewport(0, 0, m_width, m_height);
}



void BrushWorkApp::gluiControl(int controlID) {
	switch (controlID) {
		case UI_PRESET_RED:
			m_curColorRed = 1;
			m_curColorGreen = 0;
			m_curColorBlue = 0;
			break;
		case UI_PRESET_ORANGE:
			m_curColorRed = 1;
			m_curColorGreen = 0.5;
			m_curColorBlue = 0;
			break;
		case UI_PRESET_YELLOW:
			m_curColorRed = 1;
			m_curColorGreen = 1;
			m_curColorBlue = 0;
			break;
		case UI_PRESET_GREEN:
			m_curColorRed = 0;
			m_curColorGreen = 1;
			m_curColorBlue = 0;
			break;
		case UI_PRESET_BLUE:
			m_curColorRed = 0;
			m_curColorGreen = 0;
			m_curColorBlue = 1;
			break;
		case UI_PRESET_PURPLE:
			m_curColorRed = 0.5;
			m_curColorGreen = 0;
			m_curColorBlue = 1;
			break;
		case UI_PRESET_WHITE:
			m_curColorRed = 1;
			m_curColorGreen = 1;
			m_curColorBlue = 1;
			break;
		case UI_PRESET_BLACK:
			m_curColorRed = 0;
			m_curColorGreen = 0;
			m_curColorBlue = 0;
			break;
		case UI_QUIT:
			// In the event of quit button,
			// destruct this PaintShop.
			delete this;
			exit(0);
		default:
			break;
	}
	
	m_spinnerB->set_float_val(m_curColorBlue);
	m_spinnerG->set_float_val(m_curColorGreen);
	m_spinnerR->set_float_val(m_curColorRed);	
}
