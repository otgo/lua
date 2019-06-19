FROM otgo/qs:base
ENV LUA_VERSION=5.2.4
ENV LUAROCKS_VERSION=3.1.2
#LUA_INSTALL
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
RUN luarocks install lua-captcha
#CLEAN_ALL
RUN rm -r /tmp/*
#CDROOT
WORKDIR /root
