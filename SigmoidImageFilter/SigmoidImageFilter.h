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


//itk::SigmoidImageFilter ͨ����Ϊһ�����ȱ任ʹ�á���ͨ��������ֵ��һ���ض���Χ��
//�߽��һ���ǳ�ƽ��������ת�佫�����Χӳ�䵽һ���µ����ȷ�Χ���ǹ㷺ʹ�� Sigmoids
//����Ϊ��עֵ��һ�����ò���������Χ֮���ֵ��һ�����ơ�Ϊ����չ Sigmoids �˲���
//�Ļ����ԣ�ʹ���ĸ�����ͨ��ѡ���������롢������ȷ�Χ���������� ITK �е�ִ�С���
//�����ķ��̱���� Sigmoids ���ȱ任��

class SigmoidImageFilter {
    public:
		SigmoidImageFilter();
		~SigmoidImageFilter();
    public:
		int ItkSigmoidImageFilter(int agrc,char*argv[]);
	   



};