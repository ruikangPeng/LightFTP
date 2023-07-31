FROM ubuntu:latest

# 安装依赖
RUN apt update && \
	apt-get update && \
	apt-get -y install sudo \
	vim \
	git \
	openssh-server \
	net-tools \
	gcc \
	automake \
	autoconf \
	libtool \
	make \
	clang \
	apt-utils \
	build-essential \
	openssl \
	libgnutls-dev \
	gnutls-dev \
	telnet
	
# 添加一个新用户 ubuntu，pass:ubuntu
RUN groupadd ubuntu && \
	useradd -rm -d /home/ubuntu -s /bin/bash -g ubuntu -G sudo -u 1000 ubuntu -p "$(openssl passwd -1 ubuntu)"
	
# 使用 ubuntu 作为默认用户名
USER ubuntu
WORKDIR /home/ubuntu

# 下载并编译 LightFTP
RUN cd /home/ubuntu && \
    git clone https://github.com/ruikangPeng/LightFTP.git && \
    cd LightFTP/Source/Release && \
    CC=clang make clean all
