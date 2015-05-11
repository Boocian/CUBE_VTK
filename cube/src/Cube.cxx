#include <iostream>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkTexture.h>
#include <vtkJPEGReader.h>
#include <vtkImageBlend.h>


 
int main(int, char *[])
{

	int *wsk_a = new int;
	double *wsk_b = new double;
	std::cout << "SetOpacity([int], [double])" << endl;
	std::cout << "[int] ";
	std::cin >> *wsk_a;
	std::cout << endl <<"[double] ";
	std::cin >> *wsk_b;


  //Tworzenie kostki
  vtkSmartPointer<vtkCubeSource> cubeSource = 
    vtkSmartPointer<vtkCubeSource>::New();

  //Tekstur1
  vtkSmartPointer<vtkJPEGReader> jpeg1 = 
	  vtkSmartPointer<vtkJPEGReader>::New();
  jpeg1->SetFileName("tekstura11.jpg");

  //Tekstura2
  vtkSmartPointer<vtkJPEGReader> jpeg2 =
	  vtkSmartPointer<vtkJPEGReader>::New();
  jpeg2->SetFileName("tekstura22.jpg");
  //jpeg->Update();

  //Blendowanie
  vtkSmartPointer<vtkImageBlend> blend =
	  vtkSmartPointer<vtkImageBlend>::New();
  blend->AddInputConnection(jpeg1->GetOutputPort()); 
  blend->AddInputConnection(jpeg2->GetOutputPort());
  blend->SetOpacity(*wsk_a, *wsk_b); //Zmienne kontrolowania przezroczystosci [int], [double]
  //blend->SetOpacity(7, .5);

  
  vtkSmartPointer<vtkTexture> tekxtura =
	  vtkSmartPointer<vtkTexture>::New();
  tekxtura->SetInputConnection(blend->GetOutputPort());
  tekxtura->InterpolateOn();
  

  // Tworzenie mappera i aktora
  vtkSmartPointer<vtkPolyDataMapper> mapper = 
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(cubeSource->GetOutputPort());
 
  vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);
  actor->SetTexture(tekxtura);


  //Renderowanie, renderowanie okna, interaktor
  vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
  renderWindow->SetSize(480, 480);


  //Dodawanie aktora
  renderer->AddActor(actor);

  //Tlo VTK
  renderer->SetBackground(255, 255, 255);
 
 
  //Renderowanie w oknie
  renderWindow->Render();
  renderWindowInteractor->Start();
  

  delete wsk_a;
  delete wsk_b;



  //system("pause");
 
  return EXIT_SUCCESS;
}