FROM gcc:latest

WORKDIR /zungoliant
COPY . .
RUN apt-get update && apt-get -y install sudo
RUN cd lib/myhtml && make clean && make && make test && make install
RUN sudo ldconfig
RUN make clean
CMD ["make"]
