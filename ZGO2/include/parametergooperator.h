#ifndef PARAMETERGOOPERATOR_H
#define PARAMETERGOOPERATOR_H
/**
 * The parameter editor for GO operator.
 * @author ZHG <CyberZHG@gmail.com>
 */
#include "parameterabstract.h"

class QPushButton;
class QDoubleSpinBox;

class ParameterGOOperator : public ParameterAbstract
{
    Q_OBJECT
public:
    ParameterGOOperator(QWidget *parent = 0);
    void bindItem(void *item);

protected:
    QDoubleSpinBox *_spinBoxProbability0;
    QDoubleSpinBox *_spinBoxProbability1;
    QDoubleSpinBox *_spinBoxProbability2;
    QPushButton *_buttonMulitpleProbability;
    QSpinBox *_spinBox9X;
    QSpinBox *_spinBox9Y;
    QSpinBox *_spinBox11K;

    void addIDParameter();
    void addTypeParameter();
    void addNameParameter();
    void addIsDrawNameParameter();
    virtual void addOperatorParameter();
    void addFlipParameter();
    void addProbability0Parameter();
    void addProbability12Parameter();
    void addProbabilityMultipleParameter();
    void addOutputParameter();
    virtual void addOperator9XYParameter();
    virtual void addOperator11KParameter();

protected slots:
    void setItemID(int value);
    void setItemName(QString value);
    void setItemIsDrawName(bool value);
    void setItemProbability0(double value);
    void setItemProbability1(double value);
    void setItemProbability2(double value);
    void setItemMultipleProbability();
    virtual void setItem9X(int value);
    virtual void setItem9Y(int value);
    virtual void setItem11K(int value);
    void setItemHorizonFlip(bool value);
    void setItemVerticalFlip(bool value);
};

#endif // PARAMETERGOOPERATOR_H
