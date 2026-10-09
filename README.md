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

## 🎥 Demo
<div>
  <a href="https://www.loom.com/share/309da63a9d3f47db942100b24177fb36">
    <p>Book Building and Low Latency Assignment Demo - Watch Video</p>
  </a>
  <a href="https://www.loom.com/share/309da63a9d3f47db942100b24177fb36">
    <img style="max-width:300px;" src="https://cdn.loom.com/sessions/thumbnails/309da63a9d3f47db942100b24177fb36-f411896fa1ef211d-full-play.gif" alt="Demo GIF" />
  </a>
</div>

---

## ⚙️ Features
- **Dual-Pane Order Book UI:** Separate bids and asks tables with automated depth sorting (descending bids, ascending asks).
- **Color-Coded Depth:** Professional color scheme (vibrant blue for buy side, crisp red for sell side).
- **Multi-Symbol Depth Views:** Open concurrent windows for different symbols (e.g. RELIANCE, TCS, INFY).
- **Real-Time & Throttled Modes:** Configurable throttling from 0 ms (real-time stream) up to custom millisecond delay.
- **Aggregated Market Metrics:** Total Buy/Sell quantities and precise timestamp tracking (`hh:mm:ss.zzz`).
- **Zero-Copy Virtual Model:** High-throughput `QAbstractTableModel` implementation querying data without intermediate cell allocations.

---

## 📂 Repository Structure
```sh
low_latency_orderbook_assignment/
├── CMakeLists.txt                       # Root workspace build configuration
├── README.md                            # Project documentation
├── Dummy_TBT.csv                        # Bundled tick-by-tick market feed sample
├── tests/
│   └── marketdepth_test.cpp             # Unit tests for core depth structure
└── low_latency_book_building_assignment/
    ├── CMakeLists.txt                   # Application target & translation definitions
    ├── README.md                        # Component documentation
    ├── Dummy_TBT.csv                    # Local feed fallback
    ├── main.cpp                         # Application entrypoint
    ├── mainwindow.h / .cpp / .ui        # Control window with symbol menu & throttle
    ├── orderbook.h / .cpp               # Order book state engine (price levels & sides)
    ├── orderbookmanager.h / .cpp        # CSV feed loader & stream publisher
    ├── orderbookmodel.h / .cpp          # Virtual QAbstractTableModel
    ├── orderbookwindow.h / .cpp         # Depth viewer window
    ├── marketdepth.h                    # Depth container (volume & order counts)
    └── tbtrecord.h                      # Type-safe TBT record parser
```

---

## 🧩 Build & Run Instructions

### Prerequisites
- C++17 compliant compiler (`g++` 9+ or `clang++` 10+)
- CMake 3.16+
- Qt 5.15 or Qt 6 (Widgets, Core)

### Building via CMake

```bash
# From workspace root
cmake -B build -S .
cmake --build build

# Run the viewer
./build/low_latency_book_building_assignment/orderbook
```

Alternatively, open `CMakeLists.txt` directly in **Qt Creator** and click **Run**.

---

## 🧠 Architecture & Refactored Design

### 1. Model–View Architecture
- **State Layer (`OrderBook`):** Maintains sorted maps of prices to `MarketDepth` per side. Lookups and aggregations operate via iterator lookups avoiding redundant map traversals.
- **Virtual Model (`OrderBookModel`):** Implements `QAbstractTableModel` with direct projection from underlying depth data to table cells. Eliminates heap allocation of intermediate `QVariant` lists.
- **View Layer (`OrderBookWindow`):** Clean separation of bids and asks using `QTableView` with non-editable triggers, alternating row colors, and proportional stretching.
- **Feed Controller (`OrderBookManager`):** Ingests tick-by-tick records (`INSERT`, `REMOVE`), dispatches throttled updates, and automatically discovers unique symbols from the feed.

### 2. Low-Latency Optimizations
- **Type-Safe Enums:** Replaced string instructions (`"INSERT"`, `"REMOVE"`) and sides with strongly-typed `OrderInstruction` and `OrderSide` enums, cutting string allocation and comparison overhead on the update loop.
- **Direct Cell Resolution:** In `OrderBookModel::data()`, cells resolve row data via switch on column index, bypassing 2D vector allocation.
- **Pre-Allocated Vectors:** Bid and ask projections use `reserve()` to prevent vector reallocations during depth extraction.
- **Robust Path Fallbacks:** Automated discovery of `Dummy_TBT.csv` in relative paths and application directories.



