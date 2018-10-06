version="3.2.1" && \
wget "https://github.com/glfw/glfw/releases/download/${version}/glfw-${version}.zip" && \
unzip glfw-${version}.zip && \
cd glfw-${version} && \
sudo apt-get install cmake xorg-dev libglu1-mesa-dev libglew-dev && \
sudo cmake -G "Unix Makefiles" && \
sudo make && \
sudo make install && \
cd ..
