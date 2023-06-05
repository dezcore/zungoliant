FROM gcc:latest
WORKDIR /zungoliantenv
COPY . .
RUN apt-get update && apt-get -y install sudo
RUN apt-get update && apt-get -y install cmake
RUN sudo apt-get install -y build-essential gdb
RUN sudo apt-get install -y valgrind
#RUN apt-get install -y libmongoc-1.0-0
RUN sudo apt-get install -y cmake libssl-dev libsasl2-dev
#RUN cd lib/ && git clone git@github.com:lexborisov/myhtml.git
#RUN cd lib/ && git clone git@github.com:json-c/json-c.git
#RUN cd lib/ && git clone https://github.com/mongodb/mongo-c-driver.git
RUN cd lib/myhtml && make clean && make && make test && make install
RUN cd lib/ && mkdir json-c-build && cd json-c-build && cmake ../json-c 
RUN cd lib/json-c-build && make && make test && sudo make install
RUN cd lib/mongo-c-driver && git checkout 1.23.4 && mkdir cmake-build && cd cmake-build && cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..
RUN cd lib/mongo-c-driver/cmake-build && cmake --build . && sudo cmake --build . --target install
RUN sudo ldconfig
