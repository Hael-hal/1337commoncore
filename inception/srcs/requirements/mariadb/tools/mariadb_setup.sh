#!/bin/sh
set -e

# Ensure runtime directories exist with proper ownership
mkdir -p /run/mysqld /var/lib/mysql /var/log/mysql
chown -R mysql:mysql /run/mysqld /var/lib/mysql /var/log/mysql
chmod 777 /run/mysqld

# Initialize data directory if system tables are missing
if [ ! -d "/var/lib/mysql/mysql" ]; then
    mysql_install_db --user=mysql --datadir=/var/lib/mysql > /dev/null
fi

# Bootstrap database and users if the project database does not exist
if [ ! -d "/var/lib/mysql/${DB_NAME}" ]; then
    mysqld --user=mysql --bootstrap <<EOF
FLUSH PRIVILEGES;
ALTER USER 'root'@'localhost' IDENTIFIED BY '${DB_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${DB_NAME}\`;
CREATE USER IF NOT EXISTS '${DB_USER}'@'%' IDENTIFIED BY '${DB_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${DB_NAME}\`.* TO '${DB_USER}'@'%';
FLUSH PRIVILEGES;
EOF
fi

exec mysqld --user=mysql --console
