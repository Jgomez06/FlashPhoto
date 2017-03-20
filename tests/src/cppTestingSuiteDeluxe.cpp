#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <iostream>
#include <errno.h>      /* Errors */
#include <fstream>
#include <sstream>
#include <string>

#include "TSDApplicationController.h"
#include "cppTestingSuiteDeluxe.h"
#include "ColorData.h"
#include "CircleMask.h"
#include "RectangleMask.h"
#include "CircleLinearFalloffMask.h"
#include "StampTool.h"
#include "BlurTool.h"
#include "StamperMask.h"
#include "Image.h"
#include "JPEGImageAdaptor.h"
#include "MouseAction.h"

#include <cstddef>

bool cppTestingSuite::validateInput(int& argc, char* argv[])
{
        if(argc != 4){
          printf("Usage: [prog_name] [tool_type] [cmd_file] [base_image]\n");
          return false;
        }

        m_tool = getTool(argv[1]);
        if(m_tool == NULL){
                printf("Invalid tool name. Options are (case-sensitive): pen, eraser, caligraphy, highlighter, spray, special, stamp, and blur.\n");
                return false;
        }

	const std::string cmdFile(argv[2]);
	if(!hasSuffix(cmdFile, "txt")){
		printf("Invalid command file. Support types are: .txt\n");
		return false;	
	}

        if(argv[3] != NULL){
                const std::string fileName(argv[3]);
                if(!hasSuffix(fileName, "jpg")){
                        printf("Invalid base image type. Supported types are: jpeg. You gave: %s\n", argv[3]);
                        return false;
                }
        } else {
                printf("Invalid base image type, support types are: jpeg\n");
        }

        return true;
}

bool cppTestingSuite::hasSuffix(const std::string & str, const std::string & suffix){
    return str.find(suffix,str.length()-suffix.length()) != std::string::npos;
}


Tool* cppTestingSuite::getTool(char* toolName)
{
        std::string name(toolName);

        if(name.compare("pen") == 0){
		//printf("Creating a Pen\n");
                m_tool = new MaskTool(new CircleMask(3, 1), new ColorData(0,0,0), true);
		m_toolType = "pen";
	}
        else if(name.compare("caligraphy") == 0){ 
		//printf("Creating a Caligraphy Pen\n");
                m_tool = new MaskTool(new RectangleMask(5, 15), new ColorData(0,0,0), true);
		m_toolType = "caligraphy";
	}
        else if(name.compare("highlighter") == 0){
		//printf("Creating a Highlighter\n");
                m_tool = new MaskTool(new RectangleMask(5, 15, 0.3), new ColorData(0,0,0), true);
		m_toolType = "highlighter";
	}
        else if(name.compare("spray") == 0){
		//printf("Creating a Spray Can\n");
                m_tool = new MaskTool(new CircleLinearFalloffMask(41), new ColorData(0,0,0));
		m_toolType = "spray";
	}
        else if(name.compare("eraser") == 0){
		//printf("Creating an Eraser\n");
                m_tool = new MaskTool(new CircleMask(21),new ColorData(0,0,0), true);
		m_toolType = "eraser";
	}
        else if(name.compare("special") == 0){
		//printf("Creating a special tool\n");
                m_tool = new MaskTool(new StamperMask(41), new ColorData(0,0,0));
		m_toolType = "special";
	}
        else if(name.compare("stamp") == 0){
		//printf("Creating a stamp tool\n");
                StampTool* st = new StampTool();
		TSDApplicationController* appController = new TSDApplicationController();
	        Image image = appController->loadImage("stamp.jpg");
	        st->setImage(image);
		m_tool = st;
		m_toolType = "stamp";
	}
        else if(name.compare("blur") == 0){
		//printf("Creating a blur tool\n");
                m_tool = new BlurTool();
		m_toolType = "blur";
	}
        else{ 
                m_tool = NULL;
        }
        return m_tool;
}

std::vector<std::string> cppTestingSuite::split(std::string s, char delim) {
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

Image cppTestingSuite::simulateCmds(char *cmdFile)
{ 
	TSDApplicationController* appController = new TSDApplicationController();
	PixelBuffer* buf;
	if(m_toolType == "eraser")
    		buf = new PixelBuffer(800,800, new ColorData(0,0,0));
	else if(m_toolType == "blur") {
		Image image = appController->loadImage("nat.jpg");
		buf = new PixelBuffer(image.getWidth(), image.getHeight(), new ColorData(1,1,0.95));
		image.applyToBuffer(buf,0,0);
	} else
		buf = new PixelBuffer(800,800, new ColorData(1,1,0.95));

	ColorData* curColor = new ColorData(0,0,0);
	ColorData temp;
	MouseAction action;

	int x,y;
	float r,g,b;

	std::string cmds(cmdFile);
	cmds = "commands/" + cmds;
	std::ifstream file(cmds.c_str());
	std::string line;
	std::vector<std::string> lineElems;
	//std::cout << "Simulating commands..." << std::endl;

	while(std::getline(file, line)) {
		lineElems = split(line,' ');

		if(lineElems[0].compare("c") == 0)
			action = CLICK;
		else
			action = DRAG;
	
		x = atoi(lineElems[1].c_str());
		y = atoi(lineElems[2].c_str());

		if(m_toolType != "stamp" || m_toolType != "blur"){

			r = atof(lineElems[3].c_str());
			g = atof(lineElems[4].c_str());
			b = atof(lineElems[5].c_str());
		
			temp.setRed(r);
			temp.setGreen(g);
			temp.setBlue(b);

			curColor = &temp;
			m_tool->setColor(curColor);
		}	

		m_tool->onMouseAction(x, y, action, buf);
	}
	std::string fileName = "toolImages/" + m_toolType + "_sim" +  ".jpg";
	Image simImage = Image(buf->getWidth(), buf->getHeight(), buf->getData());
   	appController->saveImage(fileName, simImage);
    //std::cout << "Simulated Image is being saved, please wait." << std::endl;
    
    	return simImage;
}

int main(int argc, char* argv[]) 
{
        cppTestingSuite* cts = new cppTestingSuite();
        bool validInput = cts->validateInput(argc, argv);

        if(!validInput){
                return 0;
        } else {
		TSDApplicationController* appController = new TSDApplicationController();
			
		cts->simulateCmds(argv[2]);
		sleep(4);
		std::string sim = "toolImages/" + cts->m_toolType + "_sim" + ".jpg";
		Image simImage = appController -> loadImage(sim);
		
		std::string name(argv[3]);	
		std::string inputImage = "toolImages/" + name;
		Image baseImage = appController -> loadImage(inputImage);
		//std::cout << "Comparing simulation image to baseline..." << std::endl;
		bool result = simImage == baseImage;
		std::cout << "\n" << cts->m_toolType << " TEST RESULT (1 = SUCCESS | 0 = FAILURE): " << result << "\n" << std::endl;
	}

        return 0;
}

