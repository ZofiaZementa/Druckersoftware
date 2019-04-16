#include "motorgraph.h"

MotorGraph::MotorGraph(QObject *parent) : QObject(parent)
{

    m_graphs = new QList<QList<GraphElement>>;
    m_counter = new QList<int>;
    m_autoGarbageCollection = new bool;
    m_autoGarbageCollectionThreshold = new int;
}

MotorGraph::~MotorGraph()
{

    delete m_graphs;
    delete m_counter;
    delete m_autoGarbageCollection;
    delete m_autoGarbageCollectionThreshold;
}

void MotorGraph::setGraphCount(int count)
{

    if(m_counter < count){

        for(int i = 0;i < count - m_counter;i++){

            QList<GraphElement> t;

            m_counter->append(0);
            m_graphs->append(t);
        }
    }

    else if(count < m_counter){

        for(int i = 0;i < m_counter - count;i++){

            m_counter->removeLast();
            m_graphs->removeLast();
        }
    }
}

int MotorGraph::graphCount()
{

    return m_counter->count();
}

GraphElement MotorGraph::currentPoint(int graph)
{

    return m_graphs->at(graph).at(m_counter->at(graph));
}

int MotorGraph::currentIndex(int graph)
{

    return m_counter->at(graph);
}

GraphElement MotorGraph::getNextPoint(int graph)
{

    (*m_counter)[graph]++;

    if(*m_autoGarbageCollection == true){

        collectGarbage(graph);
    }

    return m_graphs->at(graph).at(m_counter->at(graph));
}

GraphElement MotorGraph::pointAt(int graph, int x)
{

    return m_graphs->at(graph).at(x);
}

void MotorGraph::appendPoint(int graph, GraphElement data)
{

    return m_graphs->at(graph).append(data);
}

void MotorGraph::markLastAsGarbage(int graph)
{

    m_graphs->at(graph).removeAt(m_counter->at(graph) - 1);
}

void MotorGraph::setAutoGarbageCollection(bool on)
{

    *m_autoGarbageCollection = on;
}

bool MotorGraph::autoGarbageCollection()
{

    return *m_autoGarbageCollection;
}

void MotorGraph::setAutoGarbageCollectionThreshold(int threshold)
{

    *m_autoGarbageCollectionThreshold = threshold;
}

int MotorGraph::autoGarbageCollectionThreshold()
{

    return *m_autoGarbageCollectionThreshold;
}

void MotorGraph::collectGarbage(int graph)
{

    if(m_counter->at(graph) - *m_autoGarbageCollection > 0){

        for(int i = 0;m_counter->at(graph) - *m_autoGarbageCollection;i++){

            m_graphs->at(graph).removeFirst();
            (*m_counter)[graph]--;
        }
    }
}
