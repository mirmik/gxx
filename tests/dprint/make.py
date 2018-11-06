#!/usr/bin/env	python3
#coding: utf-8

from licant.modules import submodule
from licant.cxx_modules import application
import licant

from licant.scripter import scriptq
scriptq.execute("../../gxx.g.py")


bu = licant.cxx_make.binutils(
	cxx="g++",
	cc="gcc",
	ld="g++",
	ar="ar",
	objdump="objdump"
)

application("target++",
	sources = ["mainpp.cpp"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx", "posix"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.print", "cout"),
	],
	binutils = bu,
	cxxstd =  "gnu++14",
	ccstd =  "gnu11"
)

application("ctarget",
	sources = ["cmain.c"],
	include_paths = ["../.."],
	modules = [
		submodule("gxx", "posix"),
		submodule("gxx.dprint", "cout"),
		submodule("gxx.print", "cout"),
	],
	binutils = bu,
	cxxstd =  "gnu++14",
	ccstd =  "gnu11"
)

licant.fileset("all", ["ctarget", "target++"])

licant.ex("all")