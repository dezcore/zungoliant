FROM gcc:latest

WORKDIR /zungoliant
COPY . .
RUN make clean
CMD ["make"]
