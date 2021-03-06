
import sys

# Importing vtk initializes vtkPythonMap owned by vtkPythonUtil and prevent 
# call to vtkPythonUtil::GetObjectFromPointer() from segfaulting.
# PythonQt internally uses vtkPythonUtil to properly wrap/unwrap VTK objects
from vtk import *

t = _testWrappedVTKQInvokableInstance.getTable()
print t.GetClassName()

t2 = vtkTable()
_testWrappedVTKQInvokableInstance.setTable(t2)
if _testWrappedVTKQInvokableInstance.getTable() != t2:
  sys.exit(1)
  
sys.exit(0)
