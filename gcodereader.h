#ifndef GCODEREADER_H
#define GCODEREADER_H

#include <QObject>
#include <QUrl>

class GCodeReader : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int m_lineNumber READ lineNumber WRITE setLineNumber NOTIFY lineNumberChanged)
    Q_PROPERTY(QUrl m_filePath READ filePath WRITE setFilePath NOTIFY filePathChanged)

public:
    explicit GCodeReader(QObject *parent = nullptr);
    ~GCodeReader();

    void setLineNumber(int lineNumber);
    int lineNumber();
    void setFilePath(QUrl filePath);
    QUrl filePath();

signals:

    void lineNumberChanged(int lineNumber);
    void filePathChanged(QUrl filePath);

public slots:

    void nextLine();
    void puaseReading();
    void continueReading();
    void clear();

private:

    int *m_lineNumber;
    QUrl *m_filePath;
};

#endif // GCODEREADER_H
