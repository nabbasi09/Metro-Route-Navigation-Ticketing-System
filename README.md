# 🚇 Metro Route Navigation & Ticketing System

A **C++ console-based application** that simulates a real-world metro navigation system.
It allows users to find optimal routes, detect interchanges, calculate fares, and book tickets with QR code generation.

---

## 📌 Features

* 🔍 **Smart Station Search**

  * Case-insensitive input
  * Auto-suggestions for stations

* 🚇 **Route Finding Algorithms**

  * Dijkstra → Shortest distance (best route)
  * BFS → Minimum number of stations
  * DFS → Any possible path

* 🔁 **Interchange Detection**

  * Detects line changes
  * Displays warnings and counts interchanges

* 💰 **Fare Calculation**

  * ₹10 for distance ≤ 5
  * ₹20 for distance > 5

* 🎟 **Ticket Booking**

  * Saves ticket in `ticket.txt`
  * Displays journey details

* 🔳 **QR Code Generation**

  * Generates `ticket.png`
  * Encodes ticket details

* 🔐 **User Authentication**

  * Register & Login system
  * Password hashing for security

---

## 🛠️ Technologies Used

* **Language:** C++17
* **Data Structures:** STL (vector, map, queue, priority_queue)
* **Algorithms:** Dijkstra, BFS, DFS
* **QR Tool:** qrencode
* **File Handling:** fstream

---

## 📊 System Requirements

* OS: Windows / Linux / macOS
* Compiler: g++ / clang / MSVC
* RAM: 512MB minimum
* Storage: ~50MB

---

## ⚙️ Installation & Setup

### 🔹 Step 1: Clone Repository

```bash
git clone https://github.com/nabbasi09/Metro-Route-Navigation-&-Ticketing-System
cd Metro-Route-Navigation-&-Ticketing-System
```

### 🔹 Step 2: Install QR Tool

**Linux:**

```bash
sudo apt install qrencode
```

**Mac:**

```bash
brew install qrencode
```

**Windows:**

* Use WSL or install qrencode manually

---

### 🔹 Step 3: Compile Code

```bash
g++ -std=c++17 metro.cpp -o metro
```

### 🔹 Step 4: Run Program

```bash
./metro
```

---

## 🚀 How It Works

1. User registers and logs in
2. Choose from:

   * Show Stations
   * Find Route
   * Book Ticket
3. Select algorithm (Dijkstra / BFS / DFS)
4. System displays:

   * Route
   * Interchanges
   * Distance & Fare
5. Ticket + QR code generated

---

## 📸 Sample Output

```
🚇 Route:

🔵 Rajiv Chowk
🔵 Mandi House
⚠ Change Blue → Yellow at Mandi House
🟡 Central Secretariat
🟡 AIIMS

📏 Distance: 6 km
💰 Fare: ₹20
🔁 Interchanges: 1
```

---

## 📁 Project Structure

```
📦 Metro-Route-Navigation
 ┣ 📜 metro.cpp
 ┣ 📜 ticket.txt
 ┣ 🖼️ ticket.png
 ┗ 📄 README.md
```

---

## 🔮 Future Enhancements

* GUI (Qt / Web App)
* Database integration (SQLite/MySQL)
* Real-time metro data
* Advanced fare calculation
* Mobile app version

---

## 📄 License

This project is developed for **educational purposes only**.

---

## ⭐ Support

If you like this project, give it a ⭐ on GitHub!
