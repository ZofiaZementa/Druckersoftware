#ifndef GCODEREADER_H
#define GCODEREADER_H

#include <QObject>
#include <QUrl>

class GCodeReader : public QObject
{
    Q_OBJECT
public:
    explicit GCodeReader(QObject *parent = nullptr);
    ~GCodeReader();

    void setLineNumber(int lineNumber);
    int lineNumber();

signals:

public slots:

    void read(QUrl filePath);
    void nextLine();
    void puseReading();
    void continueReading();
    void clear();

private:

    int *m_lineNumber;
};

#endif // GCODEREADER_H
