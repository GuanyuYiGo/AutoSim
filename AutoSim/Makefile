CXX = g++
CXXFLAGS = -fdiagnostics-color=always -Og -g -Wl,--stack=16777216 -I D:/Eigen3.4/eigen-3.4.0/eigen-3.4.0 -I D:/Users/25104/AppData/Local/Programs/Python/Python310/Lib/site-packages/pybind11/include -I D:/Users/25104/AppData/Local/Programs/Python/Python310/include -I D:/Users/25104/AppData/Local/Programs/Python/Python310/Lib/site-packages/numpy/core/include -I D:/OpenDrive/matplotlibcpp -I D:/OpenDrive
LDFLAGS = -L D:/Users/25104/AppData/Local/Programs/Python/Python310/libs -lpython310

SRC = planningPcoS.cpp \
      LaneMarkSensor/LaneMarkSensor.cpp \
      Visualize/visualize.cpp \
      Perception/perception.cpp \
      defineScence/defineMap.cpp \
      defineScence/defineVehicles.cpp \
      Simulation/simulation.cpp \
      Planning/planning.cpp \
      Control/control.cpp \
      Math/curve.cpp

OBJ = $(SRC:.cpp=.o)

all: planningPcoS.exe

planningPcoS.exe: $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) planningPcoS.exe