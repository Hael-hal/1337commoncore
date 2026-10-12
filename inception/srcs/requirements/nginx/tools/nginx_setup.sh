#!/bin/sh
set -e

if [ ! -f /etc/ssl/certs/nginx-selfsigned.crt ]; then
    mkdir -p /etc/ssl/certs /etc/ssl/private
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
        -keyout /etc/ssl/private/nginx-selfsigned.key \
        -out /etc/ssl/certs/nginx-selfsigned.crt \
        -subj "/CN=${DOMAIN_NAME:-hael-hal.42.fr}"
fi

exec nginx -g "daemon off;"
