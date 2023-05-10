FROM dez28/zungoliantenv as base

WORKDIR /zungoliant
COPY . .
#RUN pkg-config --libs --cflags libmongoc-1.0
RUN make clean

FROM base as test
CMD ["make", "test"]

FROM base as dev
CMD ["make"]
