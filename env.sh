#!/bin/bash

export PATH="$PATH:$(pwd)/script"
export PATH="usr/local/share/npm/bin:$PATH"
export TASK1_PROJ_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
export TASK1_SCRIPT=$TASK1_PROJ_DIR/script
export GTK_PATH=""