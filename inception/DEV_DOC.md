# Developer Documentation (DEV_DOC.md)

This documentation provides developer-oriented instructions for configuring, developing, debugging, and maintaining the Inception infrastructure.

---

## 1. Environment Setup from Scratch

### System Prerequisites
- **Operating System**: Linux (Debian 11 or 12 recommended).
- **Docker Engine**: Docker 20.10+ installed and running (`sudo systemctl start docker`).
- **Docker Compose**: Docker Compose Plugin (v2.x).
- **Domain Mapping**: Ensure `hael-hal.42.fr` points to `127.0.0.1` in `/etc/hosts`:
  ```bash
  sudo bash -c 'echo "127.0.0.1 hael-hal.42.fr" >> /etc/hosts'
  ```

### Repository Structure
```text
.
├── DEV_DOC.md
├── Makefile
├── README.md
├── USER_DOC.md
├── .gitignore
└── srcs/
    ├── .env
    ├── docker-compose.yml
    └── requirements/
        ├── mariadb/
        │   ├── conf/50-server.cnf
        │   ├── Dockerfile
        │   └── tools/mariadb_setup.sh
        ├── nginx/
        │   ├── conf/nginx.conf
        │   ├── Dockerfile
        │   └── tools/nginx_setup.sh
        └── wordpress/
            ├── conf/www.conf
            ├── Dockerfile
            └── tools/wp_setup.sh
```

### Configuration Setup
All parameters and credentials reside in `srcs/.env`.
Key configuration items:
- `DOMAIN_NAME`: `hael-hal.42.fr`
- `DB_NAME`: `wordpress_db`
- `DB_USER`: `wp_user`
- `DB_PASSWORD`: MariaDB user password
- `DB_ROOT_PASSWORD`: MariaDB root password
- `WP_ADMIN_USER`: WordPress admin login (MUST NOT contain "admin" or "Admin", e.g. `supervisor_hal`)
- `WP_ADMIN_PASSWORD`: WordPress admin password
- `WP_USER`: WordPress regular author username (`author_hal`)
- `WP_USER_PASSWORD`: WordPress author password

---

## 2. Makefile Commands

- **Build and Start (Default)**:
  ```bash
  make
  ```
  Creates host persistent directories (`/home/hael-hal/data/mariadb` and `/home/hael-hal/data/wordpress`), builds images, and starts all services in background.

- **Stop Services**:
  ```bash
  make down
  ```

- **Clean Docker System**:
  ```bash
  make clean
  ```

- **Full Reset (Deletes Volumes & Host Data)**:
  ```bash
  make fclean
  ```

- **Rebuild from Scratch**:
  ```bash
  make re
  ```

---

## 3. Data Storage & Persistence Verification

### Persistent Volume Configuration
In accordance with 42 evaluation guidelines, persistent storage uses Docker named volumes whose data is physically stored in `/home/hael-hal/data/`:
- **MariaDB Storage**: Volume `mariadb_data` binds to host path `/home/hael-hal/data/mariadb`.
- **WordPress Files Storage**: Volume `wordpress_data` binds to host path `/home/hael-hal/data/wordpress`.

### Verifying Named Volume Configuration
Run the following inspection commands to confirm the paths contain `/home/hael-hal/data/`:
```bash
docker volume ls
docker volume inspect mariadb_data
docker volume inspect wordpress_data
```
The output shows:
```json
"Options": {
    "device": "/home/hael-hal/data/mariadb",
    "o": "bind",
    "type": "none"
}
```

### Database Verification
Connect directly to MariaDB to verify data:
```bash
docker exec -it mariadb mysql -u wp_user -p"$DB_PASSWORD" wordpress_db
```
