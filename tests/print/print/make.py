#!/usr/bin/env	python3
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
from licant.scripter import scriptq
import licant

scriptq.execute("../../../gxx.g.py")

application("target",
	sources = ["main.cpp"],
	mdepends = ["gxx"]
)

licant.ex(default = "target")