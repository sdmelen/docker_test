#!/bin/bash

gcc -o hello hello.c -lfcgi
spawn-fcgi -p 8080 ./hello
# service nginx start
nginx -g 'daemon off;'
service nginx status