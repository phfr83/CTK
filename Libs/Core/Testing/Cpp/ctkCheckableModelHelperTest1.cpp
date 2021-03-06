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

// Qt includes
#include <QCoreApplication>
#include <QDebug>
#include <QFocusEvent>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTimer>

// CTK includes
#include "ctkCheckableModelHelper.h"

// STD includes
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------------------
int ctkCheckableModelHelperTest1(int argc, char * argv [] )
{
  QCoreApplication app(argc, argv);

  QStandardItemModel model;
  QList<QStandardItem*> row0;
  row0 << new QStandardItem << new QStandardItem << new QStandardItem;
  row0[0]->setText("not user checkable");
  model.appendRow(row0);
  QList<QStandardItem*> row1;
  row1 << new QStandardItem << new QStandardItem << new QStandardItem;
  row1[0]->setCheckable(true);
  row1[0]->setText("checkable");
  model.appendRow(row1);
  QList<QStandardItem*> row2;
  row2 << new QStandardItem << new QStandardItem << new QStandardItem;
  row2[0]->setCheckable(true);
  row2[0]->setText("checkable");
  model.appendRow(row2);

  // items are unchecked by default 
  if (row0[0]->checkState() != Qt::Unchecked ||
      row1[0]->checkState() != Qt::Unchecked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "QStandardItem default failed: "
	      << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  // Header is checked by default
  model.setHeaderData(0, Qt::Horizontal, Qt::Checked, Qt::CheckStateRole);

  ctkCheckableModelHelper* modelHelper =
    new ctkCheckableModelHelper(Qt::Horizontal);
  modelHelper->setModel(&model);
  // propagatetoitems is true by default
  //modelHelper->setPropagateToItems(true);

  // As propagateToItems is true, once the model is set to the modelHelper,
  // the checkable header is updated from the check state of all the items
  // all the items are unchecked by default, so the header becomes unchecked
  if (modelHelper->headerCheckState(0) != Qt::Unchecked ||
      row0[0]->checkState() != Qt::Unchecked ||
      row1[0]->checkState() != Qt::Unchecked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "ctkCheckableModelHelper::checkstate() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
	      << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }
  // Retrieve checkstate of the header
  Qt::CheckState checkstate;
  if (!modelHelper->headerCheckState(0, checkstate))
    {
    std::cerr << "ctkCheckableModelHelper::checkstate() failed: "
              << static_cast<int>(checkstate) << std::endl;
    return EXIT_FAILURE;
    }

  if (modelHelper->propagateDepth() == 0)
    {
    std::cerr << "ctkCheckableModelHelper::propagateDepth() failed: "
              << modelHelper->propagateDepth() << std::endl;
    return EXIT_FAILURE;
    }
  modelHelper->setPropagateDepth(0);
  if (modelHelper->propagateDepth() != 0)
    {
    std::cerr << "ctkCheckableModelHelper::propagateDepth() failed: "
              << modelHelper->propagateDepth() << std::endl;
    return EXIT_FAILURE;
    }
  if (modelHelper->headerCheckState(0) != Qt::Unchecked ||
      row0[0]->checkState() != Qt::Unchecked ||
      row1[0]->checkState() != Qt::Unchecked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "ctkCheckableModelHelper::propagateToItems() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
	      << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  // check the header
  modelHelper->setHeaderCheckState(0, Qt::Checked);
  
  // make sure it didn't uncheck the checkable items
  if (modelHelper->headerCheckState(0) != Qt::Checked ||
      row0[0]->checkState() != Qt::Unchecked ||
      row1[0]->checkState() != Qt::Unchecked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << __LINE__ << " ctkCheckableModelHelper::toggleCheckState() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
	      << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  row0[0]->setCheckState(Qt::Checked);
  // make sure it didn't uncheck the checkable items
  if (modelHelper->headerCheckState(0) != Qt::Checked ||
      row0[0]->checkState() != Qt::Checked ||
      row1[0]->checkState() != Qt::Unchecked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "QStandardItem::setCheckState() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
              << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  // The checkable header gets updated with the item check states
  modelHelper->setPropagateDepth(-1);

  if (modelHelper->propagateDepth() == 0 ||
      modelHelper->headerCheckState(0) != Qt::PartiallyChecked ||
      row0[0]->checkState() != Qt::Checked ||
      row1[0]->checkState() != Qt::Unchecked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "ctkCheckableModelHelper::setPropagateToItems() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
              << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  row0[0]->setCheckState(Qt::Unchecked);
  
  if (modelHelper->headerCheckState(0) != Qt::Unchecked ||
      row0[0]->checkState() != Qt::Unchecked ||
      row1[0]->checkState() != Qt::Unchecked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "QStandardItem::setCheckState() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
              << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  row1[0]->setCheckState(Qt::Checked);
  
    // make sure it didn't uncheck the checkable items
  if (modelHelper->headerCheckState(0) != Qt::PartiallyChecked ||
      row0[0]->checkState() != Qt::Unchecked ||
      row1[0]->checkState() != Qt::Checked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "QStandardItem::setCheckState() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
              << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  row1[0]->setCheckState(Qt::Checked);
  
  // make sure it didn't check the checkable items
  if (modelHelper->headerCheckState(0) != Qt::PartiallyChecked ||
      row0[0]->checkState() != Qt::Unchecked ||
      row1[0]->checkState() != Qt::Checked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "QStandardItem::setCheckState() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
              << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  row0[0]->setCheckState(Qt::Checked);
  row2[0]->setCheckState(Qt::Checked);

  // make sure the header is now checked
  if (modelHelper->headerCheckState(0) != Qt::Checked ||
      row0[0]->checkState() != Qt::Checked ||
      row1[0]->checkState() != Qt::Checked ||
      row2[0]->checkState() != Qt::Checked)
    {
    std::cerr << "QStandardItem::setCheckState() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
              << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  modelHelper->setHeaderCheckState(0, Qt::Unchecked);
    
  if (modelHelper->headerCheckState(0) != Qt::Unchecked ||
      row0[0]->checkState() != Qt::Unchecked ||
      row1[0]->checkState() != Qt::Unchecked ||
      row2[0]->checkState() != Qt::Unchecked)
    {
    std::cerr << "ctkCheckableModelHelper::setCheckState() failed: "
              << static_cast<int>(modelHelper->headerCheckState(0)) << " "
              << static_cast<int>(row0[0]->checkState()) << " "
              << static_cast<int>(row1[0]->checkState()) << " "
              << static_cast<int>(row2[0]->checkState()) << std::endl;
    return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
