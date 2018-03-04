import numpy as np
class NearestNeighbor:
    def __init__(self):
        pass
    
    def train(self,X,y):
        self.Xtr=X
        self.ytr=y
    
    def predict(self,X):
        num_test=X.shape[0]