FROM dez28/zungoliantenv as base

WORKDIR /zungoliant
COPY . .
RUN sudo apt-get install gnupg && curl -fsSL https://pgp.mongodb.com/server-6.0.asc | sudo gpg -o /usr/share/keyrings/mongodb-server-6.0.gpg --dearmor
RUN echo "deb [ arch=amd64,arm64 signed-by=/usr/share/keyrings/mongodb-server-6.0.gpg ] https://repo.mongodb.org/apt/ubuntu jammy/mongodb-org/6.0 multiverse" | sudo tee /etc/apt/sources.list.d/mongodb-org-6.0.list
RUN sudo apt-get update &&\
sudo apt-get install -y mongodb-org
RUN sudo apt-get install -y systemd
#RUN sudo systemctl start mongod
RUN make clean

FROM base as test
CMD ["make", "test"]

FROM base as dev
CMD ["make"]
