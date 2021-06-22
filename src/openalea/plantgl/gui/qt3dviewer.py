from openalea.plantgl.all import *
from openalea.plantgl.gui.qt import qt
from openalea.plantgl.gui.qt.Qt3D import *
from openalea.plantgl.gui.qt.Qt3D import *
from openalea.plantgl.gui.qt.QtCore import QSize
# from openalea.plantgl.gui.pglnqgl import *

from openalea.plantgl.gui.qt.QtGui import QVector3D, QColor


class Qt3DViewer(Qt3DExtras.Qt3DWindow):
    def __init__(self):
        super(Qt3DViewer, self).__init__()

        # Camera
        self.camera().lens().setPerspectiveProjection(45, 16 / 9, 0.1, 1000)
        self.camera().setPosition(QVector3D(0, 0, 40))
        self.camera().setViewCenter(QVector3D(0, 0, 0))

        # For camera controls
        self.createScene()
        self.camController = Qt3DExtras.QOrbitCameraController (self.rootEntity)
        self.camController.setLinearSpeed(-180)
        self.camController.setLookSpeed(-180)
        self.camController.setCamera(self.camera())

        self.setRootEntity(self.rootEntity)

        self.cylinders = []
        self.meshes = []
        self.transforms = []

        radius = 7
        length = 15
        x = 0
        y = 0
        z = 0
        self.add_cylinder(radius, length, x, y, z, rings=30, slices=40)

        self.add_plane(40, 80, QSize(300, 400), 0, x, y, z)

    def createScene(self):
        # Root entity
        self.rootEntity = Qt3DCore.QEntity()

        # Material
        qcolor = QColor("cyan")
        self.material = Qt3DExtras.QDiffuseSpecularMaterial(self.rootEntity)
        self.material.setAmbient(qcolor)

        # self.material = Qt3DExtras.QTextureMaterial(self.rootEntity)
        # self.material.setTexture()
        # self.texture = Qt3DRender.QTextureLoader()

    def add_plane(self, height: float, width: float, resolution: QSize, mirrored, x, y, z):
    
        planeEntity = Qt3DCore.QEntity(self.rootEntity)
        planeMesh = Qt3DExtras.QPlaneMesh()
        planeMesh.setHeight (height)
        planeMesh.setMeshResolution (resolution)
        planeMesh.setMirrored (mirrored)
        planeMesh.setWidth(width)

        planeTransform = Qt3DCore.QTransform()
        planeTransform.setTranslation(QVector3D(x, y, z))

        planeEntity.addComponent(planeMesh)
        planeEntity.addComponent(self.material)
        planeEntity.addComponent(planeTransform)


    def add_cylinder(self, radius, length, x, y, z, rings=10, slices=10):

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


"""
class none():
    def __init__(self, parent = None):
        QGLViewer.__init__(self,  parent)
        self.scene = None
        self.discretizer = Discretizer()
        self.glrenderer = GLRenderer(self.discretizer)
        self.bboxcomputer = BBoxComputer(self.discretizer)
        self.animationMode = eStatic
        self.forceclear = True
        self.camera().setViewDirection(Vec(-1,0,0))
        self.camera().setUpVector(Vec(0,0,1))

    def setScene(self, scene = None):
        self.scene = scene
        if self.animationMode != eAnimatedScene or self.forceclear:
            self.glrenderer.clear()
            self.discretizer.clear()
            self.bboxcomputer.clear()
        if not scene is None:
            self.bboxcomputer.process(self.scene)
            bbx = self.bboxcomputer.result                
            if bbx : 
                self.camera().setSceneBoundingBox(*bbx2qgl(bbx))
            else: print('error computing bbox')

    def display(self,scene = None):
        self.setScene(scene)
        if self.animationMode == eStatic:
            self.showEntireScene()
        self.updateGL()

    def draw(self):        
        if self.scene and self.glrenderer.beginSceneList():
            self.glrenderer.beginProcess()
            self.scene.apply(self.glrenderer)
            self.glrenderer.endProcess()
            self.glrenderer.endSceneList()

    def setAnimation(self,flag):
        self.animationMode = flag
        modemap = { eAnimatedPrimitives : GLRenderer.Dynamic , eAnimatedScene : GLRenderer.DynamicScene, eStatic : GLRenderer.Normal }
        self.glrenderer.renderingMode = modemap[flag]

    def showMessage(self,txt,timeout=0):
        self.displayMessage(txt,timeout)

"""

if __name__ == '__main__':
    qApp = qt.QtGui.QApplication([])
    viewer = Qt3DViewer()
    # viewer.
    # viewer.display(Scene([Sphere()]))
    viewer.show()
    qApp.exec_()