cmake . -B ./temp/cmake_linux_wsl -Dgearmulator_BUILD_JUCEPLUGIN=OFF -DCMAKE_BUILD_TYPE=Release
cd ./temp/cmake_linux_wsl
cmake --build . --config Release
