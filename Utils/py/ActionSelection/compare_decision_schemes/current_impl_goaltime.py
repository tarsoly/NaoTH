import math
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.patches import Circle
from tools import action as a
from tools import Simulation as Sim
from naoth import math2d as m2d
from tools import tools
from tools import field_info as field
from tools import raw_attack_direction_provider as attack_dir


class State:
    def __init__(self):
        self.pose = m2d.Pose2D()
        self.pose.translation = m2d.Vector2(-4000, -700)
        self.pose.rotation = math.radians(-40)

        self.ball_position = m2d.Vector2(100.0, 0.0)
        self.rotation_vel = 60  # degrees per sec
        self.walking_vel = 200  # mm per sec
        self.obstacle_list = ([])  # is in global coordinates

    def update_pos(self, glob_pos, rotation):
        self.pose.translation = glob_pos
        self.pose.rotation = rotation


def draw_robot_walk(actions_consequences, state, expected_ball_pos, best_action):
    plt.clf()
    axes = plt.gca()
    origin = state.pose.translation
    arrow_head = m2d.Vector2(500, 0).rotate(state.pose.rotation)
    x = np.array([])
    y = np.array([])

    tools.draw_field()
    axes.add_artist(Circle(xy=(state.pose.translation.x, state.pose.translation.y), radius=100, fill=False, edgecolor='white'))
    axes.add_artist(Circle(xy=(expected_ball_pos.x, expected_ball_pos.y), radius=120, fill=True, edgecolor='blue'))
    axes.arrow(origin.x, origin.y, arrow_head.x, arrow_head.y, head_width=100, head_length=100, fc='k', ec='k')
    axes.text(0, 0, best_action, fontsize=12)
    for consequence in actions_consequences:
        for particle in consequence.positions():
            ball_pos = state.pose * particle.ball_pos  # transform in global coordinates

            x = np.append(x, [ball_pos.x])
            y = np.append(y, [ball_pos.y])

    plt.scatter(x, y, c='r', alpha=0.5)
    plt.pause(0.5)


def main(x, y, state, num_iter):
    start_x = x
    start_y = y
    state.update_pos(m2d.Vector2(start_x, start_y), rotation=0)

    no_action = a.Action("none", 0, 0, 0, 0)
    kick_short = a.Action("kick_short", 780, 150, 8.454482265522328, 6.992268841997358)
    sidekick_left = a.Action("sidekick_left", 750, 150, 86.170795364136380, 10.669170653645670)
    sidekick_right = a.Action("sidekick_right", 750, 150, -89.657943335302260, 10.553726275058064)

    action_list = [no_action, kick_short, sidekick_left, sidekick_right]

    # Todo: Maybe do several decision cycles not just one to get rid of accidental decisions
    timings = []
    for idx in range(num_iter):
        num_kicks = 0
        num_turn_degrees = 0
        goal_scored = False
        total_time = 0
        while not goal_scored:
            actions_consequences = []
            # Simulate Consequences
            for action in action_list:
                single_consequence = a.ActionResults([])
                actions_consequences.append(Sim.simulate_consequences(action, single_consequence, state, a.num_particles))

            # Decide best action
            best_action = Sim.decide_smart(actions_consequences, state)

            # expected_ball_pos should be in local coordinates for rotation calculations
            expected_ball_pos = actions_consequences[best_action].expected_ball_pos

            # Check if expected_ball_pos inside opponent goal
            opp_goal_back_right = m2d.Vector2(field.opponent_goalpost_right.x + field.goal_depth, field.opponent_goalpost_right.y)
            opp_goal_box = m2d.Rect2d(opp_goal_back_right, field.opponent_goalpost_left)

            goal_scored = opp_goal_box.inside(state.pose * expected_ball_pos)
            inside_field = field.field_rect.inside(state.pose * expected_ball_pos)

            # Assert that expected_ball_pos is inside field or inside opp goal
            if not inside_field and not goal_scored:
                # print("Error: This position doesn't manage a goal")
                total_time = float('inf')
                break

            if not action_list[best_action].name == "none":

                # draw_robot_walk(actions_consequences, state, state.pose * expected_ball_pos, action_list[best_action].name)

                # calculate the time needed
                rotation = np.arctan2(expected_ball_pos.y, expected_ball_pos.x)
                rotation_time = np.abs(rotation / state.rotation_vel)
                distance = np.hypot(expected_ball_pos.x, expected_ball_pos.y)
                distance_time = distance / state.walking_vel
                total_time += distance_time + rotation_time

                # update the robots position
                state.update_pos(state.pose * expected_ball_pos, state.pose.rotation + rotation)
                num_kicks += 1

            elif action_list[best_action].name == "none":
                # print(str(state.pose * expected_ball_pos) + " Decision: " + str(action_list[best_action].name))
                # draw_robot_walk(actions_consequences, state, state.pose * expected_ball_pos, action_list[best_action].name)

                # Calculate rotation time
                total_time += np.abs(math.radians(10) / state.rotation_vel)

                attack_direction = attack_dir.get_attack_direction(state)
                # Todo: can run in a deadlock for some reason
                if attack_direction > 0:
                    state.update_pos(state.pose.translation, state.pose.rotation + math.radians(10))  # Should be turn right
                else:
                    state.update_pos(state.pose.translation, state.pose.rotation - math.radians(10))  # Should be turn left

                num_turn_degrees += 1

        # print("Num Kicks: " + str(num_kicks))
        # print("Num Turns: " + str(num_turn_degrees))
        # print("Total time to goal: " + str(total_time))
        timings.append(total_time)
    return timings


if __name__ == "__main__":
    state = State()
    total_time = main(state.pose.translation.x, state.pose.translation.y, state, num_iter=1)

    print("Total time to goal: " + str(total_time))
