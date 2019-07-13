#include "../pch.h"
#include <iostream>

#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
//itk::PNGImageIOFactory::RegisterOneFactory();
//itk::TIFFImageIOFactory::RegisterOneFactory();
//itk::BMPImageIOFactory::RegisterOneFactory();
#include "itkPNGImageIOFactory.h"
#include "itkSigmoidImageFilter.h"

#include "../ImportLib.h"


//itk::SigmoidImageFilter 通常作为一个亮度变换使用。它通过在亮度值的一个特定范围的
//边界的一个非常平滑连续的转变将这个范围映射到一个新的亮度范围，是广泛使用 Sigmoids
//来作为关注值的一个设置并逐渐削弱范围之外的值的一个机制。为了扩展 Sigmoids 滤波器
//的机动性，使用四个参数通过选择它的输入、输出亮度范围来调节它在 ITK 中的执行。接
//下来的方程表达了 Sigmoids 亮度变换：

class SigmoidImageFilter {
    public:
		SigmoidImageFilter();
		~SigmoidImageFilter();
    public:
		int ItkSigmoidImageFilter(int agrc,char*argv[]);
	   



};