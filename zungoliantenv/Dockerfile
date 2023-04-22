FROM gcc:latest
WORKDIR /zungoliantenv
COPY . .
RUN apt-get update && apt-get -y install sudo
RUN cd lib/myhtml && make clean && make && make test && make install
RUN sudo ldconfig
