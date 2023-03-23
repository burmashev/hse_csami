from __future__ import annotations

from collections import defaultdict

import numpy as np
from sklearn.metrics import roc_auc_score
from sklearn.tree import DecisionTreeRegressor


def score(clf, x, y):
    return roc_auc_score(y == 1, clf.predict_proba(x)[:, 1])


class Boosting:

    def __init__(
            self,
            base_model_params: dict = None,
            n_estimators: int = 10,
            learning_rate: float = 0.1,
            subsample: float = 0.3,
            early_stopping_rounds: int = None,
            plot: bool = False,
    ):
        self.base_model_class = DecisionTreeRegressor
        self.base_model_params: dict = {} if base_model_params is None else base_model_params

        self.n_estimators: int = n_estimators

        self.models: list = []
        self.gammas: list = []

        self.learning_rate: float = learning_rate
        self.subsample: float = subsample

        self.early_stopping_rounds: int = early_stopping_rounds
        if early_stopping_rounds is not None:
            # self.validation_loss = np.full(self.early_stopping_rounds, np.inf)
            self.bad_loss_counter = 0

        self.plot: bool = plot

        self.history = defaultdict(list)

        self.sigmoid = lambda x: 1 / (1 + np.exp(-x))
        self.loss_fn = lambda y, z: -np.log(self.sigmoid(y * z)).mean()
        self.loss_derivative = lambda y, z: -y * self.sigmoid(-y * z)

    def fit_new_base_model(self, x, y, predictions):
        # модель
        model = self.base_model_class(**self.base_model_params)
        
        # маска бутстрепа
        bootstrap_size = self.subsample * x.shape[0]
        bootstrap_mask = np.random.randint(x.shape[0], size=int(bootstrap_size))
        
        # фит предикт
        new_y = -self.loss_derivative(y[bootstrap_mask], predictions[bootstrap_mask])
        model.fit(x[bootstrap_mask], new_y)
        new_predictions = model.predict(x)
        
        # ищем гамму
        gamma = self.find_optimal_gamma(y, predictions, new_predictions)
        
        self.gammas.append(gamma)
        self.models.append(model)

    def fit(self, x_train, y_train, x_valid, y_valid):
        """
        :param x_train: features array (train set)
        :param y_train: targets array (train set)
        :param x_valid: features array (validation set)
        :param y_valid: targets array (validation set)
        """
        train_predictions = np.zeros(y_train.shape[0])
        valid_predictions = np.zeros(y_valid.shape[0])

        for i in range(self.n_estimators):
            self.fit_new_base_model(x_train, y_train, train_predictions)
            
            train_pred = self.gammas[-1] * self.learning_rate * self.models[-1].predict(x_train)
            valid_pred = self.gammas[-1] * self.learning_rate * self.models[-1].predict(x_valid)
            train_predictions += train_pred
            valid_predictions += valid_pred
            
            train_loss = self.loss_fn(y_train, train_predictions)
            valid_loss = self.loss_fn(y_valid, valid_predictions)
            
            self.history['train_loss'].append(train_loss)
            self.history['valid_loss'].append(valid_loss)
            # self.history['valid_score'].append(self.score(x_valid, y_valid))
            
            '''
            Решил сделать как написал Makes Kiselev в флудилке пми (через счетчики),
            поскольку понял этот фрагмент именно так, как в решении через счетчики.
            Если кол-во подряд неулучшающихся итераций превысит early_stopping_rounds, я брейкаюсь,
            при хорошей итерации я счетчик зануляю
            '''
            if i != 0 and self.early_stopping_rounds is not None: 
                if self.history['valid_loss'][-1] >= self.history['valid_loss'][-2]:
                    self.bad_loss_counter += 1
                else:
                    self.bad_loss_counter = 0
                if self.bad_loss_counter == self.early_stopping_rounds:
                    break
                
        if self.plot:
            plt.figure(figsize=(10, 5))
            plt.plot(self.history['train_loss'], label='train loss')
            plt.plot(self.history['valid_loss'], label='valid loss')
            plt.xlabel('n_estimators')
            plt.ylabel('loss')
            plt.legend()
            plt.show()


    def predict_proba(self, x):
        probabilities = np.zeros(x.shape[0])
        for gamma, model in zip(self.gammas, self.models):
            probabilities += gamma * self.learning_rate * model.predict(x)
        probabilities = self.sigmoid(probabilities)
        return np.array([1 - probabilities, probabilities]).T
            

    def find_optimal_gamma(self, y, old_predictions, new_predictions) -> float:
        gammas = np.linspace(start=0, stop=1, num=100)
        losses = [self.loss_fn(y, old_predictions + gamma * new_predictions) for gamma in gammas]

        return gammas[np.argmin(losses)]

    def score(self, x, y):
        return score(self, x, y)

    @property
    def feature_importances_(self):
        pass
