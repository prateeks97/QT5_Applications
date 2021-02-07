#include "calculator.h"
#include "ui_calculator.h"

double calcValue = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
double memoryValue = 0.0;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcValue));
    QPushButton *numButtons[10];
    for(int i=0; i<10; ++i){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton * >(butName);
        connect(numButtons[i], SIGNAL(released()), this, SLOT(NumPressed()));
    }
    connect(ui->Add, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->Substract, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->Multiply, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->Divide, SIGNAL(released()), this, SLOT(MathButtonpressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this, SLOT(ChangenumberSign()));
    connect(ui->Equals, SIGNAL(released()), this, SLOT(EqualbuttonPressed()));
    connect(ui->All_Clear, SIGNAL(released()), this, SLOT(Clear()));

    connect(ui->MemAdd, SIGNAL(released()), this, SLOT(MemAdd()));
    connect(ui->MemClear, SIGNAL(released()), this, SLOT(MemClear()));
    connect(ui->MemGet, SIGNAL(released()), this, SLOT(MemRetrieve()));
}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butValue = button->text();
    QString dispValue = ui->Display->text();
    if((dispValue.toDouble() == 0) || (dispValue.toDouble() == 0.0)){
        ui->Display->setText(butValue);
    }
    else{
        QString newVal = dispValue + butValue;
        double dblValue = newVal.toDouble();
        ui->Display->setText(QString::number(dblValue, 'g', 16));
    }
}

void Calculator::MathButtonpressed(){
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString dispValue = ui->Display->text();
    calcValue = dispValue.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butValue = button->text();
    if (QString::compare(butValue, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    }
    else if (QString::compare(butValue, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    }
    else if (QString::compare(butValue, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    }
    else{
        subTrigger = true;
    }
    ui->Display->setText("");
}

void Calculator::EqualbuttonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if (addTrigger){
            solution = calcValue + dblDisplayVal;
        }
        else if (subTrigger){
            solution = calcValue - dblDisplayVal;
        }
        else if (multTrigger){
            solution = calcValue * dblDisplayVal;
        }
        else{
            solution = calcValue / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangenumberSign(){
    QString displayVal = ui->Display->text();
    double numbers = displayVal.toDouble();
    numbers = -1 * numbers;
    ui->Display->setText(QString::number(numbers));
}

void Calculator::Clear(){
    ui->Display->setText("");
}

void Calculator::MemAdd(){
    QString displayVal = ui->Display->text();
    double numbers = displayVal.toDouble();
    memoryValue = numbers;
}

void Calculator::MemClear(){
    memoryValue = 0.0;
}

void Calculator::MemRetrieve(){
    ui->Display->setText(QString::number(memoryValue));
}
