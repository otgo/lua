FROM otgo/qs:base
# LUA_INSTALL
ENV LUA_VERSION=5.3.5
WORKDIR /tmp
RUN wget -qO- http://www.lua.org/ftp/lua-${LUA_VERSION}.tar.gz | tar --transform 's/^dbt2-0.37.50.3/dbt2/' -xvz
WORKDIR lua-${LUA_VERSION}
RUN make linux test
RUN make install
RUN rm -r /tmp/*
WORKDIR /root
