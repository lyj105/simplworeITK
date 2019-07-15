
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

//i中的基本图像操作
int Solution::readItkoperationData() {





	return 0;


};

//区域生长 连接门限
//区域生长算法被证实是一个有效的图像分割方法。区域生长的基本方法是从被分割对象
//里作为种子区域(通常是一个或多个像素)的一个区域开始，在种子区域的相邻像素寻找与种
//子像素有相同或相似性质的像素，并将这些像素合并到种子像素所在的区域中。将这些新像
//素当作新的种子区域继续进行上述过程。区域生长算法主要取决于用来选择确定为种子区域
//像素的标准、用来确定相邻像素的连通性类型和用来访问相邻像素的策略
//eg: F:\itk\softworeItk\workspace\testItk\x64\Debug\testItkGithub.exe 
//F:\itk\softworeItk\workspace\testItk\x64\Debug\testItkGithub.exe F:\b\BrainProtonDensitySlice.png F:\b\ConnectedThresholdWhiteTest.png 60 116 150 180 
int Solution::ConnectedThresholdImageFilter(int argc,char * argv[]) {

	using  InternalPixeltype=float;
	constexpr unsigned int Dimendsion = 2;
	using InternalImageType=itk::Image<InternalPixeltype, Dimendsion>;


	using OutputPixeltype = unsigned char;
	using OutputImageType = itk::Image<OutputPixeltype,Dimendsion>;

	using CastingFilterType =
		itk::CastImageFilter<InternalImageType, OutputImageType>;
	CastingFilterType::Pointer caster= CastingFilterType::New();

	using ReaderType = itk::ImageFileReader<InternalImageType>;
	using WriterType = itk::ImageFileWriter<OutputImageType>;

	ReaderType::Pointer reader=ReaderType::New();
	WriterType::Pointer writer = WriterType::New();

	itk::PNGImageIOFactory::RegisterOneFactory();

	reader->SetFileName(argv[1]);
    writer->SetFileName(argv[2]);

	//使用图像类型作为模板参数来对平滑滤波器进行实例化
	using CurvatureFlowImageFilter= 
		itk::CurvatureFlowImageFilter<InternalImageType, InternalImageType>;

	//然后调用 New( )方式来创建滤波器并将接指向 itk::SmartPointer：
	CurvatureFlowImageFilter::Pointer smoothing=CurvatureFlowImageFilter::New();

	//现在我们声明区域生长滤波器的类型
	using ConnectedFilterType = itk::ConnectedThresholdImageFilter<InternalImageType, InternalImageType>;

	//然后我们使用 New( )方式构造这种类的一个滤波器：
	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();

	/*现在到了连接一个简单的线性管道的时候。在管道的开头添加一个 reader 件头并在末尾
	  添加一个 cast filter 和 writer。由于只有一小部分图像文件格式支持浮点型数据类型，所以使
	  用 cast filter 将浮点型数据类型转换成整型*/
	smoothing->SetInput(reader->GetOutput());
	connectedThreshold->SetInput(smoothing->GetOutput());
	caster->SetInput(connectedThreshold->GetOutput());
	writer->SetInput(caster->GetOutput());

	/*CurvatureFlowImageFilter 需要定义两个参数。下面是一个二维图像的常见值。当然它们
	也需要根据输入图像存在的噪声的数量进行适当的调整*/
	smoothing->SetNumberOfIterations(5);
	smoothing->SetTimeStep(0.125);

	/*ConnectedThresholdImageFilter 有两个主要的参数需要定义，它们分别是为了确定是否
	  包含在区域中的亮度值而制定的标准的上门限和下门限。这两个值设定得太接近势必会降低
	  区域生长的机动性，而设定得太远必将整个图像都卷入区域中。*/

	const InternalPixeltype lowerThreshold = std::stod(argv[5]);
	const InternalPixeltype upperThreshold = std::stod(argv[6]);

	connectedThreshold->SetLower(lowerThreshold);
	connectedThreshold->SetUpper(upperThreshold);

	/*这个滤波器的输出是一个二值图像， 这个二值图像除了分割出的区域外到处都是零值像
		素。区域中的亮度值是由 SetReplaceValue()方式来选择*/
	connectedThreshold->SetReplaceValue(255);

	/*这个算法的实例化需要用户提供一个种子点。将这个点选在被分割的解剖学结构的典型
		区域是很便捷的。种子是以一种itk::Index的形式传递给SetSeed()方式的：*/
	InternalImageType::IndexType index;
	index[0] = std::stoi(argv[3]);
	index[1] = std::stoi(argv[4]);

	connectedThreshold->SetSeed(index);

	try
	{
		writer->Update();
	}
	catch (itk::ExceptionObject & excep)
	{
		std::cout << "Exception caught !" << std::endl;
		std::cout << excep << std::endl;
	}

	return EXIT_SUCCESS;
}