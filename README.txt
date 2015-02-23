# See http://home.thep.lu.se/~torbjorn/pythiaaux/present.html

# First download the source
wget http://home.thep.lu.se/~torbjorn/pythia8/pythia8205.tgz

# Then unpack it
tar xvfz pythia8205.tgz

# Go into the main directory and configure and make pythia
cd pythia8205
./configure
make

# Now go into the examples directory and test build one of the example executables
cd examples
make main01

# If this worked, now add your own executables
cp ~aidan/public/ZPrimePythia/ZPrime.cc .

# The Makefile also needs to be changed
# Take a look inside to see how to add your own executables in the future
cp ~aidan/public/ZPrimePythia/Makefile .

# Make and execute the ZPrime binary
make ZPrime
./ZPrime > ZPrime.log

# Parse the output (units of mb)
grep Zprime0 ZPrime.log
