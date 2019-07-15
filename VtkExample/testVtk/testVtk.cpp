//.#include "../pch.h"
#include "testVtk.h"

using namespace std;

TestVtk::TestVtk() {


};

TestVtk::~TestVtk() {

};


//cmake_minimum_required(VERSION 2.8)
//
//PROJECT(ReadDICOM)
//
//find_package(VTK REQUIRED)
//include(${ VTK_USE_FILE })
//
//add_executable(ReadDICOM MACOSX_BUNDLE ReadDICOM.cxx)
//
//if (VTK_LIBRARIES)
//target_link_libraries(ReadDICOM ${ VTK_LIBRARIES })
//else()
//target_link_libraries(ReadDICOM vtkHybrid vtkWidgets)
//endif()

int TestVtk::tesstVtkReadDICOM(int agrc, char*argv[]) {

	if (agrc!=2) {
		std::cout << "Usage: " << argv[0]
			<< " Filename(.img)" << std::endl;
		return EXIT_FAILURE;
	}

	std::string inputFilename = argv[1];

	//vtkSmartPointer<vtkDICOMImageReader> reader=
	//vtkSmartPointer<vtkDICOMImageReader>::New();

	vtkDICOMImageReader* reader = vtkDICOMImageReader::New();

	reader->SetFileName(inputFilename.c_str());
	try
	{
		reader->Update();
	}
	catch (std::exception & errs)
	{
		printf("%s", errs);
		//std::cerr << "Error: " << errs << std::endl;
		std::cerr << "Error: " << "¶ÁÈ¡Òì³£" << std::endl;
		return EXIT_FAILURE;
	}
	vtkSmartPointer<vtkImageViewer2> imagesViewer=
	vtkSmartPointer<vtkImageViewer2>::New();

	imagesViewer->SetInputConnection(reader->GetOutputPort());
	
	vtkSmartPointer<vtkRenderWindowInteractor> readerWindowInteracor=
	vtkSmartPointer<vtkRenderWindowInteractor>::New();


	imagesViewer->SetupInteractor(readerWindowInteracor);
	imagesViewer->Render();
	imagesViewer->GetRenderer()->ResetCamera();
	imagesViewer->Render();

	readerWindowInteracor->Start();

	return EXIT_FAILURE;


};


int TestVtk::vtkPolygonsReadwriteExample(int agrc, char*argv[]) {
	// read in the .vtk file
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	reader->SetFileName(argv[1]);
	reader->Update();

	vtkSmartPointer<vtkPolyData> polyData = vtkSmartPointer<vtkPolyData>::New();
	polyData = reader->GetOutput();

	// define a new vtkPoints object to hold the new points
	vtkSmartPointer<vtkPoints> point_new = vtkSmartPointer<vtkPoints>::New();

	// get access to the points
	for (unsigned int i = 0; i < polyData->GetNumberOfPoints(); i++) {
		double p[3];
		polyData->GetPoint(i, p);

		point_new->InsertNextPoint(p[0] + 0.1, p[1], p[2]); // translate by 0.2 in x direction to each point
	}

	// get access to polygons (points connectivity)
	vtkSmartPointer<vtkCellArray> polys = vtkSmartPointer<vtkCellArray>::New();
	polys = polyData->GetPolys();

	// save the scaled points and the polygons to a new vtkPolyData
	vtkSmartPointer<vtkPolyData> polyData_new = vtkSmartPointer<vtkPolyData>::New();
	polyData_new->SetPoints(point_new);
	polyData_new->SetPolys(polys);

	// save this new vtkPolyData to a new .vtk file (location specified by argv[2])
	vtkSmartPointer<vtkPolyDataWriter> polyDataWriter = vtkSmartPointer<vtkPolyDataWriter>::New();
	polyDataWriter->SetInputData(polyData_new);
	polyDataWriter->SetFileName(argv[2]);
	polyDataWriter->Update();

	std::cout << "---Finished!" << std::endl;

	return EXIT_FAILURE;
};