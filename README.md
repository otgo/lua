# Q.S. docker image
###### Ducker Hub image with Lua and some required packages for Lua Telegram bots.

- [*Lua 5.2 with Ubuntu Xenial branch*](https://github.com/otgo/qs/tree/lua5.2)
  - Apt packages
     * apt-transport-https
     * ca-certificates
     * build-essential
     * libssh2-1.dev
     * librtmp-dev
     * zlib1g-dev
     * libpsl-dev
     * libreadline-dev
     * software-properties-common
     * lua5.2
     * liblua5.2-dev
     * imagemagick
     * openssl
     * libcurl3
     * libcurl3-openssl-dev
     * festival
     * libconfig-dev
     * libssl-dev
     * nano
     * net-tools
     * sysfsutils
     * libevent-dev
     * make
     * unzip
     * git
     * g++
     * libjansson-dev
     * libpython-dev
     * expat
     * libexpat1-dev
     * subversion
     * curl
     * wget
  - Compiled packages
     * LuaRocks 2.2.2
  - LuaRocks packages
     * luasocket
     * luasec
     * Lua-cURL
     * std._debug
     * std.normalize
     * luaposix
     * dkjson
     * redis-lua
     * coxpcall
     * copas
     * ltn12
     * md5
     * serpent
     * lua-term
  - **Required images** in docker-compose
     * redis:5.0

- [*Lua 5.3 with Debian Buster branch*](https://github.com/otgo/qs/tree/lua5.3)
  - Apt packages
     * apt-transport-https
     * ca-certificates
     * build-essential
     * libssh2-1.dev
     * librtmp-dev
     * zlib1g-dev
     * libpsl-dev
     * libreadline-dev
     * software-properties-common
     * imagemagick
     * openssl
     * festival
     * libconfig-dev
     * libssl-dev
     * nano
     * net-tools
     * sysfsutils
     * libevent-dev
     * make
     * unzip
     * git
     * g++
     * libjansson-dev
     * libpython-dev
     * expat
     * libexpat1-dev
     * subversion
     * wget
  - Compiled packages
     * LuaRocks 3.1.2
     * Lua 5.3.5
     * Curl 7.64.1
  - LuaRocks packages
     * luasocket
     * luasec
     * Lua-cURL
     * std._debug
     * std.normalize
     * luaposix
     * dkjson
     * redis-lua
     * coxpcall
     * copas
     * ltn12
     * md5
     * serpent
     * lua-term
  - **Required images** in docker-compose
     * redis:5.0
