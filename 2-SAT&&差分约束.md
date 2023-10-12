## 2-SAT

判断是否存在满足布尔方程 $(a\vee b)\wedge (c\vee d)...$ 的一组可行解。

通过将上述布尔方程进行转化（蕴含），$a\vee b=\neg a \rightarrow b \wedge \neg b \rightarrow a$ ，继而将其转化为一个图上问题，通过判断 $a$ 和 $\neg a$ 是否在同一个强连通分量判断。特殊的 $a = \neg a \rightarrow a$，这在构造可行解是必须的。

2-SAT 的构造是对于每个变量取拓扑序大的那个（用 tarjan 处理后的拓扑序为倒序）。

## 差分约束

差分约束系统是 $n$ 元一次不等式组。建立一个超级源点，该点向其余点连一条边，用来设置初值以及保证求出的解具有一定的性质。

对于一个不等式 $x_u \leq x_v + w$，可以建一条 $e(v \rightarrow u, w)$ 的边，以小于等于号建出的图可以求$x_i \leq x_{s_0}$ 的最大解；同理，将上述不等式转化后 $x_u \geq x_v + w$ ，可以建一条 $e(v \rightarrow u, w)$ 的边，求$x_i \geq x_{s_0}$ 的最小解。