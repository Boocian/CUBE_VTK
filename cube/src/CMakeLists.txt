cmake_minimum_required(VERSION 2.8)
 
PROJECT(Cube)
 
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
 
add_executable(Cube MACOSX_BUNDLE Cube)
 
if(VTK_LIBRARIES)
  target_link_libraries(Cube ${VTK_LIBRARIES})
else()
  target_link_libraries(Cube vtkHybrid vtkWidgets)
endif()