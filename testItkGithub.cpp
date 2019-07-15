// testItkGithub.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include "testitk.h"
#include "SigmoidImageFilter/SigmoidImageFilter.h"
#include "CoreCommon/headFile/BuildAHelloWorldProgram.h"
#include "./VtkExample/testVtk/testVtk.h"

int main(int argc, char *argv[])
{
	Solution* solu=new Solution;
	SigmoidImageFilter* sigmoidImage = new SigmoidImageFilter;
	


	int ret = EXIT_SUCCESS;
	//ret = solu->readImageDataITK();
	//ret=solu->readImageDateVtk();
	//ret = solu->CombineTwoImagesWithCheckerBoardPattern(argc,argv);
	//ret = solu->ImageFileReadeRGB(argc, argv);

	//区域生长 连接门限
	//ret=solu->ConnectedThresholdImageFilter(argc, argv);
	//const char *arv[] = {"F:\b\SigmoidImageFilter.png.png","F:\b\SigmoidImageFilter.pngTest.png","10", "240", "10", "107" },
	//sigmoidImage->ItkSigmoidImageFilter(argc, argv);

	CoreCommomImages* common = new CoreCommomImages;
	//common->ItkBuildAHelloWorldProgram(argc, argv);

	//common->CreateAImageRegion();


	//vtk
	
	TestVtk* testVtk = new TestVtk;
	//读取png 图片
	//testVtk->tesstVtkReadDICOM(argc, argv);

	testVtk->vtkPolygonsReadwriteExample(argc,argv);


	delete sigmoidImage;
	delete solu;
	delete common;
	delete testVtk;
	return ret;
}
