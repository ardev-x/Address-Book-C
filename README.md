# C Address Book Application 🛠️

A robust, modular console application built in C for managing personal contacts, featuring input validation, modular function design, and data persistence via a CSV database. This project was developed in a Linux environment (WSL).

## 📐 Modular System Architecture

The application is structured into distinct modules for optimal maintainability and readability.

* `address_book.h`: Common struct definitions, constant definitions, and function prototypes.
* `main.c`: The core program control loop and main menu interface.
* `fileStorage.c`: Dedicated functions for loading and saving contact data to `contacts.csv`.
* `contacts.c`: Implements key features: Create, Search, and *[Edit/Delete in progress]* 🚧.

<p align="center">
  <img src="Diagrams/system_architecture.jpg" alt="System Flowchart" width="700">
</p>

## 🚀 Key Operational Flows

These flowcharts visualize the logical progression and modular interactions of the core features.

### ➕ Create Contact Flow
Details the multi-step process for data entry, strict validation (Name/Phone), and duplicate detection before saving in memory.

<p align="center">
  <img src="Diagrams/createContact.jpg" alt="Create Contact Flow" width="700">
</p>

### 🔍 Search Contact Flow
Illustrates the modular search logic, allowing users to find contacts by Name or Phone using `strcmp` iteration.

<p align="center">
  <img src="Diagrams/searchContact.jpg" alt="Search Contact Flow" width="700">
</p>

### ✏️ Display Contact Flow
It shows how the contacts are being displayed

<p align="center">
  <img src="Diagrams/displayContact.jpg" alt="Display Contact Flow" width="700">
</p>

## 💾 CSV Database Layout

Data persistence is managed via a simple, scalable `contacts.csv` file.
