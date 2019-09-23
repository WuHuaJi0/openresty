DESTDIR ?= /home/wuhuaji/openresty/

.PHONY: all install clean

all:
	cd /home/wuhuaji/openresty/build/LuaJIT-2.1-20190507 && $(MAKE) TARGET_STRIP=@: CCDEBUG=-g XCFLAGS='-DLUAJIT_ENABLE_LUA52COMPAT -DLUAJIT_ENABLE_GC64 -msse4.2' CC=cc PREFIX=compile/luajit
	cd /home/wuhuaji/openresty/build/lua-cjson-2.1.0.7 && $(MAKE) DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/home/wuhuaji/openresty/build/luajit-root/compile/luajit/include/luajit-2.1 LUA_CMODULE_DIR=compile/lualib LUA_MODULE_DIR=compile/lualib CJSON_CFLAGS="-g -fpic" CC=cc
	cd /home/wuhuaji/openresty/build/lua-resty-signal-0.02 && $(MAKE) DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/home/wuhuaji/openresty/build/luajit-root/compile/luajit/include/luajit-2.1 LUA_LIB_DIR=compile/lualib CC=cc
	cd /home/wuhuaji/openresty/build/lua-redis-parser-0.13 && $(MAKE) DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/home/wuhuaji/openresty/build/luajit-root/compile/luajit/include/luajit-2.1 LUA_LIB_DIR=compile/lualib CC=cc
	cd /home/wuhuaji/openresty/build/lua-rds-parser-0.06 && $(MAKE) DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/home/wuhuaji/openresty/build/luajit-root/compile/luajit/include/luajit-2.1 LUA_LIB_DIR=compile/lualib CC=cc
	cd /home/wuhuaji/openresty/build/nginx-1.15.8 && $(MAKE)

install: all
	mkdir -p $(DESTDIR)./compile/
	-cp /home/wuhuaji/openresty/COPYRIGHT $(DESTDIR)./compile/
	cd /home/wuhuaji/openresty/build/LuaJIT-2.1-20190507 && $(MAKE) install TARGET_STRIP=@: CCDEBUG=-g XCFLAGS='-DLUAJIT_ENABLE_LUA52COMPAT -DLUAJIT_ENABLE_GC64 -msse4.2' CC=cc PREFIX=compile/luajit DESTDIR=$(DESTDIR)
	cd /home/wuhuaji/openresty/build/lua-cjson-2.1.0.7 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/home/wuhuaji/openresty/build/luajit-root/compile/luajit/include/luajit-2.1 LUA_CMODULE_DIR=compile/lualib LUA_MODULE_DIR=compile/lualib CJSON_CFLAGS="-g -fpic" CC=cc
	cd /home/wuhuaji/openresty/build/lua-resty-signal-0.02 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/home/wuhuaji/openresty/build/luajit-root/compile/luajit/include/luajit-2.1 LUA_LIB_DIR=compile/lualib CC=cc
	cd /home/wuhuaji/openresty/build/lua-redis-parser-0.13 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/home/wuhuaji/openresty/build/luajit-root/compile/luajit/include/luajit-2.1 LUA_LIB_DIR=compile/lualib CC=cc
	cd /home/wuhuaji/openresty/build/lua-rds-parser-0.06 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_INCLUDE_DIR=/home/wuhuaji/openresty/build/luajit-root/compile/luajit/include/luajit-2.1 LUA_LIB_DIR=compile/lualib CC=cc
	cd /home/wuhuaji/openresty/build/lua-resty-dns-0.21 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-memcached-0.14 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-redis-0.27 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-mysql-0.21 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-string-0.11 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-upload-0.10 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-websocket-0.07 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-lock-0.08 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-lrucache-0.09 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-core-0.1.17 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-upstream-healthcheck-0.06 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-limit-traffic-0.06 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-resty-shell-0.02 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/lua-tablepool-0.01 && $(MAKE) install DESTDIR=$(DESTDIR) LUA_LIB_DIR=compile/lualib INSTALL=/home/wuhuaji/openresty/build/install
	cd /home/wuhuaji/openresty/build/opm-0.0.5 && /home/wuhuaji/openresty/build/install bin/* $(DESTDIR)./compile/bin/
	cd /home/wuhuaji/openresty/build/resty-cli-0.24 && /home/wuhuaji/openresty/build/install bin/* $(DESTDIR)./compile/bin/
	cp /home/wuhuaji/openresty/build/resty.index $(DESTDIR)./compile/
	cp -r /home/wuhuaji/openresty/build/pod $(DESTDIR)./compile/
	cd /home/wuhuaji/openresty/build/nginx-1.15.8 && $(MAKE) install DESTDIR=$(DESTDIR)
	mkdir -p $(DESTDIR)./compile/site/lualib $(DESTDIR)./compile/site/pod $(DESTDIR)./compile/site/manifest
	ln -sf ./compile/nginx/sbin/nginx $(DESTDIR)./compile/bin/openresty

clean:
	rm -rf build
