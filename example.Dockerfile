FROM otgo/qs:lua5.3
#LUAROCKS_LIBRARY
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
