"""
Provides QtCore classes and functions.
"""
import os

from openalea.plantgl.gui.qt import QT_API, PYQT5_API, PYQT4_API, PYSIDE_API, PYSIDE2_API
from openalea.plantgl.config import PGL_QT_VERSION

# os.environ[QT_API] may not be properly set when multiple bindings are installed
# for example, if PyQt5 is installed alone,  os.environ[QT_API] = ['PyQt5']
# but when PySide2 is installed along with PyQt5, it overrides the environment variable, setting os.environ[QT_API] = ['PySide2'] only
# it could be a side-effect of the PySide2 conda package (thanks, conda /S)
# so checking the environment variable may not lead to what we want.
# Instead, let's reckon this: PlantGL currently relies solely on PyQt5 which is the only supported binding for most of the features.
# In particular, PyQGLViewer only exposes PyQt5 bindings so we must comply with that.
# Some features must include PySide2 instead (like Qt3D) which are manually specified.

from PyQt5.QtCore import *
# compatibility with pyside
from PyQt5.QtCore import pyqtSignal as Signal
from PyQt5.QtCore import pyqtSlot as Slot
from PyQt5.QtCore import pyqtProperty as Property
# use a common __version__
from PyQt5.QtCore import QT_VERSION_STR as __version__
    
"""
if os.environ[QT_API] in PYSIDE2_API:
    from PySide2.QtCore import *
    from PySide2.QtCore import QSortFilterProxyModel
    # use a common __version__
    import PySide2.QtCore
    __version__ = PySide2.QtCore.__version__
elif os.environ[QT_API] in PYQT5_API:
    from PyQt5.QtCore import *
    # compatibility with pyside
    from PyQt5.QtCore import pyqtSignal as Signal
    from PyQt5.QtCore import pyqtSlot as Slot
    from PyQt5.QtCore import pyqtProperty as Property
    # use a common __version__
    from PyQt5.QtCore import QT_VERSION_STR as __version__
"""

