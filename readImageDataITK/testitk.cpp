
#include "pch.h"
#include "testitk.h"

Solution::Solution() {


};

Solution::~Solution() {

};

int Solution::readImageDataPng() {

	const unsigned int Dimension = 2;                                          //定义图像维数 
	//typedef unsigned char                                     PixelType;      //定义像素类型 
	typedef itk::RGBPixel< unsigned char >   PixelType;
	typedef itk::Image< PixelType, 2 >       ImageType;

	typedef itk::ImageFileReader< ImageType >  ReaderType;
	typedef itk::ImageFileWriter< ImageType >  WriterType;
	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	itk::PNGImageIOFactory::RegisterOneFactory();

	reader->SetFileName("F:\\b\\untitled.png");
	writer->SetFileName("F:\\b\\untitled2.png");

	ImageType::Pointer image = reader->GetOutput();
	writer->SetInput(image);

	//  Aliased to the Write() method to be consistent with the rest of the pipeline.
	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
		return EXIT_FAILURE;
	}


};

int Solution::readImageDataITK() {

	typedef itk::RGBPixel< unsigned char >   PixelType;
	typedef itk::Image< PixelType, 2 >       ImageType;//set the type of pic

	// Software Guide : BeginCodeSnippet
	typedef itk::ImageFileReader< ImageType >  ReaderType;
	typedef itk::ImageFileWriter< ImageType >  WriterType;

	ReaderType::Pointer reader = ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	itk::PNGImageIOFactory::RegisterOneFactory();

	reader->SetFileName("F:\\b\\untitled.png");
	writer->SetFileName("F:\\b\\untitled11.png");
	// Software Guide : EndCodeSnippet

	ImageType::Pointer image = reader->GetOutput();
	writer->SetInput(image);
	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;



};

int Solution::readImageDateVtk() {
	typedef itk::Image<unsigned short, 2> ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;   //图像读取类
	typedef itk::ImageToVTKImageFilter<ImageType> ConnectorType;  //VTK和ITK链接器

	ReaderType::Pointer reader = ReaderType::New();
	ConnectorType::Pointer connector = ConnectorType::New();

	const char* fileName = "F:\\b\\lena.png";

	reader->SetFileName(fileName);
	connector->SetInput(reader->GetOutput());
	connector->Update();

	vtkImageViewer *viewer = vtkImageViewer::New();
	vtkRenderWindowInteractor *interactor = vtkRenderWindowInteractor::New();
	viewer->SetInputData(connector->GetOutput());
	viewer->SetupInteractor(interactor);
	viewer->SetColorWindow(255); //设置窗宽
	viewer->SetColorLevel(128);   //设置窗位
	viewer->Render();
	interactor->Initialize();
	interactor->Start();
	return EXIT_SUCCESS;
};



int Solution::CombineTwoImagesWithCheckerBoardPattern(int argc, char *argv[]) {
	if (argc != 2)
	{
		std::cerr << "Usage:" << std::endl;
		std::cerr << argv[0] << " <OutputImage>" << std::endl;
		return EXIT_FAILURE;
	}

	constexpr unsigned int Dimension = 2;

	using PixelType = unsigned char;
	using ImageType = itk::Image< PixelType, Dimension >;

	ImageType::IndexType start;
	start.Fill(0);

	ImageType::SizeType size;
	size.Fill(100);

	ImageType::RegionType region;
	region.SetSize(size);
	region.SetIndex(start);

	ImageType::Pointer image1 = ImageType::New();
	image1->SetRegions(region);
	image1->Allocate();
	image1->FillBuffer(0);

	ImageType::Pointer image2 = ImageType::New();
	image2->SetRegions(region);
	image2->Allocate();
	image2->FillBuffer(255);

	using CheckerBoardFilterType = itk::CheckerBoardImageFilter< ImageType >;
	CheckerBoardFilterType::Pointer checkerBoardFilter =
		CheckerBoardFilterType::New();
	checkerBoardFilter->SetInput1(image1);
	checkerBoardFilter->SetInput2(image2);

	using WriterType = itk::ImageFileWriter< ImageType >;
	WriterType::Pointer writer = WriterType::New();
	writer->SetInput(checkerBoardFilter->GetOutput());
	writer->SetFileName(argv[1]);

	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;

};


//https://blog.imalan.cn/archives/66/   ok
int Solution::ImageFileReadeRGB(int argc, char * argv[]) {
	//声明一些参量类型
	//指定图片像素类型为RGB,unsigned char,2维平面图
	//通过指定的图像类型声明图像读取器



	typedef itk::RGBPixel<unsigned char>PixelType;
	typedef itk::Image<PixelType, 2>ImageType;
	typedef itk::ImageFileReader<ImageType> ReaderType;

	//创建图像读取器
	ReaderType::Pointer reader = ReaderType::New();

	itk::PNGImageIOFactory::RegisterOneFactory();

	//从命令行参数获取文件路径，并设置给reader
	const char* filename = "F:\\b\\lena.png";
	reader->SetFileName(filename);
	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject & error)
	{
		std::cerr << "Error: " << error << std::endl;

	}
	//声明图像object，并与读取器输出绑定
	ImageType::Pointer image = ImageType::New();
	image = reader->GetOutput();

	//itk中访问图像数据需要通过Index，Index在这里理解成一个数组
	//维数与图像维数对应
	//并设置要访问的位置[0,0]
	ImageType::IndexType pixcelIndex;
	pixcelIndex[0] = 0;//列数
	pixcelIndex[1] = 0;//行数

	//获取图像的像素数据
	PixelType pixel1 = image->GetPixel(pixcelIndex);
	PixelType::ValueType red = pixel1.GetRed();
	PixelType::ValueType green = pixel1.GetGreen();
	PixelType::ValueType blue = pixel1.GetBlue();

	//输出数据，注意，itk中的像素数据需要由专门的模块来处理
	cout << "get pixel at [0,0]:" << endl;
	cout << "R:" << itk::NumericTraits<PixelType::ValueType>::PrintType(red) << endl;
	cout << "G:" << itk::NumericTraits<PixelType::ValueType>::PrintType(green) << endl;
	cout << "B:" << itk::NumericTraits<PixelType::ValueType>::PrintType(blue) << endl;

	return 0;


};