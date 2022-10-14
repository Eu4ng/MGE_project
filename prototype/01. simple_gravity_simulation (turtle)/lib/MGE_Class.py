from lib.physics_function import *

class GameObject:
    def __init__(self, object):
        self.name = object['name']
        self.mass = object['mass']
        self.pos = CheckShape2D('_pos', object['_pos'])
        self.velocity = CheckShape2D('_velocity', object['_velocity'])
        self.gravity_factor = 1
        self.apply_gravity = True

    def SetGravity(self, gravity):
        if self.apply_gravity:
            self.gravity_force = self.mass * gravity * self.gravity_factor
        else:
            self.gravity_force = CheckShape2D('no_apply_gravity', [[0,0]])
    
    def CalFinalPos(self, delta_time):
        final_force = self.gravity_force # 나중에 외부에서 가해지는 힘 추가 예정
        velocity_change = (final_force / self.mass) * delta_time # 등가속도 운동 한정
        final_velocity = self.velocity + velocity_change

        final_pos = self.pos + 0.5 * (self.velocity + final_velocity) * delta_time

        self.pos = final_pos
        self.velocity = final_velocity