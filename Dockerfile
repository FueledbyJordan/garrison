FROM alpine:latest

RUN apk -U upgrade; \
apk add cmake; \
apk add make; \
apk add gtest; \
apk add python3; \
ln -s /usr/bin/python3 /usr/bin/python

WORKDIR .
