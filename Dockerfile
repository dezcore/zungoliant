FROM dez28/zungoliantenv as base

WORKDIR /zungoliant
COPY . .

#MakeFile
RUN make clean

FROM base as test
CMD ["make", "test"]

FROM base as dev
CMD ["make"]
