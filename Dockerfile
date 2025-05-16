FROM ubuntu:22.04
RUN apt-get update && \
    apt-get install -y cmake g++ python3 python3-pip build-essential git && \
    apt-get clean
WORKDIR /app
COPY . .
RUN cmake . && make
ENTRYPOINT ["./bloomserver"]