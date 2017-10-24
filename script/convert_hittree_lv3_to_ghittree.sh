#!/bin/sh

locallv3="$1"
echo "./app_hittree_local_to_global $locallv3"
./app_hittree_local_to_global $locallv3

globallv3="${locallv3/_hittree_lv3.root/_globalhittree_lv3.root}"
echo "./app_make_ghittree_from_lv3 $globallv3"
./app_make_ghittree_from_lv3 $globallv3

ghitname="${globallv3/_globalhittree_lv3.root/_ghittree.root}"
echo "mv $globallv3 ../ghittree"
mv $globallv3 ../ghittree
echo "mv $ghitname ../ghittree"
mv $ghitname ../ghittree
