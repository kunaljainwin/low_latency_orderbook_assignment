# Book Building Project

This project implements a low-latency order book viewer using Qt C++ with a multi-window user interface for real-time updates of bid and ask market depth per symbol.

## Features

- **Tick-by-Tick Ingestion:** Processes tick instructions (`INSERT`, `REMOVE`) from TBT feeds.
- **Dual-Sided Depth:** Maintains separated BID and ASK books with automatic sorting (descending bids, ascending asks).
- **Multi-Window Support:** Independently open and view market depth windows for multiple symbols simultaneously.
- **Dynamic Throttle Control:** Adjust update frequency from real-time (0 ms) to delayed intervals via a top-level spinbox.
- **Zero-Copy Model Streaming:** Virtual table models directly index depth vectors without intermediate cell allocations.

## Setup Instructions

- Requirements: C++17 compiler, CMake 3.16+, Qt 5.15 or Qt 6.x (Widgets, Core, LinguistTools).
- Ensure `Dummy_TBT.csv` is present in the working directory (sample provided).
- Build using CMake or open `CMakeLists.txt` in Qt Creator.

## Code Overview

- `tbtrecord.h`: Type-safe parser and data structure for TBT records with enum-based instructions.
- `marketdepth.h`: Compact market depth container aggregating order count and volume.
- `orderbook.h` / `orderbook.cpp`: Core order book data structure with price level aggregation.
- `orderbookmodel.h` / `orderbookmodel.cpp`: `QAbstractTableModel` implementation directly querying market depth.
- `orderbookmanager.h` / `orderbookmanager.cpp`: Background CSV feeder with configurable throttling timer.
- `orderbookwindow.h` / `orderbookwindow.cpp`: View window displaying side-by-side bids and asks.
- `mainwindow.h` / `mainwindow.cpp`: Main control panel with symbol menu and throttle controls.

