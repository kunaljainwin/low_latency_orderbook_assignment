# Book Building Project

This project implements a low latency order book builder using Qt C++ with a user interface for real-time updates of bid and ask books per symbol.

## Features

- Builds order book from CSV instructions (INSERT, REMOVE)
- Separate books for BID and ASK sides per symbol
- Multiple windows can be opened for different symbols
- User-selectable throttle for update frequency (real-time or delayed)
- Intuitive UI with dropdown to select symbols
- Live updating tables for price and size per side

## Setup Instructions

- Ensure Qt 5.15 or above and Qt Creator IDE is installed.
- Place `Dummy_TBT.csv` file in the project root folder.
- Open project in Qt Creator.
- Build and run the project.

## Usage

- On startup, select the `Dummy_TBT.csv` file.
- Use the dropdown to select a symbol and view its order book.
- Adjust the update throttle via the input box (0 = realtime).
- Open multiple windows for multiple symbols.

## Code Overview

- `OrderBookManager` handles CSV parsing and order book state management.
- `OrderBookWindow` displays UI with bid and ask tables.
- `main.cpp` manages file selection and opens initial window.

## Project Structure

- `main.cpp` — app entry point  
- `OrderBookManager.h/.cpp` — backend logic  
- `OrderBookWindow.h/.cpp` — frontend UI  
- `Dummy_TBT.csv` — input file  

---

For building and running detailed instructions, code comments, and screenshots, please see the attached documentation.

[Reference](https://www.qt.io) for Qt official resources.
