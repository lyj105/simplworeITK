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
	



	//��������˲��������롢������غ�ͼ�����ͣ�
	using InputPixelType = unsigned char;
	using OutputPixelType = unsigned char;

	using InputImageType = itk::Image<InputPixelType,2>;
	using OutputImageType = itk::Image<OutputPixelType,2>;

	using ReaderType = itk::ImageFileReader<InputImageType>;
	using WriterType = itk::ImageFileWriter<OutputImageType>;

	//���ھͿ����� Reader ���������� Reader ����һ����::Pointer ����� itk::SmartPointer
	//ָ������ָ���´����� Reader������ New()����������ͼ�� Reader ��ʵ����
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
	  // ͼ��������ʵ�����˲������Ͳ������˲�������
	  using SigmoidFilterType = 
		    itk::SigmoidImageFilter<InputImageType,OutputImageType>;

	 SigmoidFilterType::Pointer  sigmoidFilter= SigmoidFilterType::New();

	 /*����е���Сֵ�����ֵ�ֱ�ʹ�� SetOutputMinimum()�� SetOutputMaximum()��ʽ��
		 ����*/
	 std::cout << "argv[3]" << argv[3] << std::endl;
	 std::cout << "argv[4]" << argv[4] << std::endl;

	 const OutputPixelType outputMinnum = std::stoi(argv[3]);
	 const OutputPixelType outputMaxnum = std::stoi(argv[4]);

	 sigmoidFilter->SetOutputMaximum(outputMaxnum);
	 sigmoidFilter->SetOutputMinimum(outputMinnum);

	 /*ʹ�� SetAlpha()�� SetBeta()������ϵ�� �� �� �¡�ע�� �� �Ǻ��������ȴ��ڳɱ����ġ���
	   �չ������ǿ���˵��������Ǽ��[-3���� 3��]�����ȴ��ڵı߽粢�����ԡ���ͼ 6 - 6 ��ʾ�� ��
	   ƽ�ȵؽӽ����ļ�ֵ��������ͨ����Χ���˿ھ�ֵ��Χ����һ�����[-3�ң� 3��]������һ��
	   �˿ڲ����ķ�Χʱ�������ͬ������ʽ�����п���*/
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
