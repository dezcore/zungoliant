FROM gcc:latest
WORKDIR /zungoliantenv
COPY . .
RUN apt-get update && apt-get -y install sudo
RUN apt-get update && apt-get -y install cmake
#RUN cd lib/ && git clone git@github.com:lexborisov/myhtml.git
#RUN cd lib/ && git clone git@github.com:json-c/json-c.git
RUN cd lib/myhtml && make clean && make && make test && make install
RUN cd lib/ && mkdir json-c-build && cd json-c-build && cmake ../json-c 
RUN cd lib/json-c-build && make && make test && sudo make install
RUN sudo ldconfig
