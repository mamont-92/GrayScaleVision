msvc {
  QMAKE_CXXFLAGS += -openmp -arch:AVX -D "_CRT_SECURE_NO_WARNINGS"
  QMAKE_CXXFLAGS_RELEASE *= -O2
}

gcc {
  QMAKE_CXXFLAGS += -fopenmp -mavx -fabi-version=0 -ffast-math
  QMAKE_LFLAGS += -fopenmp
  QMAKE_CXXFLAGS_RELEASE *= -O3
}
