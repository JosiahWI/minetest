#!/usr/bin/env python3
from minetest_env import Minetest

seed = 42
env = Minetest(seed=seed)
obs = env.reset()
render = False
done = False
while not done:
    try:
        action = env.action_space.sample()
        obs, rew, done, info = env.step(action)
        if render:
            env.render()
    except KeyboardInterrupt:
        break
env.close()