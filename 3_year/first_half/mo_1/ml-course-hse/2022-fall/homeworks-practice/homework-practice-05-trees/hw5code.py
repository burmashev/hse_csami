import numpy as np
from collections import Counter


def find_best_split(feature_vector, target_vector):
    """
    Под критерием Джини здесь подразумевается следующая функция:
    $$Q(R) = -\frac {|R_l|}{|R|}H(R_l) -\frac {|R_r|}{|R|}H(R_r)$$,
    $R$ — множество объектов, $R_l$ и $R_r$ — объекты, попавшие в левое и правое поддерево,
     $H(R) = 1-p_1^2-p_0^2$, $p_1$, $p_0$ — доля объектов класса 1 и 0 соответственно.

    Указания:
    * Пороги, приводящие к попаданию в одно из поддеревьев пустого множества объектов, не рассматриваются.
    * В качестве порогов, нужно брать среднее двух соседних (при сортировке) значений признака
    * Поведение функции в случае константного признака может быть любым.
    * При одинаковых приростах Джини нужно выбирать минимальный сплит.
    * За наличие в функции циклов балл будет снижен. Векторизуйте! :)

    :param feature_vector: вещественнозначный вектор значений признака
    :param target_vector: вектор классов объектов,  len(feature_vector) == len(target_vector)

    :return thresholds: отсортированный по возрастанию вектор со всеми возможными порогами, по которым объекты можно
     разделить на две различные подвыборки, или поддерева
    :return ginis: вектор со значениями критерия Джини для каждого из порогов в thresholds len(ginis) == len(thresholds)
    :return threshold_best: оптимальный порог (число)
    :return gini_best: оптимальное значение критерия Джини (число)
    """
    
    '''
    Преобразования над исходными данными и подсчет порогов 
    '''
    sorted_target = target_vector[np.argsort(feature_vector)]
    sorted_features = np.sort(feature_vector)
    unique_features = np.sort(np.unique(feature_vector))
    thresholds = (sorted_features[:-1] + sorted_features[1:]) / 2 
    unique_for_gini = (sorted_features[:-1] != sorted_features[1:])
    thresholds = thresholds[unique_for_gini]
    
    '''
    Считаю кол-во единичек/нулей для каждого разбиения
    С помощью кумулятивной суммы можно обойтись без циклов
    Чтобы посчитать кол-во нулей инвертирую биты и посчитать как кол-во единичек
    Чтобы посчитать правое разбиение можно развернуть массив, посчитать как для левого разбиения и потом снова развернуть
    (проще не придумал сорри)
    '''    
    left_1 = np.cumsum(sorted_target[:-1]) 
    left_0 = np.cumsum(1 - sorted_target[:-1])
    
    right_1 = np.cumsum(sorted_target[:0:-1])[::-1]
    right_0 = np.cumsum(1 - sorted_target[:0:-1])[::-1]
    
    '''
    Функция для подсчета H(R)
    '''
    def get_h(ones, zeroes):
        p1 = ones / (ones + zeroes)
        p0 = zeroes / (ones + zeroes)
        return 1 - np.square(p1) - np.square(p0)
    
    '''
    Вычисляю все нужные переменные для подсчета Джини
    ''' 
    H_l = get_h(left_1, left_0)
    H_r = get_h(right_1, right_0)
    R_size = feature_vector.shape[0]
    R1_size = np.arange(1, R_size)
    R2_size = R_size - R1_size
    
    '''
    Вычисляю критерий Джини
    '''
    ginis = -np.array((R1_size / R_size) * H_l) - np.array((R2_size / R_size) * H_r) 
    ginis = ginis[unique_for_gini]
    
    '''
    Выбираю лучший порог (ну и критерий Джини)
    '''
    best_idx = np.argmax(ginis)
    threshold_best = thresholds[best_idx]
    gini_best = ginis[best_idx]
    return (thresholds, ginis, threshold_best, gini_best)

    
class DecisionTree:
    def __init__(self, feature_types, max_depth=None, min_samples_split=None, min_samples_leaf=None):
        if np.any(list(map(lambda x: x != "real" and x != "categorical", feature_types))):
            raise ValueError("There is unknown feature type")

        self._tree = {}
        self._feature_types = feature_types
        self._max_depth = max_depth
        self._min_samples_split = min_samples_split
        self._min_samples_leaf = min_samples_leaf

    def _fit_node(self, sub_X, sub_y, node):
        if np.all(sub_y == sub_y[0]): # было sub_y != sub_y, но мы наоборот должны стопаться при эквивалентности чтобы стать листом
            node["type"] = "terminal"
            node["class"] = sub_y[0]
            return

        feature_best, threshold_best, gini_best, split = None, None, None, None
        for feature in range(0, sub_X.shape[1]): # был цикл с 1й feature, непонятно зачем пропускать 0й feature
            feature_type = self._feature_types[feature]
            categories_map = {}

            if feature_type == "real":
                feature_vector = sub_X[:, feature]
            elif feature_type == "categorical":
                counts = Counter(sub_X[:, feature])
                clicks = Counter(sub_X[sub_y == 1, feature])
                ratio = {}
                for key, current_count in counts.items():
                    if key in clicks:
                        current_click = clicks[key]
                    else:
                        current_click = 0
                    ratio[key] = current_click / current_count # было наоборот, поделим на 0 и будет больно, а так делим то где класс 1 на общее кол-во
                sorted_categories = list(map(lambda x: x[0], sorted(ratio.items(), key=lambda x: x[1]))) # было x[1], но это же категории, а не их рейтинги, так что надо смотреть на ключи (категории) в ratio
                categories_map = dict(zip(sorted_categories, list(range(len(sorted_categories)))))

                feature_vector = np.array(list(map(lambda x: categories_map[x], sub_X[:, feature]))) # было без list, уже как-то пытался напрямую array на map кинуть, не работает
            else:
                raise ValueError
       
            if np.all(feature_vector == feature_vector[0]): # если хотя бы 2 разных значения есть, то идем дальше
                continue
                
            _, _, threshold, gini = find_best_split(feature_vector, sub_y)
            if gini_best is None or gini > gini_best:
                feature_best = feature
                gini_best = gini
                split = feature_vector < threshold

                if feature_type == "real":
                    threshold_best = threshold
                elif feature_type == "categorical": # опечатка с капсом, но зачем такое добавлять, что за тест на внимательность :(
                    threshold_best = list(map(lambda x: x[0],
                                              filter(lambda x: x[1] < threshold, categories_map.items())))
                else:
                    raise ValueError

        if feature_best is None:
            node["type"] = "terminal"
            '''
            most_common возвращает n наиболее распространенных элементов в виде пар
            здесь n = 1, он вернет одну пару, нужно взять её из массива а затем взять pair.first
            '''
            node["class"] = Counter(sub_y).most_common(1)[0][0] # было без [0][0]
            return

        node["type"] = "nonterminal"

        node["feature_split"] = feature_best
        if self._feature_types[feature_best] == "real":
            node["threshold"] = threshold_best
        elif self._feature_types[feature_best] == "categorical":
            node["categories_split"] = threshold_best
        else:
            raise ValueError
        node["left_child"], node["right_child"] = {}, {}
        self._fit_node(sub_X[split], sub_y[split], node["left_child"])
        self._fit_node(sub_X[np.logical_not(split)], sub_y[np.logical_not(split)], node["right_child"]) # для sub_y нужно аналогичное sub_X

    def _predict_node(self, x, node):
        if node['type'] == 'terminal': # можем выходить и возвращать класс
            return node['class']
        if "threshold" in node: # численные
            if x[node['feature_split']] < node['threshold']:
                # идем налево
                return self._predict_node(x, node['left_child'])
            else:
                # идем направо
                return self._predict_node(x, node['right_child'])
        elif "categories_split" in node: # категориальные:
            if x[node['feature_split']] in node['categories_split']:
                # идем налево
                return self._predict_node(x, node['left_child'])
            else:
                # идем направо
                return self._predict_node(x, node['right_child'])

    def fit(self, X, y):
        self._fit_node(X, y, self._tree)

    def predict(self, X):
        predicted = []
        for x in X:
            predicted.append(self._predict_node(x, self._tree))
        return np.array(predicted)
    