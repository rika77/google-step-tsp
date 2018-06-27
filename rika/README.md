# solver
## 全探索
`all_search.cpp`
## Nearest Neighbor Method
`nearest_negihbor.cpp`

sample/greedyと出力が同じだった。
## Nearest Insertion Method
`nearest_insertion.cpp`

最適解の2倍以内に収まることが保証されている解法。

あれーgreedyよりも値が大きくなってしまった。ふーん...

## 2-opt Method
`2-opt.cpp`

二本のEdgeを入れ替えることで短くなるなら、入れ替える

## 3-opt Method
`3-opt.cpp`

三本のEdgeを入れ替えることで短くなるなら、入れ替える
N=512で数秒、N=2048で結構まつ。

## 2-opt (?) by MST
`mst.cpp`

references

2-opt by MST <http://www.lab2.kuis.kyoto-u.ac.jp/~shuichi/algintro/alg-8s.pdf>
Kruskal <http://www.me.titech.ac.jp/~shioura/shioura/teaching/opt15/optim15-08.pdf>
Make MST by Kruskal <http://dai1741.github.io/maximum-algo-2012/docs/minimum-spanning-tree/>
