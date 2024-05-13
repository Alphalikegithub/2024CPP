from sklearn.ensemble import RandomForestRegressor
import numpy as np

# 假设你已经有了训练样本数据
# 根据你提供的表格，我简化了样本数据的表示
X = np.array([
    [0.87, 70, 0.096, 1.56, 120, 2.76, 165, 3.40, 2.8, 4.8, 4.3, 4.4],
    [0.91, 75, 0.590, 2.06, 210, 1.50, 155, 4.50, 4.4, 4.2, 4.6, 4.7],
    [1.10, 67, 0.750, 2.70, 312, 1.61, 178, 6.40, 3.2, 5.0, 4.0, 4.2],
    [0.53, 79, 0.530, 3.10, 237, 1.59, 172, 5.10, 4.5, 6.6, 3.9, 4.5],
    [0.48, 65, 0.720, 1.60, 150, 0.96, 163, 3.50, 5.4, 4.6, 4.2, 3.5],
    [0.62, 35, 0.220, 2.61, 175, 2.89, 150, 3.32, 4.0, 5.8, 3.7, 6.2]
])

# 目标值
y = np.array([4.8, 4.3, 5.0, 6.6, 4.6, 5.8])

# 构建随机森林模型
forest = RandomForestRegressor(n_estimators=50, random_state=42)

# 训练模型
forest.fit(X, y)

# 一、得到基于指标贡献度的权重α
alpha_weights = []
for tree in forest.estimators_:
    # 计算每一指标的累计贡献度
    feature_contributions = np.array([tree.tree_.compute_feature_importances(normalize=False)[i] for i in range(X.shape[1])])
    alpha_weights.append(feature_contributions)

# 打印α
print("基于指标贡献度的权重α:")
for i, alpha_weight in enumerate(np.mean(alpha_weights, axis=0)):
    print(f"Feature X{i+1}: {alpha_weight}")

# 二、遍历所有指标，对每个指标值进行随机重置，得到每次重置后指标重要性得分
beta_weights = []
for j in range(X.shape[1]):
    # 复制原始数据
    X_reset = X.copy()
    # 随机重置第j个指标
    X_reset[:, j] = np.random.permutation(X_reset[:, j])
    # 得到重置后的R2
    r_squared_reset = forest.score(X_reset, y)
    # 计算指标重要性得分
    beta_weights.append(r_squared_reset)

# 打印β
print("\n基于指标重置的权重β:")
for i, beta_weight in enumerate(beta_weights):
    print(f"Feature X{i+1}: {beta_weight}")

# 三、计算得到基于指标重置的权重β
beta_weights /= np.sum(beta_weights)

# 打印调整系数ω为0.5的客观指标权重
omega = 0.5
final_weights = omega * np.mean(alpha_weights, axis=0) + (1 - omega) * beta_weights
print("\n客观指标权重:")
for i, final_weight in enumerate(final_weights):
    print(f"Feature X{i+1}: {final_weight}")