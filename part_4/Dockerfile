FROM nginx

COPY nginx.conf /etc/nginx/nginx.conf
COPY hello.c /home/hello.c
COPY build.sh /home/build.sh

RUN apt-get update && apt-get install -y libfcgi-dev gcc spawn-fcgi

WORKDIR /home/

ENTRYPOINT ["sh", "./build.sh"]
