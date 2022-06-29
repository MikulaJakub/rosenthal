#include <iostream>

// Include VTK header files:
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkQuad.h>
#include <vtkPoints.h>
#include <vtkCellArray.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkDoubleArray.h>
#include <vtkPointData.h>

#define pi 3.14159265358979323846

using namespace std;
int main()
{
	cout << "Main program has started ... " << endl;

	// [[ INPUT PARAMETERS ]]
	// ---------------------------------------------
	// domain size (number of points):
	const int nx = 1200; 	// number of points
	const int ny = 200; 	// number of points

	// domain size (dimensions):
	const double LX = 0.12;			// [m]
	const double LY = 0.02;			// [m]

	// ambient temperature:
	const double T0 = 300.0;		// [K]
	// effective laser power:
	const double q = 840.0;			// [W]
	// conductivity coefficient:
	const double k = 35.0;			// [W/m/K]
	// specific heat:
	const double cp = 600.0;		// [J/kg/K]
	// density:
	const double rho = 7600.0;		// [kg/m^3]

	// laser speed (1000 mm/min):
	const double v = 1000.0/1000.0/60.0;	// [m/s]
	// ---------------------------------------------

	// temperature field:
	vtkSmartPointer<vtkDoubleArray> T = nullptr;
	T = vtkSmartPointer<vtkDoubleArray>::New();
	T->SetNumberOfComponents(1);
	T->SetName("Temperature [K]");
	T->SetNumberOfTuples(nx*ny);
	
	// Rosenthal's equation:
	int ip=0;
	for (int i=0; i<nx; i++)
	for (int j=0; j<ny; j++)
	{
		double a = k/rho/cp;
		double w = LX/double(nx-1)*double(i)-LX/2.0;
		double R = sqrt(w*w + pow(LY/double(ny-1)*double(j)-LY/2.0,2));
		double t = T0+q/2.0/pi/k/R*exp(-v*(w+R)/2.0/a);
		T->SetTuple1(ip, t);
		ip++;
	}

	// Create a polydata grid:
	vtkSmartPointer<vtkUnstructuredGrid> us = nullptr;
	us = vtkSmartPointer<vtkUnstructuredGrid>::New();

	vtkSmartPointer<vtkQuad> quad;
	quad = vtkSmartPointer<vtkQuad>::New();

	vtkSmartPointer<vtkCellArray> cells = vtkSmartPointer<vtkCellArray>::New();
	vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

	for (int j=0; j<nx; j++){
	for (int i=0; i<ny; i++){
		points->InsertNextPoint(LX/double(nx)*i, LY/double(ny)*j, 0.0);

	}
	}

	for (int j=0; j<nx-1; j++){		// number of cells
	for (int i=0; i<ny-1; i++){		// number of cells 
		quad->GetPointIds()->SetNumberOfIds(4);
		quad->GetPointIds()->SetId(0,nx*i+j);
		quad->GetPointIds()->SetId(1,nx*i+j+1);
		quad->GetPointIds()->SetId(2,nx*(i+1)+j+1);
		quad->GetPointIds()->SetId(3,nx*(i+1)+j);

		cells->InsertNextCell(quad);		
	}
	}

	us->SetPoints(points);
	us->SetCells(9,cells);

	// Add temperature data to grid:
	us->GetPointData()->AddArray(T);

	// Save as a .vtk file:
	vtkSmartPointer<vtkUnstructuredGridWriter> w = nullptr;
	w = vtkSmartPointer<vtkUnstructuredGridWriter>::New();
	w->SetInputData(us);
	w->SetFileName("rosenthal.vtk");
	w->Write();	

	cout << "Main program has finished!" << endl;
	return 0;
}
