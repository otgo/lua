FROM debian:buster
LABEL com.telegram-bot.vendor="otgo"
LABEL com.telegram-bot.email="otgo@outlook.es"
ARG DEBIAN_FRONTEND=noninteractive
#VARIABLES
ENV CURL_VERSION=7.64.1
#CD_HOME
WORKDIR /home
#MKDIR_TELEGRAM-BOT
RUN mkdir telegram-bot
#APT_UPDATE
RUN apt-get update
#APT_UPGRADE
RUN apt-get upgrade -qq -y
#APT_UTILS
RUN apt-get install -y --assume-yes \
	apt-utils \
	dialog
#APT_PACKAGES
RUN apt-get install -y -qq \
	apt-transport-https \
	ca-certificates \
	build-essential \
	libssh2-1.dev \
	librtmp-dev \
	zlib1g-dev \
	libpsl-dev \
	libreadline-dev \
	software-properties-common \
	imagemagick \
	openssl \
	festival \
	libconfig-dev \
	libssl-dev \
	nano \
	net-tools \
	sysfsutils \
	libevent-dev \
	make \
	unzip \
	git \
	g++ \
	libjansson-dev \
	libpython-dev \
	expat \
	libexpat1-dev \
	subversion \
	wget \
	m4 \
	libgd-dev \
	libpng-dev \
	libgif-dev \
	libjpeg-dev \
	libncurses-dev
#CURL_INSTALL
WORKDIR /tmp
RUN wget -qO- https://curl.haxx.se/download/curl-${CURL_VERSION}.tar.gz | tar --transform 's/^dbt2-0.37.50.3/dbt2/' -xvz
WORKDIR curl-${CURL_VERSION}
RUN ./configure --with-ssl --with-ssh --with-rtmps --prefix=/usr
RUN make
RUN make install
#WFRS_INSTALL
WORKDIR /tmp
RUN wget https://raw.githubusercontent.com/otgo/qs/master/wfrs.c
RUN gcc wfrs.c -o /usr/bin/wfrs -lcurl
#CLEAN_ALL
RUN rm -r /tmp/*
#NGINX_DIR
RUN mkdir /var/www
RUN mkdir /var/www/html
