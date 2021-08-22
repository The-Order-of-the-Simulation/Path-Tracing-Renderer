echo
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
./OpenPT
echo
echo Test Complete!
echo