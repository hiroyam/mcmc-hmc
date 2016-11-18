# hmc

Hamiltonian Monte Carlo method

[![Build Status](https://travis-ci.org/hiroyam/hmc.svg?branch=master)](https://travis-ci.org/hiroyam/hmc)

---

#### これは何？

MCMCのハミルトニアンモンテカルロ法のC++によるフルスクラッチです。

##### 概要

ランダムウォーク系のMCMCとしてはメトロポリス・ヘイスティングス法などがありますが、高次元空間では次元の呪いの影響で受容率が低くなるため、なかなか収束しません。ハミルトニアンモンテカルロはランダムウォーク系のMCMCと違い、高次元空間での積分でも受容率が高くなるため、現実的な時間内に収束するのが特徴です。

メトロポリスヘイスティングス法に関してはこちら。
https://github.com/hiroyam/metropolis-hastings

##### 動作サンプル

リープフロッグで遷移している様子をプロットしました。

![](images/plot1.png)

ハミルトニアンを保存しながら遷移しているのが分かります。

![](images/plot2.png)

d=1の場合のHMCとしてガンマ分布に従う乱数を発生させた例です。受容率は99%でした。

![](images/plot3.png)

d=2の場合のHMCとしてN(170,49)のガウス分布から作成した標本からガウス分布のパラメタを推定してみた例です。受容率は99%でした。

![](images/plot4.png)
