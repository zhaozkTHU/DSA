| 单位(s)  (插入次数，查询次数) | 规模较大、插入查询相当、均匀分布(100000,100000) | 规模较小、插入多于查询，集中分布(10000,5000) | 规模较大，查询多于插入，均匀分布(100000,200000) |
| ----------------------------- | ----------------------------------------------- | -------------------------------------------- | ----------------------------------------------- |
| 坏哈希函数+线性策略           | 43.854227                                       | 0.275608                                     | 71.901624                                       |
| 坏哈希函数+双向平方策略       | 2.051782                                        | 0.024504                                     | 4.366719                                        |
| 坏哈希函数+溢出区策略         | 40.589291                                       | 0.223230                                     | 62.628860                                       |
| hashcode+线性策略             | 0.310592                                        | 0.013834                                     | 0.580501                                        |
| hashcode+双向平方策略         | 0.367363                                        | 0.012102                                     | 0.557211                                        |
| hashcode+溢出区策略           | 2.698526                                        | 0.010036                                     | 4.714887                                        |