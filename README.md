# CodeAlpha Banking System

A console-based C++ banking simulation using classes, objects, vectors, and transaction records.

## Features
- Create accounts with unique account numbers
- Deposit and withdraw funds
- Transfer funds between accounts
- Display account details and transaction history
- Validate common invalid operations

## Compile and run
```bash
g++ main.cpp -o banking
./banking
```
On Windows PowerShell, run `.anking.exe` after compiling with `g++ main.cpp -o banking.exe`.

## Limitations
This is an educational in-memory demo. Account data and transactions are lost when the program exits. It is not a real banking application and does not implement authentication, persistent storage, audit-grade transaction processing, or production security.
