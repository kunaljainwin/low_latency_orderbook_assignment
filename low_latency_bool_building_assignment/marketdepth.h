#pragma once

struct MarketDepth {
private:
    qint64 m_nOrderCount;
    qint64 m_nVolume;

public:
    // Default constructor
    MarketDepth()
        : m_nOrderCount(0), m_nVolume(0) {}

    // Parameterized constructor
    MarketDepth(qint64 orderCount, qint64 volume)
        : m_nOrderCount(orderCount), m_nVolume(volume) {}

    // Getters
    qint64 orderCount() const { return m_nOrderCount; }
    qint64 volume() const { return m_nVolume; }

    // Setters
    void setOrderCount(qint64 count) { m_nOrderCount = count; }
    void setVolume(qint64 volume) { m_nVolume = volume;m_nOrderCount++; }
};

