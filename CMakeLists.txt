#The cmake file creates the executable files needed for creating the simulation

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation)

#--- ROOT built with CMake. Add in CMAKE_PREFIX_PATH the installation prefix for ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})

foreach(path ${CMAKE_PREFIX_PATH})
  message("Path: " ${path})
endforeach(path)

#---Locate the ROOT package and defines a number of variables (e.g. ROOT_INCLUDE_DIRS)
find_package(ROOT REQUIRED COMPONENTS RIO Hist Tree Net RooFit RooStats RooFitCore)


#---Define useful ROOT functions and macros (e.g. ROOT_GENERATE_DICTIONARY)
include(${ROOT_USE_FILE})

add_definitions(${ROOT_CXX_FLAGS})


#packages to be included, Geant4 is mandatory, ui_all is for user interface and 
# vi_all is for creating a visual interface (if needed).
find_package(Geant4 REQUIRED ui_all vis_all)
#find_package(ROOT)

#including the packages inside the written path
include(${Geant4_USE_FILE})
#include(${ROOT_USE_FILE})
#include_directories(${ROOT_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR})
#link_directories(${ROOT_LIBRARY_DIR})

#For putting several classes and files inside the project
file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

# for creating the executables
add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})

target_link_libraries(sim ${ROOT_LIBRARIES})


add_custom_target(Simulation DEPENDS sim)
