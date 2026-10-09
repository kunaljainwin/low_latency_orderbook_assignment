#include <cassert>
#include <iostream>
#include "../low_latency_book_building_assignment/marketdepth.h"

void testMarketDepthDefaults() {
    MarketDepth depth;
    assert(depth.orderCount() == 0);
    assert(depth.volume() == 0);
}

void testMarketDepthParameterized() {
    MarketDepth depth(5, 1500);
    assert(depth.orderCount() == 5);
    assert(depth.volume() == 1500);
}

void testMarketDepthAddLevel() {
    MarketDepth depth(1, 100);
    depth.addLevel(250, 1);
    assert(depth.volume() == 350);
    assert(depth.orderCount() == 2);

    depth.addLevel(50, 2);
    assert(depth.volume() == 400);
    assert(depth.orderCount() == 4);
}

void testMarketDepthSetters() {
    MarketDepth depth;
    depth.setOrderCount(10);
    depth.setVolume(5000);
    assert(depth.orderCount() == 10);
    assert(depth.volume() == 5000);
}

int main() {
    testMarketDepthDefaults();
    testMarketDepthParameterized();
    testMarketDepthAddLevel();
    testMarketDepthSetters();
    std::cout << "All MarketDepth unit tests passed successfully." << std::endl;
    return 0;
}
