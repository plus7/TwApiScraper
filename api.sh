#!/bin/sh
i=0
cat $1 | while read s; do ### 各行をsに代入。行ごとに以下を実行
  ./makestub.sh $s
done
