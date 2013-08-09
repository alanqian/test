#!/bin/bash

# hosts pretending to be a Pythonic dictionary
hosts=( "lion:lion.mei.fm"
        "puma:puma.mei.fm"
        "tiger:tiger.mei.fm"
        "leopard:leopard.mei.fm"
        "fetcher1:fetcher1.meiwei.fm"
        "fetcher2:fetcher2.meiwei.fm"
      )

for animal in "${hosts[@]}" ; do
    KEY="${animal%%:*}"
    VALUE="${animal##*:}"
    alias "$KEY"="ssh deploy\@${VALUE}"
    printf "%s: %s\n" "$KEY" "$VALUE"
done

exit 0

hosts=(["lion"]="lion.mei.fm",["leopard"]="leopard.mei.fm")
echo ${hosts["lion"]}
echo ${hosts["leopard"]}

