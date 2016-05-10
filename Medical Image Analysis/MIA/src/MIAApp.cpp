#include "MIAApp.h"
#include "ColorData.h"
#include "PixelBuffer.h"
#include "ToolFactory.h"
#include "Tool.h"
#include "Blur.h"
#include "Sharpen.h"
#include "MotionBlur.h"
#include "EdgeDetect.h"
#include "SpecialFilter.h"
#include "ImageHandler.h"

#include "fChannel.h"
#include "fQuantize.h"
#include "fThreshold.h"
#include "fSaturation.h"

#include <cmath>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <sstream>
#include <dirent.h>
#include <vector>

using std::cout;
using std::endl;

MIAApp::MIAApp(int argc, char* argv[], int width, int height, ColorData backgroundColor) : BaseGfxApp(argc, argv, width, height, 50, 50, GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH, true, width+51, 50)
{
    // Set the name of the window
    setCaption("Medical Image Analysis (MIA)");

    // Initialize Interface
    initializeBuffers(backgroundColor, width, height);
    m_tools = new Tool* [2];
    m_tools[0] = ToolFactory::createTool(0);
    m_tools[1] = ToolFactory::createTool(6);

    initGlui();
    initGraphics();
    m_argc = argc;
    m_argv = argv;
    m_Mode = true;
}
void printHelp()
{
  std::cout <<"HELP MESSAGE\n"
  << "file/directory -sharpen <integer> file/directory\n"
  << "file/directory -edgedetect file/directory\n"
  << "file/directory -thresh <float> file/directory\n"
  << "file/directory -quantize <int> file/directory\n"
  << "file/directory -blur <float> file/directory\n"
  << "file/directory -saturate <float> file/directory\n"
  << "file/directory -multrgb <float> <float> <float> file/directory\n"
  << "file -compare file\n" << std::endl;
}
void MIAApp::parser()
{
    m_Mode = false;
    std::vector<std::string> fileNames;
    std::vector<std::string> inputFiles;
    std::vector<std::string> outputFiles;
    std::string cpp_string;
    if(m_argc == 2){
        if(!strcmp(m_argv[1], "-h")) {
            printHelp();
        }
        else {
            std::cout << "Please use -h to check usage.\n" << std::endl;
            printHelp();
            exit(1);
        }
        return;
    }
    else if(!strcmp(m_argv[2], "-compare")) {
        if(m_argc == 4) {
            if(!isValidImageFile(m_argv[1]) || !isValidImageFile(m_argv[3]))
                std::cout << " Input image file(s) is(are) not valid for comparing.\n" << std::endl;
            else {
                std::cout << "Comparing two image files...\n" << std::endl;
                m_fileName = m_argv[1];
                loadImageToCanvas();//load the first image tp m_displayBuffer
                PixelBuffer* first_image_file = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), ColorData(1,1,0.95));
                PixelBuffer::copyPixelBuffer(m_displayBuffer, first_image_file);
                m_fileName = m_argv[3];
                loadImageToCanvas();//load the second image to m_displayBuffer
                if(compare(first_image_file))
                {
                    std::cout << "1\n" << std::endl;
                }
                else
                {
                    std::cout << "0\n" << std::endl;
                }
            }
        }
        else {
            std::cout << "Wrong usage of -compare.\n" << std::endl;
            std::cout << "Please use -h to check usage.\n" << std::endl;
            printHelp();
            exit(1);
        }
    }
    else {
        if(isValidImageFile(m_argv[1])){
            std::cout << "First input is a image file.\n" << std::endl;
            if(isValidImageFileName(m_argv[m_argc - 1])) {
                inputFiles.push_back(m_argv[1]);
                outputFiles.push_back(m_argv[m_argc - 1]);

            }
            else {
                std::cout << "Output image name should be in format of .jpg, .jpeg or .png.\n" << std::endl;
                std::cout << "Please use -h to check usage.\n" << std::endl;
                printHelp();
                exit(1);
            }
        }
        else if(isValidDir(m_argv[1])){
            std::cout << "First input is a directory.\n" << std::endl;
            if(isValidDir(m_argv[m_argc - 1])) {
                std::cout << "Output Dir Found.\n" << std::endl;
                getImageFiles(m_argv[1], fileNames);
                for(int i = 0; i < fileNames.size(); i++) {
                    cpp_string = m_argv[1];
                    inputFiles.push_back(cpp_string + "/" + fileNames[i]);
                    cpp_string = m_argv[m_argc - 1];
                    outputFiles.push_back(cpp_string + "/" + fileNames[i]);
                }
            }
            else {
                std::cout << "Output directory is not valid." << std::endl;
                std::cout << "Please use -h to check usage.\n" << std::endl;
                printHelp();
                exit(1);
            }
        }
        else {
            std::cout << "Input should be either a image file or a directory." << std::endl;
            std::cout << "Please use -h to check usage.\n" << std::endl;
            printHelp();
            exit(1);
        }
        for(int j = 0; j < inputFiles.size(); j++) {
            m_fileName = inputFiles[j];
            loadImageToCanvas();
            for(int i = 2; i < m_argc - 1; i++) {
                if(!strcmp(m_argv[i],"-sharpen"))
                {
                    i++;
                    if(atoi(m_argv[i]) || strcmp(m_argv[i],"0") == 0)
                    {
                        m_filterParameters.sharpen_amount = atoi(m_argv[i]);
                        applyFilterSharpen();
                        std::cout << "Sharpen success." << std::endl;
                    }
                    else
                    {
                        std::cout << "Wrong sharpen usage." << std::endl;
                        std::cout << "Please use -h to check usage.\n" << std::endl;
                        printHelp();
                        exit(1);
                    }

                }
                else if(!strcmp(m_argv[i],"-edgedetect"))
                {
                    applyFilterEdgeDetect();
                    std::cout << "EdgeDetect success." << std::endl;
                }
                else if(!strcmp(m_argv[i],"-thresh"))
                {
                    i++;
                    if(atof(m_argv[i]) || strcmp(m_argv[i],"0") == 0) {
                        m_filterParameters.threshold_amount = atof(m_argv[i]);
                        applyFilterThreshold();
                        std::cout << "Threshold success." << std::endl;
                    }
                    else {
                        std::cout << "Wrong threshold usage." << std::endl;
                        std::cout << "Please use -h to check usage.\n" << std::endl;
                        printHelp();
                        exit(1);
                    }
                }
                else if(!strcmp(m_argv[i],"-quantize"))
                {
                    i++;
                    if(atoi(m_argv[i]) || strcmp(m_argv[i],"0") == 0) {
                        m_filterParameters.quantize_bins = atoi(m_argv[i]);
                        applyFilterQuantize();
                        std::cout << "Quantize success." << std::endl;
                    }
                    else {
                        std::cout << "Wrong quantize usage." << std::endl;
                        std::cout << "Please use -h to check usage.\n" << std::endl;
                        printHelp();
                        exit(1);
                    }
                }
                else if(!strcmp(m_argv[i],"-blur"))
                {
                    i++;
                    if(atof(m_argv[i]) || strcmp(m_argv[i],"0") == 0) {
                        m_filterParameters.blur_amount = atof(m_argv[i]);
                        applyFilterBlur();
                        std::cout << "Blur success." << std::endl;
                    }
                    else {
                        std::cout << "Wrong blur usage." << std::endl;
                        std::cout << "Please use -h to check usage.\n" << std::endl;
                        printHelp();
                        exit(1);
                    }
                }
                else if(!strcmp(m_argv[i],"-saturate"))
                {
                    i++;
                    if(atof(m_argv[i]) || strcmp(m_argv[i],"0") == 0) {
                        m_filterParameters.saturation_amount = atof(m_argv[i]);
                        applyFilterSaturate();
                        std::cout << "Saturate success." << std::endl;
                    }
                    else {
                        std::cout << "Wrong saturate usage." << std::endl;
                        std::cout << "Please use -h to check usage.\n" << std::endl;
                        printHelp();
                        exit(1);
                    }
                }
                else if(!strcmp(m_argv[i],"-multrgb"))
                {
                    float p1, p2, p3;
                    if(((p1 = atof(m_argv[i+1])) || strcmp(m_argv[i+1],"0") == 0) && ((p2 = atof(m_argv[i+2])) || strcmp(m_argv[i+2],"0") == 0) && ((p3 = atof(m_argv[i+3])) || strcmp(m_argv[i+3],"0") == 0))
                    {
                        m_filterParameters.multiply_colorRed = p1;
                        m_filterParameters.multiply_colorGreen = p2;
                        m_filterParameters.multiply_colorBlue = p3;
                        applyFilterMultiplyRGB();
                        std::cout << "Multrgb success." << std::endl;
                    }
                    else
                    {
                        std::cout << "Wrong multrgb usage." << std::endl;
                        std::cout << "Please use -h to check usage.\n" << std::endl;
                        printHelp();
                        exit(1);
                    }
                    i = i + 3;
                }
                else {
                    std::cout << "Wrong option(s). Check out option usage." << std::endl;
                    std::cout << "Please use -h to check usage.\n" << std::endl;
                    printHelp();
                    exit(1);
                }
            }
            m_fileName = outputFiles[j];
            saveCanvasToFile();
        }
    }
}

bool MIAApp::isValidDir(const std::string & name)
{
    bool isValid = false;
    DIR* dirp = opendir(name.c_str());
    if(dirp)
        isValid = true;
    closedir(dirp);
    return isValid;
}

void MIAApp::getImageFiles(const std::string & dirName, std::vector<std::string> & fileNames)
{
    DIR* dirp = opendir(dirName.c_str());
    struct dirent* dp;
    while(dp = readdir(dirp)) {
        std::string cpp_string = dp->d_name;
        if(strcmp(dp->d_name, ".") && strcmp(dp->d_name, "..") && isValidImageFileName(cpp_string))
            fileNames.push_back(cpp_string);//**** c string might not work
    }
    closedir(dirp);
}

bool MIAApp::compare(PixelBuffer* new_m_displayBuffer)
{
    const ColorData* new_data_array = new_m_displayBuffer->getData();
    const ColorData* data_array = m_displayBuffer->getData();
    int width;
    int height;
    if((width = new_m_displayBuffer->getWidth()) != m_displayBuffer->getWidth() || (height = new_m_displayBuffer->getHeight()) != m_displayBuffer->getHeight()) {
        return false;
    }
    else {
        for(int i = 0; i < width * height; i++) {
            if(new_data_array[i].getRed() != data_array[i].getRed() || new_data_array[i].getGreen() != data_array[i].getGreen() || new_data_array[i].getBlue() != data_array[i].getBlue()) {
                return false;
            }
        }
    }
    return true;
}

void MIAApp::display()
{
    drawPixels(0, 0, m_width, m_height, m_displayBuffer->getData());
}

MIAApp::~MIAApp()
{
    if (m_displayBuffer) {
        delete m_displayBuffer;
        delete m_stampBuffer;
        undoRedoEmpty();
        delete &m_undoStack;
        delete &m_redoStack;
    }
    // Delete each of the tools before deleting the list of tool pointers.
    if (m_tools) {
        Tool ** toolsEnd =  m_tools + 2;
        for (Tool ** tool_i = m_tools; tool_i < toolsEnd; tool_i++) {
            Tool* tool = *tool_i;
            if (tool) {
                delete tool;
            }
        }

        delete [] m_tools;
    }
}


void MIAApp::mouseDragged(int x, int y)
{
    if(m_curTool==1)//TOOL_STAMP
    {
        return;
    }
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
        m_tools[m_curTool]->applyToBuffer(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer, m_stampBuffer);
    }

    // let the previous point catch up with the current.
    m_mouseLastX = x;
    m_mouseLastY = y;
}

void MIAApp::mouseMoved(int x, int y)
{

}

void MIAApp::leftMouseDown(int x, int y)
{
    undoPush();
    while(!m_redoStack.empty())
    {
        m_redoStack.pop();
    }

    //std::cout << "mousePressed " << x << " " << y << std::endl;

    m_tools[m_curTool]->applyToBuffer(x, m_height-y, ColorData(m_curColorRed, m_curColorGreen, m_curColorBlue), m_displayBuffer, m_stampBuffer);

    m_mouseLastX = x;
    m_mouseLastY = y;
}

void MIAApp::leftMouseUp(int x, int y)
{
    std::cout << "mouseReleased " << x << " " << y << std::endl;
    redoEnabled(!m_redoStack.empty());
    undoEnabled(!m_undoStack.empty());
}

void MIAApp::initializeBuffers(ColorData backgroundColor, int width, int height) {
    m_displayBuffer = new PixelBuffer(width, height, backgroundColor);
    m_stampBuffer = new PixelBuffer(0, 0, backgroundColor);
}

void MIAApp::initGlui()
{
    // Select first tool (this activates the first radio button in glui)
    m_curTool = 0;

    // Set the defult pen color to red
    m_curColorRed = 1;
    m_curColorGreen = 0;
    m_curColorBlue = 0;

    m_fileName = "marker.png";
    loadImageToStamp();

    new GLUI_Column(m_glui, false);
    GLUI_Panel *toolPanel = new GLUI_Panel(m_glui, "Tool Type");
    {
        GLUI_RadioGroup *radio = new GLUI_RadioGroup(toolPanel, &m_curTool, UI_TOOLTYPE, s_gluicallback);
        // Create interface buttons for different tools:
        new GLUI_RadioButton(radio, "Pen");
        new GLUI_RadioButton(radio, "Arrow");

    }


    GLUI_Panel *filterPanel = new GLUI_Panel(m_glui, "Filters");
    {
        GLUI_Panel *sharpenPanel = new GLUI_Panel(filterPanel, "Sharpen");
        {
            GLUI_Spinner * filterSharpAmount = new GLUI_Spinner(sharpenPanel, "Amount:", &m_filterParameters.sharpen_amount);
            filterSharpAmount->set_int_limits(1, 10);
            filterSharpAmount->set_int_val(1);
            filterSharpAmount->set_speed(0.1);

            new GLUI_Button(sharpenPanel, "Apply", UI_APPLY_SHARP, s_gluicallback);
        }
        GLUI_Panel *edgeDetPanel = new GLUI_Panel(filterPanel, "Edge Detect");

        {
            new GLUI_Button(edgeDetPanel, "Apply", UI_APPLY_EDGE, s_gluicallback);
        }
        GLUI_Panel *thresPanel = new GLUI_Panel(filterPanel, "Threshold");
        {
            GLUI_Spinner * filterThresholdAmount = new GLUI_Spinner(thresPanel, "Level:", &m_filterParameters.threshold_amount);
            filterThresholdAmount->set_float_limits(0, 1);
            filterThresholdAmount->set_float_val(0.5);

            new GLUI_Button(thresPanel, "Apply", UI_APPLY_THRESHOLD, s_gluicallback);
        }

        GLUI_Panel *multiplyPanel = new GLUI_Panel(filterPanel, "Multiply RGB");
        {
            GLUI_Spinner * filterChannelRed = new GLUI_Spinner(multiplyPanel, "R:", &m_filterParameters.multiply_colorRed);
            GLUI_Spinner * filterChannelGreen = new GLUI_Spinner(multiplyPanel, "G:", &m_filterParameters.multiply_colorGreen);
            GLUI_Spinner * filterChannelBlue = new GLUI_Spinner(multiplyPanel, "B:", &m_filterParameters.multiply_colorBlue);

            filterChannelRed->set_float_limits(0, 10);
            filterChannelRed->set_float_val(1);
            filterChannelGreen->set_float_limits(0, 10);
            filterChannelGreen->set_float_val(1);
            filterChannelBlue->set_float_limits(0, 10);
            filterChannelBlue->set_float_val(1);

            new GLUI_Button(multiplyPanel, "Apply", UI_APPLY_MULTIPLY_RGB, s_gluicallback);
        }

        GLUI_Panel *quantPanel = new GLUI_Panel(filterPanel, "Quantize");
        {
            GLUI_Spinner * filterQuantizeBins = new GLUI_Spinner(quantPanel, "Bins:", &m_filterParameters.quantize_bins);
            filterQuantizeBins->set_int_limits(2, 256);
            filterQuantizeBins->set_int_val(8);
            filterQuantizeBins->set_speed(0.1);

            new GLUI_Button(quantPanel, "Apply", UI_APPLY_QUANTIZE, s_gluicallback);
        }

        GLUI_Panel *grayPanel = new GLUI_Panel(filterPanel, "Grayscale");
        {

            new GLUI_Button(grayPanel, "Apply", UI_APPLY_GRAYSCALE, s_gluicallback);
        }



        // UNDO,REDO,QUIT
        {
            m_gluiControlHooks.undoButton = new GLUI_Button(m_glui, "Undo", UI_UNDO, s_gluicallback);
            undoEnabled(false);
            m_gluiControlHooks.redoButton  = new GLUI_Button(m_glui, "Redo", UI_REDO, s_gluicallback);
            redoEnabled(false);

            new GLUI_Separator(m_glui);
            new GLUI_Button(m_glui, "Quit", UI_QUIT, (GLUI_Update_CB)exit);
        }
    }

    new GLUI_Column(m_glui, true);

    GLUI_Panel *imagePanel = new GLUI_Panel(m_glui, "Image I/O");
    {
        m_gluiControlHooks.fileBrowser = new GLUI_FileBrowser(imagePanel, "Choose Image", false, UI_FILE_BROWSER, s_gluicallback);

        m_gluiControlHooks.fileBrowser->set_h(400);

        m_gluiControlHooks.fileNameBox = new     GLUI_EditText( imagePanel , "Image:", m_fileName, UI_FILE_NAME, s_gluicallback );
        m_gluiControlHooks.fileNameBox->set_w(200);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.currentFileLabel = new GLUI_StaticText(imagePanel, "Will load image: none");
        m_gluiControlHooks.loadCanvasButton = new GLUI_Button(imagePanel, "Load Canvas", UI_LOAD_CANVAS_BUTTON, s_gluicallback);

        new GLUI_Separator(imagePanel);

        m_gluiControlHooks.saveFileLabel = new GLUI_StaticText(imagePanel, "Will save image: none");

        m_gluiControlHooks.saveCanvasButton = new GLUI_Button(imagePanel, "Save Canvas", UI_SAVE_CANVAS_BUTTON, s_gluicallback);


        m_gluiControlHooks.previousImageButton = new GLUI_Button(imagePanel, "Previous Image", UI_PREVIOUS_IMAGE_BUTTON, s_gluicallback);
        m_gluiControlHooks.nextImageButton = new GLUI_Button(imagePanel, "Next Image", UI_NEXT_IMAGE_BUTTON, s_gluicallback);


        loadCanvasEnabled(false);
        saveCanvasEnabled(false);
        nextImageEnabled(false);
        previousImageEnabled(false);
    }
    return;
}

void MIAApp::gluiControl(int controlID)
{

    switch (controlID) {
        case UI_APPLY_SHARP:
            applyFilterSharpen();
            break;
        case UI_APPLY_EDGE:
            applyFilterEdgeDetect();
            break;
        case UI_APPLY_THRESHOLD:
            applyFilterThreshold();
            break;
        case UI_APPLY_GRAYSCALE:
            applyFilterGrayScale();
            break;
        case UI_APPLY_MULTIPLY_RGB:
            applyFilterMultiplyRGB();
            break;
        case UI_APPLY_QUANTIZE:
            applyFilterQuantize();
            break;
        case UI_FILE_BROWSER:
            setImageFile(m_gluiControlHooks.fileBrowser->get_file());
            break;
        case UI_LOAD_CANVAS_BUTTON:
            loadImageToCanvas();
            break;
        case UI_SAVE_CANVAS_BUTTON:
            saveCanvasToFile();
            // Reload the current directory:
            m_gluiControlHooks.fileBrowser->fbreaddir(".");
            break;
        case UI_NEXT_IMAGE_BUTTON:
            loadNextImage();
            break;
        case UI_PREVIOUS_IMAGE_BUTTON:
            loadPreviousImage();
            break;
        case UI_FILE_NAME:
            setImageFile(m_fileName);
            break;
        case UI_UNDO:
            undoOperation();
            break;
        case UI_REDO:
            redoOperation();
            break;
        default:
            break;
    }

    // Forces canvas to update changes made in this function
    m_glui->post_update_main_gfx();
}

// **********************
// *** GLUI CALLBACKS ***

// Edit these functions to provide instructions
// for how MIAApp should respond to the
// button presses.

void MIAApp::loadImageToCanvas()
{
    if (m_displayBuffer) { delete m_displayBuffer; }
    m_displayBuffer = ImageHandler::loadImage(m_fileName);
    setWindowDimensions(m_displayBuffer->getWidth(), m_displayBuffer->getHeight());

    if(m_Mode)
    {
        cout << "Load Canvas has been clicked for file " << m_fileName << endl;
        // Determining whether there are next or previous images
        m_nextFileName = getImageNamePlusSeqOffset(m_fileName, 1);
        m_prevFileName = getImageNamePlusSeqOffset(m_fileName, -1);

        nextImageEnabled(isValidImageFile(m_nextFileName));
        previousImageEnabled(isValidImageFile(m_prevFileName));
    }
}

void MIAApp::saveCanvasToFile()
{
    if(m_Mode)
        cout << "Save Canvas has been clicked for file " << m_fileName << endl;
    if (ImageHandler::saveImage(m_fileName, m_displayBuffer)) {
        std::cout << "successfully saved image" << std::endl;
    } else {
        std::cout << "unsuccessfully saved image..." << std::endl;
    }
}

void MIAApp::loadImageToStamp()
{
    m_stampBuffer = ImageHandler::loadImage(m_fileName);
}

void MIAApp::applyFilterBlur()
{
    if(m_Mode) {
        undoPush();
        cout << "Apply has been clicked for Blur with amount = " << m_filterParameters.blur_amount << endl;
    }
    int radius = 1; //3x3 kernel
    Blur *blurFilter = new Blur(m_filterParameters.blur_amount,radius);
    blurFilter->applyToBuffer(m_displayBuffer);
    delete blurFilter;
}

void MIAApp::applyFilterThreshold()
{
    if(m_Mode) {
        undoPush();
        cout << "Apply has been clicked for Threshold has been clicked with amount =" << m_filterParameters.threshold_amount << endl;
    }
    fThreshold* thresholdFilter = new fThreshold(m_filterParameters.threshold_amount);
    thresholdFilter->applyToBuffer(m_displayBuffer);
    delete thresholdFilter;
}

void MIAApp::applyFilterMultiplyRGB()
{
    if(m_Mode) {
        undoPush();
        cout << "Apply has been clicked for Channels with red = " << m_filterParameters.multiply_colorRed
        << ", green = " << m_filterParameters.multiply_colorGreen
        << ", blue = " << m_filterParameters.multiply_colorBlue << endl;
    }
    fChannel *channelFilter = new fChannel(m_filterParameters.multiply_colorRed, m_filterParameters.multiply_colorGreen, m_filterParameters.multiply_colorBlue);
    channelFilter->applyToBuffer(m_displayBuffer);
    delete channelFilter;
}

void MIAApp::applyFilterGrayScale()
{
    cout << "Apply has been clicked for Grayscale" << endl;
    m_filterParameters.saturation_amount = 0;
    applyFilterSaturate();
}

void MIAApp::applyFilterSaturate()
{
    if(m_Mode) {
        undoPush();
        cout << "Apply has been clicked for Saturate with amount = " << m_filterParameters.saturation_amount << endl;
    }
    fSaturation* saturationFilter = new fSaturation(m_filterParameters.saturation_amount);
    saturationFilter->applyToBuffer(m_displayBuffer);
    delete saturationFilter;
}


void MIAApp::applyFilterSharpen()
{
    if(m_Mode) {
        undoPush();
        cout << "Apply has been clicked for Sharpen with amount = " << m_filterParameters.sharpen_amount << endl;
    }
    //3x3 kernel for sharpen for a subtler sharpen
    int radius =1;
    Sharpen *sharpenFilter = new Sharpen(m_filterParameters.sharpen_amount/50+1,radius);
    sharpenFilter->applyToBuffer(m_displayBuffer);
    delete sharpenFilter;
}

void MIAApp::applyFilterEdgeDetect() {
    if(m_Mode){
        undoPush();
        cout << "Apply has been clicked for Edge Detect" << endl;
    }
    EdgeDetect *edgeFilter = new EdgeDetect();
    edgeFilter->applyToBuffer(m_displayBuffer);
    delete edgeFilter;
}

void MIAApp::applyFilterQuantize() {
    if(m_Mode) {
        undoPush();
        cout << "Apply has been clicked for Quantize with bins = " << m_filterParameters.quantize_bins << endl;
    }
    fQuantize* quantizeFilter = new fQuantize(m_filterParameters.quantize_bins);
    quantizeFilter->applyToBuffer(m_displayBuffer);
    delete quantizeFilter;
}

void MIAApp::undoOperation()
{
    if(!m_undoStack.empty())
    {
        cout << "Undoing..." << endl;

        //create a copy of the current display
        PixelBuffer* tempHolder = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
        PixelBuffer::copyPixelBuffer(m_displayBuffer, tempHolder);

        //push that copy onto the redo stack.
        m_redoStack.push(tempHolder);

        //update the display buffer
        PixelBuffer::copyPixelBuffer(m_undoStack.top(), m_displayBuffer);

        //remove the now undone action from the stack.
        delete m_undoStack.top();
        m_undoStack.pop();
    }
    else
    {
        cout << "cannot undo, nothing to undo..." << endl;
        undoEnabled(false);
    }
    //update the status of the undo/redo buttons.
    redoEnabled(!m_redoStack.empty());
    undoEnabled(!m_undoStack.empty());
}

void MIAApp::undoPush()
{
    //create a copy of the current display
    PixelBuffer* tempHolder = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
    PixelBuffer::copyPixelBuffer(m_displayBuffer, tempHolder);

    //push the copy onto the undo stack
    m_undoStack.push(tempHolder);

    //update the undo/redo buttons
    redoEnabled(!m_redoStack.empty());
    undoEnabled(!m_undoStack.empty());
}

void MIAApp::undoRedoEmpty()
{
    //iterate through each stack while they have items and delete pointer and pop.
    while(!m_undoStack.empty())
    {
        delete m_undoStack.top();
        m_undoStack.pop();
    }
    while(!m_redoStack.empty())
    {
        delete m_redoStack.top();
        m_redoStack.pop();
    }
    //update the undo and redo buttons.
    undoEnabled(!m_undoStack.empty());
    redoEnabled(!m_redoStack.empty());
}

void MIAApp::redoOperation()
{
    //Just in case, checks to be sure the redo stack isn't empty
    if(!m_redoStack.empty())
    {
        cout << "Redoing..." << endl;
        //creates a copy of the current display
        PixelBuffer* temp = new PixelBuffer(m_displayBuffer->getWidth(), m_displayBuffer->getHeight(), m_displayBuffer->getBackgroundColor());
        PixelBuffer::copyPixelBuffer(m_displayBuffer, temp);

        //copy what is currently on the top of the stack to the display
        PixelBuffer::copyPixelBuffer(m_redoStack.top(), m_displayBuffer);

        //push a version of the copy onto the undo stack.
        m_undoStack.push(temp);

        //remove the now undone action from the redo stack.
        delete m_redoStack.top();
        m_redoStack.pop();
    }
    else
    {
        cout << "cannot undo, nothing to undo..." << endl;
        redoEnabled(false);
    }
    //update undo/redo buttons
    redoEnabled(!m_redoStack.empty());
    undoEnabled(!m_undoStack.empty());
}
// ** END OF CALLBACKS **
// **********************


// **********************
// Provided code for managing the
// GLUI interface.

void MIAApp::buttonEnabled(GLUI_Button * button, bool enabled) {
    if(enabled) button->enable();
    else button->disable();
    button->redraw();
}

void MIAApp::redoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.redoButton, enabled);
}

void MIAApp::undoEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.undoButton, enabled);
}

void MIAApp::saveCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.saveCanvasButton, enabled);
}

void MIAApp::loadCanvasEnabled(bool enabled)
{
    buttonEnabled(m_gluiControlHooks.loadCanvasButton, enabled);
}

void MIAApp::previousImageEnabled(bool enabled) {
    buttonEnabled(m_gluiControlHooks.previousImageButton, enabled);
}

void MIAApp::nextImageEnabled(bool enabled) {
    buttonEnabled(m_gluiControlHooks.nextImageButton, enabled);
}

void MIAApp::loadNextImage()
{
    setImageFile(m_nextFileName);
    loadImageToCanvas();
}

void MIAApp::loadPreviousImage()
{
    setImageFile(m_prevFileName);
    loadImageToCanvas();
}


bool MIAApp::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}

bool MIAApp::isValidImageFileName(const std::string & name) {

    if (hasSuffix(name, ".png")
        || hasSuffix(name, ".jpg")
        || hasSuffix(name, ".jpeg")
        )
        return true;
    else
        return false;
}

bool MIAApp::isValidImageFile(const std::string & name) {

    FILE *f;
    bool isValid = false;
    if (isValidImageFileName(name)) {
        if ((f = fopen( name.c_str(), "r"))) {
            isValid = true;
            fclose(f);
        }
    }


    return isValid;
}

std::string MIAApp::getImageNamePlusSeqOffset(const std::string & currentFileName, int offset)
{

    int digitCount = 3;

    std::string extension, name, number;
    size_t dotPos = currentFileName.find_last_of(".");
    if (dotPos ==  std::string::npos || dotPos == 0) {
        return "";
    }

    extension = currentFileName.substr(dotPos+1);
    name = currentFileName.substr(0,dotPos);
    if (name.length() < digitCount) {
        return "";
    }

    number = name.substr(name.length()-digitCount);
    name = name.substr(0,name.length()-digitCount);
    int num;
    std::istringstream ( number ) >> num;
    int output_num = num +offset;
    if (output_num < 0) {
        return "";
    }
    std::stringstream ss;
    ss << output_num;
    std::string output_number;
    ss >> output_number;

    // Append zero chars
    size_t str_length = output_number.length();
    for (int i = 0; i < digitCount - str_length; i++)
        output_number = "0" + output_number;





    return (name + output_number + "." + extension);
}

void MIAApp::initGraphics() {
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

void MIAApp::setImageFile(const std::string & fileName)
{
    // If a directory was selected
    // instead of a file, use the
    // latest file typed or selected.
    std::string imageFile = fileName;
    if (!isValidImageFileName(imageFile)) {
        imageFile = m_fileName;
    }


    // TOGGLE SAVE FEATURE
    // If no file is selected or typed,
    // don't allow file to be saved. If
    // there is a file name, then allow
    // file to be saved to that name.

    if (!isValidImageFileName(imageFile)) {
        m_gluiControlHooks.saveFileLabel->set_text("Will save image: none");
        saveCanvasEnabled(false);
    } else {
        m_gluiControlHooks.saveFileLabel->set_text((std::string("Will save image: ") + imageFile).c_str());
        saveCanvasEnabled(true);
    }

    // TOGGLE LOAD FEATURE

    // If the file specified cannot be opened,
    // then disable stamp and canvas loading.
    if (isValidImageFile(imageFile)) {
        loadCanvasEnabled(true);

        m_gluiControlHooks.currentFileLabel->set_text((std::string("Will load: ") + imageFile).c_str());
        m_gluiControlHooks.fileNameBox->set_text(imageFile);
    } else {
        loadCanvasEnabled(false);
        m_gluiControlHooks.currentFileLabel->set_text("Will load: none");
    }
}
