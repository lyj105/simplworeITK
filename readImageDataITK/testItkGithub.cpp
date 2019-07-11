// testItkGithub.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

#include "testitk.h"

int main(int argc, char *argv[])
{
	Solution* solu=new Solution;

	int ret = EXIT_SUCCESS;
	//ret = solu->readImageDataITK();
	//ret=solu->readImageDateVtk();
	//ret = solu->CombineTwoImagesWithCheckerBoardPattern(argc,argv);
	//ret = solu->ImageFileReadeRGB(argc, argv);
	delete solu;



	return ret;
}

