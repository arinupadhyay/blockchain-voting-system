# 🗳️ C++ Object-Oriented Voting System

A secure and modular console-based voting application developed using C++17. The project demonstrates core and advanced Object-Oriented Programming (OOP) concepts, including encapsulation, inheritance, abstraction, and polymorphism.

The system is designed with a modular software architecture and uses SHA-256 hash chaining to provide tamper-evident and verifiable vote records. It also demonstrates practical concepts such as STL containers, file handling, data persistence, logging, and structured software design.

---

## 🎯 Overview &  Architecture !!!!

This project models an end-to-end election system designed around solid software engineering and OOP design patterns:

* **Heavy OOP Design:** Built using **Encapsulation**, **Abstraction**, **Inheritance**, and **Runtime Polymorphism** to cleanly separate system roles and domains[cite: 1].
* **Modular Codebase:** Complete separation of interfaces (`include/` `.hpp` headers) and implementations (`src/` `.cpp` files)[cite: 1].
* **Tamper-Evident Data Structure:** Employs SHA-256 hash chaining to ensure historical vote records remain immutable and verifiable[cite: 1].
* **System Persistence & Logging:** Manages state persistence via standard I/O streams and maintains audit logs for operational security[cite: 1].

---

## 🏗️ C++ & OOP Concepts Demonstrated

| Concept | Implementation Details |
| :--- | :--- |
| **Inheritance** | Derived `Voter` and `ElectionOfficer` classes inheriting from an abstract `User` base class[cite: 1]. |
| **Polymorphism** | Overridden virtual methods like `displayMenu()` providing custom execution flows per user role[cite: 1]. |
| **Encapsulation** | Protected state variables (`userId`, `votedStatus`) with controlled public interfaces/getters[cite: 1]. |
| **STL & DSA** | Extensive use of standard containers (`std::vector`, `std::map`) for state tracking and vote tallying[cite: 1]. |
| **Resource Management** | RAII principles, clean constructor/destructor lifetime management, and const-correctness[cite: 1]. |

---

## 📁 Directory Structure

```text
blockchain-voting-system/
├── data/              # Persistent data files and system audit logs
├── include/           # Header files (.hpp) — Class interfaces & declarations
│   ├── User.hpp       # User, Voter, and ElectionOfficer inheritance hierarchy
│   ├── Vote.hpp       # Core vote data structures
│   ├── Block.hpp      # Hash-linked node structure
│   ├── Blockchain.hpp # Chain integrity, traversal, and validation logic
│   ├── Election.hpp   # Candidate management and election lifecycle state machine
│   ├── Logger.hpp     # System exception and audit logging utilities
│   └── Database.hpp   # File I/O persistence manager
├── src/               # Implementation files (.cpp)
│   ├── User.cpp
│   ├── Block.cpp
│   ├── Blockchain.cpp
│   ├── Election.cpp
│   ├── Logger.cpp
│   ├── Database.cpp
│   └── main.cpp       # Application entry point and interactive console menus
├── CMakeLists.txt     # Build configuration file
└── README.md          # Project documentation
