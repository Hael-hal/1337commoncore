*This project has been created as part of the 42 curriculum by hael-hal.*

# Inception

## Description

The **Inception** project aims to broaden system administration knowledge using Docker and Docker Compose. The objective is to build a secure, containerized, multi-service web infrastructure composed of distinct services running in independent, dedicated containers within a personal virtual machine.

In compliance with the project guidelines, the infrastructure consists solely of the mandatory services:
- **NGINX**: The single secure entrypoint to the entire infrastructure, accessible strictly on port `443` using modern TLS protocols (`TLSv1.2` and `TLSv1.3`). Port 80 is strictly disabled.
- **WordPress with PHP-FPM**: Serves the WordPress dynamic website, running PHP-FPM 7.4 without an embedded web server. Communicates with NGINX through FastCGI over an isolated internal Docker bridge network on port `9000`.
- **MariaDB**: The relational database management system storing WordPress site data, running on internal port `3306` with no host-published ports.

Each service is built from Debian (`debian:bookworm`) using dedicated custom Dockerfiles. Ready-made images from Docker Hub are avoided in accordance with 42 evaluation rules.

---

### Architectural Design Choices & Comparisons

#### 1. Virtual Machines vs. Docker
| Aspect | Virtual Machines (VMs) | Docker Containers |
|---|---|---|
| **Architecture** | Emulates complete hardware via a Hypervisor (Type 1 or Type 2); runs a full guest operating system. | Shares the host Linux kernel; isolates processes using Linux namespaces and cgroups. |
| **Resource Overhead** | Heavy: high RAM and disk footprint for OS kernels and system background processes. | Minimal: shares kernel memory and host drivers, resulting in low overhead and near-instant startup. |
| **Isolation Level** | Strong hardware-level isolation. | Process-level isolation provided by kernel primitives (`cgroups`, `namespaces`, `seccomp`). |
| **Project Fit** | Inception runs inside a host VM, while application services are containerized via Docker inside it. | Containers provide lightweight modularity, reproducibility, and deterministic environments. |

#### 2. Docker Secrets vs. Environment Variables
| Aspect | Environment Variables (`.env`) | Docker Secrets |
|---|---|---|
| **Storage & Visibility** | Stored in process memory environment blocks; inspectable via `docker inspect` or `docker compose config`. | Mounted as in-memory files at `/run/secrets/<secret_name>` (`tmpfs`); never written to disk inside container. |
| **Best Used For** | Non-sensitive runtime configuration parameters (e.g., domain names, service ports, public user names). | Sensitive credentials (e.g., database passwords, root credentials, administrative API tokens). |
| **Security Risk** | Can easily leak into system process listings (`ps aux`), child processes, or bug reports. | Highly restricted; only mounted inside containers that explicitly declare access in compose configuration. |
| **Project Choice** | Non-sensitive configs (`DOMAIN_NAME`, `DB_NAME`, usernames) reside in `.env`; all passwords use Docker secrets. |

#### 3. Docker Network (Bridge) vs. Host Network
| Aspect | Docker User-Defined Network (Bridge) | Host Network (`network: host`) |
|---|---|---|
| **Isolation** | Creates a private virtual network namespace. Containers communicate only if attached to the network. | Bypasses container network isolation; containers bind directly to host network interfaces and ports. |
| **Service Discovery** | Provides automatic embedded DNS resolution using container and service names (e.g., `wordpress`, `mariadb`). | Requires manual port management on the host; port conflicts occur easily. |
| **Security** | Internal services (MariaDB, PHP-FPM) remain unexposed to the host machine or public network. | Completely opens container ports to the host network interface, creating significant security vulnerabilities. |
| **Project Choice** | A private bridge network (`inception-network`) is used. Using `network: host` is strictly prohibited by subject rules. |

#### 4. Docker Volumes vs. Bind Mounts
| Aspect | Docker Named Volumes | Host Bind Mounts |
|---|---|---|
| **Management** | Managed directly by the Docker daemon lifecycle (`docker volume ls`, `docker volume rm`). | Directly references an arbitrary path on the host filesystem without Docker management abstractions. |
| **Portability** | Abstraction decouples container storage logic from host-specific filesystem layouts. | Strictly coupled to host filesystem structure and absolute directory permissions. |
| **Subject Requirement** | Must be Docker named volumes whose data ends up in `/home/login/data`. | Direct bind mounts in compose volume definitions are forbidden by the subject. |
| **Project Choice** | Configured as named volumes (`mariadb_data`, `wordpress_data`) using Docker's `local` driver `driver_opts` pointing to `/home/hael-hal/data/`. |

---

## Instructions

### Prerequisites
- Operating System: Linux (Debian 11/12 recommended)
- Container Runtime: Docker Engine and Docker Compose plugin (`docker compose`)
- Administrative or sudo access to configure local `/etc/hosts` and volume mount paths

### 1. Domain Resolution Setup
Map the local domain name `hael-hal.42.fr` to `127.0.0.1` in your `/etc/hosts` file:
```bash
echo "127.0.0.1 hael-hal.42.fr" | sudo tee -a /etc/hosts
```

### 2. Compilation and Launch
To initialize required directories, build container images, and launch the stack in detached mode:
```bash
make
```

### 3. Verification & Management Commands
- Check running container status:
  ```bash
  make status
  ```
- View service logs:
  ```bash
  make logs
  ```
- Stop the stack:
  ```bash
  make down
  ```
- Full cleanup (stops containers, removes images, networks, volumes, and clears host data):
  ```bash
  make fclean
  ```
- Rebuild and relaunch from clean state:
  ```bash
  make re
  ```

### 4. Accessing the Services
- **WordPress Website**: `https://hael-hal.42.fr`
- **WordPress Admin Dashboard**: `https://hael-hal.42.fr/wp-admin`
- **HTTP Check**: Attempting to connect via `http://hael-hal.42.fr` (port 80) will be refused, verifying port 443 exclusivity.

---

## Resources

### Documentation & References
- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose File Reference](https://docs.docker.com/compose/compose-file/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [MariaDB Knowledge Base](https://mariadb.com/kb/en/)
- [WordPress Developer Resources & WP-CLI Handbook](https://make.wordpress.org/cli/handbook/)
- [Debian Official Package Repositories (Bookworm)](https://packages.debian.org/bookworm/)

### AI Usage Disclosure
In adherence to the 42 AI guidelines (Chapter IV), Artificial Intelligence was utilized as an assistive pair-programming and design review tool:
- **Project Structure Validation**: Used to cross-reference the 42 Inception subject (v5.4) and the evaluation sheet (`eval`) to ensure complete compliance with negative constraints (such as avoiding background entrypoints, prohibited infinite sleep patterns, and disallowing `latest` tags).
- **Comparative Analysis**: Assisted in articulating technical distinctions in the README (VMs vs. Containers, Docker Secrets vs. Environment Variables, Docker Networks vs. Host Network, and Named Volumes vs. Bind Mounts).
- **Drafting Documentation**: Accelerated the formulation of comprehensive `USER_DOC.md` and `DEV_DOC.md` guides.
All generated code, Dockerfiles, and shell scripts were systematically reviewed, validated against project standards, and adjusted to guarantee deterministic and safe execution.
