#!/usr/bin/env bash

./codespell/codespell.sh ../config >> codespell_config.log
./codespell/codespell.sh ../common  >> codespell_common.log
./codespell/codespell.sh ../interfaces >> codespell_interfaces.log
./codespell/codespell.sh ../doc >> codespell_doc.log
