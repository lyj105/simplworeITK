
#include <iostream>

#include "itkImage.h"
#include "itkImageRegion.h"

#include "../../ImportLib.h"


class CoreCommomImages {
    public:
		CoreCommomImages();
		~CoreCommomImages();
    public:
		int ItkBuildAHelloWorldProgram(int agrc,char*argv[]);
		int CreateAImageRegion();
	   



};