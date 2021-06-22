import os

from openalea.plantgl.gui.qt import QT_API, PYQT5_API, PYQT4_API, PYSIDE_API, PYSIDE2_API
from openalea.plantgl.config import PGL_QT_VERSION

try:
    if os.environ[QT_API] in PYSIDE2_API:
        from PySide2.Qt3DAnimation import Qt3DAnimation
        from PySide2.Qt3DCore import Qt3DCore
        from PySide2.Qt3DExtras import Qt3DExtras
        from PySide2.Qt3DInput import Qt3DInput
        from PySide2.Qt3DLogic import Qt3DLogic
        from PySide2.Qt3DRender import Qt3DRender
    else:
        raise NotImplementedError

except ImportError as e:
    message = 'You must install %s-tools' % os.environ['QT_API']
    e.args = (message,)
    raise e