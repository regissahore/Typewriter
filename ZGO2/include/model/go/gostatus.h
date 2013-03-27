#ifndef GOSTATUS_H
#define GOSTATUS_H
/**
 * The status of the GO operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QVector>
#include <QString>

class GOStatus
{
public:
    GOStatus();
    int number() const;
    void setNumber(int number);
    float probability(int index) const;
    void setProbability(int index, const float value);
    QString description(int index) const;
    void setDescription(int index, const QString value);

protected:
    QVector<float> _probability;
    QVector<QString> _description;
};

#endif // GOSTATUS_H
