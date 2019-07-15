//.#include "../pch.h"
#include "../../CoreCommon/headFile/BuildAHelloWorldProgram.h"

CoreCommomImages::CoreCommomImages() {


};

CoreCommomImages::~CoreCommomImages() {

};

//Templated n - dimensional image class.
//
//Images are templated over a pixel type(modeling the dependent variables), and a dimension(number of independent variables).The container for the pixel data is the ImportImageContainer.
//
//Within the pixel container, images are modelled as arrays, defined by a start index and a size.
//
//The superclass of Image, ImageBase, defines the geometry of the image in terms of where the image sits in physical space, how the image is oriented in physical space, the size of a pixel, and the extent of the image itself.ImageBase provides the methods to convert between the index and physical space coordinate frames.
//
//Pixels can be accessed direcly using the SetPixel() and GetPixel() methods or can be accessed via iterators that define the region of the image they traverse.
//
//The pixel type may be one of the native types; a Insight - defined class type such as Vector; or a user - defined type.Note that depending on the type of pixel that you use, the process objects(i.e., those filters processing data objects) may not operate on the image and/or pixel type.This becomes apparent at compile - time because operator overloading (for the pixel type) is not supported.
//
//The data in an image is arranged in a 1D array as[][][][slice][row][col] with the column index varying most rapidly.The Index type reverses the order so that with Index[0] = col, Index[1] = row, Index[2] = slice, .
//
int CoreCommomImages::ItkBuildAHelloWorldProgram(int argc, char*argv[]) {

	using ImageType=itk::Image<unsigned short, 3>;

	ImageType::Pointer Image=ImageType::New();

	std::cout << "itk hello world" << std::endl;

	std::cout << Image << std::endl;
	
	 return EXIT_SUCCESS;
	
};

int CoreCommomImages::CreateAImageRegion() {

	constexpr unsigned int Dimension = 2;

	using RegionType=itk::ImageRegion<Dimension>;

	RegionType::SizeType size;
	size.Fill(3);

	RegionType::IndexType index;
	index.Fill(1);

	RegionType region(index,size);

	std::cout << region << std::endl;

	return EXIT_SUCCESS;




};
