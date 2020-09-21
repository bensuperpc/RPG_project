cd build
#cmake .. && make -j 12
#Release/Debug/Coverage/MinSizeRel
cmake -DCMAKE_BUILD_TYPE=Release -G Ninja ..

ninja
#cp -R -u -p ../texture/rpg-pack texture/rpg-pack
ctest --output-on-failure #--extra-verbose

#make install 
