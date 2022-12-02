#!/bin/sh

# Copyright (c) 2022 - CCOS ICMC-USP
# SPDX-License-Identifier: GPL-3.0-only

PROGRAM="./snaskii.bin"

cd $(dirname $0)


if [ -f "$PROGRAM" ]; then
    if [ -z "$1" ] ; then
	./$PROGRAM -d../scenes
    else
	./$PROGRAM "$1"
    fi
else
    echo "Program not found."
    exit 1
fi

