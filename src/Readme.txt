Using CMake:

Download CMake Version 3.22.0: https://cmake.org/download/

CMake GUI requires 2 things to build the executable:

location of the source, in our case ex:
C:/Users/Ivan/Desktop/Extracting-Requirements-From-Code/src

location of where to build the solution, in our case ex (CMake creates directories if not found):
C:/Users/Ivan/Desktop/Extracting-Requirements-From-Code/src/build

Click Generate and select which ever version of Visual Studio:
Ex. Visual Studio 16 2019

Leave the rest of the settings as default

Last step:

Drag and drop the "Test1.cpp" Test Case into the build folder that was generated
(This is for Debugging Purposes)

(I'm still looking into alternatives to this since Cmake only allows us to add code as
executables which is the exact opposite of what we want this program to analyze.
Although I don't think this will be a huge issue since down the line the user will be uploading
their desired file.)
