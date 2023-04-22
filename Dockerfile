FROM dez28/zungoliantenv

WORKDIR /zungoliant
COPY . .
RUN make clean
CMD ["make"]
