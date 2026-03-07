# Seat Booking System

A full-stack Web Application and an enhanced C program built for a seat ticket booking utility. 

## What the System is Based On
This project originated as a command-line C program for managing seat reservations. It has now been transformed and expanded into a **hybrid architecture** that includes:

1. **Native C Execution (`seatbooking_system.c`)**: 
   - A low-level compiled program that uses standard C library functions to loop through a ticketing menu.
   - **File Persistence**: It uses C File I/O (`<stdio.h>`) to save and load passenger grid data into a local `seats.dat` file. This prevents data loss when the application terminates.
   
2. **Modern Web API Backend (`app.py`)**: 
   - Powered by **Python** and the **Flask Web Framework**.
   - Acts as an asynchronous web server that intercepts HTTP requests (GET, POST) over network ports.
   - Replaces the C-based memory arrays with a pseudo-database using a `database.json` file for lightweight live data tracking.
   
3. **Responsive Client Interface (`templates/index.html`)**:
   - The user frontend is built with pure **HTML5**, **JavaScript (ES6+)**, and **Tailwind CSS**.
   - It relies on AJAX `fetch()` requests to communicate with the Flask API, allowing the browser to update visuals dynamically without reloading the webpage.

---

## 1. Running the C Program Locally
Compile the C file using standard compiler rules and execute the binary.
```bash
gcc seatbooking_system.c -o seat_booking
./seat_booking
```

## 2. Running the Web Application Locally
Ensure you have the required Python packages installed:
```bash
pip install -r requirements.txt
```
Start the web server (Note: it runs on port 5001 to avoid macOS AirPlay conflicts):
```bash
python3 app.py
```
Then, open your web browser and navigate to `http://127.0.0.1:5001`.

---

## 3. How to Update Your GitHub Repository
If you make changes locally and want to sync them with GitHub (and remove the old files), follow these steps in your terminal:

**Step A: Navigate to your project folder**
```bash
cd "/Users/manitjain/Desktop/CODING/C Programming/c"
```

**Step B: Remove the old C file from Git**
If Git is still tracking the old file (`innovativeassignment.c`), tell git to remove it:
```bash
git rm innovativeassignment.c
```

**Step C: Add all new and updated files**
```bash
git add .
```

**Step D: Commit your changes**
```bash
git commit -m "Updated README, fixed port 5001 conflict, and removed old C file."
```

**Step E: Push to GitHub**
```bash
git push -u origin main
```
*(If prompted for a password, paste your GitHub Personal Access Token).*
# Seat Booking System

A simple seat booking system written in C.

## Live Demo
https://seat-booking-system-flame.vercel.app/
