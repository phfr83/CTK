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

#ifndef __ctkCallback_h
#define __ctkCallback_h

// Qt includes
#include <QObject>

// CTK includes
#include "ctkCoreExport.h"

//---------------------------------------------------------------------------
class CTK_CORE_EXPORT ctkCallback : public QObject
{
  Q_OBJECT
public:

  ctkCallback(QObject * parentObject = 0);
  ctkCallback(void (*callback)(void * data), QObject * parentObject = 0);
  virtual ~ctkCallback();

  /// Returns the current pointer function
  void (*callback()const)(void*);
  /// Sets a pointer function to call when invoke() is called.
  void setCallback(void (*callback)(void * data));
  
  /// Returns the current callback data.
  /// \note By default ctkCallback itself will be passed has callback data
  /// \sa setCallbackData
  void * callbackData()const;
  /// Set callback data
  void setCallbackData(void * data);
  
public slots:
  /// Internally calls the pointer function \a callback.
  virtual void invoke();
  
private:
  void (*Callback)(void * data);
  void * CallbackData;
};

#endif

