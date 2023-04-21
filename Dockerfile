FROM gcc:latest

WORKDIR /zungoliant
COPY . .
RUN cd lib/myhtml && make clean && make && make test && make install
RUN make clean
CMD ["make"]
