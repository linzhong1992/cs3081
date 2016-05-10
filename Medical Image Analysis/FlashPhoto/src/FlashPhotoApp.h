//
//  FlashPhotoApp.h
//  Originally created by the CSci-3081W TAs.
//

#ifndef FLASHPHOTOAPP_H
#define FLASHPHOTOAPP_H

#include "BaseGfxApp.h"
#include <stack>
//#include <zlib.h>

class ColorData;
class PixelBuffer;
class Tool;

///This is the Flashphoto app class. It utilizes the filters as well as the tools to edit images. It uses the libphoto library
class FlashPhotoApp : public BaseGfxApp {
public:

///initialize the Flashphoto app with the specified width, height, and backgroundColor
    FlashPhotoApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    ///destructor to free memory after exit
    virtual ~FlashPhotoApp();

    ///apply the current tool to the canvas at the inputted coordinates
    void mouseDragged(int x, int y) ;
    ///empty function. We did not have a use for mouse move
    void mouseMoved(int x, int y);
    ///apply the current tool to the canvas at the inputted coordinates
    void leftMouseDown(int x, int y);
    ///dont apply current tool to the canvas. setup undo and redo queue
    void leftMouseUp(int x, int y);
    ///initialize the canvas with the default colorData
    void display();
    ///this function is called with the controlID to determine which buttons on the FlashPhoto GUI are selected and will call the corresponding functions
    void gluiControl(int controlID);
    ///initialze the background buffer and the stamp buffer to the default colordata
    void initGraphics();

private:

    /// GLUI INTERFACE ELEMENTS: Tooltype, color, buttons
    enum UIControlType {
        UI_TOOLTYPE,
        UI_COLOR_R,
        UI_COLOR_G,
        UI_COLOR_B,
        UI_PRESET_RED,
        UI_PRESET_ORANGE,
        UI_PRESET_YELLOW,
        UI_PRESET_GREEN,
        UI_PRESET_BLUE,
        UI_PRESET_PURPLE,
        UI_PRESET_WHITE,
        UI_PRESET_BLACK,
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_LOAD_STAMP_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_BLUR,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_THRESHOLD,
        UI_APPLY_DITHER,
        UI_APPLY_SATURATE,
        UI_APPLY_CHANNEL,
        UI_APPLY_QUANTIZE,
        UI_APPLY_MOTION_BLUR,
        UI_APPLY_SPECIAL_FILTER,
        UI_UNDO,
        UI_REDO,
        UI_QUIT
    };

    ///set the image file name to be either loaded, saved, or loaded onto stamp
    void setImageFile(const std::string & filepath);
    ///not used in the most current version of FlashPhoto
    void read_png_file(const char *file_name);
    //void abort_(const char * s, ...);
    ///tests if the input string is a valid filename
    bool isValidImageFileName(const std::string & name);
    ///tests if the input string is a valid file
    bool isValidImageFile(const std::string & name);
    ///get the file type. png, jpg, etc.
    bool hasSuffix(const std::string & str, const std::string & suffix);
    ///make the input button enabled accordin gto the input bool
    void buttonEnabled(GLUI_Button * button, bool enabled);
    ///make the undo button enabled according to the input bool
    void undoEnabled(bool enabled);
    ///make the redo button enabled according to the input bool
    void redoEnabled(bool enabled);
    ///make the save canvas button enabled according to the input bool
    void saveCanvasEnabled(bool enabled);
    ///make the load canvas button enabled according to the input bool
    void loadCanvasEnabled(bool enabled);
    ///make the load stamp button enabled according to the input bool
    void loadStampEnabled(bool enabled);
    ///update the canvas colors to what is stored in the pixelbuffer
    void updateColors();

    ///load the current image to canvas
    void loadImageToCanvas();
    ///load the current image to stamp
    void loadImageToStamp();
    ///save the current canvas to specified file
    void saveCanvasToFile();

    ///apply blur filter to canvas
    void applyFilterBlur();
    ///apply sharpen filter to canvas
    void applyFilterSharpen();
    ///apply motionblur filter to canvas
    void applyFilterMotionBlur();
    ///apply edgedetect filter to canvas
    void applyFilterEdgeDetect();
    ///apply threshold filter to canvas
    void applyFilterThreshold();
    ///apply channel filter to canvas
    void applyFilterChannel();
    ///apply saturate filter to canvas
    void applyFilterSaturate();
    ///apply quantize filter to canvas
    void applyFilterQuantize();
    ///apply special filter to canvas
    void applyFilterSpecial();

    ///undo the last action done in the app
    void undoOperation();
    ///redo the last action done in the app
    void redoOperation();
    ///push the operation into the undo queue
    void undoPush();
    ///empty the undo queue
    void undoRedoEmpty();

    ///initialize all the visual aspects of FlashPhotoApp including all the buttons and input boxes as well as the radiobuttons
    void initGlui();

    ///initialize the default background buffer and the stamp buffer
    void initializeBuffers(ColorData initialColor, int width, int height);

    ///directions used for motionblur filter
    enum UIMotionBlurDirections {
        DIR_N_S,
        DIR_E_W,
        DIR_NE_SW,
        DIR_NW_SE
    };

    ///filter input parameters
    struct {
        float channel_colorRed;
        float channel_colorGreen;
        float channel_colorBlue;
        float saturation_amount;
        float threshold_amount;
        float blur_amount;
        float sharpen_amount;
        float motionBlur_amount;
        int motionBlur_direction;
        int quantize_bins;
    } m_filterParameters;
    ///buttons on the FlashPhotoApp
    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *loadStampButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;
        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;

        GLUI_Spinner *spinnerRed;
        GLUI_Spinner *spinnerGreen;
        GLUI_Spinner *spinnerBlue;



    } m_gluiControlHooks;




    /// This is the pointer to the buffer where the display PixelBuffer is stored
    PixelBuffer* m_displayBuffer;
	PixelBuffer* m_stampBuffer;
	///These are used to store the undo and redo stacks.
	std::stack <PixelBuffer*> m_undoStack;
	std::stack <PixelBuffer*> m_redoStack;

    /// These are used to store the selections from the GLUI user interface
    int m_curTool;
    ///array of pointers to tools
    Tool **m_tools;

    ///stores the current color selected
    float m_curColorRed, m_curColorGreen, m_curColorBlue;
    ///stores the filename of the filename inputted
    std::string m_fileName;

    /// Previous mouse coordinates for interpolating mouse moves
    int m_mouseLastX, m_mouseLastY;
    // int width, height;
    // png_byte color_type;
    // png_byte bit_depth;
    // png_bytep *row_pointers;
};


#endif
