# Main Ideas about Machine Learning that I learned through doing these Tutorials

## Frameworks
- Tensorflow is impossible to use, use Keras which has best of both worlds in Functional, Models (PyTorch), and Sequential layers
- PyTorch is really easy to use and is very similar to MxNet!
- Need to get a GPU for PyTorch

## Hyperparameters
- lr = self.learning_rate = 0.001 is a good baseline to start, the larger the learning rate the less likely it is to diverge 
- self.gamma in reinforcement learning is 0.95 but should be decreased from 1 -> 0
- self.epsilon for exploration vs explotation in reinforcement learning should be 


## Loss Functions
- Softmax outputs proabibilities and goes with cross entropy or log loss

## Image Processing


## Text

## Deep Reinforcement Learning 
- CNN Take pictures as state -> get Q(s, a) as output
- state = next_state to update from state to state
- Sample batches from memory and replay to train, remember to build memory, key idea
- Very powerful ideas in that it does not need any training data, everything is found through exploration (unsupervised with long-time rewards)
- 2 problems in Reinforcement Learning - delayed reward gratification and exploration vs exploitation
- Really nice idea of joining two algorithms together, Q state updates (which has complexity issues), and CNN
- Do more open AI problems in different ways

# Resources used to Implement these models
- https://github.com/adventuresinML 
- https://github.com/keon/deep-q-learning/
-

# Software Principles
- Simplicity -- Maximize work not done
- Learning usually involves copying others solutions and gradually adjusting learning rate to trust your own idea more and more until you become the programmer you want to be
- Just like RL you need to replay and remember past expierences of success
