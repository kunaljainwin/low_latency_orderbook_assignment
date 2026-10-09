#pragma once

#include <QString>
#include <QStringList>
#include <QtGlobal>

enum class OrderInstruction {
    Unknown,
    Insert,
    Remove
};

enum class OrderSide {
    Unknown,
    Buy,
    Sell
};

// Represents a single tick/record from TBT feed
struct TbtRecord {
    QString symbol;
    OrderInstruction instruction = OrderInstruction::Unknown;
    OrderSide side = OrderSide::Unknown;
    double price = 0.0;
    qint64 size = 0;
    qint64 sequenceId = 0;

    TbtRecord() = default;

    explicit TbtRecord(const QStringList &fields) {
        parseFields(fields);
    }

    bool isValid() const {
        return !symbol.isEmpty()
            && instruction != OrderInstruction::Unknown
            && side != OrderSide::Unknown;
    }

private:
    void parseFields(const QStringList &fields) {
        constexpr int MIN_FIELD_COUNT = 6;
        if (fields.size() < MIN_FIELD_COUNT) {
            return;
        }

        symbol = fields[0].trimmed();

        const QString inst = fields[1].trimmed().toUpper();
        if (inst == "INSERT") {
            instruction = OrderInstruction::Insert;
        } else if (inst == "REMOVE") {
            instruction = OrderInstruction::Remove;
        }

        const QString sideStr = fields[2].trimmed().toUpper();
        if (!sideStr.isEmpty()) {
            const QChar c = sideStr.at(0);
            if (c == 'B') {
                side = OrderSide::Buy;
            } else if (c == 'S') {
                side = OrderSide::Sell;
            }
        }

        price = fields[3].toDouble();
        size = fields[4].toLongLong();
        sequenceId = fields[5].toLongLong();
    }
};
