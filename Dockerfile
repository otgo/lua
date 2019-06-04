FROM debian:buster
LABEL com.telegram-bot.vendor="otgo"
LABEL com.telegram-bot.email="otgo@outlook.es"
ARG DEBIAN_FRONTEND=noninteractive
# VERSION_ARGS
ARG LUAROCKS_VERSION=3.1.2
ARG LUA_VERSION=5.3.5
ARG CURL_VERSION=7.64.1
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
	wget
# CURL_INSTALL
WORKDIR /tmp
RUN wget -qO- https://curl.haxx.se/download/curl-${CURL_VERSION}.tar.gz | tar --transform 's/^dbt2-0.37.50.3/dbt2/' -xvz
WORKDIR curl-${CURL_VERSION}
RUN ./configure --with-ssl --with-ssh --with-rtmps --prefix=/usr
RUN make
RUN make install
# LUA_INSTALL
WORKDIR /tmp
RUN wget -qO- http://www.lua.org/ftp/lua-${LUA_VERSION}.tar.gz | tar --transform 's/^dbt2-0.37.50.3/dbt2/' -xvz
WORKDIR lua-${LUA_VERSION}
RUN make linux test
RUN make install
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
RUN luarocks install lbase64
RUN luarocks install luafilesystem
RUN luarocks install cqueues
RUN luarocks install telegram
# WFRS_INSTALL
WORKDIR /tmp
RUN wget https://raw.githubusercontent.com/otgo/qs/master/wfrs.c
RUN gcc wfrs.c -o /usr/bin/wfrs -lcurl
# _
RUN rm -r /tmp/*
RUN mkdir /var/www
RUN mkdir /var/www/html
WORKDIR /root
