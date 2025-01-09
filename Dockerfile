FROM ubuntu:latest

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    man-db \
    manpages \
    manpages-dev \
    g++ \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* 

COPY . .

CMD [ "bin/bash" ]