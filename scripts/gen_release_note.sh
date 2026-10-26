#!/bin/bash

pandoc -s -r markdown -t html5 -c "_htmresc/mini-st_2020.css" Release_Notes.md > Release_Notes.html