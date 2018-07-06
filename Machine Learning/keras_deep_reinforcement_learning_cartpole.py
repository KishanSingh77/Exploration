
# coding: utf-8

# In[4]:


import random
import gym
import numpy as np
from collections import deque
from keras.models import Sequential
from keras.layers import Dense
from keras.optimizers import Adam


# In[5]:


EPISODES = 1000


# In[21]:


class DQNAgent:
    def __init__(self, state_size, action_size):
        self.state_size = state_size
        self.action_size = action_size
        self.memory = deque(maxlen = 2000)
        self.gamma = 0.95 # discount rate 
        self.epsilon = 1.0 # exploration rate 
        self.epsilon_min = 0.1
        self.epsilon_decay = 0.995
        self.learning_rate = 0.001 # learning rate of neural network
        self.model = self._build_model()
        
    def _build_model(self):
        model = Sequential()
        model.add(Dense(24, input_dim = self.state_size, activation = "relu"))
        model.add(Dense(24, activation = "relu"))
        model.add(Dense(self.action_size, activation = "linear")) #may update to better output layer
        model.compile(loss = "mse", optimizer = Adam(lr = self.learning_rate))
        return model
    
    def remember(self, state, action, reward, next_state, done):
        self.memory.append((state, action, reward, next_state, done))
        
    def act(self, state):
        if random.random() <= self.epsilon:
            return random.randrange(self.action_size)
        act_values = self.model.predict(state)
        # print(act_values)
        # act_values[0] is the  Q(s, a) or Q values, the value represents the 
        # expected value of your maximal score at the end of the game if you were at that 
        # state and played that action 
        # np.amax() determines the value, np.argmax() indexes to the action that generates the maximum value
        return np.argmax(act_values[0]) 
    
    def replay(self, batch_size):
        minibatch = random.sample(self.memory, batch_size)
        for state, action, reward, next_state, done in minibatch:
            target = reward
            if not done: 
                target = target + self.gamma * np.amax(self.model.predict(next_state)[0])
            target_f = self.model.predict(state)
            target_f[0][action] = target
            self.model.fit(state, target_f, epochs = 1, verbose = 0)
        if self.epsilon_min < self.epsilon:
            self.epsilon *= self.epsilon_decay
            
    

                


# In[22]:


def main():
    env = gym.make("CartPole-v0")
    state_size = env.observation_space.shape[0]
    action_size = env.action_space.n
    agent = DQNAgent(state_size, action_size)
    done = False
    batch_size = 32
    
    for e in range(EPISODES):
        state = env.reset()
        state = np.reshape(state, [1, state_size])
        for time in range(500):
            #env.render()
            action = agent.act(state)
            next_state, reward, done, info = env.step(action)
            reward = reward if not done else -10
            next_state = np.reshape(next_state, [1, state_size])
            agent.remember(state, action, reward, next_state, done)
            state = next_state
            if done:
                print("Episode: {} / {}, score: {}, e: {:.2}".format(e, EPISODES, time, agent.epsilon) )
                break;
            if len(agent.memory) > batch_size:
                agent.replay(batch_size)


# In[ ]:


main()

