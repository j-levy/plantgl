import os

from openalea.plantgl.gui.qt import QT_API, PYQT5_API, PYQT4_API, PYSIDE_API, PYSIDE2_API
from openalea.plantgl.config import PGL_QT_VERSION

try:
    if os.environ[QT_API] in PYSIDE2_API:
        from PySide2.Qt3DAnimation import *
        from PySide2.Qt3DCore import *
        from PySide2.Qt3DExtras import *
        from PySide2.Qt3DInput import *
        from PySide2.Qt3DLogic import *
        from PySide2.Qt3DRender import *
    else:
        raise NotImplementedError

except ImportError as e:
    message = 'You must install %s-tools' % os.environ['QT_API']
    e.args = (message,)
    raise e