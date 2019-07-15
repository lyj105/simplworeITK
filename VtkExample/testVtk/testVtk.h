
#include <iostream>


#include "vtkSmartPointer.h"
#include "vtkImageViewer2.h"
#include "vtkDICOMImageReader.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"


#include "vtkPolyDataReader.h"
#include <vtkPolyDataWriter.h>
#include <vtkPolyDataReader.h>
#include "vtkPolyData.h"
#include "vtkPoints.h"
#include <vtkCellArray.h>

#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL);

#include "../../ImportLib.h"
class TestVtk {
    public:
		TestVtk();
		~TestVtk();
    public:
		//
		int tesstVtkReadDICOM(int agrc,char*argv[]);
		//
		int vtkPolygonsReadwriteExample(int agrc, char*argv[]);
	   



};