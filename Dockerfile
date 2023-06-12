FROM dez28/zungoliantenv as base

WORKDIR /zungoliant
COPY . .

#MakeFile
RUN make clean

FROM base as dev
RUN make
CMD ["./bin/main"]

FROM base as test
RUN make test
CMD ["./bin/test"]

FROM base as debug
RUN make

FROM base as debug_test
RUN make test
