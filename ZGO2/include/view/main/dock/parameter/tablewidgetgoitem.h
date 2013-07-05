#ifndef TABLEWIDGETGOITEM_H
#define TABLEWIDGETGOITEM_H
/**
 * The table widget with GO parameter flag.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include <QTableWidgetItem>

class TableWidgetGOItem : public QTableWidgetItem
{
public:
    enum GOParameterType
    {
        PARAMETER_POSITION_X,
        PARAMETER_POSITION_Y,
        PARAMETER_TEXT,
        PARAMETER_ID,
        PARAMETER_TYPE,
        PARAMETER_PROBABILITY_0,
        PARAMETER_PROBABILITY_1,
        PARAMETER_PROBABILITY_2,
        PARAMETER_PROBABILITY_MULTIPLE,
        PARAMETER_OUTPUT,
        PARAMETER_GO_9_X,
        PARAMETER_GO_9_Y,
        PARAMETER_GO_11_K,
        PARAMETER_GO_MARKOV_FAILURE,
        PARAMETER_GO_MARKOV_REPAIR,
        PARAMETER_GO_MARKOV_REPAIR_TIME,
        PARAMETER_GO_MARKOV_EQUIVALENT_I,
        PARAMETER_GO_MARKOV_EQUIVALENT_L,
        PARAMETER_GO_MARKOV_EQUIVALENT_J,
        PARAMETER_GO_MARKOV_COMMON_CAUSE,
        PARAMETER_GO_MARKOV_FAILURE_1,
        PARAMETER_GO_MARKOV_REPAIR_1,
        PARAMETER_GO_MARKOV_REPAIR_TIME_1,
        PARAMETER_GO_MARKOV_FAILURE_2,
        PARAMETER_GO_MARKOV_REPAIR_2,
        PARAMETER_GO_MARKOV_REPAIR_TIME_2
    };
    TableWidgetGOItem(const QString &text);
    TableWidgetGOItem(const double value);
    GOParameterType parameterType() const;
    void setParameterType(GOParameterType type);

protected:
    GOParameterType _parameterType;
};

#endif // TABLEWIDGETGOITEM_H
