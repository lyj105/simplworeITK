#pragma once
#include "pch.h"
#include <iostream>

#include "itkImage.h" 
#include "itkImageFileReader.h" 
#include "itkImageFileWriter.h"
#include "itkImageToVTKImageFilter.h"
#include "itkCheckerBoardImageFilter.h"
#include "itkPNGImageIOFactory.h"

#include "itkRGBPixel.h"
//itk::PNGImageIOFactory::RegisterOneFactory();
//itk::TIFFImageIOFactory::RegisterOneFactory();
//itk::BMPImageIOFactory::RegisterOneFactory();

#include "vtkImageViewer.h"
#include "vtkRenderWindowInteractor.h"



#include "ImportLib.h"

class Solution {
    public:
		Solution();
		~Solution();
    public:
		//读取图像
		int readImageDataPng();
		int readImageDataITK();
		//读取图像并且vtk 显示出来
		int readImageDateVtk();
		//https//itk.org/ITKExamples/src/Filtering/ImageCompare/CombineTwoImagesWithCheckerBoardPattern/Documentation.html
		int CombineTwoImagesWithCheckerBoardPattern(int argc, char *argv[]);
		//使用 ITK 读取 RGB 图像并获取像素值
		int ImageFileReadeRGB(int argc, char * argv[]);
};