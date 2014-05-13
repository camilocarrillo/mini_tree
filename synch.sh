#!/bin/bash
rsync -av --progress --rsh='ssh' /home/miloc/yy/$1/ carrillo@lxplus5.cern.ch:www/higgs/yy/$1
