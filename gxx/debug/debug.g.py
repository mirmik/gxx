from licant import *

implementation("gxx.dprint", "stub", 
	sources = "dprint_func_stub.c dprint_stub.c dprintxx.cpp".split(" ")
)

implementation("gxx.dprint", "diag", 
	sources = "dprint_func_impl.c dprint_diag.c dprintxx.cpp".split(" "),
	cc_flags = "-Wno-pointer-to-int-cast",
	depends = "gxx.diag",
)

implementation("gxx.dprint", "manually", 
	sources = "dprint_func_impl.c dprint_manually.c dprintxx.cpp".split(" ")
)

implementation("gxx.dprint", "cout",
	sources = "dprint_func_impl.c dprint_stdout.c dprintxx.cpp".split(" ")
)

implementation("gxx.dprint", "stdout",
	sources = "dprint_func_impl.c dprint_stdout.c dprintxx.cpp".split(" ")
)

module_defimpl("gxx.dprint", "cout")