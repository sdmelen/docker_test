FROM nginx

COPY nginx.conf /etc/nginx/nginx.conf
COPY hello.c /home/part5/hello.c
COPY build.sh /home/part5/build.sh

RUN apt-get update \
    && apt-get install -y \
    nginx \
    libfcgi-dev \
    gcc \
    spawn-fcgi \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /home/part5

RUN chown -R nginx:nginx /home/part5; \
    chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /var/cache/nginx; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid

USER nginx

ENTRYPOINT ["sh", "./build.sh"]

HEALTHCHECK NONE


