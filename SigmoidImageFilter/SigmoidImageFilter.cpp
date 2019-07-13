//.#include "../pch.h"
#include "SigmoidImageFilter.h"

SigmoidImageFilter::SigmoidImageFilter() {


};

SigmoidImageFilter::~SigmoidImageFilter() {

};

int SigmoidImageFilter::ItkSigmoidImageFilter(int argc, char*argv[]) {
	if (argc < 7)
	{
		std::cerr << "Usage: " << std::endl;
		std::cerr << argv[0] << "  inputImageFile   outputImageFile";
		std::cerr << " OutputMin OutputMax SigmoidAlpha SigmoidBeta" << std::endl;
		return EXIT_FAILURE;
	}
	



	//定义这个滤波器的输入、输出像素和图像类型：
	using InputPixelType = unsigned char;
	using OutputPixelType = unsigned char;

	using InputImageType = itk::Image<InputPixelType,2>;
	using OutputImageType = itk::Image<OutputPixelType,2>;

	using ReaderType = itk::ImageFileReader<InputImageType>;
	using WriterType = itk::ImageFileWriter<OutputImageType>;

	//现在就可以用 Reader 类型来创建 Reader 对象。一个由::Pointer 定义的 itk::SmartPointer
	//指针用来指向新创建的 Reader。调用 New()方法来创建图像 Reader 的实例。
	  ReaderType::Pointer reader=ReaderType::New();
	  WriterType::Pointer writer= WriterType::New();

	  itk::PNGImageIOFactory::RegisterOneFactory();
	  std::cout << "argv[1]" << argv[1] << std::endl;
	  std::cout << "argv[2]" << argv[2] << std::endl;

	  reader->SetFileName(argv[1]);
	  writer->SetFileName(argv[2]);

	  //  Software Guide : BeginLatex
	  //
	  //  Using the image types, we instantiate the filter type
	  //  and create the filter object.
	  //
	  //  \index{itk::SigmoidImageFilter!instantiation}
	  //  \index{itk::SigmoidImageFilter!New()}
	  //  \index{itk::SigmoidImageFilter!Pointer}
	  //
	  //  Software Guide : EndLatex
	  // Software Guide : BeginCodeSnippet
	  // 图像类型来实例化滤波器类型并创建滤波器对象
	  using SigmoidFilterType = 
		    itk::SigmoidImageFilter<InputImageType,OutputImageType>;

	 SigmoidFilterType::Pointer  sigmoidFilter= SigmoidFilterType::New();

	 /*输出中的最小值和最大值分别使用 SetOutputMinimum()和 SetOutputMaximum()方式来
		 定义*/
	 std::cout << "argv[3]" << argv[3] << std::endl;
	 std::cout << "argv[4]" << argv[4] << std::endl;

	 const OutputPixelType outputMinnum = std::stoi(argv[3]);
	 const OutputPixelType outputMaxnum = std::stoi(argv[4]);

	 sigmoidFilter->SetOutputMaximum(outputMaxnum);
	 sigmoidFilter->SetOutputMinimum(outputMinnum);

	 /*使用 SetAlpha()和 SetBeta()来设置系数 α 和 β。注意 α 是和输入亮度窗口成比例的。按
	   照惯例我们可以说这个窗口是间距[-3α， 3α]。亮度窗口的边界并不明显。如图 6 - 6 所示， α
	   平稳地接近它的极值。当你想通过在围绕人口均值周围定义一个间距[-3σ， 3σ]来设置一个
	   人口测量的范围时，你可以同样的形式来进行考虑*/
	 std::cout << "argv[5]" << argv[5] << std::endl;
	 std::cout << "argv[6]" << argv[6] << std::endl;
	 const double  alpha = std::stod(argv[5]);
	 const double  beta = std::stod(argv[6]);
	 std::cout << "argv[5]" << alpha << std::endl;
	 std::cout << "argv[6]" << beta << std::endl;

	 // Software Guide : BeginCodeSnippet
	 sigmoidFilter->SetAlpha(alpha);
	 sigmoidFilter->SetBeta(beta);

	 sigmoidFilter->SetInput(reader->GetOutput());
	 writer->SetInput(sigmoidFilter->GetOutput());

	 try
	 {
		 writer->Update();
	 }
	 catch (const itk::ExceptionObject * error)
	 {
		 std::cerr << "Error: " << error << std::endl;
		 return EXIT_FAILURE;
	 }

	 return EXIT_SUCCESS;
	
};
