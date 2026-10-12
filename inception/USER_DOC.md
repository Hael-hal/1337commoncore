# User Documentation (USER_DOC.md)

This guide provides basic usage instructions for an end user or administrator managing the Inception infrastructure.

---

## 1. Provided Services Overview

The Inception stack provides a secure, containerized WordPress publication platform consisting of three coordinated services:
- **NGINX**: A high-performance reverse proxy and web server providing encrypted HTTPS communication via TLSv1.2/1.3 on port `443`.
- **WordPress (PHP-FPM)**: The content management system executing WordPress core scripts and managing articles, media, and comments.
- **MariaDB**: The relational database management system securely storing WordPress site data, tables, user accounts, and posts.

---

## 2. Starting and Stopping the Project

All operational lifecycle commands are managed from the root of the project using `make`:

- **Start the Stack**:
  ```bash
  make
  ```
  Initializes host directories, builds the custom images, and starts all containers.

- **Stop and Remove Containers**:
  ```bash
  make down
  ```
  Stops and removes running containers while preserving persistent database and website volume data.

- **Full Reset**:
  ```bash
  make fclean
  ```
  Stops containers, deletes images, networks, volumes, and persistent storage data.

---

## 3. Accessing the Website and Administration Panel

### Prerequisite Domain Configuration
Ensure that `hael-hal.42.fr` resolves to your local machine (`127.0.0.1`). Add the following entry to `/etc/hosts`:
```text
127.0.0.1 hael-hal.42.fr
```

### URLs
- **Public WordPress Website**:
  Navigate to: [https://hael-hal.42.fr](https://hael-hal.42.fr)
  *(Accept the self-signed SSL warning in your browser).*

- **WordPress Administration Dashboard**:
  Navigate to: [https://hael-hal.42.fr/wp-admin](https://hael-hal.42.fr/wp-admin)

---

## 4. Locating and Managing Credentials

All configuration variables and passwords are centrally stored in the local file `srcs/.env`:

| Role / Component | Username / Variable | Default Value |
|---|---|---|
| **WordPress Administrator** | `WP_ADMIN_USER` | `supervisor_hal` |
| **WordPress Admin Password** | `WP_ADMIN_PASSWORD` | `supervisor_strong_pass_42!` |
| **WordPress Standard User** | `WP_USER` | `author_hal` |
| **WordPress User Password** | `WP_USER_PASSWORD` | `author_regular_pass_42!` |
| **MariaDB Database Name** | `DB_NAME` | `wordpress_db` |
| **MariaDB User** | `DB_USER` | `wp_user` |
| **MariaDB User Password** | `DB_PASSWORD` | `wp_db_pass_2026!` |
| **MariaDB Root Password** | `DB_ROOT_PASSWORD` | `root_db_pass_2026!` |

To change credentials before building, edit `srcs/.env`.

---

## 5. Checking that Services are Running Correctly

1. **Verify Port 80 is Closed**:
   ```bash
   curl -I http://hael-hal.42.fr
   ```
   *(Connection refused — Port 80 is closed).*

2. **Verify HTTPS (Port 443)**:
   ```bash
   curl -k -I https://hael-hal.42.fr
   ```
   *(HTTP 200 OK — Using TLSv1.2/TLSv1.3).*
