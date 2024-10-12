FROM nginx

RUN apt-get update && \
    apt-get install -y \
        libfcgi-dev \
        gcc \
        spawn-fcgi \
    && rm -rf /var/lib/apt/lists/*

COPY nginx.conf /etc/nginx/nginx.conf
COPY build.sh /home/part5/build.sh

RUN chown -R nginx:nginx /home/part5; \
    chown -R nginx:nginx /etc/nginx/nginx.conf; \
    chown -R nginx:nginx /var/cache/nginx; \
    touch /var/run/nginx.pid; \
    chown -R nginx:nginx /var/run/nginx.pid

USER nginx

WORKDIR /home/part5/

ENTRYPOINT ["sh", "./build.sh"]

HEALTHCHECK NONE