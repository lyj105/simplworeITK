

//�������� ��������
//���������㷨��֤ʵ��һ����Ч��ͼ��ָ�������������Ļ��������Ǵӱ��ָ����
//����Ϊ��������(ͨ����һ����������)��һ������ʼ���������������������Ѱ������
//����������ͬ���������ʵ����أ�������Щ���غϲ��������������ڵ������С�����Щ����
//�ص����µ�����������������������̡����������㷨��Ҫȡ��������ѡ��ȷ��Ϊ��������
//���صı�׼������ȷ���������ص���ͨ�����ͺ����������������صĲ���
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

	//ʹ��ͼ��������Ϊģ���������ƽ���˲�������ʵ����
	using CurvatureFlowImageFilter= 
		itk::CurvatureFlowImageFilter<InternalImageType, InternalImageType>;

	//Ȼ����� New( )��ʽ�������˲���������ָ�� itk::SmartPointer��
	CurvatureFlowImageFilter::Pointer smoothing=CurvatureFlowImageFilter::New();

	//���������������������˲���������
	using ConnectedFilterType = itk::ConnectedThresholdImageFilter<InternalImageType, InternalImageType>;

	//Ȼ������ʹ�� New( )��ʽ�����������һ���˲�����
	ConnectedFilterType::Pointer connectedThreshold = ConnectedFilterType::New();

	/*���ڵ�������һ���򵥵����Թܵ���ʱ���ڹܵ��Ŀ�ͷ���һ�� reader ��ͷ����ĩβ
	  ���һ�� cast filter �� writer������ֻ��һС����ͼ���ļ���ʽ֧�ָ������������ͣ�����ʹ
	  �� cast filter ����������������ת��������*/
	smoothing->SetInput(reader->GetOutput());
	connectedThreshold->SetInput(smoothing->GetOutput());
	caster->SetInput(connectedThreshold->GetOutput());
	writer->SetInput(caster->GetOutput());

	/*CurvatureFlowImageFilter ��Ҫ��������������������һ����άͼ��ĳ���ֵ����Ȼ����
	Ҳ��Ҫ��������ͼ����ڵ����������������ʵ��ĵ���*/
	smoothing->SetNumberOfIterations(5);
	smoothing->SetTimeStep(0.125);

	/*ConnectedThresholdImageFilter ��������Ҫ�Ĳ�����Ҫ���壬���Ƿֱ���Ϊ��ȷ���Ƿ�
	  �����������е�����ֵ���ƶ��ı�׼�������޺������ޡ�������ֵ�趨��̫�ӽ��Ʊػή��
	  ���������Ļ����ԣ����趨��̫Զ�ؽ�����ͼ�񶼾��������С�*/

	const InternalPixeltype lowerThreshold = std::stod(argv[5]);
	const InternalPixeltype upperThreshold = std::stod(argv[6]);

	connectedThreshold->SetLower(lowerThreshold);
	connectedThreshold->SetUpper(upperThreshold);

	/*����˲����������һ����ֵͼ�� �����ֵͼ����˷ָ���������⵽��������ֵ��
		�ء������е�����ֵ���� SetReplaceValue()��ʽ��ѡ��*/
	connectedThreshold->SetReplaceValue(255);

	/*����㷨��ʵ������Ҫ�û��ṩһ�����ӵ㡣�������ѡ�ڱ��ָ�Ľ���ѧ�ṹ�ĵ���
		�����Ǻܱ�ݵġ���������һ��itk::Index����ʽ���ݸ�SetSeed()��ʽ�ģ�*/
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