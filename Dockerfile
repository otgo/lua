FROM otgo/qs:base
#VARIABLES
ENV LUA_VERSION=5.1.5
ENV LUAROCKS_VERSION=3.1.2
#LUA_INSTALL
WORKDIR /tmp
RUN wget -qO- http://www.lua.org/ftp/lua-${LUA_VERSION}.tar.gz | tar --transform 's/^dbt2-0.37.50.3/dbt2/' -xvz
WORKDIR lua-${LUA_VERSION}
RUN make linux test
RUN make install
#LUAROCKS_INSTALL
WORKDIR /tmp
RUN wget -qO- http://luarocks.org/releases/luarocks-${LUAROCKS_VERSION}.tar.gz | tar --transform 's/^dbt2-0.37.50.3/dbt2/' -xvz
WORKDIR luarocks-${LUAROCKS_VERSION}
RUN ./configure
RUN make build
RUN make install
#CLEAN_ALL
RUN rm -r /tmp/*
#CD_ROOT
WORKDIR /root
