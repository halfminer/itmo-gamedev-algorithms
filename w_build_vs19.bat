set BUILD_DIR=build_x64_VS2019
rmdir /S /Q %BUILD_DIR%
mkdir %BUILD_DIR%
cd %BUILD_DIR%
cmake ../ -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 16 2019"
cmake --build . --config=Debug -j 12
cmake ../ -DCMAKE_BUILD_TYPE=Release -G "Visual Studio 16 2019"
cmake --build . --config=Release -j 12
cd ..
