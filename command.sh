./configure --prefix=./compile --add-module=./ext

./configure --prefix=./mac --add-module=./ext

sudo ./compile/nginx/sbin/nginx

sudo ./compile/nginx/sbin/nginx -s stop