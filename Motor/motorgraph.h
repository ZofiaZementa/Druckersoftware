#ifndef MOTORGRAPH_H
#define MOTORGRAPH_H

#include <QObject>

typedef struct GraphElement{

    int motorPosition;
    int rpm;
}GraphElement;

class MotorGraph : public QObject
{
    Q_OBJECT
public:
    explicit MotorGraph(QObject *parent = 0);
    ~MotorGraph();

    void setGraphCount(int count);
    int graphCount();
    GraphElement currentPoint(int graph);
    int currentIndex(int graph);
    GraphElement getNextPoint(int graph);
    GraphElement pointAt(int graph, int x);
    void appendPoint(int graph, GraphElement data);
    void markLastAsGarbage(int graph);
    void setAutoGarbageCollection(bool on);
    bool autoGarbageCollection();
    void setAutoGarbageCollectionThreshold(int threshold);
    int autoGarbageCollectionThreshold();

signals:

public slots:

private:

    void collectGarbage();

    QList<QList<GraphElement>> *m_graphs;
    QList<int> *m_counter;
    bool *m_autoGarbageCollection;
    int *m_autoGarbageCollectionThreshold;

};

#endif // MOTORGRAPH_H
