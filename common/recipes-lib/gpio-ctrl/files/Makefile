# Copyright 2019-present Facebook. All Rights Reserved.
#
# This program file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; version 2 of the License.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
# for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program in a file named COPYING; if not, write to the
# Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor,
# Boston, MA 02110-1301 USA

lib: libgpio-ctrl.so

C_SRCS := $(wildcard *.c)
C_OBJS := ${C_SRCS:.c=.o}
TEST_C_OBJS := ${C_SRCS:.c=.test.o}
TEST_CPP_SRCS := $(wildcard *.cpp)
TEST_CPP_OBJS := ${TEST_CPP_SRCS:.cpp=.o}

CFLAGS += -Wall -Werror -fPIC
CXXFLAGS += -Wall -Werror -std=c++17 -D__TEST__

libgpio-ctrl.so: $(C_OBJS)
	$(CC) -shared -o libgpio-ctrl.so $^ -lc $(LDFLAGS)

$(C_SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) $< >$@

$(TEST_C_OBJS):%.test.o:%.c
	$(CC) $(CFLAGS) -c -D__TEST__ $< -o $@

$(CPP_SRCS:.cpp=.d):%.d:%.cpp
	$(CXX) $(CXXFLAGS) $< >$@

test-libgpio-ctrl: $(TEST_C_OBJS) $(TEST_CPP_OBJS)
	$(CXX) -o -std=c++17 -o $@ $^ $(LDFLAGS) -lgtest -lgmock -lgtest_main

.PHONY: clean

clean:
	rm -rf *.o libgpio-ctrl.so libgpio-ctrl-test
