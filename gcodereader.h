#ifndef GCODEREADER_H
#define GCODEREADER_H

#include <QObject>
#include <QUrl>
#include <QBuffer>
#include <QFile>
#include <QStringList>

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

    void g0(qreal x, qreal y, qreal z, qreal e, qreal f, int s);    //rapid linear move
    void g1(qreal x, qreal y, qreal z, qreal e, qreal f, int s);    //linear move
    void g2(qreal x, qreal y, qreal i, qreal j, qreal e, qreal f);    //clockwise arc
    void g3(qreal x, qreal y, qreal i, qreal j, qreal e, qreal f);    //counter-clockwise arc
    void g4(int p);    //pause the machine for a period of time
    void g10(qreal s);    //retracts the filament
    void g11(qreal s);    //unretracts the filament
    void g28(bool x, bool y, bool z);    //moves to origin/home
    void g90();    //sets absolute positioning
    void g91();    //sets relative positioning
    void g92(bool xB, bool yB, bool zB, bool eB, qreal x, qreal y, qreal z, qreal e);    //set position
    void m0(int p, int s);    //stop
    void m1();    //sleep
    void m82();    //sets extruder to absolut mode
    void m83();    //sets extuder to relative mode
    void m104(int s);   //set extruder temperature
    void m106(int p, int s);    //turn fan on
    void m107();    //turn fan off
    void m109(int s, int r);    //set extruder temperature and wait
    void m110(int n);    //set current line number
    void m112();    //emergency stop
    void m116(int p, int h);    //wait until heating/cooling finished
    void m140(int s);    //set bed temperature
    void m190(int s);    //wait for bed temperature to reach target temperature
    void m200(int d);    //set filament diameter
    void m201(qreal x, qreal y, qreal z, qreal e);    //set max printing acceleration
    void m202(qreal x, qreal y, qreal z, qreal e);    //set max travel acceleration
    void m203(qreal x, qreal y, qreal z, qreal e);    //set max feedrate
    void m204(qreal p, qreal t);    //set default acceleration
    void m400();    //wait for current moves to finish
    void lineNumberChanged(int lineNumber);
    void filePathChanged(QUrl filePath);
    void logEntry(QString logMessage, int code);
    void error(QString errorMessage);

public slots:

    bool startReading();
    bool load();
    void nextLine();
    void clear();

private:

    bool readline(int lineNumber);
    QStringList breakUpString(QString string);

    qreal *m_unit;
    int *m_lineNumber;
    QUrl *m_filePath;
    QByteArray *m_file;
    QBuffer *m_buffer;
    qint64 *m_pos;
};

#endif // GCODEREADER_H
