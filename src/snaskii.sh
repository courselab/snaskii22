#!/bin/sh

# Copyright (c) 2022 - CCOS ICMC-USP

# This file is part of Snaskii22.
# Snaskii22 is based on Snaskii, available at
# https://github.com/courselab/snaskii.

# Snaskii22 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

