FROM ubuntu:xenial
LABEL com.telegram-bot.vendor="otgo"
LABEL com.telegram-bot.email="otgo@outlook.es"
ARG DEBIAN_FRONTEND=noninteractive
# VERSION_ARGS
ARG LUAROCKS_VERSION=2.2.2
# _
WORKDIR /home
RUN mkdir telegram-bot
RUN apt-get update
RUN apt-get upgrade -qq -y
RUN apt-get install -y --assume-yes \
	apt-utils
RUN apt-get install -y -qq \
	dialog
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
	lua5.2 \
	liblua5.2-dev \
	imagemagick \
	openssl \
	libcurl3 \
	libcurl3-openssl-dev \
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
	curl \
	wget
# LUAROCKS_INSTALL
WORKDIR /tmp
RUN wget -qO- http://luarocks.org/releases/luarocks-${LUAROCKS_VERSION}.tar.gz | tar --transform 's/^dbt2-0.37.50.3/dbt2/' -xvz
WORKDIR luarocks-${LUAROCKS_VERSION}
RUN ./configure
RUN make build
RUN make install
# LUAROCKS_LIBRARY
WORKDIR /tmp
RUN luarocks install luasocket
RUN luarocks install luasec
RUN luarocks install Lua-cURL CURL_DIR=/usr
RUN luarocks install std._debug
RUN luarocks install std.normalize
RUN luarocks install luaposix
RUN luarocks install dkjson
RUN luarocks install redis-lua
RUN luarocks install coxpcall
RUN luarocks install copas
RUN luarocks install --server=http://luarocks.org/dev ltn12
RUN luarocks install md5
RUN luarocks install serpent 2>/dev/stdout
RUN luarocks install lua-term
# WFRS_INSTALL
WORKDIR /tmp
COPY wfrs.c ./
RUN gcc wfrs.c -o /usr/bin/wfrs -lcurl
# _
RUN rm -r /tmp/*
RUN mkdir /var/www
RUN mkdir /var/www/html
WORKDIR /root
