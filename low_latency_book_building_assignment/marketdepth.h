#pragma once

#if defined(QT_CORE_LIB) || defined(QT_VERSION)
#include <QtGlobal>
#else
#include <cstdint>
using qint64 = std::int64_t;
#endif

struct MarketDepth {
private:
    qint64 m_orderCount = 0;
    qint64 m_volume = 0;

public:
    MarketDepth() = default;

    MarketDepth(qint64 count, qint64 vol)
        : m_orderCount(count), m_volume(vol) {}

    qint64 orderCount() const { return m_orderCount; }
    qint64 volume() const { return m_volume; }

    void setOrderCount(qint64 count) { m_orderCount = count; }
    void setVolume(qint64 vol) { m_volume = vol; }

    void addLevel(qint64 vol, qint64 count = 1) {
        m_volume += vol;
        m_orderCount += count;
    }
};

