#!/bin/bash

fonctiondetest() {
   echo "Hello world !" $1
}

build() {
    cd zungoliantenv
    docker build -t zungoliantenv .
    cd ..
}

push() {
    build
    docker login -u dez28
    docker tag zungoliantenv dez28/zungoliantenv
    docker push dez28/zungoliantenv
}

clean() {
    docker compose down -v
}

run() {
    clean
    docker build -t zungoliant .
    docker compose up
}

if [[ "$1" == "test" ]];then
fonctiondetest
elif [[ "$1" == "run" ]];then
run
elif [[ "$1" == "build" ]];then
build
elif [[ "$1" == "push" ]];then
push
elif [[ "$1" == "clean" ]];then
clean
fi
#run