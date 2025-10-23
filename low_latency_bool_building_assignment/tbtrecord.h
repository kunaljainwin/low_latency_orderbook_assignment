#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>

// Represents a single record (line) from Dummy_TBT.csv
struct TbtRecord {
    QString symbol;
    QString instruction;   // "INSERT" or "REMOVE"
    QChar side;            // 'B' or 'S'
    double price;
    qint64 size;
    qint64 sequenceId;

    TbtRecord() = default;

    TbtRecord(const QStringList &fields) {
        // Assuming fields = {Symbol, Instruction, Side, Price, Size, Sequence_id}
        if (fields.size() >= 6) {
            symbol = fields[0].trimmed();
            instruction = fields[1].trimmed().toUpper();
            side = fields[2].trimmed().isEmpty() ? QChar('B') : fields[2].trimmed().at(0).toUpper();
            price = fields[3].toDouble();
            size = fields[4].toLongLong();
            sequenceId = fields[5].toLongLong();
        }
    }

    bool isValid() const {
        return !symbol.isEmpty() && (instruction == "INSERT" || instruction == "REMOVE");
    }
};
