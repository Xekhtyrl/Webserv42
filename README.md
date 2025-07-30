# Webserv42 🌐

**Custom HTTP/1.1 web server written in C++ using non-blocking I/O (select-based).**

---

## 🚀 Overview

* Built from scratch in **C++98** for the 42 Network curriculum
* Implements a functional HTTP web server using **non-blocking sockets** (`select()`), supports **multiple clients simultaneously**
* Parses custom configuration files (**inspired by NGINX syntax**) to manage server behavior

---

## 🔧 Features

* Supports simple HTTP methods: **GET**, **POST**, **DELETE**
* Serves static files and executes dynamic content using **CGI** scripts (e.g. python, pearl)
* Handles **chunked requests**, method validation, redirects, and large body uploads
* Custom request parser and response builder following HTTP/1.1 RFC standards

---

## 🧠 Project Structure

* **Server core**: socket initialization, connection listener, multiplexed I/O using `select()`
* **Request parser**: HTTP message parsing via state machine for accurate syntax validation
* **Response builder**: generates headers, status codes, body content, and error pages
* **Configuration**: supports server and location blocks with directives like `listen`, `root`, `index`, `autoindex`, and more
* **CGI support**: execute external scripts (tested: .pl, .py)(implemented to work with others but not tested) with correct headers for dynamic content

---

## 🛠 Installation & Usage

```bash
git clone https://github.com/Xekhtyrl/Webserv42.git
cd Webserv42
make
./webserv <config_file_path>  # optional: default used if none provided
```

then visit at http://localhost::<port>/

---

## 🧩 Sample Configuration (`config.conf`)

see config file for structure.

---

## 📚 What You Learned

* Fundamentals of **socket programming** and non-blocking I/O with `select()`
* Robust HTTP/1.1 compliance in requests and responses
* File upload handling, CGI execution, and configuration-driven behavior
* Basics of server architecture, performance tuning, and network efficiency

---

## 🎯 Why This Project Matters

* Builds solid understanding of **low-level networking** and HTTP internals
* Experience writing production-grade code in **C++98**, including error handling, parsing, and state machines
* Enhances skills in managing multiple client connections efficiently without threads
* Simulates real-life server behavior and configuration workflows at the OS level

---

## ✅ Suggested Enhancements

* Implement **persistent connections** (Keep-Alive) and advanced status codes
* Support **IPv6** or switch to `poll()` / `epoll()` for greater scalability
* Add **TLS support** via OpenSSL
* Implement caching, gzip support, or request rate limiting
* Implement coockies service

---
