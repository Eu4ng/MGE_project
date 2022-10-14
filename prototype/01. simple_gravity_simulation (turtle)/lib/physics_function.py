import numpy as np

def CalPosByVelocity(pos, velocity, time):
    return pos + velocity * time

def CalVerticesByPos(vertices, pos):
    return vertices + pos

# 2D position check ex) [[1,5]]
def CheckShapePos(_pos):
    pos = np.array(_pos)
    if pos.shape == (1,2):
        return pos
    else:
        print("CheckShapePos Failed")
        quit()

# 2D vertices check ex) [[1,5]]
def CheckShapeVertices(_vertices):
    vertices = np.array(_vertices)
    if vertices.shape[1] == 2:
        return vertices
    else:
        print("CheckShapeVertices Failed")
        quit()

# 2D velocity check ex) [[1,5]]
def CheckShapeVelocity(_velocity):
    velocity = np.array(_velocity)
    if velocity.shape == (1,2):
        return velocity
    else:
        print("CheckShapeVelocity Failed")
        quit()

def CheckShape2D(name, list):
    vect = np.array(list)
    if vect.shape == (1,2):
        return vect
    else:
        print("CheckShape2D Failed: " + name)
        quit()