/* 
 * File:   CurveOptionWidget.cc
 * Author: blueck
 * 
 * Created on 21. Oktober 2010, 10:37
 */

#include "CurveOptionWidget.h"

CurveOptionWidget::CurveOptionWidget()
{
    
}

CurveOptionWidget::~CurveOptionWidget()
{
    for(int i=0;i<buttons.size();i++)
    {
        ColorPickerButton* button = buttons[i];
        if(button != NULL)
        {
            delete(button);
        }
    }
    buttons.clear();
    for(int i=0;i<boxes.size();i++)
    {
        QComboBox* box = boxes[i];
        if(box != NULL)
        {
            delete(box);
        }
    }
    boxes.clear();
    for(int i=0;i<spinBoxes.size();i++)
    {
        QSpinBox* spinBox = spinBoxes[i];
        if(spinBox != NULL)
        {
            delete(spinBox);
        }
    }
    spinBoxes.clear();
}

void CurveOptionWidget::updateExistingCurves()
{
    for(int i=0;i<curves.size();i++)
    {
        QwtPlotCurve* curve = curves[i];
        if(curve != NULL)
        {
            QPen pen = curve->pen();
            pen.setColor(buttons[i]->getDisplayColor());
            pen.setWidth(spinBoxes[i]->value());
            curve->setPen(pen);
            QwtPlotCurve::CurveStyle style = (QwtPlotCurve::CurveStyle)boxes[i]->currentIndex();
            curve->setStyle(style);
        }
    }
}

void CurveOptionWidget::initializeLayout(std::vector<QwtPlotCurve*> curves)
{
    QFrame* layoutFrame = new QFrame();
    QGridLayout* baseLayout = new QGridLayout();
    this->curves = curves;
    buttons.resize(curves.size());
    boxes.resize(curves.size());
    spinBoxes.resize(curves.size());
    layout.setAlignment(Qt::AlignTop);
    baseLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
    for(int i=0;i<curves.size();i++)
    {
        QFrame* outerFrame = new QFrame();
        outerFrame->setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
        outerFrame->setLineWidth(2);
        QGridLayout* outerGridLayout = new QGridLayout();
        QwtPlotCurve* curve = curves[i];
        if(curve != NULL)
        {
            QLabel* label = new QLabel(QString::number(i));
            QPen pen = curve->pen();
            
            ColorPickerButton* button = new ColorPickerButton(pen.color());
            buttons[i] = button;

            QSpinBox* spinBox = new QSpinBox();
            spinBox->setValue(pen.width());
            spinBoxes[i] = spinBox;

            QComboBox* combo = new QComboBox();
            combo->addItem("No Curve", QVariant(0));
            combo->addItem("Lines", QVariant(1));
            combo->addItem("Sticks", QVariant(2));
            combo->addItem("Steps", QVariant(3));
            combo->addItem("Dots", QVariant(4));
            combo->setCurrentIndex(curve->style());
            boxes[i] = combo;

            outerGridLayout->setAlignment(Qt::AlignTop);
            outerGridLayout->addWidget(label, i, 0, 1, 1);
            outerGridLayout->addWidget(spinBox, i, 1, 1, 1);
            outerGridLayout->addWidget(combo, i, 2, 1, 1);
            outerGridLayout->addWidget(button, i, 3, 1, 1);

            outerFrame->setLayout(outerGridLayout);
            outerFrame->setMinimumSize(320, 250);
            baseLayout->addWidget(outerFrame, i, 0, 1, 1);
        }
    }
    layoutFrame->setLayout(baseLayout);
    scrollArea.setWidget(layoutFrame);
    scrollArea.setWidgetResizable(true);
    layout.addWidget(&scrollArea);
    setLayout(&layout);
}

