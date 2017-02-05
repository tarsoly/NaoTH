from matplotlib import pyplot as plt
from matplotlib.patches import Circle
import field_info as f
import matplotlib as mpl


def draw_field():  # Todo use field_info

    mpl.rcParams['lines.linewidth'] = 2
    mpl.rcParams['axes.color_cycle'] = ['white']

    ax = plt.gca()
    ax.plot([0, 0], [-f.y_length * 0.5, f.y_length * 0.5])  # Middle line

    ax.plot([f.x_opponent_groundline, f.x_opponent_groundline], [f.y_left_sideline, f.y_right_sideline])  # opponent ground line
    ax.plot([f.x_own_groundline, f.x_own_groundline], [f.y_right_sideline, f.y_left_sideline])  # own ground line

    ax.plot([f.x_own_groundline, f.x_opponent_groundline], [f.y_left_sideline, f.y_left_sideline])
    ax.plot([f.x_own_groundline, f.x_opponent_groundline], [f.y_right_sideline, f.y_right_sideline])

    ax.plot([f.x_opponent_groundline-f.x_penalty_area_length, f.x_opponent_groundline-f.x_penalty_area_length], [-f.y_penalty_area_length*0.5, f.y_penalty_area_length*0.5])  # opp penalty
    ax.plot([f.x_opponent_groundline, f.x_opponent_groundline-f.x_penalty_area_length], [f.y_penalty_area_length*0.5, f.y_penalty_area_length*0.5])  # opp penalty
    ax.plot([f.x_opponent_groundline, f.x_opponent_groundline-f.x_penalty_area_length], [-f.y_penalty_area_length*0.5, -f.y_penalty_area_length*0.5])  # opp penalty

    ax.plot([f.x_own_groundline+f.x_penalty_area_length, f.x_own_groundline+f.x_penalty_area_length], [-f.y_penalty_area_length*0.5, f.y_penalty_area_length*0.5])  # own penalty
    ax.plot([f.x_own_groundline, f.x_own_groundline+f.x_penalty_area_length], [f.y_penalty_area_length*0.5, f.y_penalty_area_length*0.5])  # own penalty
    ax.plot([f.x_own_groundline, f.x_own_groundline+f.x_penalty_area_length], [-f.y_penalty_area_length*0.5, -f.y_penalty_area_length*0.5])  # own penalty

    # Middle Circle
    ax.add_artist(Circle(xy=(0, 0), radius=f.center_circle_radius, fill=False, edgecolor='white'))
    # Penalty Marks
    ax.add_artist(Circle(xy=(f.x_opponent_groundline - f.x_penalty_mark_distance, 0), radius=f.penalty_cross_radius, color='white'))
    ax.add_artist(Circle(xy=(f.x_own_groundline + f.x_penalty_mark_distance, 0), radius=f.penalty_cross_radius, color='white'))

    # Own goal box
    ax.add_artist(Circle(xy=(f.own_goalpost_right.x, f.own_goalpost_right.y), radius=f.goalpost_radius, color='white'))  # GoalPostRight
    ax.add_artist(Circle(xy=(f.own_goalpost_left.x, f.own_goalpost_left.y), radius=f.goalpost_radius, color='white'))  # GoalPostLeft
    ax.plot([f.x_own_groundline, f.x_own_groundline - f.goal_depth], [-f.goal_width*0.5, -f.goal_width*0.5])  # own goal box
    ax.plot([f.x_own_groundline, f.x_own_groundline - f.goal_depth], [f.goal_width*0.5, f.goal_width*0.5])  # own goal box
    ax.plot([f.x_own_groundline - f.goal_depth, f.x_own_groundline - f.goal_depth], [-f.goal_width*0.5, f.goal_width*0.5])  # own goal box

    # Opp GoalBox
    ax.add_artist(Circle(xy=(f.opponent_goalpost_right.x, f.opponent_goalpost_right.y), radius=f.goalpost_radius, color='white'))  # GoalPostRight
    ax.add_artist(Circle(xy=(f.opponent_goalpost_left.x, f.opponent_goalpost_left.y), radius=f.goalpost_radius, color='white'))  # GoalPostLeft
    ax.plot([f.x_opponent_groundline, f.x_opponent_groundline + f.goal_depth], [-f.goal_width*0.5, -f.goal_width*0.5])  # Opp goal box
    ax.plot([f.x_opponent_groundline, f.x_opponent_groundline + f.goal_depth], [f.goal_width*0.5, f.goal_width*0.5])  # Opp goal box
    ax.plot([f.x_opponent_groundline + f.goal_depth, f.x_opponent_groundline + f.goal_depth], [-f.goal_width*0.5, f.goal_width*0.5])  # Opp goal box

    ax.set_xlim([-f.x_field_length * 0.5, f.x_field_length * 0.5])
    ax.set_ylim([-f.y_field_length * 0.5, f.y_field_length * 0.5])
    ax.set_axis_bgcolor('green')
    ax.set_aspect("equal")
