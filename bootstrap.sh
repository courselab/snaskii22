#!/bin/sh

# Copyright (c) 2022 - CCOS ICMC-USP
# SPDX-License-Identifier: GPL-3.0-only

RECOMMENDED_FILES="NEWS README AUTHORS ChangeLog"

AUTORECONF=$(which autoreconf)
if test -z "$AUTORECONF"; then
  echo "Program autoreconf not found"
  exit 1
fi

echo -n "Bootstrapping project..."

for i in $RECOMMENDED_FILES; do
    if test ! -f "$i" ; then 
	touch "$i"
    fi
done

$AUTORECONF --install

echo "Done"
