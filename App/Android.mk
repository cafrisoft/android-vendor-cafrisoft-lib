common_dirs := Server Client Control
               
include $(call all-named-subdir-makefiles,$(common_dirs))