import PySide2
from PySide2.QtCore import QPoint, QRect, QSize, QUrl, qAtan2
# from openalea.plantgl.gui.pglnqgl import *

from PySide2 import QtWidgets
from PySide2 import QtCore
from PySide2 import QtGui
from PySide2.QtGui import QVector3D, QColor, QWindow, qRgb
from PySide2.QtWidgets import QApplication

from PySide2.Qt3DCore import Qt3DCore
from PySide2.Qt3DExtras import Qt3DExtras
from PySide2.Qt3DRender import Qt3DRender
from PySide2.Qt3DInput import Qt3DInput

class Qt3dViewerWidget(QtWidgets.QWidget):
    def __init__(self, parent: QtWidgets.QWidget = None):
        super().__init__(parent)
        
        minScreenSize = QSize(300, 200)
        maxScreenSize = QSize(800, 600)
        self.setMinimumSize(minScreenSize)
        self.setMaximumSize(maxScreenSize)
        self.setSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        self.setFocusPolicy(QtCore.Qt.TabFocus)

        self.view = Qt3DViewer()
        self.container = self.createWindowContainer(self.view, self)
        self.setSizePolicy(QtWidgets.QSizePolicy.Maximum, QtWidgets.QSizePolicy.Maximum)

        self.view.addLight(50, 100, 100, intensity = 1.7, color="pink")
        self.view.addLight(-50, 100, -100, intensity = 1.7, color="green")
        self.view.addModel("/home/levy/lpy/src/openalea/lpy/gui/catalog/assets/teapot/teapot.obj")
        self.view.resetCamera()

    def show(self):
        super().show()
        self.view.show()

    def resizeEvent(self, event: QtGui.QResizeEvent):
        self.container.resize(event.size().width(), event.size().height())
        return super().resizeEvent(event)



       
        

class Qt3DViewer(Qt3DExtras.Qt3DWindow):
    def __init__(self) -> None:
        super(Qt3DViewer, self).__init__()
        self.defaultFrameGraph().setClearColor(qRgb(22, 54, 92))
        self.rootEntity = Qt3DCore.QEntity()
        self.setRootEntity(self.rootEntity)

        # Camera
        self.captureCamera = Qt3DRender.QCamera()


        self.captureCamera.lens().setPerspectiveProjection(45.0, 16.0/9.0, 0.1, 1000)
        self.defaultFrameGraph().setCamera(self.camera())

        # For camera controls
        self.camController = Qt3DExtras.QOrbitCameraController (self.rootEntity)
        self.camController.setLinearSpeed(200) # disable linear speed, no translation allowed.
        self.camController.setLookSpeed(-500)
        
        self.camController.setCamera(self.camera())
        self.resetCamera()
        self.defaultFrameGraph().dumpObjectTree()
        # # Material
        # qcolor = QColor("cyan")
        # self.material = Qt3DExtras.QDiffuseSpecularMaterial(self.rootEntity)
        # self.material.setAmbient(qcolor)

        # self.add_plane(40, 80, QSize(300, 400), 0, x, y, z)

    def camera(self):
        return self.captureCamera

    def resetDefaultScene(self):
        # Root entity
        for child in self.rootEntity.children():

            if isinstance(child, Qt3DCore.QEntity) and not(isinstance(child, Qt3DExtras.QOrbitCameraController)) and not(isinstance(child.children()[0], Qt3DRender.QPointLight)):
                print(f"remove: {child}")
                child.setEnabled(False)

    def keyPressEvent(self, arg__1: QtGui.QKeyEvent):
        print(f"key press: {arg__1}")
        if arg__1.key() == QtCore.Qt.Key_R:
            self.resetCamera()
            print("Reset camera")
            arg__1.accept()
            return True
        elif arg__1.key() == QtCore.Qt.Key_1:
            self.addModel("/home/levy/lpy/src/openalea/lpy/gui/catalog/assets/leucopholis-irrorata/Leucopholis_irrorata.obj")
        elif arg__1.key() == QtCore.Qt.Key_2:
            self.addModel("/home/levy/lpy/src/openalea/lpy/gui/catalog/assets/teapot/teapot.obj")
        elif arg__1.key() == QtCore.Qt.Key_3:
            self.addModel("/home/levy/lpy/src/openalea/lpy/gui/catalog/assets/teddy/teddy.obj")
        elif arg__1.key() == QtCore.Qt.Key_Space:
            self.resetDefaultScene()
        elif arg__1.key() == QtCore.Qt.Key_P:
            self.screenshot = self.capture()
        elif arg__1.key() == QtCore.Qt.Key_S:
            import pry; pry()
        else:
            return super().keyPressEvent(arg__1)

    def wheelEvent(self, arg__1: QtGui.QWheelEvent):
        numDegrees: QtCore.QPoint = arg__1.angleDelta() / 8
        # super().wheelEvent(arg__1)
        # self.camera().setViewCenter(QVector3D(0,0,0))
        # return True

        print(numDegrees)
        if numDegrees.y() > 0:
            keyPress = QtGui.QKeyEvent(QtCore.QEvent.Type.KeyPress, QtCore.Qt.Key_PageUp, QtCore.Qt.ShiftModifier)
            self.keyPressEvent(keyPress)
            return True
        elif numDegrees.y() < 0:
            keyPress = QtGui.QKeyEvent(QtCore.QEvent.Type.KeyPress, QtCore.Qt.Key_PageDown, QtCore.Qt.ShiftModifier)
            self.keyPressEvent(keyPress)
            return True
        else:
            return super().wheelEvent(arg__1)

    def resetCamera(self) -> None:
        self.camera().setPosition(QVector3D(0, 0, 15))
        self.camera().setViewCenter(QVector3D(0, 0, 0))
        self.camera().setUpVector(QVector3D(0, 1, 0))

    def addModel(self, filePath: str) -> None:
        sceneLoaderEntity = Qt3DCore.QEntity(self.rootEntity)
        loader = Qt3DRender.QSceneLoader(sceneLoaderEntity)
        loader.setObjectName(filePath)
        sceneLoaderEntity.addComponent(loader)
        loader.setSource(QUrl(f"file:{filePath}"))

        loaderTransform = Qt3DCore.QTransform(sceneLoaderEntity)
        loaderTransform.setTranslation(QVector3D(0, 0, 0))
        sceneLoaderEntity.addComponent(loaderTransform)

    def addLight(self, x, y, z, intensity: float = 1.0, color: str = "white"):
        self.lightEntity = Qt3DCore.QEntity(self.rootEntity)

        self.light = Qt3DRender.QPointLight(self.lightEntity)
        self.light.setColor(color)
        self.light.setIntensity(intensity)
        self.lightEntity.addComponent(self.light)

        lightTransform = Qt3DCore.QTransform(self.lightEntity)
        lightTransform.setTranslation(QVector3D(x, y, z))
        self.lightEntity.addComponent(lightTransform)

    def capture(self):
        framegraph = self.defaultFrameGraph()
        camSelector = framegraph.findChild(Qt3DRender.QCamera)
        print(f"camSelector: {camSelector}")
        renderCapture = Qt3DRender.QRenderCapture(camSelector)
        framegraph.dumpObjectTree()
        self.screenshot = renderCapture.requestCapture()
        print(self.screenshot.image())
    
    def switchFrameGraph(self):
        framegraph = self.activeFrameGraph()
        self.frameGraph = framegraph


    def add_cylinder(self, radius, length, x, y, z, rings=10, slices=10) -> None:

        cylinderEntity = Qt3DCore.QEntity(self.rootEntity)
        cylinderMesh = Qt3DExtras.QCylinderMesh()
        cylinderMesh.setRadius(radius)
        cylinderMesh.setLength(length)
        cylinderMesh.setSlices(rings)
        cylinderMesh.setRings(slices)
        cylinderTransform = Qt3DCore.QTransform()
        cylinderTransform.setTranslation(QVector3D(x, y, z))

        cylinderEntity.addComponent(cylinderMesh)
        cylinderEntity.addComponent(self.material)
        cylinderEntity.addComponent(cylinderTransform)

        self.cylinders.append(cylinderEntity)
        self.meshes.append(cylinderMesh)
        self.transforms.append(cylinderTransform)

        return cylinderEntity



if __name__ == '__main__':
    qApp = QApplication([])
    # viewer.
    # viewer.display(Scene([Sphere()]))
    qt3dwidget = Qt3dViewerWidget()
    qt3dwidget.show()

    qApp.exec_()