FROM alpine:latest

ENV CC /usr/bin/gcc
ENV CXX /usr/bin/g++

RUN apk -U upgrade; \
apk add g++; \
apk add make; \
apk add cmake; \
apk add gtest; \
apk add python3; \
apk add curl; \
ln -s /usr/bin/python3 /usr/bin/python; \
curl -L https://github.com/jarro2783/cxxopts/archive/v2.2.1.tar.gz | tar -xz && mkdir cxxopts-2.2.1/build && cd cxxopts-2.2.1/build && cmake .. && make -j 4 && make install && cd / && rm -rf cxxopts-2.2.1

COPY . /usr/src/garrison
WORKDIR /usr/src/garrison
