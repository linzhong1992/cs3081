//
//  MIAApp.h
//  Originally created by the CSci-3081W TAs.
//


#ifndef MIAAPP_H
#define MIAAPP_H

#include "BaseGfxApp.h"
#include <stack>

class ColorData;
class PixelBuffer;
class Tool;

///This is the MIA application main file. It can be used in GUI mode as well as command line mode. It utilizes filters as well as tools to edit images. Uses the libphoto library
class MIAApp : public BaseGfxApp {
public:
    ///This is the constructor that initializes canvas' height, width and background color.
    MIAApp(int argc, char* argv[], int width, int height, ColorData backgroundColor);
    virtual ~MIAApp();

    /// Glut overrided function, called back in Glut.
    void mouseDragged(int x, int y) ;
    /// Glut overrided function, called back in Glut.
    void mouseMoved(int x, int y);
    /// Glut overrided function, called back in Glut.
    void leftMouseDown(int x, int y);
    /// Glut overrided function, called back in Glut.
    void leftMouseUp(int x, int y);
    /// Glut overrided function, called back in Glut.
    void display();
    /// Glut overrided function, called back in Glut.
    void gluiControl(int controlID);
    /// Initialize OpenGL for 2D graphics.
    void initGraphics();
    /** This function handles command-line input in MIAApp. It parses any possible inputs,
    and makes use of many functions that relates filter, image saving/loading, etc.. Moreover,
    It makes use of three helper functions: getImageFiles(), isValidDir() and compare().*/
    void parser();
    /** A helper function that is called in parser(). It loops through all image
    files in a directory, and store theses image file names into a string vector.*/
    void getImageFiles(const std::string & dirName, std::vector<std::string> & fileNames);
    /** A helper function that is called in parser(). It checks if it is valid a directory.*/
    bool isValidDir(const std::string & name);
    /** A helper function that is called in parser(). It compares a
    new displayBuffer, whose pointer is taken as an argument,
    with the member variable m_displayBuffer.*/
    bool compare(PixelBuffer* new_m_displayBuffer);

private:

    /// GLUI INTERFACE ELEMENTS
    enum UIControlType {
        UI_TOOLTYPE,
        UI_FILE_BROWSER,
        UI_LOAD_CANVAS_BUTTON,
        UI_SAVE_CANVAS_BUTTON,
        UI_NEXT_IMAGE_BUTTON,
        UI_PREVIOUS_IMAGE_BUTTON,
        UI_FILE_NAME,
        UI_APPLY_SHARP,
        UI_APPLY_EDGE,
        UI_APPLY_THRESHOLD,
        UI_APPLY_GRAYSCALE,
        UI_APPLY_MULTIPLY_RGB,
        UI_APPLY_QUANTIZE,
        UI_UNDO,
        UI_REDO,
        UI_QUIT
    };
    void setImageFile(const std::string & filepath);
    bool isValidImageFileName(const std::string & name);
    bool isValidImageFile(const std::string & name);
    bool hasSuffix(const std::string & str, const std::string & suffix);
    std::string getImageNamePlusSeqOffset(const std::string & currentFileName, int offset);
    void buttonEnabled(GLUI_Button * button, bool enabled);
    void undoEnabled(bool enabled);
    void redoEnabled(bool enabled);
    void saveCanvasEnabled(bool enabled);
    void loadCanvasEnabled(bool enabled);
    void previousImageEnabled(bool enabled);
    void nextImageEnabled(bool enabled);

    void loadImageToCanvas();
    void loadImageToStamp();
    void saveCanvasToFile();
    void loadNextImage();
    void loadPreviousImage();

    void applyFilterSharpen();
    void applyFilterEdgeDetect();
    void applyFilterThreshold();
    void applyFilterMultiplyRGB();
    void applyFilterSaturate();
    void applyFilterGrayScale();
    void applyFilterQuantize();
    void applyFilterBlur();

    void undoOperation();
    void redoOperation();
    void undoPush();
    void undoRedoEmpty();


    void initGlui();
    void initializeBuffers(ColorData initialColor, int width, int height);


    struct {
        float multiply_colorRed;
        float multiply_colorGreen;
        float multiply_colorBlue;
        float threshold_amount;
        float sharpen_amount;
        float saturation_amount;
        float blur_amount;
        int quantize_bins;
    } m_filterParameters;

    struct {
        GLUI_FileBrowser* fileBrowser;
        GLUI_Button *loadCanvasButton;
        GLUI_Button *saveCanvasButton;
        GLUI_Button* nextImageButton;
        GLUI_Button* previousImageButton;
        GLUI_Button *redoButton;
        GLUI_Button *undoButton;
        GLUI_StaticText * currentFileLabel;
        GLUI_EditText* fileNameBox;
        GLUI_StaticText * saveFileLabel;
    } m_gluiControlHooks;


    /// This is the pointer to the buffer where the display PixelBuffer is stored.
    PixelBuffer* m_displayBuffer;
    /// This is the pointer to the buffer where the stamp PixelBuffer is stored.
    PixelBuffer* m_stampBuffer;
    /// It is used to store the undo and undo stacks.
    std::stack <PixelBuffer*> m_undoStack;
    /// It is used to store the undo and redo stacks.
    std::stack <PixelBuffer*> m_redoStack;

    /// It is used to store the selections from the GLUI user interface.
    int m_curTool;
    /// It is used to store the selections from the GLUI user interface.
    Tool **m_tools;
    /// It is used to store the selections from the GLUI user interface.
    std::string m_fileName;
    /// It is used to store the selections from the GLUI user interface.
    std::string m_nextFileName;
    /// It is used to store the selections from the GLUI user interface.
    std::string m_prevFileName;

    /// It is used to store the selections from the GLUI user interface.
    float m_curColorRed, m_curColorGreen, m_curColorBlue;

    /// It is used to interpolate gaps between points when drawing.
    int m_mouseLastX, m_mouseLastY;
    /// Number of command-line tokens are stored as member variables.
    int m_argc;
    /// Command-line inputs are stored as member variables.
    char** m_argv;
    /// "true" means command-line mode, while "false" means GLUI mode.
    bool m_Mode;
};


#endif
