/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "QmitkControlPointDialog.h"

#include <QAbstractItemModel>
#include <QStringListModel>
#include <QLabel>
#include <QLayout>
#include <qpushbutton.h>

QmitkControlPointDialog::QmitkControlPointDialog(QWidget* parent)
  : QDialog(parent)
{
  //QDialog::setFixedSize(250, 105);

  QBoxLayout* verticalLayout = new QVBoxLayout(this);
  verticalLayout->setMargin(5);
  verticalLayout->setSpacing(5);

  QLabel* dateLabel = new QLabel(tr("Set date"), this);
  verticalLayout->addWidget(dateLabel);

  m_DateEdit = new QDateEdit(this);
  m_DateEdit->setDisplayFormat("yyyy-MM-dd");
  m_DateEdit->setFocus();
  verticalLayout->addWidget(m_DateEdit);

  QPushButton* acceptButton = new QPushButton(tr("Ok"), this);
  QPushButton* cancelButton = new QPushButton(tr("Cancel"), this);
  acceptButton->setDefault(true);

  connect(acceptButton, SIGNAL(clicked()), SLOT(accept()));
  connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));

  QBoxLayout* horizontalLayout = new QHBoxLayout();
  horizontalLayout->setSpacing(5);
  horizontalLayout->addStretch();
  horizontalLayout->addWidget(acceptButton);
  horizontalLayout->addWidget(cancelButton);
  verticalLayout->addLayout(horizontalLayout);
}

QmitkControlPointDialog::~QmitkControlPointDialog()
{
}

void QmitkControlPointDialog::SetCurrentDate(SemanticTypes::Date currentDate)
{
  m_DateEdit->setDate(QDate(currentDate.year, currentDate.month, currentDate.day));
}

QDate QmitkControlPointDialog::GetCurrentDate() const
{
  return m_DateEdit->date();
}
