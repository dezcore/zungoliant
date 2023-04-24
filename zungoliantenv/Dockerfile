FROM gcc:latest
WORKDIR /zungoliantenv
COPY . .
RUN apt-get update && apt-get -y install sudo
RUN apt-get update && apt-get -y install cmake
RUN cd lib/myhtml && make clean && make && make test && make install
RUN cd lib/json-c && mkdir build && cd build && ../cmake-configure --prefix=/some/install/path && make
RUN sudo ldconfig
