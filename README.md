# ASP Project – Exercise 2: URL Blacklist Server with Bloom Filter
second exercise
## JIRA Sprint Board
You can find the project sprint and tasks here:  
[JIRA Sprint Link](https://muradkhalaily.atlassian.net/jira/software/projects/AP/boards/34)

## 📘 Overview
This project transforms our Bloom Filter URL blacklist from a CLI app into a TCP-based client-server system. It enables persistent, extensible, and test-driven filtering of blacklisted URLs, following clean architecture and SOLID principles.

---

## 🛠️ Technologies & Practices
- **C++ (server-side)** with STL only
- **Python (client-side)** for simplicity and testing
- **TDD**: Red-Green-Refactor unit tests for server
- **JIRA**: Agile planning and task tracking
- **Docker**: Build & run environments
- **CMake**: Cross-platform C++ build system

---

## ⚙️ Project Structure

```
ASP-Project/
├── src/                      # C++ source code
│   ├── server/               # Bloom filter, request handling
│   └── tests/                # Unit tests
├── client/                   # Python TCP client
├── data/                     # Persistent files
├── Dockerfile                # Server container
├── CMakeLists.txt            # C++ build config
└── README.md                 # Project documentation
```

---

## 🚀 Running the Project

### 🐳 Docker (Recommended)
```bash
docker build -t bloomserver .
docker run -it --rm -v server_data:/app/data -p 12345:12345 bloomserver 12345 8 1 2
```

### 🧱 Manual
#### Compile & Run Server
```bash
cmake .
make
./bloomserver 12345 8 1 2
```

#### Run Client
```bash
python3 client/client.py 127.0.0.1 12345
```

---

## 📡 Command Protocol (Client → Server)

| Command            | Description               | Response              |
|--------------------|---------------------------|------------------------|
| `POST [URL]`       | Add URL to blacklist      | `201 Created`          |
| `GET [URL]`        | Check if URL is blacklisted | `200 Ok` / `404 Not Found` |
| `DELETE [URL]`     | Remove URL from list      | `204 No Content` / `404 Not Found` |
| Invalid command    | Malformed or unknown      | `400 Bad Request`      |

**All commands/responses are newline-terminated.**

---

## 📦 Features
- Add, query, and delete blacklisted URLs
- Supports multiple clients (one at a time)
- Bloom filter with configurable size and hash functions
- Bloom state auto-persisted to disk
- Modular and testable architecture
- Fully TDD-compliant server implementation
- Easily extendable with new hash functions or commands

---

## 🧠 Design Highlights

### SOLID Principles
| Principle | Implementation |
|----------|----------------|
| SRP       | `App` handles parsing; `BloomFilter` manages logic |
| OCP       | Add commands/hash functions without changing core code |
| LSP       | `IHashFunction` interface supports swappable logic |
| ISP       | Separated I/O and logic layers |
| DIP       | High-level modules depend on abstractions |

---

### Extensibility Wins
- I/O moved from `cin/cout` to socket – zero logic change
- New `DELETE` command added – no change to `POST/GET` logic
- Persistent layer separated cleanly – swap file with DB easily

---

## 🧪 TDD Testing
- All logic tested using Red-Green-Refactor
- Covered:
  - Bit array manipulation
  - Multi-hash correctness
  - Command handling (POST/GET/DELETE)
  - Invalid input responses

---

## 📁 Data Persistence
- `bloom.dat`: Bit array snapshot
- `blacklist.txt`: Raw URL records
- Automatically restored on startup

---

## 🧩 Future Extensions
- REST API wrapper (e.g., Flask + C++ backend)
- Threaded server: multiple clients simultaneously
- DB integration (SQLite/Redis)
- More advanced hash functions
- Full client app with GUI

---

## 🧱 Docker Support
The project includes a working `Dockerfile` and `docker-compose.yml`:
- Buildable and runnable on any system
- Auto-loads persisted data
- Useful for deployment or testing environments

---

## 🧷 Final Notes
- ✅ Fully SOLID-compliant and test-driven
- ✅ Easily maintainable and extendable
- ✅ Strictly standard C++ with STL only
- ✅ Followed Agile process with JIRA
- ✅ Ready for future upgrades and scalability

---

## 📎 Example Session

```
POST www.test.com
→ 201 Created

GET www.test.com
→ 200 Ok
true true


DELETE www.test.com
→ 204 No Content

GET www.test.com
→ 404 Not Found
```

---

## 🧑‍💻 Authors
- **Saleh Sarsur**
- **Murad Khalaily**
- **Mostafa Shalash**

---