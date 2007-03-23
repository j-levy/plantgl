#!/usr/bin/env python
"""example1.py

Showing the concept of PlantGL4D.

:version: pon mar 19 17:29:11 CET 2007

:author:  szymon stoma
"""

import openalea.plantgl.all as pgl
import openalea.plantgl.ext.all as pd

a0 = pd.ASphereI()
a0.pos = pgl.Vector3(1,0,1)
a0.axis=pgl.Vector3(1,0,1)
a0.roll=30
a0.radius=0.7
a0.height=15
a0.material=pd.green
a0.visible = False
del a0

a0 = pd.ACylinderI()
a0.pos = pgl.Vector3(1,0,1)
a0.axis=pgl.Vector3(1,0,1)
a0.roll=30
a0.radius=0.7
a0.height=15
a0.material=pd.green
a0.visible = False
del a0

a0 = pd.AArrowI()
a0.pos = pgl.Vector3(1,0,1)
a0.axis=pgl.Vector3(1,0,1)
a0.roll=30
a0.radius=0.7
a0.height=15
a0.material=pd.green

