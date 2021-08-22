echo Generating CMake Project...
echo
cmake CMakeLists.txt
echo
echo Building Project...
echo
cmake --build ./
echo
echo Running Project...
echo
./pathtracingrenderer
echo
echo Test Complete!
echo