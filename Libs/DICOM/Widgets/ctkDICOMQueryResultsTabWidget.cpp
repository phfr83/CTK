/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

// Qt widgets
#include <QDebug>
#include <QTabBar>

// ctkDICOMWidgets includes
#include "ctkDICOMQueryResultsTabWidget.h"

//----------------------------------------------------------------------------
// ctkDICOMQueryResultsTabWidget methods

//----------------------------------------------------------------------------
ctkDICOMQueryResultsTabWidget::ctkDICOMQueryResultsTabWidget(QWidget* parentWidget)
 : Superclass(parentWidget)
{
}

//----------------------------------------------------------------------------
ctkDICOMQueryResultsTabWidget::~ctkDICOMQueryResultsTabWidget()
{
}


//----------------------------------------------------------------------------
void ctkDICOMQueryResultsTabWidget::disableCloseOnTab(int index)
{
  Q_UNUSED(index);
  this->tabBar()->setTabButton(0, QTabBar::RightSide, 0);
  this->tabBar()->setTabButton(0, QTabBar::LeftSide, 0);
}
