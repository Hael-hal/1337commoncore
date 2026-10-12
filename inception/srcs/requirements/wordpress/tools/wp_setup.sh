#!/bin/sh
set -e

mkdir -p /var/www/wordpress /run/php
chown -R www-data:www-data /run/php

# Wait for MariaDB with a countdown timeout
echo "Waiting for MariaDB to be ready..."
timeout=60
while ! mariadb -h mariadb -u "${DB_USER}" -p"${DB_PASSWORD}" -e "SELECT 1;" >/dev/null 2>&1; do
    sleep 1
    timeout=$((timeout - 1))
    if [ "$timeout" -le 0 ]; then
        echo "Error: MariaDB did not become available in time."
        exit 1
    fi
done
echo "MariaDB connection established."

# Download WordPress and configure if wp-config.php doesn't exist
if [ ! -f /var/www/wordpress/wp-config.php ]; then
    echo "Downloading and configuring WordPress..."
    wp core download --allow-root --path=/var/www/wordpress
    wp config create --allow-root --path=/var/www/wordpress \
        --dbname="${DB_NAME}" --dbuser="${DB_USER}" --dbpass="${DB_PASSWORD}" --dbhost=mariadb:3306
fi

# Install WordPress if not already installed
if ! wp core is-installed --allow-root --path=/var/www/wordpress; then
    echo "Installing WordPress core..."
    wp core install --allow-root --path=/var/www/wordpress \
        --url="https://${DOMAIN_NAME}" --title="Inception" \
        --admin_user="${WP_ADMIN_USER}" --admin_password="${WP_ADMIN_PASSWORD}" \
        --admin_email="${WP_ADMIN_EMAIL}" --skip-email
fi

# Create secondary user if not exists
if ! wp user get "${WP_USER}" --allow-root --path=/var/www/wordpress >/dev/null 2>&1; then
    echo "Creating WordPress author user..."
    wp user create "${WP_USER}" "${WP_USER_EMAIL}" --role=author \
        --user_pass="${WP_USER_PASSWORD}" --allow-root --path=/var/www/wordpress
fi

# Enable immediate comment posting without admin moderation queue
wp option update comment_moderation 0 --allow-root --path=/var/www/wordpress
wp option update default_comment_status open --allow-root --path=/var/www/wordpress

chown -R www-data:www-data /var/www/wordpress

echo "Starting PHP-FPM..."
exec php-fpm8.2 -F
