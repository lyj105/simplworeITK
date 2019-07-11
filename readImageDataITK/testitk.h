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
		//��ȡͼ��
		int readImageDataPng();
		int readImageDataITK();
		//��ȡͼ����vtk ��ʾ����
		int readImageDateVtk();
		//https//itk.org/ITKExamples/src/Filtering/ImageCompare/CombineTwoImagesWithCheckerBoardPattern/Documentation.html
		int CombineTwoImagesWithCheckerBoardPattern(int argc, char *argv[]);
		//ʹ�� ITK ��ȡ RGB ͼ�񲢻�ȡ����ֵ
		int ImageFileReadeRGB(int argc, char * argv[]);
};