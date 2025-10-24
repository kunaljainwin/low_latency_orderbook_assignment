# Order Book Viewer (Qt Application)

## 📝 Overview
A simple real-time Order Book Viewer built using Qt (C++).  
It displays bid (buy) and ask (sell) sides using separate `QTableView`s, color-coded and updated dynamically.

---

## 🕒 Estimated Completion Time
Approx. 8–10 hours including design, implementation, and testing.

---
## Screenshots
<img width="1919" height="1006" alt="image" src="https://github.com/user-attachments/assets/ddabc26a-76a4-430d-abab-c3b8cd79a322" />

<img width="1917" height="1010" alt="image" src="https://github.com/user-attachments/assets/86d66cda-e33b-46e8-ac5e-2881cd594490" />

---
## ⚙️ Features
- Dual-pane Order Book UI (bids & asks)
- Blue text for buy side, red for sell side
- Totals and timestamp at the bottom
- Automatic size management with minimum window dimensions
- Dynamic throttling options

---
## Folder structure
```sh
orderbook/
│
├── main.cpp
├── orderbookwindow.h
├── orderbookwindow.cpp
├── orderbookmodel.h
├── orderbookmodel.cpp
├── marketdepth.h
├── CMakeLists.txt  (or .pro file if using qmake)
└── README.md
```

---

## 🧩 Compilation Instructions

### Using cmake
```bash
mkdir build && cd build
cmake ..
make
./orderbook
```

### Running the Application

```bash
./orderbook
```

## 🧠 Approach

### 1. **Architecture Design**
The project follows the **Model–View architecture** provided by Qt:
- **Model (`OrderBookModel`)** handles all order data and exposes it to the view.
- **View (`QTableView`)** displays the data in tabular format.
- **Controller (`OrderBookWindow`)** connects models and views, handling updates and layout.

This separation ensures a scalable and maintainable design where data logic is independent of the UI.

---

### 2. **Data Handling**
- Two separate models are used — one for **bids** and one for **asks**.
- Each model holds a list of orders with fields such as **Price**, **Volume**, and **Total Orders**.
- Updates are triggered through an `updateOrderBook()` method that refreshes the models with the latest state.

---

### 3. **Model Implementation**
The `OrderBookModel` class inherits from `QAbstractTableModel` and overrides the following key methods:
- `rowCount()` and `columnCount()` – define the table size.
- `data()` – provides the value, color, and alignment for each cell.
- `headerData()` – defines column headers.

Custom roles are implemented to:
- **Color cells:** blue for bids (buy side), red for asks (sell side).
- **Align text:** left-aligned for better readability.

---

### 4. **UI Layout**
The `OrderBookWindow` manages all visual components:
- Two `QTableView`s are placed side by side using a horizontal layout.
- Totals and last update time are shown below using a vertical layout.
- Minimum window size is enforced for consistent display.

Each view:
- Uses its own model (`bidsModel`, `asksModel`).
- Has headers and columns stretched proportionally.
- Is styled for readability with alternating row colors and fixed column widths.

---

### 5. **Dynamic Updates**
When the order book is updated:
- New bid and ask data are passed to their respective models.
- The models emit `dataChanged()` signals to notify views.
- The views automatically refresh to show the latest state.

This mechanism ensures that even with frequent updates, the UI remains responsive and accurate.

---

### 6. **Performance Considerations**
- The table uses a **throttled update mechanism** (optional) to avoid excessive UI refreshes.
- Only visible data cells are updated to maintain performance.
- Thread-safety can be integrated later for real-time data streams.

---

### 7. **User Experience Enhancements**
- Text alignment and color coding make it easy to distinguish bids and asks.
- Minimum width and height ensure the window never collapses visually.
- The last update timestamp helps track the freshness of the data.

---

### 8. **Outcome**
The resulting application provides a clear, structured, and visually intuitive Order Book UI that can easily integrate with a real-time trading backend or simulated data feed.


