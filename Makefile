# 变量定义
INCLUDEDIR = ./include
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

CXX = clang++
CXXFLAGS += -std=c++11 -Wall -I./include

# Rules
$(BINDIR)/main : $(addprefix $(OBJDIR)/,main.o compute_biological_info.o) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $(addprefix $(OBJDIR)/,main.o compute_biological_info.o) -o $(BINDIR)/main

$(OBJDIR)/%.o : $(SRCDIR)/%.cc | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BINDIR):
	mkdir $(BINDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean  : 
	rm $(BINDIR)/* $(OBJDIR)/* .depend

run : $(BINDIR)/main 
	$(BINDIR)/main

# 头文件依赖相关
depend: .depend

.depend: $(SRCDIR)/*.cc
	rm -f "$@"
	$(CXX) $(CXXFLAGS) -MM $^ -MF "$@"

include .depend
